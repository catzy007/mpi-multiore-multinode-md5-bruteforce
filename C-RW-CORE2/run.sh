#!/bin/sh
hostfile="$1"
if [ -z "$hostfile" ]; then
	echo "Usage : "
	echo "  ./run.sh <hostfile>"
	echo
	echo "hostfile : "
	echo "  a filename that lists hosts on which to launch MPI processes"
	echo "  example:"
	echo "    local machine with 4 core 8 threads"
	echo "      localhost:8"
	echo "    remote machine 192.168.1.250 - 253 with 4 core each"
	echo "      192.168.1.250:4"
	echo "      192.168.1.251:4"
	echo "      192.168.1.252:4"
	echo "      192.168.1.253:4"
else
	mpicc cmpi.c -o cmpi -lcrypto
#	mpiexec --hostfile ${hostfile} ./cmpi
fi
