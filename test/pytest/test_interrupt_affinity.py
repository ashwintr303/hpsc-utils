import subprocess
import pytest

testers = ["interrupt-affinity-tester.sh"]

def run_tester_on_host(hostname, tester_num, tester_pre_args, tester_post_args):
    tester_remote_path = "/opt/hpsc-utils/" + testers[tester_num]
    out = subprocess.run(['ssh', hostname] + tester_pre_args + [tester_remote_path] + tester_post_args, universal_newlines=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return out

# Since this first test will boot QEMU, it is given more time.
@pytest.mark.timeout(200)
def test_all_dma_channels_interrupt_affinity(boot_qemu_per_module, host):
    out = run_tester_on_host(host, 0, [], [])
    assert out.returncode == 0
