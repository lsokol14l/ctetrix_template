#include "figure_service.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rotate_figure(figure_t* figure) {
  if (figure->figure_type == I_SHAPE) {
    rotate_float_figure(figure);
  } else if (figure->figure_type != O_SHAPE) {
    int x_center = figure->center_x.int_coord;
    int y_center = figure->center_y.int_coord;

    for (int i = 0; i < FIGURE_SIZE; i++) {
      int temp = figure->coordinates[i][0];

      figure->coordinates[i][0] =
          figure->coordinates[i][1] - y_center + x_center;
      figure->coordinates[i][1] = x_center - temp + y_center;
    }
  }
}

void rotate_float_figure(figure_t* figure) {
  float x_center = figure->center_x.float_coord;
  float y_center = figure->center_y.float_coord;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    float temp_x = (float)figure->coordinates[i][0];
    float temp_y = (float)figure->coordinates[i][1];

    float res_x = temp_y - y_center + x_center;
    float res_y = x_center - temp_x + y_center;

    figure->coordinates[i][0] =
        (int)(res_x < 0 ? (res_x - 0.5) : (res_x + 0.5));
    figure->coordinates[i][1] =
        (int)(res_y < 0 ? (res_y - 0.5) : (res_y + 0.5));
  }
}

void move_figure(int offset_x, int offset_y, figure_t* figure) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure->coordinates[i][0] += offset_x;
    figure->coordinates[i][1] += offset_y;
  }

  if (figure->figure_type == I_SHAPE || figure->figure_type == O_SHAPE) {
    figure->center_x.float_coord += (float)offset_x;
    figure->center_y.float_coord += (float)offset_y;
  } else {
    figure->center_x.int_coord += offset_x;
    figure->center_y.int_coord += offset_y;
  }
}
void move_int_figure_to_abs_coordinate(int x, int y, figure_t* figure) {
  int cur_x = figure->center_x.int_coord;
  int cur_y = figure->center_y.int_coord;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure->coordinates[i][0] = figure->coordinates[i][0] - cur_x + x;
    figure->coordinates[i][1] = figure->coordinates[i][1] - cur_y + y;
  }
  figure->center_x.int_coord = x;
  figure->center_y.int_coord = y;
}

void move_float_figure_to_abs_coordinate(int x, int y, figure_t* figure) {
  figure_t meta_figure = {0};

  meta_figure.figure_type = figure->figure_type;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    meta_figure.coordinates[i][0] = figure->coordinates[i][0];
    meta_figure.coordinates[i][1] = figure->coordinates[i][1];
  }

  meta_figure.center_x.int_coord = floor(figure->center_x.float_coord);
  meta_figure.center_y.int_coord = floor(figure->center_y.float_coord);

  float shift_floor_x =
      figure->center_x.float_coord - floor(figure->center_x.float_coord);

  float shift_floor_y =
      figure->center_y.float_coord - floor(figure->center_y.float_coord);

  move_int_figure_to_abs_coordinate(x, y, &meta_figure);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure->coordinates[i][0] = meta_figure.coordinates[i][0];
    figure->coordinates[i][1] = meta_figure.coordinates[i][1];
  }

  figure->center_x.float_coord = (float)x + shift_floor_x;
  figure->center_y.float_coord = (float)y + shift_floor_y;
}

void move_figure_to_abs_coordinate(int x, int y, figure_t* figure) {
  if (figure->figure_type == O_SHAPE || figure->figure_type == I_SHAPE) {
    move_float_figure_to_abs_coordinate(x, y, figure);
  } else {
    move_int_figure_to_abs_coordinate(x, y, figure);
  }
}

// [-1 0] [0 0] [1 0] [1 -1]
void fill_figure_from_string(figure_t* figure, const char* str) {
  const char* ptr = str;
  int len = 0;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    sscanf(ptr, "[%d %d]%n", figure->coordinates[i], figure->coordinates[i] + 1,
           &len);
    ptr += len;
    while (*ptr == ' ') {
      ptr++;
    }
  }
}

void copy_figure(const figure_t* src, figure_t* dst) {
  dst->figure_type = src->figure_type;

  if (src->figure_type == I_SHAPE) {
    dst->center_x.float_coord = src->center_x.float_coord;
    dst->center_y.float_coord = src->center_y.float_coord;
  } else {
    dst->center_x.float_coord = src->center_x.float_coord;
    dst->center_y.float_coord = src->center_y.float_coord;
  }

  for (int i = 0; i < FIGURE_SIZE; i++) {
    dst->coordinates[i][0] = src->coordinates[i][0];
    dst->coordinates[i][1] = src->coordinates[i][1];
  }
}

int get_offset_for_inscribed_coord(int start_coord, int end_coord,
                                   int coord_index, const figure_t* figure) {
  int min = start_coord;
  int max = end_coord;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    if (figure->coordinates[i][coord_index] < min) {
      min = figure->coordinates[i][coord_index];
    }
    if (figure->coordinates[i][coord_index] > max) {
      max = figure->coordinates[i][coord_index];
    }
  }

  int res = 0;

  if (min != start_coord) {
    res = start_coord - min;
  }
  if (max != end_coord) {
    res = end_coord - max;
  }

  return res;
}
int get_offset_for_inscribed_horizontal_coord(int start_coord, int end_coord,
                                              const figure_t* figure) {
  return get_offset_for_inscribed_coord(start_coord, end_coord, 0, figure);
}

int get_offset_for_inscribed_vertical_coord(int start_coord, int end_coord,
                                            const figure_t* figure) {
  return get_offset_for_inscribed_coord(start_coord, end_coord, 1, figure);
}

void fill_float_figure(figure_t* figure) {
  switch (figure->figure_type) {
    case I_SHAPE:
      figure->center_x.float_coord = 0.5f;
      figure->center_y.float_coord = -0.5f;
      fill_figure_from_string(figure, "[2 0] [1 0] [0 0] [-1 0]");
      break;
    case O_SHAPE:
      figure->center_x.float_coord = 0.5;
      figure->center_y.float_coord = 0.5;
      fill_figure_from_string(figure, "[1 1] [1 0] [0 0] [0 1]");
      break;
    default:
      break;
  }
}

void fill_int_figure(figure_t* figure) {
  figure->center_x.int_coord = 0;
  figure->center_y.int_coord = 0;

  switch (figure->figure_type) {
    case J_SHAPE:
      fill_figure_from_string(figure, "[-1 1] [-1 0] [0 0] [1 0]");
      break;
    case L_SHAPE:
      fill_figure_from_string(figure, "[-1 0] [0 0] [1 0] [1 1]");
      break;
    case S_SHAPE:
      fill_figure_from_string(figure, "[-1 0] [0 0] [0 1] [1 1]");
      break;
    case Z_SHAPE:
      fill_figure_from_string(figure, "[-1 1] [0 1] [0 0] [1 0]");
      break;
    case T_SHAPE:
      fill_figure_from_string(figure, "[0 0] [-1 0] [1 0] [0 1]");
      break;
    default:
      break;
  }
}

void generate_figure(figure_t* figure) {
  const int num_shapes = S_SHAPE + 1;
  figure_type_t type_for_new_figure = (figure_type_t)(rand() % num_shapes);

  figure->figure_type = type_for_new_figure;

  if (type_for_new_figure == I_SHAPE || type_for_new_figure == O_SHAPE) {
    fill_float_figure(figure);
  } else {
    fill_int_figure(figure);
  }
}