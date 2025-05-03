#include "game_controller.h"

#include <stdlib.h>

#include "tetris_controller.h"

GameInfo_t updateCurrentState() {
  fill_game_info_board();
  fill_game_info_figure_on_board();
  fill_game_info_table_zeros();
  fill_game_info_next_figure_on_info_table();
  fill_game_info_game_state();
  return get_game()->game_info;
}

void fill_game_info_board() {
  tetris_game_t* game = get_game();
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      game->game_info.field[i][j] = (int)game->board.matrix[i][j];
    }
  }
}

void fill_game_info_figure_on_board() {
  tetris_game_t* game = get_game();
  if (game->state != GAMEOVER && game->figure.figure_type != NON_SHAPE) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      int cur_x = game->figure.coordinates[i][0];
      int cur_y = game->figure.coordinates[i][1];
      game->game_info.field[cur_y][cur_x] = 1;
    }
  }
}

void fill_game_info_table_zeros() {
  tetris_game_t* game = get_game();
  for (int i = 0; i < INFO_FIGURE_BOARD_ROWS; i++) {
    for (int j = 0; j < INFO_FIGURE_BOARD_COLS; j++) {
      game->game_info.next[i][j] = 0;
    }
  }
}

void fill_game_info_game_state() {
  tetris_game_t* game = get_game();
  game->game_info.level = game->level;
  game->game_info.score = game->score;
  switch (game->state) {
    case PAUSE_STATE:
      game->game_info.pause = PAUSE_INT_ENUM;
      break;
    case START:
      game->game_info.pause = START_INT_ENUM;
      break;
    case GAMEOVER:
      game->game_info.pause = GAMEOVER_INT_ENUM;
      break;
    case EXIT_STATE:
      game->game_info.pause = EXIT_GAME_INT_ENUM;
      break;
    default:
      game->game_info.pause = -1;
      break;
  }
  game->game_info.high_score = game->high_score;
}

void fill_game_info_next_figure_on_info_table() {
  tetris_game_t* game = get_game();
  if (game->next_figure.figure_type != NON_SHAPE) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      int cur_x = game->next_figure.coordinates[i][0];
      int cur_y = game->next_figure.coordinates[i][1];
      game->game_info.next[cur_y][cur_x] = 1;
    }
  }
}

tetris_game_t* get_game() {
  static tetris_game_t game;
  return &game;
}

void init_game() {
  srand(time(NULL));
  tetris_game_t* game = get_game();
  init_board(&(game->board));
  init_empty_figure(&(game->figure));
  init_empty_figure(&(game->next_figure));
  game->state = START;
  game->game_info.field = alloc_matrix(BOARD_ROWS, BOARD_COLUMNS);
  game->game_info.next =
      alloc_matrix(INFO_FIGURE_BOARD_ROWS, INFO_FIGURE_BOARD_COLS);
}

void destroy_game() {
  tetris_game_t* game = get_game();

  for (size_t i = 0; i < BOARD_ROWS; i++) {
    free(game->game_info.field[i]);
  }
  free(game->game_info.field);

  for (size_t i = 0; i < INFO_FIGURE_BOARD_ROWS; i++) {
    free(game->game_info.next[i]);
  }
  free(game->game_info.next);
}

int** alloc_matrix(int rows, int columns) {
  int** matrix = NULL;
  matrix = malloc(rows * sizeof(int*));
  if (matrix != NULL) {
    int i = 0;
    bool is_error = false;
    while (!is_error && i < rows) {
      matrix[i] = calloc(sizeof(int), columns);
      is_error = matrix[i] == NULL;
      i++;
    }

    if (is_error) {
      for (int j = 0; j < i - 1; j++) {
        free(matrix[j]);
      }
      free(matrix);
      matrix = NULL;
    }
  }
  return matrix;
}
