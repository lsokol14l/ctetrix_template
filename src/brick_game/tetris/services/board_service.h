#ifndef __BOARD_SERVICE_H__
#define __BOARD_SERVICE_H__

#include <stddef.h>

#include "entities/board.h"

size_t get_list_fill_rows_index(const board_t* board, int row_indexes[],
                                size_t max_size);

void fill_board_from_bits(board_t* board, const int binares[BOARD_ROWS]);

void clear_row(board_t* board, int row_index);
void clear_board(board_t* board);
void shift_row_down_once(board_t* board, int start_index);

size_t destruction_filled_rows(board_t* board);

void set_coordinates(board_t* board, bool raise, const int coordinates[][2],
                     size_t size);

void fill_coordinates_on_board(board_t* board, const int coordinates[][2],
                               size_t size);

#endif  // __BOARD_SERVICE_H__
