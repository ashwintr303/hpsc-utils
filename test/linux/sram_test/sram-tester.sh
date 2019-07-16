#!/bin/bash

EXEC=./sram_single_test

# print the SRAM contents
${EXEC} -s p
printf "Exit code = $?\n"

# modify the SRAM contents
${EXEC} -s m
printf "Exit code = $?\n"

# PERFORM A MANUAL HPPS REBOOT HERE

# print the SRAM contents to verify that our changes are non-volatile
${EXEC} -s p
printf "Exit code = $?\n\n"

# now test illegal parameters

# illegal file size should result in exit code 3
printf "Test with invalid file size:"
${EXEC} -f -1
printf "Exit code = $?\n\n"

# illegal SRAM access parameter should result in exit code 1
printf "Test with invalid SRAM access parameter:\n"
${EXEC} -s z
printf "Exit code = $?\n"
