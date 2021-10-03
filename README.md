## C program implementing Message Passing Interface (MPI) with MD5 Brute force

### Dependency
* compiler `sudo apt install build-essential`
* [MPICH](https://www.mpich.org/downloads/) or via apt `sudo apt install mpich libmpich-dev`
* libssl `sudo apt install libssl-dev`

### Usage
`./run.sh -r hostfile`

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
MPI MD5 BREAKER V2.0
Size : 24
Date : 2020/04/23 - 23:14:53
Test : 4c467321dd2d571a787706eb4466a09d
Hello From Thread 00
Hello From Thread 01
Hello From Thread 02
Hello From Thread 03
Hello From Thread 04
Hello From Thread 05
Hello From Thread 06
Hello From Thread 07
Hello From Thread 08
Hello From Thread 09
Hello From Thread 10
Hello From Thread 11
Hello From Thread 12
Hello From Thread 13
Hello From Thread 14
Hello From Thread 15
Hello From Thread 16
Hello From Thread 17
Hello From Thread 18
Hello From Thread 19
Hello From Thread 20
Hello From Thread 21
Hello From Thread 22
Hello From Thread 23
Date : 2020/04/24 - 01:31:49
Core 08 - The Result Was : ZZZZZZ
Done!
```

### NOTE
> Change hostfile before running on your machine! different machine can have different configurations
