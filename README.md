## Simple C program implementing Message Parsing Interface (MPI) with MD5 Brute force

### Dependency
* [MPICH](https://www.mpich.org/downloads/) or via apt `sudo apt install mpich`
* libssl `sudo apt install libssl-dev`

### Usage
`./run.sh hostfile`

### Hostfile
a filename that lists hosts on which to launch MPI processes
* example:
  * local machine with 4 core 8 threads
    ```
    localhost:8
    ```
  * remote machine 192.168.1.250 - 253 with 4 core each
    ```
    192.168.1.250:4
    192.168.1.251:4
    192.168.1.252:4
    192.168.1.253:4
    ```
### Sample Output
```
MPI MD5 BREAKER
Core : 8
Date : 2019/05/11 - 23:33:16
Data : 8315ead3918667a547bbb390185c362c
Hello From Core 00
Hello From Core 01
Hello From Core 02
Hello From Core 03
Hello From Core 04
Hello From Core 05
Hello From Core 06
Hello From Core 07
Date : 2019/05/11 - 23:33:20
Core 07 - The Result Was : ZZZZ0000
Done!
```

### NOTE
> Change hostfile before running on your machine! different machine can have different configurations
