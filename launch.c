#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "io/io.h"
#include "cmd/cmd.h"

int main(int argc, char** argv) {
  char* buffer = NULL;
  const char* prompt = "308sh>";

  // parse the command arguments
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
    buffer = get_line(prompt, buffer);
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (pid != 0 && pid != -1) {
      if (WIFEXITED(status)) {
        printf("Child Process [%d] Exited: %d\n", pid, WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
        printf("Child Process [%d] Killed: %d\n", pid, WEXITSTATUS(status));
      }
    }
    run_command(buffer);
  }

}
