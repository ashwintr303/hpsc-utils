HPSC Automated Tests
====================

This directory contains PyTest test scripts for testing various HPSC
functionality.  Before running the scripts, the user should verify the
following:
* Python and PyTest are installed locally.
* All of the tests are built.  Currently, this only consists of the tests
in hpsc-utils/test/linux.
* The remote machine which will be tested is up and running.  In addition,
the local machine is able to connect to this machine by hostname alone.
For instance, in order to connect to HPSC QEMU, the following "config" file
can be placed in the user's .ssh directory:

```Host hpscqemu
     HostName localhost
     User root
     Port 3088
     StrictHostKeyChecking no
     UserKnownHostsFile=/dev/null
```

Once the prerequisites are met, run the full test suite as follows:

    pytest -v --host [hostname]

e.g.,

    pytest -v --host hpscqemu

In order to run the tests in a specific file:

    pytest -v [test_file] --host [hostname]

e.g.,

    pytest -v test_dma.py --host hpscqemu
