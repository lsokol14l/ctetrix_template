#include "objects.h"
#include "services/figure_service.h"
#include "test_services.h"

START_TEST(test_rotate_figure) {
  figure_t res = {0};
  figure_t estimated = {0};

  /*
  000
    0
  */
  res.figure_type = J_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [1 0] [1 -1]");

  /*
   0
   0
  00
  */
  estimated.figure_type = J_SHAPE;
  estimated.center_x.int_coord = 0;
  estimated.center_y.int_coord = 0;
  fill_figure_from_string(&estimated, "[0 1] [0 0] [0 -1] [-1 -1]");

  rotate_figure(&res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_int_eq(res.center_x.int_coord, estimated.center_x.int_coord);
  ck_assert_int_eq(res.center_y.int_coord, estimated.center_y.int_coord);
}
END_TEST;

START_TEST(test_multi_rotate_figure) {
  figure_t res = {0};
  figure_t estimated = {0};

  /*
  000
    0
  */
  res.figure_type = J_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [1 0] [1 -1]");

  /*
  0
  000
  */
  estimated.figure_type = J_SHAPE;
  estimated.center_x.int_coord = 0;
  estimated.center_y.int_coord = 0;
  fill_figure_from_string(&estimated, "[1 0] [0 0] [-1 0] [-1 1]");

  rotate_figure(&res);
  rotate_figure(&res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  fill_figure_from_string(&estimated, "[0 -1] [0 0] [0 1] [1 1]");

  rotate_figure(&res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_int_eq(res.center_x.int_coord, estimated.center_x.int_coord);
  ck_assert_int_eq(res.center_y.int_coord, estimated.center_y.int_coord);
}
END_TEST;

START_TEST(test_rotate_i_figure) {
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

  estimated.figure_type = I_SHAPE;
  estimated.center_x.float_coord = 0.5f;
  estimated.center_y.float_coord = 0.5f;
  fill_figure_from_string(&estimated, "[2 1] [1 1] [0 1] [-1 1]");

  rotate_figure(&res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  fill_figure_from_string(&estimated, "[1 -1] [1 0] [1 1] [1 2]");

  rotate_figure(&res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  fill_figure_from_string(&estimated, "[-1 0] [0 0] [1 0] [2 0]");

  rotate_figure(&res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(res.figure_type, estimated.figure_type);

  ck_assert_float_eq_tol(res.center_x.float_coord,
                         estimated.center_x.float_coord, 0.0001);
  ck_assert_float_eq_tol(res.center_y.float_coord,
                         estimated.center_y.float_coord, 0.0001);
}
END_TEST;

START_TEST(test_move_figure) {
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

  estimated.figure_type = S_SHAPE;
  estimated.center_x.int_coord = 5;
  estimated.center_y.int_coord = -3;
  fill_figure_from_string(&estimated, "[4 -3] [5 -3] [5 -2] [6 -2]");

  move_figure(5, -3, &res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_int_eq(res.center_x.int_coord, estimated.center_x.int_coord);
  ck_assert_int_eq(res.center_y.int_coord, estimated.center_y.int_coord);
}
END_TEST;

START_TEST(test_move_figure_to_abs_coordinate_float) {
  figure_t res = {0};
  figure_t estimated = {0};

  /*
  00
  00
  */
  res.figure_type = O_SHAPE;
  res.center_x.float_coord = 0.5;
  res.center_y.float_coord = 0.5;
  fill_figure_from_string(&res, "[1 1] [1 0] [0 0] [0 1]");

  estimated.figure_type = O_SHAPE;
  estimated.center_x.float_coord = 10.5;
  estimated.center_y.float_coord = 5.5;
  fill_figure_from_string(&estimated, "[11 6] [11 5] [10 5] [10 6]");

  move_figure(5, -3, &res);
  move_figure_to_abs_coordinate(10, 5, &res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_int_eq(res.center_x.float_coord, estimated.center_x.float_coord);
  ck_assert_int_eq(res.center_y.float_coord, estimated.center_y.float_coord);

  move_figure(-3, 10, &res);
  move_figure_to_abs_coordinate(10, 5, &res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_int_eq(res.center_x.float_coord, estimated.center_x.float_coord);
  ck_assert_int_eq(res.center_y.float_coord, estimated.center_y.float_coord);

  move_figure(0, 0, &res);
  move_figure_to_abs_coordinate(10, 5, &res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_int_eq(res.center_x.float_coord, estimated.center_x.float_coord);
  ck_assert_int_eq(res.center_y.float_coord, estimated.center_y.float_coord);
}
END_TEST;

START_TEST(test_move_figure_to_abs_coordinate_float_neg) {
  figure_t res = {0};
  figure_t estimated = {0};

  /*
  00
  00
  */
  res.figure_type = O_SHAPE;
  res.center_x.float_coord = 0.5;
  res.center_y.float_coord = 0.5;
  fill_figure_from_string(&res, "[1 1] [1 0] [0 0] [0 1]");

  estimated.figure_type = O_SHAPE;
  estimated.center_x.float_coord = -7.5;
  estimated.center_y.float_coord = -4.5;
  fill_figure_from_string(&estimated, "[-7 -4] [-7 -5] [-8 -5] [-8 -4]");

  move_figure(5, -3, &res);
  move_figure_to_abs_coordinate(-8, -5, &res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_int_eq(res.center_x.float_coord, estimated.center_x.float_coord);
  ck_assert_int_eq(res.center_y.float_coord, estimated.center_y.float_coord);
}
END_TEST;

START_TEST(test_move_and_rotate_figure) {
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

  estimated.figure_type = S_SHAPE;
  estimated.center_x.int_coord = 5;
  estimated.center_y.int_coord = -3;
  fill_figure_from_string(&estimated, "[5 -2] [5 -3] [6 -3] [6 -4]");

  move_figure(5, -3, &res);
  rotate_figure(&res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_int_eq(res.center_x.int_coord, estimated.center_x.int_coord);
  ck_assert_int_eq(res.center_y.int_coord, estimated.center_y.int_coord);
}
END_TEST;

START_TEST(test_rotate_and_move_i_figure) {
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

  estimated.figure_type = I_SHAPE;
  estimated.center_x.float_coord = -4.5f;
  estimated.center_y.float_coord = 3.5f;
  fill_figure_from_string(&estimated, "[-3 4] [-4 4] [-5 4] [-6 4]");

  move_figure(-5, 3, &res);
  rotate_figure(&res);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  ck_assert_int_eq(res.figure_type, estimated.figure_type);

  ck_assert_float_eq_tol(res.center_x.float_coord,
                         estimated.center_x.float_coord, 0.0001);
  ck_assert_float_eq_tol(res.center_y.float_coord,
                         estimated.center_y.float_coord, 0.0001);
}
END_TEST;

START_TEST(test_copy_figure) {
  figure_t res = {0};
  figure_t estimated = {0};

  /*
   0
   0
   0
   0
  */
  estimated.figure_type = S_SHAPE;
  estimated.center_x.int_coord = 0;
  estimated.center_y.int_coord = 0;
  fill_figure_from_string(&estimated, "[-1 0] [0 0] [0 1] [1 1]");

  copy_figure(&estimated, &res);

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_int_eq(res.center_x.int_coord, estimated.center_x.int_coord);
  ck_assert_int_eq(res.center_y.int_coord, estimated.center_y.int_coord);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_figure(1, 1, &res);

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_int_ne(res.center_x.int_coord, estimated.center_x.int_coord);
  ck_assert_int_ne(res.center_y.int_coord, estimated.center_y.int_coord);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_ne(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_ne(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_copy_figure_i_shape) {
  figure_t res = {0};
  figure_t estimated = {0};

  /*
   0
   0
   0
   0
  */
  estimated.figure_type = I_SHAPE;
  estimated.center_x.float_coord = 0.5f;
  estimated.center_y.float_coord = 0.5f;
  fill_figure_from_string(&estimated, "[0 2] [0 1] [0 0] [0 -1]");

  copy_figure(&estimated, &res);

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_float_eq_tol(res.center_x.float_coord,
                         estimated.center_x.float_coord, 0.01);
  ck_assert_float_eq_tol(res.center_y.float_coord,
                         estimated.center_y.float_coord, 0.01);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_eq(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_eq(res.coordinates[i][1], estimated.coordinates[i][1]);
  }

  move_figure(1, 1, &res);

  ck_assert_int_eq(res.figure_type, estimated.figure_type);
  ck_assert_float_ne_tol(res.center_x.float_coord,
                         estimated.center_x.float_coord, 0.01);
  ck_assert_float_ne_tol(res.center_y.float_coord,
                         estimated.center_y.float_coord, 0.01);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_int_ne(res.coordinates[i][0], estimated.coordinates[i][0]);
    ck_assert_int_ne(res.coordinates[i][1], estimated.coordinates[i][1]);
  }
}
END_TEST;

START_TEST(test_get_offset_for_inscribed_coord_horizontal) {
  figure_t res = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  ck_assert_int_eq(
      get_offset_for_inscribed_horizontal_coord(0, BOARD_COLUMNS - 1, &res), 1);

  move_figure(0, 2, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_horizontal_coord(0, BOARD_COLUMNS - 1, &res), 1);

  move_figure(-3, 0, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_horizontal_coord(0, BOARD_COLUMNS - 1, &res), 4);

  move_figure(4 + BOARD_COLUMNS, 0, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_horizontal_coord(0, BOARD_COLUMNS - 1, &res),
      -3);

  move_figure(-3, 0, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_horizontal_coord(0, BOARD_COLUMNS - 1, &res), 0);

  move_figure(-3, 0, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_horizontal_coord(0, BOARD_COLUMNS - 1, &res), 0);
}
END_TEST;

START_TEST(test_get_offset_for_inscribed_coord_vertical) {
  figure_t res = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");

  move_figure(0, -1, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_vertical_coord(0, BOARD_ROWS - 1, &res), 1);

  move_figure(2, 0, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_vertical_coord(0, BOARD_ROWS - 1, &res), 1);

  move_figure(0, -3, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_vertical_coord(0, BOARD_ROWS - 1, &res), 4);

  move_figure(0, BOARD_ROWS + 4, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_vertical_coord(0, BOARD_ROWS - 1, &res), -2);

  move_figure(0, -3, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_vertical_coord(0, BOARD_ROWS - 1, &res), 0);

  move_figure(0, -3, &res);
  ck_assert_int_eq(
      get_offset_for_inscribed_vertical_coord(0, BOARD_ROWS - 1, &res), 0);
}
END_TEST;

START_TEST(test_figure_generator) {
  figure_t res = {0};

  for (int i = 0; i < 40; i++) {
    res.figure_type = NON_SHAPE;
    res.center_x.int_coord = 0;
    res.center_y.int_coord = 0;
    fill_figure_from_string(&res, "[-20 -20] [-20 -20] [-20 -20] [-20 -20]");
    generate_figure(&res);
    ck_assert_int_ne(res.figure_type, NON_SHAPE);
    for (int j = 0; j < FIGURE_SIZE; j++) {
      ck_assert_int_ne(res.coordinates[j][0], -20);
      ck_assert_int_ne(res.coordinates[j][1], -20);
    }
  }
}
END_TEST;

TCase *get_figure_service_test_case() {
  TCase *tc = tcase_create("figure_service");

  tcase_add_test(tc, test_rotate_figure);
  tcase_add_test(tc, test_multi_rotate_figure);
  tcase_add_test(tc, test_rotate_i_figure);

  tcase_add_test(tc, test_move_figure);
  tcase_add_test(tc, test_move_figure_to_abs_coordinate_float);
  tcase_add_test(tc, test_move_figure_to_abs_coordinate_float_neg);
  tcase_add_test(tc, test_move_and_rotate_figure);
  tcase_add_test(tc, test_rotate_and_move_i_figure);

  tcase_add_test(tc, test_copy_figure);
  tcase_add_test(tc, test_copy_figure_i_shape);

  tcase_add_test(tc, test_get_offset_for_inscribed_coord_horizontal);
  tcase_add_test(tc, test_get_offset_for_inscribed_coord_vertical);

  tcase_add_test(tc, test_figure_generator);

  return tc;
}
