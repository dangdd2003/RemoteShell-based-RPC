#include "shell.h"
#include <rpc/clnt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int main(int argc, char *argv[]) {
  char *host = argv[1]; // host ip address
  if (host == NULL) {
    host = "localhost";
  }
  CLIENT *cl; // init client
  cl = clnt_create(host, SHELL_PROG, SHELL_VERS, "tcp");
  if (cl == NULL) {
    clnt_pcreateerror(host);
    exit(EXIT_FAILURE);
  } else {
    printf("Connect sucessfully!\n");
  }

  buffer *buff = malloc(sizeof(buffer));
  char *command_line = malloc(MAX_SIZE);
  int n;
  buffer *result;
  for (;;) {
    // set bytes of the buffers to zero
    bzero(buff, sizeof(buffer));
    bzero(command_line, MAX_SIZE);

    // read input command_line from stdin
    n = 0;
    printf("> ");
    while ((command_line[n++] = getchar()) != '\n')
      ;
    if (strncmp("exit", command_line, 4) == 0) {
      printf("Client exit!\n");
      strcpy(buff->input, command_line);
      buff->numbytes = sizeof(command_line);
      shell_output_1(buff, cl);
      break;
    }

    // send to server and get result
    strcpy(buff->input, command_line);
    buff->numbytes = sizeof(command_line);
    result = shell_output_1(buff, cl);
    if (result == NULL) {
      clnt_perror(cl, host);
      exit(EXIT_FAILURE);
    }

    // get result
    printf("Size of output: %d\n%s\n", result->numbytes, result->input);
  }

  return EXIT_SUCCESS;
}
