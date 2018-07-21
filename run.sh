#!/bin/sh
mpicc cmpi.c -o cmpi -lcrypto
mpiexec --hostfile ./hostfile -n 8 ./cmpi
