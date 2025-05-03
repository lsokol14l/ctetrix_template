
#include "entities/figure.h"
#include "services/board_service.h"
#include "services/figure_service.h"
#include "test_utils.h"
#include "utils/board_validators.h"

START_TEST(test_is_coordinates_in_board_horizontal) {
  figure_t res = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), false);

  move_figure(BOARD_COLUMNS / 2, 0, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  move_figure((BOARD_COLUMNS / 2) + 2, 0, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), false);
}
END_TEST;

START_TEST(test_is_coordinates_in_board_vertical) {
  figure_t res = {0};

  /*
   00
  00
  */
  res.figure_type = S_SHAPE;
  res.center_x.int_coord = 0;
  res.center_y.int_coord = 0;
  fill_figure_from_string(&res, "[-1 0] [0 0] [0 1] [1 1]");
  move_figure(1, -1, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), false);

  move_figure(0, BOARD_ROWS / 2, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);

  move_figure(0, (BOARD_ROWS / 2) + 2, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), false);
}
END_TEST;

START_TEST(test_is_intersect_coordinates_left_down) {
  board_t board = {0};
  int binares[] = {0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b1000000000};

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
  move_figure(1, 0, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), true);

  move_figure(1, 0, &res);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), false);

  move_figure(-1, 1, &res);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), false);
}
END_TEST;

START_TEST(test_is_intersect_coordinates_right_down) {
  board_t board = {0};
  int binares[] = {0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000001};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};

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

  move_figure(BOARD_COLUMNS - 1, 1, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), true);

  move_figure(-1, 0, &res);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), false);

  move_figure(1, 1, &res);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), false);
}
END_TEST;

START_TEST(test_is_intersect_coordinates_right_up) {
  board_t board = {0};
  int binares[] = {0b0000000001, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};

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

  move_figure(BOARD_COLUMNS - 1, BOARD_ROWS - 3, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), true);

  move_figure(-1, 0, &res);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), false);

  move_figure(1, -1, &res);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), false);
}
END_TEST;

START_TEST(test_is_intersect_coordinates_left_up) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  figure_t res = {0};

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

  move_figure(0, BOARD_ROWS - 3, &res);
  ck_assert_int_eq(is_coordinates_in_board(res.coordinates, 4), true);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), true);

  move_figure(1, 0, &res);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), false);

  move_figure(-1, -1, &res);
  ck_assert_int_eq(is_intersect_coordinates(&board, res.coordinates, 4), false);
}
END_TEST;

TCase *get_board_validators_test_case() {
  TCase *tc = tcase_create("board_validators");

  tcase_add_test(tc, test_is_coordinates_in_board_horizontal);
  tcase_add_test(tc, test_is_coordinates_in_board_vertical);

  tcase_add_test(tc, test_is_intersect_coordinates_left_down);
  tcase_add_test(tc, test_is_intersect_coordinates_right_down);
  tcase_add_test(tc, test_is_intersect_coordinates_right_up);
  tcase_add_test(tc, test_is_intersect_coordinates_left_up);

  return tc;
}
