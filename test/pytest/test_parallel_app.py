import subprocess
import pytest
import re

testers = ["ep.A.x"]

def run_tester_on_host(hostname, tester_num, num_threads):
    tester_remote_path = "/opt/nas-parallel-benchmarks/NPB3.3.1-OMP/bin/" + testers[tester_num]
    # first set OMP_NUM_THREADS and OMP_PROC_BIND, then run the tester
    out = subprocess.run("ssh " + hostname + " \"export OMP_NUM_THREADS=" + str(num_threads) +"; export OMP_PROC_BIND=TRUE; " + tester_remote_path + "\"", stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
    return out

# verify that the scaling the NAS EP benchmark on the HPPS cores leads to speedup
@pytest.mark.timeout(800)
def test_parallel_app_scaling(boot_qemu, host):
    executed_thread_counts = []
    executed_cpu_times = []
    for thr in [1,2,4,8]:
        out = run_tester_on_host("hpscqemu", 0, thr)
        cpu_time = float(re.search(r"(\S+)$", re.search(r"CPU Time =(\s+)(\S+)", out.stdout).group(0)).group(0))
        executed_thread_counts.append(thr)
        executed_cpu_times.append(cpu_time)

        returncode = 0
        if (thr > 1):
            if (cpu_time >= prior_cpu_time):
                if (thr == 2):
                    returncode = 1
                elif (thr == 4):
                    returncode = 2
                elif (thr == 8):
                    returncode = 3
        assert returncode == 0, "NAS EP class A run times for " + str(executed_thread_counts) + " OMP threads are " + str(executed_cpu_times) + " seconds respectively."
        prior_cpu_time = cpu_time
