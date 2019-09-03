#!/bin/bash
#
# Verify that scaling the NAS EP benchmark on the HPPS cores
# leads to speedup.
#

NPB_OMP_DIR=/opt/nas-parallel-benchmarks/NPB3.3.1-OMP/bin/
DEFAULT_CLASS=S

function check_class {
    local value=$1

    for legal_class in S W A B C
    do
	if [ ${value} == ${legal_class} ]; then
	    printf "NAS EP benchmark class=${CLASS}\n"
	    return 0
	fi
    done

    printf "Invalid NAS EP benchmark class: ${CLASS}\n"
    printf "Valid values are: S, W, A, B, and C.\n"
    exit 1
}

# This function assumes that f1 and f2 are the same length
# before and after the decimal point
# returns -1 if f1>f2, 0 if they are equal, and +1 if f1<f2
function compare_floats {
    local f1=$1
    local f2=$2

    f1_int=$(echo ${f1} | cut -d "." -f 1)
    f2_int=$(echo ${f2} | cut -d "." -f 1)
    f1_frac=$(echo ${f1} | cut -d "." -f 2)
    f2_frac=$(echo ${f2} | cut -d "." -f 2)

    if [ ${f1_int} -lt ${f2_int} ]; then
	echo -1
    elif [ ${f1_int} -gt ${f2_int} ]; then
	echo 1
    else
	if [ ${f1_frac} -lt ${f2_frac} ]; then
	    echo -1
	elif [ ${f1_frac} -gt ${f2_frac} ]; then
	    echo 1
	else
	    echo 0
	fi
    fi
    return 0
}

while getopts c: option
do
case "${option}"
in
c) CLASS=${OPTARG};;
esac
done

# set default value for CLASS (if not already set)
if [[ -z "${CLASS}" ]]; then
    CLASS=${DEFAULT_CLASS}
fi

check_class ${CLASS}

for threads in 1 2 4 8
do
    export OMP_NUM_THREADS=${threads}
    cpu_time=$(${NPB_OMP_DIR}/ep.${CLASS}.x | grep "CPU Time" | tr -s " " | cut -d " " -f 4)
    printf "Time for ${threads} threads is ${cpu_time}\n"
    if [ ${threads} -gt 1 ]; then
	new_cpu_time=${cpu_time}
	if [ $(compare_floats ${n1} ${n2}) -eq 1 ]; then
	    if [ ${threads} -eq 2 ]; then
		# runtime for 2 threads is slower than that for 1 thread
		exit 2
	    elif [ ${threads} -eq 4 ]; then
		# runtime for 4 threads is slower than that for 2 threads
		exit 3
	    elif [ ${threads} -eq 8 ]; then
		# runtime for 8 threads is slower than that for 4 threads
		exit 4
	    fi
	fi
    fi
    old_cpu_time=${cpu_time}
done

exit 0
