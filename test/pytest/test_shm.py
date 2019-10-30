import subprocess
import pytest
import re

testers = ["shm-standalone-tester", "shm-tester"]

def run_tester_on_host(hostname, tester_num, tester_pre_args, tester_post_args):
    tester_remote_path = "/opt/hpsc-utils/" + testers[tester_num]
    out = subprocess.run(['ssh', hostname] + tester_pre_args + [tester_remote_path] + tester_post_args, universal_newlines=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return out

# Since this first test may need to boot QEMU, it is given more time.
@pytest.mark.timeout(200)
def test_write_then_read_on_each_shm_region(boot_qemu, host):
    shm_dir = '/dev/hpsc_shmem/'
    num_write_bytes = 32

    # get a list of shared memory regions
    out = subprocess.run(['ssh', host, "ls", shm_dir], universal_newlines=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    assert out.returncode == 0
    shm_regions = out.stdout.splitlines()

    for shm_region in shm_regions:
        # write 0xff to each of num_write_bytes consecutive bytes of each shm_region
        out = run_tester_on_host(host, 0, [], ['-f', shm_dir + shm_region, '-s', str(num_write_bytes), '-w', '0xff'])
        assert out.returncode == 0
        # now perform a read to confirm the write
        out = run_tester_on_host(host, 0, [], ['-f', shm_dir + shm_region, '-s', str(num_write_bytes), '-r'])
        read_contents = (re.search(r"Start:(.+)$", out.stdout).group(0))[6:]
        assert out.returncode == 0
        assert read_contents == ' 0xff' * num_write_bytes

@pytest.mark.timeout(60)
def test_hpps_to_trch(boot_qemu, host):
    out = run_tester_on_host(host, 1, [], ['-i', '/dev/hpsc_shmem/region0', '-o', '/dev/hpsc_shmem/region1'])
    assert out.returncode == 0
