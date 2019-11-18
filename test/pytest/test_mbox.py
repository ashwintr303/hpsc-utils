import subprocess
import pytest

testers = ["mboxtester", "mbox-multiple-core-tester"]

def run_tester_on_host(hostname, tester_num, tester_pre_args, tester_post_args):
    tester_remote_path = "/opt/hpsc-utils/" + testers[tester_num]
    out = subprocess.run(['ssh', hostname] + tester_pre_args + [tester_remote_path] + tester_post_args, universal_newlines=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return out
    
# Verify that mboxtester works with the process pinned separately to each HPPS core.
# Since this first test will boot QEMU, it is given more time.
@pytest.mark.timeout(200)
@pytest.mark.parametrize('core_num', range(8))
def test_hpps_to_trch_with_no_notification_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-n', 'none', '-c', str(core_num)])
    assert out.returncode == 0

@pytest.mark.timeout(60)
@pytest.mark.parametrize('core_num', range(8))
def test_hpps_to_trch_with_select_notification_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-n', 'select', '-c', str(core_num)])
    assert out.returncode == 0

@pytest.mark.timeout(60)
@pytest.mark.parametrize('core_num', range(8))
def test_hpps_to_trch_with_poll_notification_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-n', 'poll', '-c', str(core_num)])
    assert out.returncode == 0

@pytest.mark.timeout(60)
@pytest.mark.parametrize('core_num', range(8))
def test_hpps_to_trch_with_epoll_notification_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-n', 'epoll', '-c', str(core_num)])
    assert out.returncode == 0

@pytest.mark.timeout(60)
@pytest.mark.parametrize('core_num', range(8))
def test_hpps_to_rtps_with_no_notification_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-n', 'none', '-o', '/dev/mbox/1/mbox0', '-i', '/dev/mbox/1/mbox1', '-c', str(core_num)])
    assert out.returncode == 0

@pytest.mark.timeout(60)
@pytest.mark.parametrize('core_num', range(8))
def test_hpps_to_rtps_with_select_notification_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-n', 'select', '-o', '/dev/mbox/1/mbox0', '-i', '/dev/mbox/1/mbox1', '-c', str(core_num)])
    assert out.returncode == 0

@pytest.mark.timeout(60)
@pytest.mark.parametrize('core_num', range(8))
def test_hpps_to_rtps_with_poll_notification_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-n', 'poll', '-o', '/dev/mbox/1/mbox0', '-i', '/dev/mbox/1/mbox1', '-c', str(core_num)])
    assert out.returncode == 0

@pytest.mark.timeout(60)
@pytest.mark.parametrize('core_num', range(8))
def test_hpps_to_rtps_with_epoll_notification_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-n', 'epoll', '-o', '/dev/mbox/1/mbox0', '-i', '/dev/mbox/1/mbox1', '-c', str(core_num)])
    assert out.returncode == 0

@pytest.mark.timeout(60)
@pytest.mark.parametrize('core_num', range(8))
def test_invalid_outbound_mailbox_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-c', str(core_num), '-o', '32'])
    assert out.returncode == 1

@pytest.mark.timeout(60)
@pytest.mark.parametrize('core_num', range(8))
def test_invalid_inbound_mailbox_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-c', str(core_num), '-i', '32'])
    assert out.returncode == 1

# Verify that mboxtester fails with the correct exit code when a timeout
# occurs with the process pinned separately to each HPPS core
@pytest.mark.timeout(60)
@pytest.mark.parametrize('core_num', range(8))
def test_early_timeout_on_each_core(boot_qemu_per_module, host, core_num):
    out = run_tester_on_host(host, 0, [], ['-c', str(core_num), '-t', '0'])
    assert out.returncode == 22

# verify that mbox-multiple-core-tester works with core 0 performing a
# write-read followed by core 1 doing another write-read using the same mailbox
@pytest.mark.timeout(60)
def test_multiple_cores_same_mbox(boot_qemu_per_module, host):
    out = run_tester_on_host(host, 1, [], ['-C', '0', '-c', '1'])
    assert out.returncode == 0

@pytest.mark.timeout(60)
def test_multiple_cores_same_mbox_invalid_CPU1(boot_qemu_per_module, host):
    out = run_tester_on_host(host, 1, [], ['-C', '-1', '-c', '1'])
    assert out.returncode == 1

@pytest.mark.timeout(60)
def test_multiple_cores_same_mbox_invalid_CPU2(boot_qemu_per_module, host):
    out = run_tester_on_host(host, 1, [], ['-C', '0', '-c', '9'])
    assert out.returncode == 2
