#include "score_controller.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "tetris_backend_defines.h"

void add_to_game_score(int *score, size_t count_distruction_rows) {
  int added_score = count_distruction_rows == 0 ? 0 : ADDED_SCORE;
  if (count_distruction_rows > 0) {
    for (size_t i = 0; i < count_distruction_rows - 1; i++) {
      added_score = (added_score * 2) + ADDED_SCORE;
    }
  }
  *score += added_score;
}

int get_level(int score) {
  return fmin(MAX_LEVEL, (score / SCORE_PER_LEVEL) + 1);
}

void update_level(int score, int *level) { *level = get_level(score); }

void init_game_info(int *score, int *level) {
  *score = 0;
  *level = 1;
}

int get_high_score(const char *filename) {
  int high_score = 0;
  bool is_error = 0;
  FILE *file = NULL;

  const char *home_dir = getenv("HOME");
  is_error = home_dir == NULL;

  if (!is_error) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s/%s", home_dir, GAME_FOLDER, filename);
    file = fopen(path, "r");
    is_error = file == NULL;
  }

  if (!is_error) {
    is_error = fscanf(file, "%d", &high_score) != 1;
  }

  if (file != NULL) {
    fclose(file);
  }

  return is_error ? 0 : high_score;
}

void set_high_score_if_needed(int high_score, const char *filename) {
  if (high_score > get_high_score(filename)) {
    bool is_error = 0;
    FILE *file = NULL;
    char path[256];

    const char *home_dir = getenv("HOME");
    is_error = home_dir == NULL;
    if (!is_error) {
      snprintf(path, sizeof(path), "%s/%s", home_dir, GAME_FOLDER);

      struct stat st = {0};
      is_error = stat(path, &st) == -1 && mkdir(path, 0755) != 0;
    }

    if (!is_error) {
      strcat(path, "/");
      strcat(path, filename);
      file = fopen(path, "w");
      is_error = file == NULL;
    }

    if (!is_error) {
      fprintf(file, "%d", high_score);
    }
    if (file != NULL) {
      fclose(file);
    }
  }
}