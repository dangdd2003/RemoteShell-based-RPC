#include "shell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <rpc/clnt.h>
#include <rpc/svc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")
#define die(e)                                                                 \
  do {                                                                         \
    fprintf(stderr, "Cause of error: %s\n", e);                                \
    exit(EXIT_FAILURE);                                                        \
  } while (0);

char *shell(char *input_string) {
  char *output_string =
      malloc(MAX_SIZE);         // store output of system shell in dynamic array
  char output_buffer[MAX_SIZE]; // store output of system shell in static array
  bzero(output_buffer, sizeof(output_buffer));

  int link[2];
  pid_t pid;

  if (pipe(link) == -1) {
    die("pipe");
  }

  if ((pid = fork()) == -1) {
    die("fork");
  }

  if (pid == 0) {
    // Child process
    dup2(link[1], STDOUT_FILENO);
    close(link[0]);
    close(link[1]);
    printf("when pid = 0");
    execl("/bin/bash", "bash", "-c", input_string,
          (char *)0); // use the command in execl()
    die("execl");
  } else {
    // Parent process
    close(link[1]);
    int nbytes = read(link[0], output_buffer, sizeof(output_buffer));
    wait(NULL);
  }

  // copy to dynamic size allocated string
  strcpy(output_string, output_buffer);
  printf("%s", output_string);

  return output_string;
}

buffer *shell_output_1_svc(buffer *recvbuff, struct svc_req *req) {

  // visualize the input from client
  printf("Client enter: %s\n", recvbuff->input);
  printf("Total byte: %d \n", recvbuff->numbytes);

  // create a buffer to store the output
  buffer *result = malloc(sizeof(buffer));
  char *output = shell(recvbuff->input); // store system shell output

  // return output buffer to client
  strcpy(result->input, output);
  result->numbytes = sizeof(output);
  return result;
}
