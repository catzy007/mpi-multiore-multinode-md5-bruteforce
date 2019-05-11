#!/bin/sh
thread="$1"
hostfile="$2"
if [ -z "$thread" ] || [ -z "$hostfile" ]; then
	echo "Usage : "
	echo "  ./run.sh <thread> <hostfile>"
	echo
	echo "thread : "
	echo "  amount of computing thread/cores your processor have"
	echo "  example:"
	echo "    machine with core i7-7700HQ with 4 core 8 thread"
	echo "      use 8 in the parameter"
	echo "    machine with 1.2GHz quad-core ARM Cortex-A53"
	echo "      use 4 in the parameter"
	echo
	echo "hostfile : "
	echo "  a filename that lists hosts on which to launch MPI processes"
	echo "  example:"
	echo "    local machine with 8 threads"
	echo "      localhost:8"
	echo "    remote machine 192.168.1.250 - 253 with 4 threads each"
	echo "      192.168.1.250:4"
	echo "      192.168.1.251:4"
	echo "      192.168.1.252:4"
	echo "      192.168.1.253:4"
else
	mpicc cmpi.c -o cmpi -lcrypto
	mpiexec --hostfile ${hostfile} -n ${thread} ./cmpi
fi
