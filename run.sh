#!/bin/bash
POSITIONAL=()
key="$1"
hostfile="$2"

case $key in
    -r|--run)
        gcc -c md5parser.c -lcrypto
        gcc -c datetime.c
        gcc -c resumestate.c
	mpicc -c bruteforce.c
        mpicc -c core.c
        mpicc *.o -o core -lcrypto
        rm *.o
        mpiexec --hostfile ${hostfile} ./core
    ;;
    -c|--compile)
        gcc -c md5parser.c -lcrypto
        gcc -c datetime.c
        gcc -c resumestate.c
        mpicc -c bruteforce.c
        mpicc -c core.c
        mpicc *.o -o core -lcrypto
        rm *.o
        echo "Compilation has completed!"
    ;;
    *)
        echo "-c --compile"
        echo "   only compile the program"
        echo "-r --run"
        echo "   compile the program and execute it"
        echo "-h --help"
        echo "   show this help message"
    ;;
esac
