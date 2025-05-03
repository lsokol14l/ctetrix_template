#ifndef __SCORE_CONTROLLER_H__
#define __SCORE_CONTROLLER_H__

#include <stddef.h>

void add_to_game_score(int *score, size_t count_distruction_rows);
int get_level(int score);

void update_level(int score, int *level);
void init_game_info(int *score, int *level);

int get_high_score(const char *filename);
void set_high_score_if_needed(int high_score, const char *filename);

#endif  // __SCORE_CONTROLLER_H__
