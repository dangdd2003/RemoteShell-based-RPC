const LENGTH = 1024;
typedef char command[LENGTH];

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
