#!/bin/sh
mpicc cmpi.c -o cmpi -lcrypto
mpiexec --hostfile ./hostfile -n 4 ./cmpi
