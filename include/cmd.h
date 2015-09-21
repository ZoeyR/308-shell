#ifndef CMD_H
#define CMD_H

#include <stdlib.h>

static const char* EXIT = "exit";
static const char* PID = "pid";
static const char* PPID = "ppid";
static const char* CD = "cd";
static const char* PWD = "pwd";
static const char* SET = "set";
static const char* GET = "get";

typedef struct {
  char** args;
  size_t size;
} cmd_args_t;

typedef struct {
  char* bin;
  cmd_args_t args;
} command_t;

int run_command(command_t* cmd);

void sh_exit();
void sh_pid();
void sh_ppid();
void sh_cd(cmd_args_t args);
void sh_pwd();
void sh_set(cmd_args_t args);
void sh_get(cmd_args_t args);

// command must be free'd after creation.
command_t make_command(char* input);
void free_command(command_t* cmd);
#endif
