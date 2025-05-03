#include <unistd.h>

#include "controllers/fcm_controller.h"
#include "controllers/game_controller.h"
#include "entities/board.h"
#include "entities/figure.h"
#include "entities/tetris_state.h"
#include "objects.h"
#include "test_controllers.h"
#include "tetris_backend_api.h"

START_TEST(test_pause_state_pause_btn) {
  UserAction_t sig = Pause;
  tetris_state state = GAMEOVER;
  on_pause_state(sig, &state);
  ck_assert_int_eq(state, MOVING);
}
END_TEST;

START_TEST(test_pause_state_start_btn) {
  UserAction_t sig = Start;
  tetris_state state = GAMEOVER;
  on_pause_state(sig, &state);
  ck_assert_int_eq(state, START);
}
END_TEST;

START_TEST(test_pause_state_stop_btn) {
  UserAction_t sig = Terminate;
  tetris_state state = GAMEOVER;
  on_pause_state(sig, &state);
  ck_assert_int_eq(state, EXIT_STATE);
}
END_TEST;

START_TEST(test_pause_state_other_btn) {
  UserAction_t sig[] = {Up, Down, Right, Left, Action};

  for (int i = 0; i < 5; i++) {
    tetris_state state = GAMEOVER;
    on_pause_state(sig[i], &state);
    ck_assert_int_eq(state, PAUSE_STATE);
  }
}
END_TEST;

START_TEST(test_game_over_state_stop_btn) {
  UserAction_t sig = Terminate;
  tetris_state state = GAMEOVER;
  on_game_over_state(sig, &state, -1);
  ck_assert_int_eq(state, EXIT_STATE);
}
END_TEST;

START_TEST(test_game_over_state_start_btn) {
  UserAction_t sig = Start;
  tetris_state state = GAMEOVER;
  on_game_over_state(sig, &state, -1);
  ck_assert_int_eq(state, START);
}
END_TEST;

START_TEST(test_game_over_state_other_btn) {
  UserAction_t sig[] = {Up, Pause, Down, Right, Left, Action};

  for (int i = 0; i < 6; i++) {
    tetris_state state = START;
    on_game_over_state(sig[i], &state, -1);
    ck_assert_int_eq(state, GAMEOVER);
  }
}
END_TEST;

START_TEST(test_attaching_state) {
  figure_t figue;
  figue.center_x.int_coord = 0;
  figue.center_y.int_coord = 0;
  figue.figure_type = NON_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figue.coordinates[i][0] = 0;
    figue.coordinates[i][1] = 0;
  }
  board_t board;
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board.matrix[i][j] = 0;
    }
  }
  int level = 1;
  int score = 0;

  tetris_state state = ATTACHING;
  on_attaching_state(&state, &figue, &board, &level, &score);
  ck_assert_int_eq(state, SPAWN);
}
END_TEST;

START_TEST(test_moving_state_other_btn) {
  UserAction_t sig[] = {Up, Right, Left, Action};

  figure_t figure;
  figure.center_x.int_coord = 0;
  figure.center_y.int_coord = 0;
  figure.figure_type = NON_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure.coordinates[i][0] = 0;
    figure.coordinates[i][1] = 0;
  }

  board_t board;
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board.matrix[i][j] = 0;
    }
  }

  int level = 1;
  struct timespec start_time;

  for (int i = 0; i < 4; i++) {
    tetris_state state = START;
    timespec_get(&start_time, TIME_UTC);
    on_moving_state(sig[i], &state, &figure, &board, &start_time, level);
    ck_assert_int_eq(state, MOVING);
  }
}
END_TEST;

START_TEST(test_moving_state_when_shifting) {
  UserAction_t sig = Up;

  figure_t figure;
  figure.center_x.int_coord = 0;
  figure.center_y.int_coord = 0;
  figure.figure_type = NON_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure.coordinates[i][0] = 0;
    figure.coordinates[i][1] = 0;
  }

  board_t board;
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board.matrix[i][j] = 0;
    }
  }

  int level = 10;
  struct timespec start_time;
  timespec_get(&start_time, TIME_UTC);

  tetris_state state = START;
  sleep(1);
  on_moving_state(sig, &state, &figure, &board, &start_time, level);
  ck_assert_int_eq(state, SHIFTING);
}
END_TEST;

START_TEST(test_shifting_state) {
  figure_t figure;
  figure.center_x.int_coord = 0;
  figure.center_y.int_coord = 0;
  figure.figure_type = NON_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure.coordinates[i][0] = 1;
    figure.coordinates[i][1] = 1;
  }

  board_t board;
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board.matrix[i][j] = 0;
    }
  }

  tetris_state state = START;
  on_shifting_state(&state, &figure, &board);
  ck_assert_int_eq(state, MOVING);
  on_shifting_state(&state, &figure, &board);
  ck_assert_int_eq(state, ATTACHING);
}
END_TEST;

START_TEST(test_moving_state_chang_state_btn) {
  UserAction_t sig[] = {Down, Pause, Terminate};

  figure_t figure;
  figure.center_x.int_coord = 0;
  figure.center_y.int_coord = 0;
  figure.figure_type = NON_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure.coordinates[i][0] = 0;
    figure.coordinates[i][1] = 0;
  }

  board_t board;
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board.matrix[i][j] = 0;
    }
  }

  int level = 1;
  struct timespec start_time;
  timespec_get(&start_time, TIME_UTC);

  for (int i = 0; i < 3; i++) {
    tetris_state state = MOVING;
    timespec_get(&start_time, TIME_UTC);
    on_moving_state(sig[i], &state, &figure, &board, &start_time, level);
    ck_assert_int_ne(state, MOVING);
  }
}
END_TEST;

START_TEST(test_spawn_state) {
  figure_t figure;
  figure.center_x.int_coord = 0;
  figure.center_y.int_coord = 0;
  figure.figure_type = NON_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure.coordinates[i][0] = 0;
    figure.coordinates[i][1] = 0;
  }

  figure_t next_figure;
  next_figure.center_x.int_coord = 0;
  next_figure.center_y.int_coord = 0;
  next_figure.figure_type = NON_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    next_figure.coordinates[i][0] = 0;
    next_figure.coordinates[i][1] = 0;
  }

  board_t board;
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board.matrix[i][j] = 0;
    }
  }

  int level = 1;
  int score = 0;
  struct timespec start_time;
  timespec_get(&start_time, TIME_UTC);

  tetris_state state = MOVING;
  timespec_get(&start_time, TIME_UTC);
  on_spawn_state(&state, &board, &start_time, score, &level, &figure,
                 &next_figure);
  ck_assert_int_eq(state, MOVING);
}
END_TEST;

START_TEST(test_start_state) {
  UserAction_t sig[] = {Start, Terminate};

  figure_t figure;
  figure.center_x.int_coord = 0;
  figure.center_y.int_coord = 0;
  figure.figure_type = NON_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure.coordinates[i][0] = 0;
    figure.coordinates[i][1] = 0;
  }

  figure_t next_figure;
  next_figure.center_x.int_coord = 0;
  next_figure.center_y.int_coord = 0;
  next_figure.figure_type = NON_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    next_figure.coordinates[i][0] = 0;
    next_figure.coordinates[i][1] = 0;
  }

  board_t board;
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board.matrix[i][j] = 0;
    }
  }

  int level = 1;
  int score = 0;
  int high_score = 0;

  for (int i = 0; i < 2; i++) {
    tetris_state state = START;
    on_start_state(sig[i], &state, &score, &level, &high_score, &board, &figure,
                   &next_figure);
    ck_assert_int_ne(state, START);
  }
}
END_TEST;

START_TEST(test_start_state_non_change_state) {
  UserAction_t sig[] = {Up, Down, Right, Left, Action, Pause};

  figure_t figure;
  figure.center_x.int_coord = 0;
  figure.center_y.int_coord = 0;
  figure.figure_type = J_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    figure.coordinates[i][0] = 0;
    figure.coordinates[i][1] = 0;
  }

  figure_t next_figure;
  next_figure.center_x.int_coord = 0;
  next_figure.center_y.int_coord = 0;
  next_figure.figure_type = S_SHAPE;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    next_figure.coordinates[i][0] = 0;
    next_figure.coordinates[i][1] = 0;
  }

  board_t board;
  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      board.matrix[i][j] = 0;
    }
  }

  int level = 1;
  int score = 0;
  int high_score = 0;

  for (int i = 0; i < 6; i++) {
    tetris_state state = START;
    on_start_state(sig[i], &state, &score, &level, &high_score, &board, &figure,
                   &next_figure);
    ck_assert_int_eq(state, START);
  }
}
END_TEST;

START_TEST(test_sig_act) {
  UserAction_t sig[] = {Up, Down, Right, Left, Action, Pause, Start, Terminate};
  const tetris_state states[] = {START,     SPAWN,    MOVING,     SHIFTING,
                                 ATTACHING, GAMEOVER, EXIT_STATE, PAUSE_STATE};

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      for (int k = 0; k < 2; k++) {
        init_game();
        get_game()->state = states[j];
        userInput(sig[i], (bool)k);
        destroy_game();
      }
    }
  }
}
END_TEST;

TCase *get_fcm_controller_test_case() {
  TCase *tc = tcase_create("fcm_controller");

  tcase_add_test(tc, test_pause_state_pause_btn);
  tcase_add_test(tc, test_pause_state_start_btn);
  tcase_add_test(tc, test_pause_state_stop_btn);
  tcase_add_test(tc, test_pause_state_other_btn);

  tcase_add_test(tc, test_game_over_state_stop_btn);
  tcase_add_test(tc, test_game_over_state_start_btn);
  tcase_add_test(tc, test_game_over_state_other_btn);

  tcase_add_test(tc, test_attaching_state);

  tcase_add_test(tc, test_moving_state_other_btn);
  tcase_add_test(tc, test_moving_state_when_shifting);

  tcase_add_test(tc, test_shifting_state);
  tcase_add_test(tc, test_moving_state_chang_state_btn);
  tcase_add_test(tc, test_spawn_state);

  tcase_add_test(tc, test_start_state);
  tcase_add_test(tc, test_start_state_non_change_state);

  tcase_add_test(tc, test_sig_act);

  return tc;
}