#include "controllers/tetris_controller.h"
#include "services/board_service.h"
#include "services/figure_service.h"
#include "test_controllers.h"
#include "utils/board_validators.h"

START_TEST(test_rotate_figure_if_possible_empty_board) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};

  figure_t estimated = {0};
  /*
   0
   0
   0
   0
  */
  res.figure_type = I_SHAPE;
  res.center_x.float_coord = 0.5f;
  res.center_y.float_coord = 0.5f;
  fill_figure_from_string(&res, "[0 2] [0 1] [0 0] [0 -1]");

  /*
  0000
  */
  estimated.figure_type = I_SHAPE;
  estimated.center_x.float_coord = 0.5f;
  estimated.center_y.float_coord = 0.5f;
  fill_figure_from_string(&estimated, "[3 2] [2 2] [1 2] [0 2]");

  move_figure(0, 1, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  rotate_figure_if_possible(&res, &board);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_figure(0, -1, &res);
  fill_figure_from_string(&estimated, "[3 1] [2 1] [1 1] [0 1]");

  rotate_figure_if_possible(&res, &board);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_rotate_figure_i_shape_up) {
  board_t board = {0};
  int binares[] = {0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};

  figure_t estimated = {0};
  /*
  0000
  */
  res.figure_type = I_SHAPE;
  res.center_x.float_coord = 0.5f;
  res.center_y.float_coord = -0.5f;
  fill_figure_from_string(&res, "[2 0] [1 0] [0 0] [-1 0]");
  move_figure(5, BOARD_ROWS - 1, &res);
  rotate_figure_if_possible(&res, &board);

  estimated.figure_type = I_SHAPE;
  fill_figure_from_string(&estimated, "[6 16] [6 17] [6 18] [6 19]");

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_rotate_figure_if_possible_intersect_in_other_figure) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0001000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};

  figure_t estimated = {0};
  /*
   0
   0
   0
   0
  */
  res.figure_type = I_SHAPE;
  res.center_x.float_coord = 0.5f;
  res.center_y.float_coord = 0.5f;
  fill_figure_from_string(&res, "[0 2] [0 1] [0 0] [0 -1]");

  /*
   0
   0
   0
   0
  */
  estimated.figure_type = I_SHAPE;
  estimated.center_x.float_coord = 0.5f;
  estimated.center_y.float_coord = 0.5f;
  fill_figure_from_string(&estimated, "[0 3] [0 2] [0 1] [0 0]");

  move_figure(0, 1, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  rotate_figure_if_possible(&res, &board);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_move_horizontal_figure_if_possible) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};
  figure_t estimated = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  /*
   00
  00
  */
  estimated.figure_type = S_SHAPE;
  estimated.center_x.int_coord = 0;
  estimated.center_y.int_coord = 0;
  fill_figure_from_string(&estimated, "[1 0] [2 0] [2 1] [3 1]");

  move_figure(3, 0, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  move_horizontal_figure_if_possible(&res, &board, Left);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  fill_figure_from_string(&estimated, "[0 0] [1 0] [1 1] [2 1]");

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  move_horizontal_figure_if_possible(&res, &board, Left);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  move_horizontal_figure_if_possible(&res, &board, Left);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_figure(BOARD_COLUMNS - 4, 0, &res);
  fill_figure_from_string(&estimated, "[6 0] [7 0] [7 1] [8 1]");

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_horizontal_figure_if_possible(&res, &board, Right);

  fill_figure_from_string(&estimated, "[7 0] [8 0] [8 1] [9 1]");
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_horizontal_figure_if_possible(&res, &board, Right);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_move_horizontal_figure_if_possible_other_figures) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000100000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};
  figure_t estimated = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  /*
   00
  00
  */
  estimated.figure_type = S_SHAPE;
  estimated.center_x.int_coord = 0;
  estimated.center_y.int_coord = 0;
  fill_figure_from_string(&estimated, "[5 2] [6 2] [6 3] [7 3]");

  move_figure(6, 2, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_horizontal_figure_if_possible(&res, &board, Left);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_horizontal_figure_if_possible(&res, &board, Right);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_move_down_to_possible) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};
  figure_t estimated = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  /*
   00
  00
  */
  estimated.figure_type = S_SHAPE;
  estimated.center_x.int_coord = 0;
  estimated.center_y.int_coord = 0;
  fill_figure_from_string(&estimated, "[2 0] [3 0] [3 1] [4 1]");

  move_figure(3, 8, &res);

  move_down_to_intersect(&res, &board);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_down_to_intersect(&res, &board);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_move_down_to_possible_with_other_details) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000100000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};
  figure_t estimated = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  /*
   00
  00
  */
  estimated.figure_type = S_SHAPE;
  estimated.center_x.int_coord = 0;
  estimated.center_y.int_coord = 0;
  fill_figure_from_string(&estimated, "[2 2] [3 2] [3 3] [4 3]");

  move_figure(3, 8, &res);

  move_down_to_intersect(&res, &board);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_down_to_intersect(&res, &board);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_move_down_to_possible_with_other_details_if_not_possible) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000100000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};
  figure_t estimated = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  /*
   00
  00
  */
  estimated.figure_type = S_SHAPE;
  estimated.center_x.int_coord = 0;
  estimated.center_y.int_coord = 0;
  fill_figure_from_string(&estimated, "[2 2] [3 2] [3 3] [4 3]");

  move_figure(3, 2, &res);

  move_down_to_intersect(&res, &board);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_init_figure_on_board) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000100000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};
  figure_t estimated = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  /*
   00
  00
  */
  estimated.figure_type = S_SHAPE;
  estimated.center_x.int_coord = 4;
  estimated.center_y.int_coord = 18;
  fill_figure_from_string(&estimated, "[3 18] [4 18] [4 19] [5 19]");

  move_figure(3, 8, &res);

  ck_assert_int_eq(init_figure_on_board(&res, &board), true);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
  ck_assert_int_eq(res.center_x.int_coord, estimated.center_x.int_coord);
  ck_assert_int_eq(res.center_y.int_coord, estimated.center_y.int_coord);
}
END_TEST;

START_TEST(test_init_figure_on_board_not_possible) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000100000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000100000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  move_figure(3, 8, &res);

  ck_assert_int_eq(init_figure_on_board(&res, &board), false);
}
END_TEST;

START_TEST(test_apply_figure_on_board) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000001000, 0b0000000000, 0b1111101111};

  fill_board_from_bits(&board, binares);

  board_t estimated = {0};
  int est_arr[] = {0b0000000000, 0b1000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000010, 0b0000101000, 0b0000110000};

  fill_board_from_bits(&estimated, est_arr);

  figure_t res = {0};
  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  rotate_figure(&res);
  move_figure(4, 1, &res);

  size_t count_distruction_row;

  apply_figure_on_board(&res, &board, &count_distruction_row);

  ck_assert_int_eq(count_distruction_row, 1);

  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      ck_assert_int_eq(board.matrix[i][j], estimated.matrix[i][j]);
    }
  }
}
END_TEST;

START_TEST(test_apply_figure_on_board_without_distort) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000001000, 0b0000000000, 0b1110101111};

  fill_board_from_bits(&board, binares);

  board_t estimated = {0};
  int est_arr[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000101000, 0b0000110000, 0b1110111111};

  fill_board_from_bits(&estimated, est_arr);

  figure_t res = {0};
  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  rotate_figure(&res);
  move_figure(4, 1, &res);

  size_t count_distruction_row;

  apply_figure_on_board(&res, &board, &count_distruction_row);

  ck_assert_int_eq(count_distruction_row, 0);

  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      ck_assert_int_eq(board.matrix[i][j], estimated.matrix[i][j]);
    }
  }
}
END_TEST;

START_TEST(test_apply_figure_on_board_not_apply) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000001000, 0b0000000000, 0b1110101111};

  fill_board_from_bits(&board, binares);

  board_t estimated = {0};
  int est_arr[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000001000, 0b0000000000, 0b1110101111};

  fill_board_from_bits(&estimated, est_arr);

  figure_t res = {0};
  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  rotate_figure(&res);
  move_figure(4, 2, &res);

  size_t count_distruction_row;

  apply_figure_on_board(&res, &board, &count_distruction_row);

  ck_assert_int_eq(count_distruction_row, 0);

  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      ck_assert_int_eq(board.matrix[i][j], estimated.matrix[i][j]);
    }
  }
}
END_TEST;

START_TEST(test_move_down_once_to_possible) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0001111111, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};
  figure_t estimated = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  /*
   00
  00
  */
  estimated.figure_type = S_SHAPE;
  estimated.center_x.int_coord = 0;
  estimated.center_y.int_coord = 0;
  fill_figure_from_string(&estimated, "[2 7] [3 7] [3 8] [4 8]");

  move_figure(3, 8, &res);

  move_down_once_if_possible(&res, &board);

  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_down_once_if_possible(&res, &board);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_is_need_apply_figure_on_board) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0001111111, 0b0000000000, 0b0000000000,
                   0b0000000010, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  /*
   00
  00
  */

  move_figure(3, 8, &res);
  ck_assert_int_eq(is_need_apply_figure_on_board(&res, &board), false);

  move_down_once_if_possible(&res, &board);
  ck_assert_int_eq(is_need_apply_figure_on_board(&res, &board), true);
}
END_TEST;

START_TEST(test_is_init_empty_figure) {
  figure_t res = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  init_empty_figure(&res);
  ck_assert_int_eq(res.center_x.int_coord, 0);
  ck_assert_int_eq(res.center_y.int_coord, 0);
  ck_assert_int_eq(res.figure_type, NON_SHAPE);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], 0);
    ck_assert_int_eq(res.coordinates[i][1], 0);
  }
}
END_TEST;

TCase *get_tetris_controller_test_case() {
  TCase *tc = tcase_create("tetris_controller");

  tcase_add_test(tc, test_rotate_figure_if_possible_empty_board);
  tcase_add_test(tc, test_rotate_figure_i_shape_up);
  tcase_add_test(tc, test_rotate_figure_if_possible_intersect_in_other_figure);

  tcase_add_test(tc, test_move_horizontal_figure_if_possible);
  tcase_add_test(tc, test_move_horizontal_figure_if_possible_other_figures);

  tcase_add_test(tc, test_move_down_to_possible);
  tcase_add_test(tc, test_move_down_to_possible_with_other_details);
  tcase_add_test(tc,
                 test_move_down_to_possible_with_other_details_if_not_possible);

  tcase_add_test(tc, test_init_figure_on_board);
  tcase_add_test(tc, test_init_figure_on_board_not_possible);

  tcase_add_test(tc, test_apply_figure_on_board);
  tcase_add_test(tc, test_apply_figure_on_board_without_distort);
  tcase_add_test(tc, test_apply_figure_on_board_not_apply);

  tcase_add_test(tc, test_move_down_once_to_possible);

  tcase_add_test(tc, test_is_need_apply_figure_on_board);
  tcase_add_test(tc, test_is_init_empty_figure);

  return tc;
}