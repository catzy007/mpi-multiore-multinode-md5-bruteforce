#!/bin/sh
mpicc cmpi.c -o cmpi -lcrypto
mpiexec --hostfile ./hostfile -n 16 ./cmpi
