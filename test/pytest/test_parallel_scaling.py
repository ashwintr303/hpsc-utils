import subprocess
import pytest
import re
import time

nas_ep_class = "A"
tester_remote_path = "/opt/nas-parallel-benchmarks/NPB3.3.1-OMP/bin/ep." + nas_ep_class + ".x"

# Check the entries in /proc/cpuinfo to confirm that the HPPS has 8 cores
# Since this first test will boot QEMU, it is given more than the default time
@pytest.mark.timeout(200)
def test_verify_HPPS_core_count(qemu_instance_per_mdl, host):
    hpps_core_count = 8
    out = subprocess.run("ssh " + host + " cat /proc/cpuinfo", stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
    proc_nums = re.findall(r"processor\s+\S+\s+(\S+)", out.stdout)
    assert(len(proc_nums) == hpps_core_count), "The list of processor numbers in /proc/cpuinfo is " + proc_nums
    for i in range(hpps_core_count):
        assert(str(i) in proc_nums), "Processor " + str(i) + " is missing from the processor list: " + proc_nums + " from /proc/cpuinfo"

# Verify that when scaling the NAS EP benchmark on the HPPS cores, the correct number
# of threads is launched and that each thread is running on the expected core
@pytest.mark.parametrize('num_threads', list(range(1, 9)))
def test_parallel_scaling_with_varying_thread_counts(qemu_instance_per_mdl, host, num_threads):
    # first set OMP_NUM_THREADS and OMP_PROC_BIND, then run the tester asynchronously
    p = subprocess.Popen("ssh " + host + " \"export OMP_NUM_THREADS=" + str(num_threads) +"; export OMP_PROC_BIND=TRUE; " + tester_remote_path + "\"", stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
    time.sleep(1)
    # identify the process ID of the NAS benchmark
    out = subprocess.run("ssh " + host + " ps ", stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
    pid = re.search(r"\s+(\S+)\s+\S+\s+\S+\s+\S+\s+" + tester_remote_path, out.stdout).group(1)
    # list all of the thread IDs for this process ID
    # see https://stackoverflow.com/questions/8032372/how-can-i-see-which-cpu-core-a-thread-is-running-in for more info
    out = subprocess.run("ssh " + host + " ls /proc/" + pid + "/task", stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
    tid_list = out.stdout.split()
    # confirm that the number of threads is what we expect
    assert(len(tid_list) == num_threads)
    thread_num = 0
    for tid in tid_list:
        out = subprocess.run("ssh " + host + " cat /proc/" + pid + "/task/" + tid + "/stat", stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
        thread_stats = out.stdout.split()
        # confirm that this thread is currently running
        assert(thread_stats[2] == 'R')
        # confirm that this thread is running on the expected core
        assert(thread_stats[38] == str(thread_num))
        thread_num += 1
    # kill the current process before increasing the OMP thread count
    out = subprocess.run("ssh " + host + " kill -9 " + pid, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
    p.terminate()

# Verify that the scaling the NAS EP benchmark on the HPPS cores leads to speedup.
# The NAS EP benchmark is run multiple times, so this test is given more time.
@pytest.mark.timeout(1000)
def test_parallel_speedup(qemu_instance_per_mdl, host):
    executed_thread_counts = []
    executed_cpu_times = []
    for num_threads in [1,2,4,8]:
        # first set OMP_NUM_THREADS and OMP_PROC_BIND, then run the tester
        out = subprocess.run("ssh " + host + " \"export OMP_NUM_THREADS=" + str(num_threads) +"; export OMP_PROC_BIND=TRUE; " + tester_remote_path + "\"", stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
        cpu_time = float(re.search(r"(\S+)$", re.search(r"CPU Time =(\s+)(\S+)", out.stdout).group(0)).group(0))
        executed_thread_counts.append(num_threads)
        executed_cpu_times.append(cpu_time)

        returncode = 0
        if (num_threads > 1):
            if (cpu_time >= prior_cpu_time):
                if (num_threads == 2):
                    returncode = 1
                elif (num_threads == 4):
                    returncode = 2
                elif (num_threads == 8):
                    returncode = 3
        assert returncode == 0, "NAS EP class " + nas_ep_class + " run times for " + str(executed_thread_counts) + " OMP threads are " + str(executed_cpu_times) + " seconds respectively."
        prior_cpu_time = cpu_time
    # This print statement will only display if pytest is passed the "-s" flag
    print("\nNAS EP class " + nas_ep_class + " run times for " + str(executed_thread_counts) + " OMP threads are " + str(executed_cpu_times) + " seconds respectively.")
