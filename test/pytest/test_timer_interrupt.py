from subprocess import run
import pytest

local_dir = '../linux/'
testers = ["rtit-tester"]

@pytest.fixture(scope="function")  # scope could be "function", "class", "module", "package", or "session"
def fixture(host):
    local_tester_paths = [local_dir + t for t in testers]
    run(['scp'] + local_tester_paths + [host + ':~'])
    yield fixture # provide the fixture value, then start teardown code
    remote_tester_paths = ["~/" + t for t in testers]
    run(['ssh', host, 'rm'] + remote_tester_paths)

def run_tester_on_host(hostname, tester_num, tester_pre_args, tester_post_args):
    tester_remote_path = "~/" + testers[tester_num]
    out = run(['ssh', hostname] + tester_pre_args + [tester_remote_path] + tester_post_args, capture_output=True)
    return out
    
def test_rti_timer_on_each_core(fixture, host):
    masks = ["0x1", "0x2", "0x4", "0x8", "0x10", "0x20", "0x40", "0x80"]
    interval_ms = 2000

    for i in range(8):
        out = run_tester_on_host(host, 0, ['taskset', masks[i]], ["/dev/rti_timer" + str(i), str(interval_ms)])
        assert out.returncode == 0
