#include <ncurses.h>

#include "tetris_frontend_api.h"

void init_gui() {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

void destroy_gui() { endwin(); }