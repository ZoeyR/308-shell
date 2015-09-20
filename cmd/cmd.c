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

const char* EXIT = "exit";
const char* PID = "pid";
const char* PPID = "ppid";
const char* CD = "cd";
const char* PWD = "pwd";
const char* SET = "set";
const char* GET = "get";

static int run_builtin(char* cmd);
static int run_extern(char* cmd);

int run_command(char* cmd) {
  char* copy_cmd = (char*)malloc(strlen(cmd) * sizeof(char));
  strcpy(copy_cmd, cmd);

  if (run_builtin(copy_cmd) == 0) {
    return 0;
  }
  free(copy_cmd);

  run_extern(cmd);
  return 0;
}

static int run_builtin(char* cmd) {
  char* first_part = strtok(cmd, " ");

  if (first_part != NULL) {
    if (strcmp(first_part, EXIT) == 0) {
      exit(0);
    } else if (strcmp(first_part, PID) == 0) {
      printf("%d\n", getpid());
    } else if (strcmp(first_part, PPID) == 0) {
      printf("%d\n", getppid());
    } else if (strcmp(first_part, CD) == 0) {
      char* dir = strtok(NULL, "");
      if (dir == NULL) {
        dir = getenv("HOME");
      }

      chdir(dir);
    } else if (strcmp(first_part, PWD) == 0) {
      char* cwd = getcwd(NULL, 0);
      printf("%s\n", cwd);
      free(cwd);
    } else if (strcmp(first_part, SET) == 0) {
      char* var = strtok(NULL, " ");
      char* val = strtok(NULL, "");
      setenv(var, val, true);
    } else if (strcmp(first_part, GET) == 0) {
      char* var = strtok(NULL, "");
      char* val = getenv(var);

      printf("%s\n", val);
    } else {
      return 1;
    }
  }

  return 0;
}

static int run_extern(char* cmd) {
  bool run_bg;
  int arg_length = 5;
  char* bin = strtok(cmd, " ");
  char** options = (char**)malloc(arg_length * sizeof(intptr_t));
  char* param;

  options[0] = bin;

  int i;
  for(i = 1; (param = strtok(NULL, " ")) != NULL; i++) {
    options[i] = param;

    if (i >= arg_length - 1) {
      arg_length *= 2;
      options = (char**)realloc(options, arg_length * sizeof(char*));
    }
  }

  // check if the last character was an ampersand
  if (strcmp(options[i - 1], "&") == 0) {
    run_bg = true;
    options[i - 1] = NULL;
  } else {
    run_bg = false;
    options[i] = NULL;
  }

  pid_t pid = fork();
  if (pid) {
    //This is the parent process
    int status;

    if (!run_bg) {
      waitpid(pid, &status, 0);
      if (WIFEXITED(status)) {
        printf("%s Exit: %d\n", bin, WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
        printf("%s Killed: %d\n", bin, WEXITSTATUS(status));
      }
    }
  } else {
    // This is the child process
    printf("PID: [%d]\n", getpid());

    execvp(bin, options);
    if (errno == ENOENT) {
      printf("Error: %s: command not found\n", bin);
      exit(1);
    } else if (errno) {
      printf("Error: %d: %s\n", errno, strerror(errno));
      exit(1);
    }
  }

  return 0;
}
