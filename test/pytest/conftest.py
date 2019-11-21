import serial
import subprocess
import pytest
import os
from pexpect.fdpexpect import fdspawn

# Make sure that the CODEBUILD_SRC_DIR env var is set.  This is the directory
# where the hpsc-bsp directory is located.  On AWS CodeBuild, this is done
# automatically.  In any other environment, it needs to be set.

def boot_qemu():
    # Change to the hpsc-bsp directory
    os.chdir(str(os.environ['CODEBUILD_SRC_DIR']) + "/hpsc-bsp")

    # Create a file with unspecified port names so that screen sessions to serial ports are disabled
    f = open("./qemu-env-override.sh", "w")
    f.write("SERIAL_PORT_NAMES[serial0]=\"\"\nSERIAL_PORT_NAMES[serial1]=\"\"\nSERIAL_PORT_NAMES[serial2]=\"\"\n")
    f.close()

    # Now start QEMU without any screen sessions
    p = subprocess.Popen(["./run-qemu.sh", "-e", "./qemu-env.sh", "-e", "./qemu-env-override.sh", "--", "-S"])

    # ULTIMATELY REMOVE THESE SLEEP CALLS- THEY ARE NOT RELIABLE
    subprocess.run(['sleep', '30'])

    # connect to the HPPS serial port- HOWEVER, THE PORT SHOULD NOT BE HARD CODED
    ser = serial.Serial(port='/dev/pts/2', baudrate=115200)
    subprocess.run(['sleep', '20'])
    child = fdspawn(ser, timeout=1000)

    # USE A TRY BLOCK FOR THE FOLLOWING, QMP PORT NUMBER SHOULD NOT BE HARD CODED
    subprocess.run(["python3", "sdk/tools/qmp-cmd", "localhost", "2024", "cont"])

    # log into the HPPS, then close the HPPS serial port
    child.expect("hpsc-chiplet login: ")
#    print('child.before 1 = ', child.before)
    child.sendline('root')
    child.expect('root@hpsc-chiplet:~# ')
#    print('child.before 2 = ', child.before)
    ser.close()
    yield boot_qemu
    p.terminate()

@pytest.fixture(scope="module")
def boot_qemu_per_module():
    yield from boot_qemu()

@pytest.fixture(scope="function")
def boot_qemu_per_function():
    yield from boot_qemu()

def pytest_addoption(parser):
    parser.addoption("--host", action="store", help="host")

def pytest_generate_tests(metafunc):
    # this is called for every test
    option_value = metafunc.config.option.host
    if 'host' in metafunc.fixturenames and option_value is not None:
        metafunc.parametrize("host", [option_value])
