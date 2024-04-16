# RemoteShell-based-RPC

Implementation of Remote Shell based on RPC mechanism

## RPC (Remote Produce Call) Mechanism in Distributed System

- ...

## Implementation

- ...
- The rpc/rpc.h is part of the RPC library. On some systems, you might need to install the RPC library like on Ubuntu/Linux(UNIX) you can install it with `sudo apt-get install rpcbind libtirpc-dev`

## Deployment

- Requirement
    - rpcgen - generate RPC function
    - rpcbind - map rpc generic addresses with RPC program
    - gcc, GNU make - C compiler
- Start
    ```bash
    make
    ```
- Run
    - Prepare rpc env (with root)
    ```bash
    rpcbind start # start rpcbind
    rpcinfo # check rpc status
    ```
    - Open a shell
    ```bash
    ./server
    ```
    - Open second shell
    ```bash\
    ./client
    ```
- Stop (find and kill the process)
```bash
ps -ef | grep server
kill {PID of ./server}
```
- Clean
```bash
make clean
```
## Contributors

- BI12-073 [Trần Hải Đăng](https://github.com/thdgg)
- BI12-074 [Đoàn Đình Đăng](https://github.com/dangdd2003)
- BI12-076 [Mai Hải Đăng](https://github.com/Incomprehensibilitative)
- BI11-113 [Nguyễn Quang Huy](https://github.com/Dev789-del)
- BI12-475 [Nguyễn Hoàng Tùng](https://github.com/Tonguesten36)
- BI12-099 [Nguyễn Thanh Đức](https://github.com/990-21IB)

(Fill the name and your github link here)
