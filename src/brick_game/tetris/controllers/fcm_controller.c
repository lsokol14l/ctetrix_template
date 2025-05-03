#include "fcm_controller.h"

#include <time.h>

#include "entities/tetris_game.h"
#include "game_controller.h"
#include "score_controller.h"
#include "tetris_backend_api.h"
#include "tetris_backend_defines.h"
#include "tetris_controller.h"
#include "time_controller.h"

void userInput(UserAction_t action, bool hold) {
  tetris_game_t *game = get_game();

  tetris_state *state = &(game->state);
  board_t *board = &(game->board);
  figure_t *figure = &(game->figure);
  figure_t *next_figure = &(game->next_figure);
  struct timespec *start_time = &(game->start_time);
  int *score = &(game->score);
  int *level = &(game->level);
  int *high_score = &(game->high_score);
  if (hold) {
    action = Action + 1;
  }

  switch (*state) {
    case START:
      on_start_state(action, state, score, level, high_score, board, figure,
                     next_figure);
      break;
    case SPAWN:
      on_spawn_state(state, board, start_time, *score, level, figure,
                     next_figure);
      break;
    case MOVING:
      on_moving_state(action, state, figure, board, start_time, *level);
      break;
    case SHIFTING:
      on_shifting_state(state, figure, board);
      break;
    case ATTACHING:
      on_attaching_state(state, figure, board, score, level);
      break;
    case PAUSE_STATE:
      on_pause_state(action, state);
      break;
    case GAMEOVER:
      on_game_over_state(action, state, *score);
      break;
    default:
      break;
  }
}

void on_start_state(UserAction_t sig, tetris_state *state, int *score,
                    int *level, int *high_score, board_t *board,
                    figure_t *figure, figure_t *next_figure) {
  init_figures_as_empty(figure, next_figure);
  init_game_info(score, level);

  switch (sig) {
    case Start:
      init_board(board);
      *high_score = get_high_score(HIGH_SCORE_LEVEL_FILENAME);
      *state = SPAWN;
      break;
    case Terminate:
      *state = EXIT_STATE;
      break;
    default:
      *state = START;
      break;
  }
}

void on_spawn_state(tetris_state *state, const board_t *board,
                    struct timespec *start_time, int score, int *level,
                    figure_t *figure, figure_t *next_figure) {
  init_and_change_figures(figure, next_figure);
  update_time(start_time);
  update_level(score, level);

  if (!init_figure_on_board(figure, board)) {
    *state = GAMEOVER;
  } else {
    *state = MOVING;
  }
}

void on_moving_state(UserAction_t sig, tetris_state *state, figure_t *figure,
                     const board_t *board, struct timespec *start_time,
                     int level) {
  if (sig == Pause) {
    *state = PAUSE_STATE;
  } else if (sig == Terminate) {
    *state = GAMEOVER;
  } else if (is_need_update_time(start_time, level)) {
    update_time(start_time);
    *state = SHIFTING;
  } else {
    switch (sig) {
      case Down:
        move_down_to_intersect(figure, board);
        *state = ATTACHING;
        break;
      case Right:
      case Left:
        move_horizontal_figure_if_possible(figure, board, sig);
        *state = MOVING;
        break;
      case Action:
        rotate_figure_if_possible(figure, board);
        *state = MOVING;
        break;
      default:
        *state = MOVING;
        break;
    }
  }
}

void on_shifting_state(tetris_state *state, figure_t *figure,
                       const board_t *board) {
  if (is_need_apply_figure_on_board(figure, board)) {
    *state = ATTACHING;
  } else {
    *state = MOVING;
  }

  move_down_once_if_possible(figure, board);
}

void on_attaching_state(tetris_state *state, figure_t *figure, board_t *board,
                        int *score, int *level) {
  size_t distruction_rows = 0;

  apply_figure_on_board(figure, board, &distruction_rows);
  add_to_game_score(score, distruction_rows);
  update_level(*score, level);

  *state = SPAWN;
}

void on_game_over_state(UserAction_t sig, tetris_state *state, int score) {
  switch (sig) {
    case Start:
      set_high_score_if_needed(score, HIGH_SCORE_LEVEL_FILENAME);
      *state = START;
      break;
    case Terminate:
      set_high_score_if_needed(score, HIGH_SCORE_LEVEL_FILENAME);
      *state = EXIT_STATE;
      break;
    default:
      *state = GAMEOVER;
      break;
  }
}

void on_pause_state(UserAction_t sig, tetris_state *state) {
  switch (sig) {
    case Pause:
      *state = MOVING;
      break;
    case Start:
      *state = START;
      break;
    case Terminate:
      *state = EXIT_STATE;
      break;
    default:
      *state = PAUSE_STATE;
      break;
  }
}