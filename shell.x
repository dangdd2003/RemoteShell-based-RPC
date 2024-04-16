const MAX_SIZE = 4096;
typedef char command[MAX_SIZE];

struct buffer
{
  command input;
  int numbytes;
};

program SHELL_PROG
{
  version SHELL_VERS
  {
    buffer shell_output(buffer) = 1;
  }=1;
}=0x00000000;
