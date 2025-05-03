#ifndef __FIGURE_H__
#define __FIGURE_H__

#define FIGURE_SIZE 4

typedef enum {
  I_SHAPE = 0,
  J_SHAPE,
  L_SHAPE,
  O_SHAPE,
  Z_SHAPE,
  T_SHAPE,
  S_SHAPE,
  NON_SHAPE
} figure_type_t;

typedef union {
  int int_coord;
  float float_coord;
} rotate_coordinate;

typedef struct {
  figure_type_t figure_type;
  rotate_coordinate center_x;
  rotate_coordinate center_y;
  int coordinates[FIGURE_SIZE][2];
} figure_t;

#endif  // __FIGURE_H__
