#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part_1(FILE *stream) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int highest = 0;
  int current = 0;
  while ((read = getline(&line, &len, stream)) != -1) {
    if (strcmp(line, "\n") == 0) {
      if (current > highest) {
        highest = current;
      }
      current = 0;
    } else {
      current = current + atoi(line);
    }
  }
  printf("Day 1 result: %d\n", highest);
}

void part_2(FILE *stream) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int max_three[3] = {0, 0, 0};
  int length = sizeof(max_three) / sizeof(*max_three);
  int pos = 0;
  int current = 0;

  while ((read = getline(&line, &len, stream)) != -1) {
    if (strcmp(line, "\n") == 0) {
      for (int i = 0; i < length; i++) {
        if (max_three[i] <= max_three[pos]) {
          pos = i;
        }
      }

      if (max_three[pos] < current) {
        max_three[pos] = current;
      }

      current = 0;
    } else {
      current = current + atoi(line);
    }
  }
  int result = 0;
  for (int i = 0; i < length; i++) {
    result += max_three[i];
  }
  printf("Day 2 result: %d", result);
}

int main() {
  FILE *file;
  file = fopen("input1", "r");

  if (file != NULL) {
    part_1(file);
    // Equivalent to: fseek(file, 0L, SEEK_SET);
    rewind(file);
    part_2(file);
  }
  fclose(file);
}
