#include <stdio.h>
#include <stdlib.h>
#include "io.h"

// This function fills a string buffer with the input from stdin up to but not including
// the newline character. This function will realloc buffer as necessary to fit all
// characters from stdin
char* get_line(const char* prompt, char* buffer) {
  printf("%s", prompt);
  char c = 0;
  size_t i = 0;
  size_t stringlen = 10;
  buffer = (char*)realloc(buffer, stringlen * sizeof(char));

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
