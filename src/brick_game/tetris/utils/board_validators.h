#ifndef __BOARD_VALIDATORS_H__
#define __BOARD_VALIDATORS_H__

#include <stdbool.h>
#include <stddef.h>

#include "entities/board.h"

bool is_coordinates_in_board(const int coordinates[][2], size_t size);
bool is_intersect_coordinates(const board_t *board, const int coordinates[][2],
                              size_t size);

#endif  // __BOARD_VALIDATORS_H__
