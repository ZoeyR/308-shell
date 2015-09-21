/*! \file
  \brief This files contains methods relevant to the creation and execution of
            commands.

    The shell provides the following built-in commands.
    - exit
      + closes the shell
    - pid
      + prints the shell's process id
    - ppid
      + prints the shell's parent process id
    - cd \<dir>
      + changes the working directory to \<dir>
    - pwd
      + prints the current working directory
    - set \<var> \<value>
      + sets the environment variable \<var> to \<value>
    - get \<var>
      + prints the value of environment variable \<var>

 */
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

/*!
  \brief holds the arguments for a command.

  args is a char** containing all the arguments for the command. By convention,
  the first element in args is the command itself. args is terminated by a
  NULL element.
 */
typedef struct {
  /*!
    char** containing all the arguments for the command. By convention,
    the first element in args is the command itself. args is terminated by a
    NULL element.
  */
  char** args;
  /*!
    Total size of args.
   */
  size_t size;
} cmd_args_t;

/*!
  \brief Represents a command to be executed by the shell.

  command_t should be created using make_command(). A command_t created using
  this method must be free'd using free_command().
 */
typedef struct {
  /*!
    bin is the first part of the text that was entered into the console, the
    shell will attempt to search the path to find an executable and if none is
    found, the bin will be interpreted as a literal path to a file.
   */
  char* bin;

  /*!
    args is the arguments for the command, it contains size information in
    addition to command arguments.
   */
  cmd_args_t args;
} command_t;

/*!
  \brief Creates a command_t.

  creates a command_t from a string typed into the shell. The command_t
  returned by this method must be free'd by free_command.

  ##Example

  ---
  ~~~{.c}
  const char* input_line = "ls --color=auto";
  command_t cmd = make_command(input_line);
  ~~~
 */
command_t make_command(char* input);

/*!
  \brief Frees a command_t from memory.

  Removes the cmd from the heap. This function should only be called if
  make_command() was used to create it.

  ##Example

  ---
  ~~~{.c}
  const char* input_line = "ls --color=auto";
  command_t cmd = make_command(input_line);

  free_command(&cmd)

  // This will cause a compile error because cmd has been free'd from memory.
  cmd.bin;
  ~~~
 */
void free_command(command_t* cmd);

void run_command(command_t* cmd);

void sh_exit();
void sh_pid();
void sh_ppid();
void sh_cd(cmd_args_t args);
void sh_pwd();
void sh_set(cmd_args_t args);
void sh_get(cmd_args_t args);




#endif
