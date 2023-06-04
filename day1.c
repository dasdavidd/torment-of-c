#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int highest = 0;

  file = fopen("input1", "r");
  int current = 0;

  if (file != NULL) {
    while ((read = getline(&line, &len, file)) != -1) {
      if (strcmp(line, "\n") == 0) {
        if (current > highest) {
          highest = current;
        }
        current = 0;
      } else {
        current = current + atoi(line);
      }
    }
  }
  printf("%d", highest);
  fclose(file);
}
