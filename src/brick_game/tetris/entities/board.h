#ifndef __BOARD_H__
#define __BOARD_H__

#include "objects.h"

typedef struct {
  bool matrix[BOARD_ROWS][BOARD_COLUMNS];
} board_t;

#endif  // __BOARD_H__