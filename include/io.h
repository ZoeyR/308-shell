/*! \file
*/
#ifndef IO_H
#define IO_H

/*!
  \brief Gets a line of user input from stdin.

  The returned string will not include the newline character. The string will be
  large enough to contain all the text entered by the user and the string
  returned must be free'd.

  The prompt passed to get_line() will be displayed in the console.
  */
char* get_line(const char* prompt);


#endif
