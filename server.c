#include "shell.h"
#include <stdio.h>
#include <rpc/clnt.h>
#include <rpc/svc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <readline/readline.h> 
#include <readline/history.h>

// Clearing the shell using escape sequences 
#define clear() printf("\033[H\033[J") 
#define CMD_LENGTH 4096
#define die(e) do {fprintf(stderr, "Cause of error: %s\n", e); exit(EXIT_FAILURE); } while(0);

char *shell(char *input_string) {
    char *output_string = malloc(CMD_LENGTH); // get the output of system shell and return

    // Shell implementation here ...
    // implement "input_string" in system shell and get the output, assign it to
    // "output_string"
    int link[2];
    pid_t pid;

    if(pipe(link) == -1) {
        die("pipe");
    }

    if((pid = fork()) == -1) {
        die("fork");
    }

    if(pid == 0) {
        //Child process
        dup2(link[1], STDOUT_FILENO);
        close(link[0]);
        close(link[1]);
        execl("/bin/sh", "sh", "-c", input_string, (char *)0);  // use the command in execl()
        die("execl");
    }
    else {
        //Parent process
        close(link[1]);
        int nbytes = read(link[0], output_string, sizeof(output_string));
        wait(NULL);
    }

    return output_string;
}

buffer *shell_output_1_svc(buffer *recvbuff, struct svc_req *req) {
    printf("Client enter: %s\n", recvbuff->input);
    printf("Total byte: %d \n", recvbuff->numbytes);
    buffer *output = malloc(sizeof(buffer));
    strcpy(output->input, shell(recvbuff->input));
    return output;
}