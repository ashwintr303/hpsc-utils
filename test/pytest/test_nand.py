import serial
import subprocess
import pytest
from pexpect.fdpexpect import fdspawn
from conftest import ser_port, ser_baudrate

def run_tester_on_host(hostname, cmd):
    out = subprocess.run("ssh " + hostname + " " + cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
    return out

# Verify that a file created on the NAND-based rootfs is still present after
# rebooting HPPS.
# Since this test will boot QEMU, then reboot QEMU, it is given more time.
@pytest.mark.timeout(800)
def test_non_volatility(boot_qemu_per_module, host):
    test_dir = "/home/root/"
    test_file = "nand_test_file"

    ser = serial.Serial(port=ser_port, baudrate=ser_baudrate)
    child = fdspawn(ser, timeout=1000)

    # create the test_file, then reboot HPPS
    out = run_tester_on_host(host, "touch " + test_dir + test_file)
    assert out.returncode == 0
    child.sendline("taskset -c 0 /opt/hpsc-utils/wdtester /dev/watchdog0 0")
    assert(child.expect("hpsc-chiplet login: ") == 0)

    # after the reboot, check that the test_file is still there
    child.sendline('root')
    assert(child.expect('root@hpsc-chiplet:~# ') == 0)
    ser.close()
    out = run_tester_on_host(host, "ls " + test_dir)
    assert out.returncode == 0
    assert(test_file in out.stdout), "File " + test_file + " was not found among the following files listed in directory " + test_dir + ":\n" + out.stdout

    # finally, remove the test_file
    out = run_tester_on_host(host, "rm " + test_dir + test_file)
    assert out.returncode == 0
