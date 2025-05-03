#ifndef __TETRIS_STATE_H__
#define __TETRIS_STATE_H__

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  EXIT_STATE,
  PAUSE_STATE
} tetris_state;

#endif  // __TETRIS_STATE_H__
