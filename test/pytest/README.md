HPSC Automated Tests
====================

This directory contains PyTest test scripts for testing various HPSC
functionality.  Before running the scripts, the user should verify the
following:
* Python3 needs to be installed locally, along with the following packages:
pyserial, pexpect, pytest, pytest-timeout.
* The `CODEBUILD_SRC_DIR` environment variable is set to the absolute path
of the directory where the `hpsc-bsp` directory is located (not to the
`hpsc-bsp` directory itself).  On AWS CodeBuild, this is done automatically.
In any other environment, it needs to be set.
* The remote machine which will be tested is up and running.  In addition,
the local machine is able to connect to this machine by hostname alone.
For instance, in order to connect to HPSC QEMU, the following "config" file
can be placed in the user's .ssh directory:

```shell
Host hpscqemu
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
