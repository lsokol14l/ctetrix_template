#include "tetris_controller.h"

#include <math.h>

#include "services/board_service.h"
#include "services/figure_service.h"
#include "utils/action_validators.h"
#include "utils/board_validators.h"

void rotate_figure_if_possible(figure_t* figure, const board_t* board) {
  figure_t next_figure = {0};
  copy_figure(figure, &next_figure);

  rotate_figure(&next_figure);
  adjust_coordinates_on_board(&next_figure);
  update_coordinate_if_possible(&next_figure, figure, board);
}

void adjust_coordinates_on_board(figure_t* figure) {
  if (!is_coordinates_in_board(figure->coordinates, FIGURE_SIZE)) {
    int offset =
        get_offset_for_inscribed_horizontal_coord(0, BOARD_COLUMNS - 1, figure);
    move_figure(offset, 0, figure);

    offset = get_offset_for_inscribed_vertical_coord(0, BOARD_ROWS - 1, figure);
    if (offset < 0) {
      move_figure(0, offset, figure);
    }
  }
}

void move_horizontal_figure_if_possible(figure_t* figure, const board_t* board,
                                        UserAction_t moving_signal) {
  if (is_horizontal_move_signal(moving_signal)) {
    figure_t next_figure = {0};
    copy_figure(figure, &next_figure);

    int offset = (moving_signal == Right) ? 1 : -1;
    move_figure(offset, 0, &next_figure);

    update_coordinate_if_possible(&next_figure, figure, board);
  }
}

void move_down_once_if_possible(figure_t* figure, const board_t* board) {
  figure_t next_figure = {0};
  copy_figure(figure, &next_figure);

  move_figure(0, -1, &next_figure);
  update_coordinate_if_possible(&next_figure, figure, board);
}

void move_down_to_intersect(figure_t* figure, const board_t* board) {
  figure_t next_figure = {0};
  copy_figure(figure, &next_figure);

  move_figure(0, -1, &next_figure);

  while (update_coordinate_if_possible(&next_figure, figure, board)) {
    move_figure(0, -1, &next_figure);
  }
}

bool update_coordinate_if_possible(const figure_t* src, figure_t* dst,
                                   const board_t* board) {
  bool is_update = false;
  if (is_coordinates_in_board(src->coordinates, FIGURE_SIZE) &&
      !is_intersect_coordinates(board, src->coordinates, FIGURE_SIZE)) {
    copy_figure(src, dst);
    is_update = true;
  }
  return is_update;
}

bool is_need_apply_figure_on_board(const figure_t* figure,
                                   const board_t* board) {
  bool is_need_update = false;
  figure_t check_figure = {0};
  copy_figure(figure, &check_figure);
  move_figure(0, -1, &check_figure);

  if (!(is_coordinates_in_board(check_figure.coordinates, FIGURE_SIZE) &&
        !is_intersect_coordinates(board, check_figure.coordinates,
                                  FIGURE_SIZE))) {
    is_need_update = true;
  }
  return is_need_update;
}

void apply_figure_on_board(figure_t* figure, board_t* board,
                           size_t* count_distruction_row) {
  *count_distruction_row = 0;

  figure_t check_figure = {0};
  copy_figure(figure, &check_figure);
  move_figure(0, -1, &check_figure);

  if (!(is_coordinates_in_board(check_figure.coordinates, FIGURE_SIZE) &&
        !is_intersect_coordinates(board, check_figure.coordinates,
                                  FIGURE_SIZE))) {
    fill_coordinates_on_board(board, figure->coordinates, FIGURE_SIZE);
    *count_distruction_row = destruction_filled_rows(board);
  }
}

bool init_figure_on_board(figure_t* figure, const board_t* board) {
  move_figure_to_abs_coordinate(BOARD_COLUMNS / 2 - 1, BOARD_ROWS - 1, figure);
  adjust_coordinates_on_board(figure);
  return !is_intersect_coordinates(board, figure->coordinates, FIGURE_SIZE);
}

void init_board(board_t* board) { clear_board(board); }

void spawn_figure(figure_t* figure) { generate_figure(figure); }

void init_empty_figure(figure_t* figure) {
  figure->center_x.int_coord = 0;
  figure->center_y.int_coord = 0;
  figure->figure_type = NON_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure->coordinates[i][0] = 0;
    figure->coordinates[i][1] = 0;
  }
}

void init_and_change_figures(figure_t* figure, figure_t* next_figure) {
  if (next_figure->figure_type == NON_SHAPE) {
    spawn_figure(figure);
  } else {
    copy_figure(next_figure, figure);
  }
  spawn_figure(next_figure);
  init_figure_on_info(next_figure);
}

void init_figures_as_empty(figure_t* figure, figure_t* next_figure) {
  if (figure->figure_type != NON_SHAPE) {
    init_empty_figure(figure);
  }

  if (next_figure->figure_type != NON_SHAPE) {
    init_empty_figure(next_figure);
  }
}

void init_figure_on_info(figure_t* figure) {
  move_figure_to_abs_coordinate(1, 1, figure);
}