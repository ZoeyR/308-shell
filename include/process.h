/*! \file
*/
#ifndef PROCESS_H
#define PROCESS_H

#include "cmd.h"

/*!
  launches an executable file. If the last argument in the command is '&' the
  program is run in the background. Background processes do not block and allow
  the user to enter more commands.
  */
void launch_process(command_t* command);
#endif
