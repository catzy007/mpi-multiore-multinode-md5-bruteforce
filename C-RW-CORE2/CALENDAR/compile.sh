#!/bin/bash
gcc -c core.c
gcc -c iface.c
gcc -c main.c
gcc core.o iface.o main.o -o main
./main
