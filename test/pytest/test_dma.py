import subprocess
import pytest

testers = ["dma-tester.sh"]

# Since this first test may need to boot QEMU, it is given more time.
@pytest.mark.timeout(200)
def run_tester_on_host(hostname, tester_num, tester_pre_args, tester_post_args):
    tester_remote_path = "/opt/hpsc-utils/" + testers[tester_num]
    out = subprocess.run(['ssh', hostname] + tester_pre_args + [tester_remote_path] + tester_post_args, universal_newlines=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return out

@pytest.mark.timeout(60)
def test_all_dma_channels(boot_qemu, host):
    out = run_tester_on_host(host, 0, [], [])
    assert out.returncode == 0

@pytest.mark.timeout(60)
def test_invalid_test_buffer_size(boot_qemu, host):
    out = run_tester_on_host(host, 0, [], ['-b', '-1'])
    assert out.returncode == 1

@pytest.mark.timeout(60)
def test_invalid_threads_per_channel(boot_qemu, host):
    out = run_tester_on_host(host, 0, [], ['-h', '-1'])
    assert out.returncode == 2

@pytest.mark.timeout(60)
def test_invalid_iterations(boot_qemu, host):
    out = run_tester_on_host(host, 0, [], ['-i', '-1'])
    assert out.returncode == 3

@pytest.mark.timeout(60)
def test_invalid_timeout(boot_qemu, host):
    out = run_tester_on_host(host, 0, [], ['-t', '-1'])
    assert out.returncode == 4

@pytest.mark.timeout(60)
def test_invalid_channel(boot_qemu, host):
    out = run_tester_on_host(host, 0, [], ['-c', 'nochan'])
    assert out.returncode == 5
