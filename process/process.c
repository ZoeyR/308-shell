#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "process.h"
#include "cmd.h"

void launch_process(command_t* command) {
  bool run_bg;
  cmd_args_t args = command->args;
  size_t size = args.size;
  // check if the last character was an ampersand
  if (strcmp(args.args[size - 1], "&") == 0) {
    run_bg = true;
    args.args[size - 1] = NULL;
  } else {
    run_bg = false;
    args.args[size] = NULL;
  }

  pid_t pid = fork();
  if (pid) {
    //This is the parent process
    int status;

    if (!run_bg) {
      waitpid(pid, &status, 0);
      if (WIFEXITED(status)) {
        printf("%s Exit: %d\n", command->bin, WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
        printf("%s Killed: %d\n", command->bin, WEXITSTATUS(status));
      }
    }
  } else {
    // This is the child process
    printf("PID: [%d]\n", getpid());

    execvp(command->bin, args.args);
    if (errno == ENOENT) {
      printf("Error: %s: command not found\n", command->bin);
      exit(1);
    } else if (errno) {
      printf("Error: %d: %s\n", errno, strerror(errno));
      exit(1);
    }
  }
}
