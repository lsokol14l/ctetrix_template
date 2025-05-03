#include "print_controller.h"

#include <ncurses.h>
#include <string.h>

#include "tetris_frontend_defines.h"

void print_game(const GameInfo_t *game_info) {
  print_board((const int **)game_info->field);

  print_figure_on_info_table((const int **)game_info->next);
  print_game_info(game_info->level, game_info->score, game_info->high_score);

  switch (game_info->pause) {
    case START_INT_ENUM:
      print_start_state();
      break;
    case PAUSE_INT_ENUM:
      print_pause_state();
      break;
    case GAMEOVER_INT_ENUM:
      print_game_over_state();
      break;
    default:
      break;
  }

  refresh();
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);

  for (int i = left_x + 1; i < right_x; i++) {
    mvaddch(top_y, i, ACS_HLINE);
  }
  mvaddch(top_y, right_x, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  mvaddch(bottom_y, left_x, ACS_LLCORNER);

  for (int i = left_x + 1; i < right_x; i++) {
    mvaddch(bottom_y, i, ACS_HLINE);
  }
  mvaddch(bottom_y, right_x, ACS_LRCORNER);
}

void print_overlay() {
  print_common_rectangle();
  print_board_rectangle();
  print_info_rectangle();

  int start_text_cord = BOARD_COLUMNS + 6;
  int step_text = 3;
  int y_coord = 2;

  mvprintw(y_coord, start_text_cord, "LEVEL");
  y_coord += step_text;

  mvprintw(y_coord, start_text_cord, "SCORE");
  y_coord += step_text;

  mvprintw(y_coord, start_text_cord, "HIGH");
  y_coord++;
  mvprintw(y_coord, start_text_cord, "SCORE");
  y_coord += step_text;

  mvprintw(y_coord, start_text_cord, "NEXT");
  mvprintw(y_coord + 1, start_text_cord, "BLOCK");
}

void print_common_rectangle() {
  print_rectangle(0, BOARD_ROWS + 3, 0, BOARD_COLUMNS + INFO_COLUMNS + 4);
}

void print_board_rectangle() {
  print_rectangle(1, BOARD_ROWS + 2, 1, BOARD_COLUMNS + 2);
}

void print_info_rectangle() {
  print_rectangle(START_INFO_FIGURE_COORD_Y - 1, END_INFO_FIGURE_COORD_Y,
                  START_INFO_FIGURE_COORD_X - 1, END_INFO_FIGURE_COORD_X + 1);
}

void clear_in_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  for (int y = top_y + 1; y < bottom_y; y++) {
    for (int x = left_x + 1; x < right_x; x++) {
      mvaddch(y, x, EMPTY_CHAR);
    }
  }
}

void clear_board_rectangle() {
  clear_in_rectangle(1, BOARD_ROWS + 2, 1, BOARD_COLUMNS + 2);
}

void clear_info_rectangle() {
  clear_in_rectangle(START_INFO_FIGURE_COORD_Y - 1, END_INFO_FIGURE_COORD_Y,
                     START_INFO_FIGURE_COORD_X - 1,
                     END_INFO_FIGURE_COORD_X + 1);
}

void print_board(const int **matrix) {
  int end_y_cord = BOARD_ROWS - 1 + START_BOARD_CORD_Y;

  for (int i = 0; i < BOARD_ROWS; i++) {
    for (int j = 0; j < BOARD_COLUMNS; j++) {
      mvaddch(end_y_cord - i, j + START_BOARD_CORD_X,
              matrix[i][j] ? BOARD_CHAR : EMPTY_CHAR);
    }
  }
}

void print_figure_on_info_table(const int **matrix) {
  clear_info_rectangle();

  int end_y_cord = START_INFO_FIGURE_COORD_Y + INFO_FIGURE_BOARD_ROWS - 1;

  for (int i = 0; i < INFO_FIGURE_BOARD_ROWS; i++) {
    for (int j = 0; j < INFO_FIGURE_BOARD_COLS; j++) {
      mvaddch(end_y_cord - i, j + START_INFO_FIGURE_COORD_X + 1,
              matrix[i][j] ? BOARD_CHAR : EMPTY_CHAR);
    }
  }
}

void print_game_info(int level, int score, int high_score) {
  mvprintw(3, BOARD_COLUMNS + 4, "%9d", level);
  mvprintw(6, BOARD_COLUMNS + 4, "%9d", score);
  mvprintw(10, BOARD_COLUMNS + 4, "%9d", high_score);
}

void print_start_state() {
  clear_board_rectangle();
  clear_info_rectangle();
  print_text_on_board("WAIT START\nY-START\nESC-EXIT", BOARD_ROWS / 2 - 2);
}

void print_game_over_state() {
  print_text_on_board("GAME OVER\nY-START\n  AGAIN\nESC-EXIT",
                      BOARD_ROWS / 2 - 2);
}

void print_pause_state() {
  print_text_on_board("PAUSE\nP-RESUME\nY-START\n  AGAIN\nESC-EXIT",
                      BOARD_ROWS / 2 - 2);
}

void print_text_on_board(const char *str, int row_index) {
  char board_line[BOARD_COLUMNS + 1];
  const char *ptr = str;
  int index = 0;

  while (*(str + index) != '\0') {
    if (str[index] == '\n') {
      size_t cur_size =
          str + index - ptr > BOARD_COLUMNS ? BOARD_COLUMNS : str + index - ptr;
      memcpy(board_line, ptr, cur_size);
      board_line[cur_size] = '\0';
      print_next_text_line_on_board(board_line, &row_index);
      ptr = str + index + 1;
    }
    index++;
  }
  strcpy(board_line, ptr);
  print_next_text_line_on_board(ptr, &row_index);
  ptr = str + index + 1;
}

void print_next_text_line_on_board(const char *str, int *row_index) {
  for (int i = START_BOARD_CORD_X; i < BOARD_COLUMNS; i++) {
    mvaddch(*row_index, i, EMPTY_CHAR);
  }

  mvprintw(*row_index, START_BOARD_CORD_X, "%s", str);
  *row_index = *row_index + 1;
}
