import serial
import pytest
import re
from pexpect.fdpexpect import fdspawn

testers = ["sram-tester"]

def run_tester_on_host(hostname, tester_num, tester_pre_args, tester_post_args):
    tester_remote_path = "/opt/hpsc-utils/" + testers[tester_num]
    out = subprocess.run(['ssh', hostname] + tester_pre_args + [tester_remote_path] + tester_post_args, universal_newlines=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return out

# This SRAM test will modify an array in SRAM, reboot HPPS (using a
# watchdog timeout), then check that the SRAM array is the same.
# Since this test will boot QEMU, then reboot QEMU, it is given more time.
@pytest.mark.timeout(800)
def test_non_volatility(boot_qemu_per_module, host):
    # NEED TO REMOVE HARD-CODED PORTS LIKE BELOW
    ser = serial.Serial(port='/dev/pts/2', baudrate=115200)
    child = fdspawn(ser, timeout=1000)

    # modify the SRAM array, then reboot HPPS
    child.sendline("/opt/hpsc-utils/sram-tester -s 100 -m")
    child.sendline("taskset -c 0 /opt/hpsc-utils/wdtester /dev/watchdog0 0")
    assert(child.expect("hpsc-chiplet login: ") == 0)
    # isolate the printed SRAM contents from before the reboot
    sram_before_reboot = re.search(r'(.+)root@hpsc-chiplet', re.search(r'Latest SRAM contents:(.+)', str(child.before), flags=re.DOTALL).group(1), flags=re.DOTALL).group(1)

    # after the reboot, read the SRAM contents to verify that they haven't changed
    child.sendline('root')
    assert(child.expect('root@hpsc-chiplet:~# ') == 0)
    child.sendline("/opt/hpsc-utils/sram-tester -s 100")
    assert(child.expect('root@hpsc-chiplet:~# ') == 0)
    # isolate the printed SRAM contents from after the reboot
    sram_after_reboot = re.search(r'(.+)\'', re.search(r'Latest SRAM contents:(.+)', str(child.before), flags=re.DOTALL).group(1), flags=re.DOTALL).group(1)
    assert(sram_before_reboot == sram_after_reboot), "SRAM array before reboot was: " + sram_before_reboot + ", while SRAM array after reboot was: " + sram_after_reboot

    ser.close()
