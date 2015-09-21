#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "io.h"
#include "cmd.h"

int main(int argc, char** argv) {
  char* input_line = NULL;
  const char* prompt = "308sh>";

  // parse the command arguments.
  int opt;
  while((opt = getopt(argc, argv, "p:")) != -1) {
    switch(opt) {
      case 'p':
        prompt = optarg;
        break;
      default:
        return 1;
    }
  }

  while(true) {
    int status;
    input_line = get_line(prompt);
    command_t cmd = make_command(input_line);

    pid_t pid;

    // get all the processes that ended since the last check.
    while ((pid = waitpid(-1, &status, WNOHANG)) != 0 && pid != -1) {
      if (WIFEXITED(status)) {
        printf("Child Process [%d] Exited: %d\n", pid, WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
        printf("Child Process [%d] Killed: %d\n", pid, WEXITSTATUS(status));
      }
    }

    run_command(&cmd);
    free(input_line);
    free_command(&cmd);
  }

}
