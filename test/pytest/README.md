HPSC Automated Tests
====================

This directory contains PyTest test scripts for testing various HPSC
functionality.  The user should verify that they have Python and PyTest
installed on their machine before running these tests.

To run the full test suite:

    pytest -v --host [hostname]

e.g.,

    pytest -v --host hpscqemu

In order to run the tests in a specific file:

    pytest -v [test_file] --host [hostname]

e.g.,

    pytest -v test_dma.py --host hpscqemu
