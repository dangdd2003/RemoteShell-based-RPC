#include "shell.h"
#include "stdio.h"
#include <rpc/clnt.h>
#include <rpc/svc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#define CMD_LENGTH 1000

char *shell(char *input_string) {
  char *output_string =
      malloc(CMD_LENGTH); // get the output of system shell and return
  output_string = input_string;

  // Shell implementation here ...
  // implement "input_string" in system shell and get the output, assign it to
  // "output_string"

  return output_string;
}

buffer *shell_output_1_svc(buffer *recvbuff, struct svc_req *req) {
  printf("Client enter: %s", recvbuff->input);
  printf("Total byte: %d \n", recvbuff->numbytes);
  buffer *output = malloc(sizeof(buffer));
  strcpy(output->input, shell(recvbuff->input));
  return output;
}
