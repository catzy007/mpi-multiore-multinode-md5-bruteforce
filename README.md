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
### NOTE
> Change hostfile before running on your machine! different machine can have different configurations
