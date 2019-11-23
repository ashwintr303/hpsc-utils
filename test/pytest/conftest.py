import serial
import subprocess
import pytest
import os
import re
from pexpect.fdpexpect import fdspawn

# Make sure that the CODEBUILD_SRC_DIR env var is set.  This is the directory
# where the hpsc-bsp directory is located.  On AWS CodeBuild, this is done
# automatically.  In any other environment, it needs to be set.

def qemu_hpps_ser_conn():
    # Change to the hpsc-bsp directory
    os.chdir(str(os.environ['CODEBUILD_SRC_DIR']) + "/hpsc-bsp")

    # Create a file with unspecified port names so screen sessions to serial ports are disabled
    f = open("./qemu-env-override.sh", "w")
    f.write("SERIAL_PORT_NAMES[serial0]=\"\"\nSERIAL_PORT_NAMES[serial1]=\"\"\nSERIAL_PORT_NAMES[serial2]=\"\"\n")
    f.close()

    # Now start QEMU without any screen sessions
    # note that the Popen call below combines stdout and stderr together
    p = subprocess.Popen(["./run-qemu.sh", "-e", "./qemu-env.sh", "-e", "./qemu-env-override.sh", "--", "-S"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
    for stdout_line in iter(p.stdout.readline, ""):
        if ("QMP_PORT = " in stdout_line):
            qmp_port = re.search(r"QMP_PORT = (\d+)", stdout_line).group(1)
        elif ("(label serial2)" in stdout_line):
            hpps_ser_port = re.search(r"char device redirected to (\S+)", stdout_line).group(1)
            break
    p.stdout.close()
    
    # Connect to the HPPS serial port, then issue a continue command to QEMU
    hpps_ser_conn = serial.Serial(port=hpps_ser_port, baudrate=115200)
    hpps_ser_fd = fdspawn(hpps_ser_conn, timeout=1000)
    subprocess.run(["python3", "sdk/tools/qmp-cmd", "localhost", qmp_port, "cont"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)

    # Log into the HPPS, then send the serial connection to the individual tests
    hpps_ser_fd.expect('hpsc-chiplet login: ')
    hpps_ser_fd.sendline('root')
    hpps_ser_fd.expect('root@hpsc-chiplet:~# ')
    yield hpps_ser_conn
    # This is the teardown
    hpps_ser_conn.close()
    p.terminate()

@pytest.fixture(scope="module")
def qemu_hpps_ser_conn_per_mdl():
    yield from qemu_hpps_ser_conn()

@pytest.fixture(scope="function")
def qemu_hpps_ser_conn_per_fcn():
    yield from qemu_hpps_ser_conn()

def pytest_addoption(parser):
    parser.addoption("--host", action="store", help="remote hostname")

def pytest_generate_tests(metafunc):
    # this is called for every test
    option_value = metafunc.config.option.host
    if 'host' in metafunc.fixturenames and option_value is not None:
        metafunc.parametrize("host", [option_value])
