#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include <stdbool.h>
#include <time.h>

#define BOARD_ROWS 20
#define BOARD_COLUMNS 10

#define INFO_FIGURE_BOARD_ROWS 3
#define INFO_FIGURE_BOARD_COLS 5

#define PAUSE_INT_ENUM 1
#define GAMEOVER_INT_ENUM 0
#define START_INT_ENUM 2
#define EXIT_GAME_INT_ENUM 3

typedef enum {
  Start = 0,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif  // __OBJECTS_H__
