#include "services/board_service.h"
#include "test_services.h"

START_TEST(test_fill_board_from_bits_left_down) {
  board_t board = {0};
  int binares[] = {0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b1000000000};

  fill_board_from_bits(&board, binares);

  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      if (i == 0 && j == 0) {
        ck_assert_int_eq(board.matrix[i][j], 1);
      } else {
        ck_assert_int_eq(board.matrix[i][j], 0);
      }
    }
  }
}
END_TEST;

START_TEST(test_fill_board_from_bits_right_down) {
  board_t board = {0};
  int binares[] = {0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000001};

  fill_board_from_bits(&board, binares);
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      if (i == 0 && j == BOARD_COLUMNS - 1) {
        ck_assert_int_eq(board.matrix[i][j], 1);
      } else {
        ck_assert_int_eq(board.matrix[i][j], 0);
      }
    }
  }
}
END_TEST;

START_TEST(test_fill_board_from_bits_left_up) {
  board_t board = {0};
  int binares[] = {0b1000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      if (i == BOARD_ROWS - 1 && j == 0) {
        ck_assert_int_eq(board.matrix[i][j], 1);
      } else {
        ck_assert_int_eq(board.matrix[i][j], 0);
      }
    }
  }
}
END_TEST;

START_TEST(test_fill_board_from_bits_right_up) {
  board_t board = {0};
  int binares[] = {0b0000000001, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      if (i == BOARD_ROWS - 1 && j == BOARD_COLUMNS - 1) {
        ck_assert_int_eq(board.matrix[i][j], 1);
      } else {
        ck_assert_int_eq(board.matrix[i][j], 0);
      }
    }
  }
}
END_TEST;

START_TEST(test_get_list_fill_rows_index) {
  board_t board = {0};
  int binares[] = {0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b1111111111, 0b1111111111, 0b0000100000, 0b1000101010};

  fill_board_from_bits(&board, binares);

  int result[5] = {0};
  size_t res = get_list_fill_rows_index(&board, result, 5);
  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(result[0], 2);
  ck_assert_int_eq(result[1], 3);
}
END_TEST;

START_TEST(test_clear_row) {
  board_t board = {0};
  int binares[] = {0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b1111111111, 0b1111111111, 0b0000100000, 0b1000101010};

  fill_board_from_bits(&board, binares);
  clear_row(&board, 2);

  int result[5] = {0};
  size_t res = get_list_fill_rows_index(&board, result, 5);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(result[0], 3);
}
END_TEST;

START_TEST(test_shift_row_down_once) {
  board_t board = {0};
  int binares[] = {0b0000010000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b1111111111, 0b1111111111, 0b0000100000, 0b1000101010};

  fill_board_from_bits(&board, binares);
  shift_row_down_once(&board, 1);

  int result[5] = {0};
  size_t res = get_list_fill_rows_index(&board, result, 5);

  for (int i = 0; i < BOARD_COLUMNS; i++) {
    ck_assert_int_eq(board.matrix[BOARD_ROWS - 1][i], 0);
  }

  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(result[0], 1);
  ck_assert_int_eq(result[1], 2);
}
END_TEST;

START_TEST(test_shift_row_down_once_zero) {
  board_t board = {0};
  int binares[] = {0b0000010000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b1111111111, 0b1111111111, 0b0000100000, 0b1000101010};

  fill_board_from_bits(&board, binares);
  shift_row_down_once(&board, 0);

  int result[5] = {0};
  size_t res = get_list_fill_rows_index(&board, result, 5);

  for (int i = 0; i < BOARD_COLUMNS; i++) {
    ck_assert_int_eq(board.matrix[BOARD_ROWS - 1][i], 0);
  }

  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(result[0], 1);
  ck_assert_int_eq(result[1], 2);
}
END_TEST;

START_TEST(test_destruction_filled_rows) {
  board_t board = {0};
  int binares[] = {0b1111111111, 0b0000010000, 0b1111111111, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000010000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b1000101010, 0b0000010000,
                   0b1111111111, 0b1111111111, 0b0000100000, 0b1111111111};

  fill_board_from_bits(&board, binares);

  destruction_filled_rows(&board);

  int result[5] = {0};
  size_t res = get_list_fill_rows_index(&board, result, 5);

  ck_assert_int_eq(res, 0);
}
END_TEST;

START_TEST(test_set_coordinates) {
  board_t board = {0};
  int binares[] = {0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&board, binares);

  board_t estimated = {0};

  int est_arr[] = {0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000000000,
                   0b0000000000, 0b0000000000, 0b0000000000, 0b0000011000,
                   0b0000110000, 0b0000000000, 0b0000000000, 0b0000000000};

  fill_board_from_bits(&estimated, est_arr);

  int coordinates[4][2] = {{4, 3}, {5, 3}, {5, 4}, {6, 4}};

  set_coordinates(&board, true, coordinates, 4);

  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      ck_assert_int_eq(board.matrix[i][j], estimated.matrix[i][j]);
    }
  }
}
END_TEST;

START_TEST(test_set_coordinates_false) {
  board_t board = {0};
  int binares[] = {0b1111111111, 0b1111111111, 0b1111111111, 0b1111111111,
                   0b1111111111, 0b1111111111, 0b1111111111, 0b1111111111,
                   0b1111111111, 0b1111111111, 0b1111111111, 0b1111111111,
                   0b1111111111, 0b1111111111, 0b1111111111, 0b1111111111,
                   0b1111111111, 0b1111111111, 0b1111111111, 0b1111111111};

  fill_board_from_bits(&board, binares);

  board_t estimated = {0};

  int est_arr[] = {0b1111111111, 0b1111111111, 0b1111111111, 0b1111111111,
                   0b1111111111, 0b1111111111, 0b1111111111, 0b1111111111,
                   0b1111111111, 0b1111111111, 0b1111111111, 0b1111111111,
                   0b1111111111, 0b1111111111, 0b1111111111, 0b1111100111,
                   0b1111001111, 0b1111111111, 0b1111111111, 0b1111111111};

  fill_board_from_bits(&estimated, est_arr);

  int coordinates[4][2] = {{4, 3}, {5, 3}, {5, 4}, {6, 4}};

  set_coordinates(&board, 0, coordinates, 4);

  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      ck_assert_int_eq(board.matrix[i][j], estimated.matrix[i][j]);
    }
  }
}
END_TEST;

TCase *get_board_service_test_case() {
  TCase *tc = tcase_create("board_service");

  tcase_add_test(tc, test_fill_board_from_bits_left_down);
  tcase_add_test(tc, test_fill_board_from_bits_right_down);
  tcase_add_test(tc, test_fill_board_from_bits_left_up);
  tcase_add_test(tc, test_fill_board_from_bits_right_up);

  tcase_add_test(tc, test_get_list_fill_rows_index);
  tcase_add_test(tc, test_clear_row);
  tcase_add_test(tc, test_shift_row_down_once);
  tcase_add_test(tc, test_shift_row_down_once_zero);
  tcase_add_test(tc, test_destruction_filled_rows);
  tcase_add_test(tc, test_set_coordinates);
  tcase_add_test(tc, test_set_coordinates_false);

  return tc;
}
