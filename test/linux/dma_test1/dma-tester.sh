#!/bin/bash
#
# Test DMAs using 'dmatest' kernel module.
# The kernel module must be loaded or built-in for these tests to pass.

# Run the test with all default values, should be successful (exit code 0)
./dma-single-test.sh
printf "Exit code = $?\n"

# now test illegal parameters

# illegal "test_buf_size" should result in exit code 1
./dma-single-test.sh -b -1
printf "Exit code = $?\n"

# illegal "threads_per_chan" should result in exit code 2
./dma-single-test.sh -h -1
printf "Exit code = $?\n"

# illegal "iterations" should result in exit code 3
./dma-single-test.sh -i -1
printf "Exit code = $?\n"

# illegal "timeout" should result in exit code 4
./dma-single-test.sh -t -1
printf "Exit code = $?\n"

# illegal "channel" should result in exit code 5
./dma-single-test.sh -c nochan
printf "Exit code = $?\n"
