#include <stdio.h>
#include <stdlib.h>
#include "io.h"

// This function returns a command entered by the user on the command line not
// including the newline character. The string will be large enough to contain
// all the text entered by the user, the string returned must be free'd.
char* get_line(const char* prompt) {
  printf("%s", prompt);
  char c = 0;
  size_t i = 0;
  size_t stringlen = 10;
  char* buffer = (char*)malloc(stringlen * sizeof(char));

  while ((c = getc(stdin)) != '\n') {
    buffer[i++] = c;

    if (i >= stringlen) {
      stringlen *= 2;
      buffer = (char*)realloc(buffer, stringlen * sizeof(char));
    }
  }
  buffer[i] = '\0';

  return buffer;
}
