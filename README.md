# RemoteShell-based-RPC

Implementation of Remote Shell based on RPC mechanism.

## Prerequisite

- **Remote Procedure Call (RPC)** is when a computer program causes a procedure
or (subroutine) to execute in a different address space (commonly on another
computer on a shared computer network), and is written like a normal (local)
procedure call.
- **Remote Shell**: A tool for executing commands on a device through
command-line shell (a program enabling computer control through command)
on another device.

## Dependencies

- Libraries:
  - Required: `libtirpc`, `rpcbind`
  - Optional: `rpcsvc-proto`
- Most of the time RPC library should come pre-installed as it is used
in some systems procedure.
- However, in the off-chance you might need to install the RPC library
like on Ubuntu/Linux(UNIX) you can install it with
`sudo apt-get install rpcbind libtirpc-dev`

## System Design

- Shared Computer Network: The easiest way is to have computers connect to the
same wifi hotspot or router, the we can specify the address space (IP address)
for the client program to connect with the server.
- RPC Service:
  - The server shell will turn on set as listening until the client establish a connection.
  - When client shell connect successfully it can execute commands in the server
  command-line. Which are messages that are passed to server to execute, and the
  output is then return back to the client shell.
  - The message passing will be handled by the client-server stub generate rpc
  then the network routine is defined as simple send and receive.

![Design](./assets/RPC.png)

## Deployment

- Requirement
  - rpcgen - generate RPC function.
  - rpcbind - map rpc generic addresses with RPC program.
  - gcc, GNU make - C compiler.
- Build

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
    ./client {host - optional, default is localhost}
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

## Scenario Demonstrate

- Client Shell
  ```bash
  root@client> ./client
  Connect successfully!
  > echo HelloWorld!
  HelloWorld!
  ```
  In client shell, after connecting successully, the client takes input signal from the server. Then it will handle our input for the output. Finally, it will send the output back to the server.
  This is an example of client handle when user input "HelloWorld!". After connecting to the client, the input signal will be handled. If the output is appeared, so that it is successfully sent back to the server shell.
- Server Shell
  ```bash
  root@server> ./server
  Client enter: echo HelloWorld!
  HelloWorld!
  ```
In server shell, it authenticates sends a input command from the user. After user inputs something and enter, it will show the input and send the signal to the client shell.
For example, we want to send the input "HelloWorld!" to the client. In bash, the first line for opening a server shell, the second for our input and the last for our output after the signal sends successfully to the client and sends the output back to the server.

## Contributors

- BI12-073 [Trần Hải Đăng](https://github.com/thdgg)
- BI12-074 [Đoàn Đình Đăng](https://github.com/dangdd2003)
- BI12-076 [Mai Hải Đăng](https://github.com/Incomprehensibilitative)
- BI11-113 [Nguyễn Quang Huy](https://github.com/Dev789-del)
- BI12-475 [Nguyễn Hoàng Tùng](https://github.com/Tonguesten36)
- BI12-099 [Nguyễn Thanh Đức](https://github.com/990-21IB)

(Fill the name and your github link here)
