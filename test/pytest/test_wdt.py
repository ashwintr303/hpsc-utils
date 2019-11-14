import serial
import pexpect
import pexpect.fdpexpect
import subprocess
import pytest
from threading import Thread
from queue import Queue

testers = ["wdtester"]

def run_tester_on_host(hostname, tester_num, tester_pre_args, tester_post_args):
    tester_remote_path = "/opt/hpsc-utils/" + testers[tester_num]
    # using "Popen" instead of "run" below to make the command non-blocking
    out = subprocess.Popen(['ssh', hostname] + tester_pre_args + [tester_remote_path] + tester_post_args, universal_newlines=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return out

def enqueue_output(out, queue):
    for line in iter(out.readline, b''):
        queue.put(line)
    out.close()

# This test cycles through each core so that each one kicks its own watchdog.
# Since this test boots QEMU, it is given more time.
@pytest.mark.timeout(200)
@pytest.mark.parametrize('core_num', range(7))
def test_kicked_hpsc_watchdog(boot_qemu_per_function, host, core_num):
    p = run_tester_on_host(host, 0, ['taskset', '-c', str(core_num)], ['/dev/watchdog' + str(core_num), '1'])

    # the queue and thread below are used to check stdout in a non-blocking manner
    q = Queue()
    t = Thread(target=enqueue_output, args=(p.stdout, q))
    t.daemon = True
    t.start()

    while True:
        search_str = "Kicking watchdog: yes"
        try:
            line = q.get_nowait()
            print("line=" + line)
            if (search_str in line):
                assert (search_str in line)
                break
        except:
            pass
                
    p.terminate()
