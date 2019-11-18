import subprocess
import pytest

testers = ["rtit-tester"]
masks = ["0x1", "0x2", "0x4", "0x8", "0x10", "0x20", "0x40", "0x80"]

def run_tester_on_host(hostname, tester_num, tester_pre_args, tester_post_args):
    tester_remote_path = "/opt/hpsc-utils/" + testers[tester_num]
    out = subprocess.run(['ssh', hostname] + tester_pre_args + [tester_remote_path] + tester_post_args, universal_newlines=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return out
    
# Since this first test will boot QEMU, it is given more than the default time
@pytest.mark.timeout(200)
def test_rti_timer_on_each_core(boot_qemu_per_module, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['taskset', masks[i]], ["/dev/rti_timer" + str(i), str(2000)])
        assert out.returncode == 0
