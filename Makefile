rpcgen shell.x
gcc -c client.c -o client.o
gcc -c server.c -o server.o -lreadline
gcc -c shell_clnt.c -o shell_clnt.o
gcc -c shell_xdr.c -o shell_xdr.o
gcc -c shell_svc.c -o shell_svc.o
gcc -o client client.o shell_clnt.o shell_xdr.o -ltirpc -lreadline
gcc -o server server.o shell_svc.o shell_xdr.o -ltirpc -lreadline
