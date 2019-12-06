import serial
import pytest
from pexpect.fdpexpect import fdspawn

testers = ["wdtester"]

# Each core starts its own watchdog timer and then kicks it.
# Since this test boots QEMU, it is given more time.
@pytest.mark.timeout(400)
@pytest.mark.parametrize('core_num', range(8))
def test_kicked_watchdog_on_each_core(qemu_hpps_ser_conn_per_fcn, host, core_num):
    hpps_ser_fd = fdspawn(qemu_hpps_ser_conn_per_fcn, timeout=1000)
    hpps_ser_fd.sendline("taskset -c " + str(core_num) + " /opt/hpsc-utils/wdtester /dev/watchdog" + str(core_num) + " 1")

    # the expect call below should return a 0 on a successful match
    assert(hpps_ser_fd.expect("Kicking watchdog: yes") == 0)

# Each core starts its own watchdog timer but does not kick it.
# Since this involves a HPPS reboot, it is given more time.
@pytest.mark.timeout(800)
@pytest.mark.parametrize('core_num', range(8))
def test_unkicked_watchdog_on_each_core(qemu_hpps_ser_conn_per_fcn, host, core_num):
    hpps_ser_fd = fdspawn(qemu_hpps_ser_conn_per_fcn, timeout=1000)
    hpps_ser_fd.sendline("taskset -c " + str(core_num) + " /opt/hpsc-utils/wdtester /dev/watchdog" + str(core_num) + " 0")

    # the expect calls below should return a 0 on a successful match
    assert(hpps_ser_fd.expect("Kicking watchdog: no") == 0)
    # after HPPS reboot, its login prompt should appear
    assert(hpps_ser_fd.expect("hpsc-chiplet login: ") == 0)
