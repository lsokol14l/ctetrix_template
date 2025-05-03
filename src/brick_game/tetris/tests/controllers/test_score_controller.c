#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "controllers/score_controller.h"
#include "test_controllers.h"
#include "tetris_backend_defines.h"

void create_test_file(const char *filename, int score) {
  const char *home_dir = getenv("HOME");
  ck_assert_ptr_nonnull(home_dir);

  char path[256];
  snprintf(path, sizeof(path), "%s/%s", home_dir, GAME_FOLDER);

  struct stat st = {0};
  if (stat(path, &st) == -1) {
    ck_assert_int_eq(0, mkdir(path, 0755));
  }

  strcat(path, "/");
  strcat(path, filename);

  FILE *file = fopen(path, "w");
  ck_assert_ptr_nonnull(file);

  fprintf(file, "%d", score);
  fclose(file);
}

void delete_test_file(const char *filename) {
  const char *home_dir = getenv("HOME");
  ck_assert_ptr_nonnull(home_dir);

  char path[256];
  snprintf(path, sizeof(path), "%s/%s/%s", home_dir, GAME_FOLDER, filename);

  ck_assert_int_eq(0, remove(path));
}

START_TEST(test_set_high_score_new_higher_score) {
  const char *filename = "test_score1.txt";
  int current_score = 10;
  int new_high_score = 15;

  create_test_file(filename, current_score);
  set_high_score_if_needed(new_high_score, filename);

  ck_assert_int_eq(get_high_score(filename), new_high_score);
  delete_test_file(filename);
}
END_TEST

START_TEST(test_set_high_score_same_score) {
  const char *filename = "test_score2.txt";
  int current_score = 20;
  int new_high_score = 20;

  create_test_file(filename, current_score);
  set_high_score_if_needed(new_high_score, filename);

  ck_assert_int_eq(get_high_score(filename), current_score);
  delete_test_file(filename);
}
END_TEST

START_TEST(test_set_high_score_lower_score) {
  const char *filename = "test_score3.txt";
  int current_score = 30;
  int new_high_score = 25;

  create_test_file(filename, current_score);

  set_high_score_if_needed(new_high_score, filename);

  ck_assert_int_eq(get_high_score(filename), current_score);
  delete_test_file(filename);
}
END_TEST

START_TEST(test_update_game_score) {
  int res = 200;
  add_to_game_score(&res, 0);
  ck_assert_int_eq(res, 200);
  ck_assert_int_eq(get_level(res), 1);

  add_to_game_score(&res, 1);
  ck_assert_int_eq(res, 300);
  ck_assert_int_eq(get_level(res), 1);

  add_to_game_score(&res, 3);
  ck_assert_int_eq(res, 1000);
  ck_assert_int_eq(get_level(res), 2);
}
END_TEST;

START_TEST(test_max_score) {
  int res = 7000;
  ck_assert_int_eq(get_level(res), 10);
}
END_TEST;

TCase *get_score_controller_test_case() {
  TCase *tc = tcase_create("score_controller");

  tcase_add_test(tc, test_update_game_score);
  tcase_add_test(tc, test_max_score);

  tcase_add_test(tc, test_set_high_score_new_higher_score);
  tcase_add_test(tc, test_set_high_score_same_score);
  tcase_add_test(tc, test_set_high_score_lower_score);

  return tc;
}