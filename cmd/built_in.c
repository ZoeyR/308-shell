#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "cmd.h"

void sh_exit() {
  exit(0);
}

void sh_pid() {
  printf("%d\n", getpid());
}

void sh_ppid() {
  printf("%d\n", getppid());
}

void sh_cd(cmd_args_t args) {
  char* dir;
  if (args.size == 1) {
    dir = getenv("HOME");
  } else {
    dir = args.args[1];
  }

  chdir(dir);
}

void sh_pwd() {
  char* cwd = getcwd(NULL, 0);
  printf("%s\n", cwd);
  free(cwd);
}

void sh_set(cmd_args_t args) {
  setenv(args.args[0], args.args[1], true);
}

void sh_get(cmd_args_t args) {
  char* val = getenv(args.args[0]);

  if (val == NULL) {
    printf("(NULL)\n");
  } else {
    printf("%s\n", val);
  }

}
