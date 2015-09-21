#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "cmd.h"
#include "process.h"

static int run_builtin(command_t* cmd);

void run_command(command_t* cmd) {

  if (run_builtin(cmd) == 0) {
    return;
  }

  launch_process(cmd);
}

static int run_builtin(command_t* cmd) {
  char* first_part = cmd->bin;
  cmd_args_t args = cmd->args;
  if (first_part != NULL) {
    if (strcmp(first_part, EXIT) == 0) {
      exit(0);
    } else if (strcmp(first_part, PID) == 0) {
      sh_pid();
    } else if (strcmp(first_part, PPID) == 0) {
      sh_ppid();
    } else if (strcmp(first_part, CD) == 0) {
      sh_cd(args);
    } else if (strcmp(first_part, PWD) == 0) {
      sh_pwd();
    } else if (strcmp(first_part, SET) == 0) {
      sh_set(args);
    } else if (strcmp(first_part, GET) == 0) {
      sh_get(args);
    } else {
      return 1;
    }
  }

  return 0;
}

command_t make_command(char* input) {
  int arg_length = 5;
  char* bin = strtok(input, " ");
  char** options = (char**)malloc(arg_length * sizeof(char*));

  options[0] = bin;
  int i;
  char* param;
  for(i = 1; (param = strtok(NULL, " ")) != NULL; i++) {
    options[i] = param;

    if (i >= arg_length - 1) {
      arg_length *= 2;
      options = (char**)realloc(options, arg_length * sizeof(char*));
    }
  }
  options[i] = NULL;

  cmd_args_t args = {.args = options, .size = i};
  command_t cmd = {.bin = bin, .args = args};
  return cmd;
}

void free_command(command_t* cmd) {
  free(cmd->args.args);
}
