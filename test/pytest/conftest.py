import serial
import pexpect
import pexpect.fdpexpect
import subprocess
import pytest
import os

# Make sure that the CODEBUILD_SRC_DIR env var is set- on AWS CodeBuild,
# this is done automatically.  In any other environment, it needs to be set.

@pytest.fixture(scope="session")
def boot_qemu():
    # Create a file with unspecified port names so that screen sessions to serial ports are disabled
    f = open(str(os.environ['CODEBUILD_SRC_DIR']) + "/hpsc-bsp/qemu-env-override.sh", "w")
    f.write("SERIAL_PORT_NAMES[serial0]=\"\"\nSERIAL_PORT_NAMES[serial1]=\"\"\nSERIAL_PORT_NAMES[serial2]=\"\"\n")
    f.close()
    # Now start QEMU without any screen sessions
    p = subprocess.Popen([str(os.environ['CODEBUILD_SRC_DIR']) + "/hpsc-bsp/run-qemu.sh", "-e", str(os.environ['CODEBUILD_SRC_DIR']) + "/hpsc-bsp/qemu-env.sh", "-e", str(os.environ['CODEBUILD_SRC_DIR']) + "/hpsc-bsp/qemu-env-override.sh", "--", "-S"])

    # ULTIMATELY REMOVE THESE SLEEP CALLS- THEY ARE NOT RELIABLE
    subprocess.run(['sleep', '30'])

    # connect to the HPPS serial port- HOWEVER, THE PORT SHOULD NOT BE HARD CODED
    ser = serial.Serial(port='/dev/pts/2', baudrate=115200)
    subprocess.run(['sleep', '20'])
    child = pexpect.fdpexpect.fdspawn(ser, timeout=1000)

    # USE A TRY BLOCK FOR THE FOLLOWING, QMP PORT NUMBER SHOULD NOT BE HARD CODED
    subprocess.run(["python3", str(os.environ['CODEBUILD_SRC_DIR']) + "/hpsc-bsp/sdk/tools/qmp-cmd", "localhost", "2024", "cont"])

    # log into the HPPS, then close the HPPS serial port
    child.expect("hpsc-chiplet login: ")
#    print('child.before 1 = ', child.before)
    child.sendline('root')
    child.expect('root@hpsc-chiplet:~# ')
#    print('child.before 2 = ', child.before)
    ser.close()
    yield boot_qemu
    p.terminate()

def pytest_addoption(parser):
    parser.addoption("--host", action="store", help="host")

def pytest_generate_tests(metafunc):
    # this is called for every test
    option_value = metafunc.config.option.host
    if 'host' in metafunc.fixturenames and option_value is not None:
        metafunc.parametrize("host", [option_value])
