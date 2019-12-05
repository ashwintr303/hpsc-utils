HPSC Automated Tests
====================

This directory contains PyTest test scripts for testing various HPSC
functionality.  Before running the scripts, the user should verify the
following:
* Python3 should be installed locally, along with the following packages:
`pyserial`, `pexpect`, `pytest`, `pytest-timeout`.  On a CentOS 7 machine,
the following commands should suffice:

```shell
yum -y install https://centos7.iuscommunity.org/ius-release.rpm
yum -y install python36-pip
pip3 install --upgrade pip
pip3 install pyserial pexpect pytest pytest-timeout
```

* The `CODEBUILD_SRC_DIR` environment variable should be set to the absolute
path of the directory where the `hpsc-bsp` directory is located (not to the
`hpsc-bsp` directory itself).  On AWS CodeBuild, this is done automatically.
In any other environment, it needs to be set.
* The remote machine which will be tested should be up and running.  In
addition, the local machine should be able to connect to this machine by
hostname alone.  For instance, in order to connect to HPSC QEMU, the following
"config" file can be placed in the user's .ssh directory:

```shell
Host hpscqemu
     HostName localhost
     User root
     Port 3088
     StrictHostKeyChecking no
     UserKnownHostsFile=/dev/null
```

Once the prerequisites are met, run the full test suite as follows:

    pytest -v --host [hostname] --durations=0

e.g.,

    pytest -v --host hpscqemu --durations=0

In order to only run the tests in specific files:

    pytest -v --host [hostname] --durations=0 [test_file1] [test_file2] ... [test_fileN]

e.g.,

    pytest -v --host hpscqemu --durations=0 test_dma.py test_mbox.py test_parallel_scaling.py
