#include "structures.h"
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

  // Go to the last byte so we know the size of the file.
  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);
  // Allocate a buffer to dump in the whole content of the file.
  buffer = malloc(length);

  if (buffer == NULL) {
    exit(EXIT_FAILURE);
  }

  int ret = fread(buffer, sizeof(*buffer), length, file);

  if (ret == 0) {
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

  ht_t *ht_hand_played = ht_create();
  int xptr = 1;

  ht_set(ht_hand_played, "X", &xptr);
  ht_set(ht_hand_played, "Y", &xptr);
  ht_set(ht_hand_played, "Z", &xptr);

  printf("Current size should be 3. It's actually %zu",
         ht_length(ht_hand_played));

  while (line != NULL) {
    char hand[sizeof(*line)];
    char *saveptr;

    strcpy(hand, line);
    char *play = strtok_r(hand, " ", &saveptr);

    while (play != NULL) {
      play = strtok_r(NULL, " ", &saveptr);
    }
    line = strtok(NULL, del);
  }

  ht_destroy(ht_hand_played);
  free(buffer);
  exit(EXIT_SUCCESS);
}
