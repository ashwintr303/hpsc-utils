from subprocess import run
import pytest

local_dir = '../linux/'
testers = ['parallel-app-tester.sh']

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

def test_parallel_app_scaling(fixture, host):
    out = run_tester_on_host(host, 0, [])
    assert (out.returncode == 0)

def test_invalid_npb_problem_class(fixture, host):
    out = run_tester_on_host(host, 0, ['-c', 'D'])
    assert (out.returncode == 1)
