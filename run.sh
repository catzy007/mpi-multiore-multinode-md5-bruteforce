#!/bin/bash
POSITIONAL=()
key="$1"
hostfile="$2"

case $key in
    -r|--run)
        gcc -c md5parser.c -lcrypto
        gcc -c datetime.c
        mpicc -c bruteforce.c
        mpicc -c core.c
        mpicc *.o -o core -lcrypto
        rm *.o
        mpiexec --hostfile ${hostfile} ./core
    ;;
    -c|--compile)
        gcc -c md5parser.c -lcrypto
        gcc -c datetime.c
        mpicc -c bruteforce.c
        mpicc -c core.c
        mpicc *.o -o core -lcrypto
        rm *.o
        echo "Compilation completed!"
    ;;
    *)
        echo "-c --compile"
        echo "   Only compile the program"
        echo "-r --run"
        echo "   Compile the program and execute it"
        echo "-h --help"
        echo "   Show this help message"
    ;;
esac
