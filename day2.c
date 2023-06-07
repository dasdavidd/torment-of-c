#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *buffer = 0;
  long length;

  FILE *file;
  file = fopen("./input2", "rb");

  if (file == NULL) {
    exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);
  buffer = malloc(length);

  if (buffer == NULL) {
    exit(EXIT_FAILURE);
  }

  int ret = fread(buffer, length, length, file);
  if (ret != 1) {
    exit(EXIT_FAILURE);
  }
  fclose(file);

  char *del = "\n";
  char *line = strtok(buffer, del);

  // A: enemy rock
  // B: enemy paper
  // C: enemy scissor
  //
  // X: player rock (1 pts)
  // Y: player paper (2 pts)
  // Z: player scissor (3 pts)
  //
  // win -> 6
  // draw -> 3
  // loss -> 0
  //
  // points = result + choice
  // e.g. B Z -> win (6 pts) + scissor (3 pts)
  while (line != NULL) {
    printf("Line is: %s\n", line);
    line = strtok(NULL, del);
  }

  free(buffer);
  exit(EXIT_SUCCESS);
}
