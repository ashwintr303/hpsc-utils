from subprocess import run
import pytest

#host = 'hpscqemu'
local_dir = '../linux/'
testers = ["mboxtester", "mbox-multiple-core-tester"]

@pytest.fixture(scope="function")  # scope could be "function", "class", "module", "package", or "session"
def fixture(host):
    local_tester_paths = [local_dir + t for t in testers]
    run(['scp'] + local_tester_paths + [host + ':~'])
    yield fixture # provide the fixture value, then start teardown code
    remote_tester_paths = ["~/" + t for t in testers]
    run(['ssh', host, 'rm'] + remote_tester_paths)

def run_tester_on_host(hostname, tester_num, tester_args):
    tester_remote_path = "~/" + testers[tester_num]
    out = run(['ssh', hostname, tester_remote_path] + tester_args, capture_output=True)
    return out

# verify that mboxtester works with the process pinned separately to each
# HPPS core
@pytest.mark.timeout(30)
def test_hpps_to_trch_with_no_notification_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-n', 'none', '-c', str(i)])
        assert out.returncode == 0

@pytest.mark.timeout(30)
def test_hpps_to_trch_with_select_notification_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-n', 'select', '-c', str(i)])
        assert out.returncode == 0

@pytest.mark.timeout(30)
def test_hpps_to_trch_with_poll_notification_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-n', 'poll', '-c', str(i)])
        assert out.returncode == 0

@pytest.mark.timeout(30)
def test_hpps_to_trch_with_epoll_notification_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-n', 'epoll', '-c', str(i)])
        assert out.returncode == 0

@pytest.mark.timeout(30)
def test_hpps_to_rtps_with_no_notification_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-n', 'none', '-o', '/dev/mbox/1/mbox0', '-i', '/dev/mbox/1/mbox1', '-c', str(i)])
        assert out.returncode == 0

@pytest.mark.timeout(30)
def test_hpps_to_rtps_with_select_notification_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-n', 'select', '-o', '/dev/mbox/1/mbox0', '-i', '/dev/mbox/1/mbox1', '-c', str(i)])
        assert out.returncode == 0

@pytest.mark.timeout(30)
def test_hpps_to_rtps_with_poll_notification_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-n', 'poll', '-o', '/dev/mbox/1/mbox0', '-i', '/dev/mbox/1/mbox1', '-c', str(i)])
        assert out.returncode == 0

@pytest.mark.timeout(30)
def test_hpps_to_rtps_with_epoll_notification_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-n', 'epoll', '-o', '/dev/mbox/1/mbox0', '-i', '/dev/mbox/1/mbox1', '-c', str(i)])
        assert out.returncode == 0

@pytest.mark.timeout(30)
def test_invalid_outbound_mailbox_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-c', str(i), '-o', '32'])
        assert out.returncode == 1

@pytest.mark.timeout(30)
def test_invalid_inbound_mailbox_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-c', str(i), '-i', '32'])
        assert out.returncode == 1

# verify that mboxtester fails with the correct exit code when a timeout
# occurs with the process pinned separately to each HPPS core
@pytest.mark.timeout(30)
def test_early_timeout_on_each_core(fixture, host):
    for i in range(8):
        out = run_tester_on_host(host, 0, ['-c', str(i), '-t', '0'])
        assert out.returncode == 22

# verify that mbox-multiple-core-tester works with core 0 performing a
# write-read followed by core 1 doing another write-read using the same mailbox
def test_multiple_cores_same_mbox(fixture, host):
    out = run_tester_on_host(host, 1, ['-C', '0', '-c', '1'])
    assert out.returncode == 0

def test_multiple_cores_same_mbox_invalid_CPU1(fixture, host):
    out = run_tester_on_host(host, 1, ['-C', '-1', '-c', '1'])
    assert out.returncode == 1

def test_multiple_cores_same_mbox_invalid_CPU2(fixture, host):
    out = run_tester_on_host(host, 1, ['-C', '0', '-c', '9'])
    assert out.returncode == 2
