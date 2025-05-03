#include "board_service.h"

#include <math.h>
#include <stdbool.h>

size_t get_list_fill_rows_index(const board_t* board, int row_indexes[],
                                size_t max_size) {
  size_t res = 0;
  int* cur_ptr = row_indexes;
  bool is_full_indexes = max_size == res;

  for (int i = 0; !is_full_indexes && i < BOARD_ROWS; i++) {
    bool is_filled = true;

    for (int j = 0; is_filled && j < BOARD_COLUMNS; j++) {
      if (!board->matrix[i][j]) {
        is_filled = false;
      }
    }

    if (is_filled) {
      *cur_ptr = i;
      cur_ptr++;
      res++;
    }

    is_full_indexes = max_size == res;
  }

  return res;
}

void clear_row(board_t* board, int row_index) {
  for (int i = 0; i < BOARD_COLUMNS; i++) {
    board->matrix[row_index][i] = false;
  }
}

void clear_board(board_t* board) {
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board->matrix[i][j] = false;
    }
  }
}

void shift_row_down_once(board_t* board, int start_index) {
  for (int i = fmax(1, start_index); i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board->matrix[i - 1][j] = board->matrix[i][j];
    }
  }
  clear_row(board, BOARD_ROWS - 1);
}

size_t destruction_filled_rows(board_t* board) {
  int row_index[BOARD_ROWS] = {0};
  size_t size = get_list_fill_rows_index(board, row_index, BOARD_ROWS);

  for (size_t i = 0; i < size; i++) {
    shift_row_down_once(board, row_index[i] + 1 - i);
  }
  return size;
}

void set_coordinates(board_t* board, bool raise, const int coordinates[][2],
                     size_t size) {
  for (size_t i = 0; i < size; i++) {
    int row = coordinates[i][1];
    int col = coordinates[i][0];
    board->matrix[row][col] = raise;
  }
}

void fill_coordinates_on_board(board_t* board, const int coordinates[][2],
                               size_t size) {
  set_coordinates(board, true, coordinates, size);
}

/*
int binares = {
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000000000,
0b0000100000,
0b1000101010,
}
*/

void fill_board_from_bits(board_t* board, const int binares[BOARD_ROWS]) {
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board->matrix[i][j] =
          (binares[BOARD_ROWS - i - 1] >> (BOARD_COLUMNS - j - 1)) & 1;
    }
  }
}
