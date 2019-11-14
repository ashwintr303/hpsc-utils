import subprocess
import pytest
import re

testers = ["ep.S.x"]

def run_tester_on_host(hostname, tester_num, num_threads):
    tester_remote_path = "/opt/nas-parallel-benchmarks/NPB3.3.1-OMP/bin/" + testers[tester_num]
    # first set OMP_NUM_THREADS and OMP_PROC_BIND, then run the tester
    out = subprocess.run("ssh " + hostname + " \"export OMP_NUM_THREADS=" + str(num_threads) +"; export OMP_PROC_BIND=TRUE; " + tester_remote_path + "\"", stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
    return out

# verify that the scaling the NAS EP benchmark on the HPPS cores leads to speedup
@pytest.mark.timeout(100)
def test_parallel_app_scaling(boot_qemu, host):
    for thr in [1,2,4,8]:
        out = run_tester_on_host("hpscqemu", 0, thr)
        cpu_time = float(re.search(r"(\S+)$", re.search(r"CPU Time =(\s+)(\S+)", out.stdout).group(0)).group(0))
        returncode = 0
        if (thr > 1):
            if (cpu_time >= prior_cpu_time):
                if (thr == 2):
                    returncode = 1
                elif (thr == 4):
                    returncode = 2
                elif (thr == 8):
                    returncode = 3
        assert returncode == 0
        prior_cpu_time = cpu_time
