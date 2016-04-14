/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TARGET "/usr/local/bin/pwgen"

int main(void)
{
  char *args[3];
  char *env[1];

  // one way to invoke backup
  system("/usr/local/bin/pwgen --help");

  // another way
  args[0] = TARGET; args[1] = "--help";
  args[2] = NULL;

  env[0] = NULL;

  if (execve(TARGET, args, env) < 0)
    fprintf(stderr, "execve failed.\n");

  exit(0);
}
