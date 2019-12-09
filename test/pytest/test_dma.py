import subprocess
import pytest

testers = ["dma-tester.sh"]

def run_tester_on_host(hostname, tester_num, tester_pre_args, tester_post_args):
    tester_remote_path = "/opt/hpsc-utils/" + testers[tester_num]
    out = subprocess.run(['ssh', hostname] + tester_pre_args + [tester_remote_path] + tester_post_args, universal_newlines=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return out

# Since this first test will boot QEMU, it is given more than the default time
@pytest.mark.timeout(200)
def test_all_dma_channels(qemu_instance_per_mdl, host):
    out = run_tester_on_host(host, 0, [], [])
    assert out.returncode == 0

def test_invalid_test_buffer_size(qemu_instance_per_mdl, host):
    out = run_tester_on_host(host, 0, [], ['-b', '-1'])
    assert out.returncode == 1

def test_invalid_threads_per_channel(qemu_instance_per_mdl, host):
    out = run_tester_on_host(host, 0, [], ['-h', '-1'])
    assert out.returncode == 2

def test_invalid_iterations(qemu_instance_per_mdl, host):
    out = run_tester_on_host(host, 0, [], ['-i', '-1'])
    assert out.returncode == 3

def test_invalid_timeout(qemu_instance_per_mdl, host):
    out = run_tester_on_host(host, 0, [], ['-t', '-1'])
    assert out.returncode == 4

def test_invalid_channel(qemu_instance_per_mdl, host):
    out = run_tester_on_host(host, 0, [], ['-c', 'nochan'])
    assert out.returncode == 5
