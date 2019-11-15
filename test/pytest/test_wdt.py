import serial
import pytest
from pexpect.fdpexpect import fdspawn

testers = ["wdtester"]

# Each core starts its own watchdog timer and then kicks it.
# Since this test boots QEMU, it is given more time.
@pytest.mark.timeout(200)
@pytest.mark.parametrize('core_num', range(7))
def test_kicked_watchdog_on_each_core(boot_qemu_per_function, host, core_num):
    # NEED TO REMOVE HARD-CODED PORTS LIKE BELOW
    ser = serial.Serial(port='/dev/pts/2', baudrate=115200)
    child = fdspawn(ser, timeout=1000)
    child.sendline("taskset -c " + str(core_num) + " /opt/hpsc-utils/wdtester /dev/watchdog" + str(core_num) + " 1")
    # the expect call below should return a 0 on a successful match
    assert(child.expect("Kicking watchdog: yes") == 0)
    ser.close()
