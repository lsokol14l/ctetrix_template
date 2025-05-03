#include "board_validators.h"

bool is_coordinates_in_board(const int coordinates[][2], size_t size) {
  bool in_board = true;
  for (size_t i = 0; in_board && i < size; i++) {
    if (!(0 <= coordinates[i][1] && coordinates[i][1] < BOARD_ROWS)) {
      in_board = false;
    }

    if (!(0 <= coordinates[i][0] && coordinates[i][0] < BOARD_COLUMNS)) {
      in_board = false;
    }
  }

  return in_board;
}

bool is_intersect_coordinates(const board_t *board, const int coordinates[][2],
                              size_t size) {
  bool is_intersect = false;
  for (size_t i = 0; !is_intersect && i < size; i++) {
    int checked_row = coordinates[i][1];
    int checked_col = coordinates[i][0];

    if (board->matrix[checked_row][checked_col]) {
      is_intersect = true;
    }
  }

  return is_intersect;
}
