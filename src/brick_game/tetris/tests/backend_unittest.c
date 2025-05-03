#include <check.h>

#include "controllers/test_controllers.h"
#include "services/test_services.h"
#include "utils/test_utils.h"

int main() {
  int number_failed;
  Suite *suite = suite_create("s21_tetris_tests");
  SRunner *runner = srunner_create(suite);

  // controllers
  suite_add_tcase(suite, get_tetris_controller_test_case());
  suite_add_tcase(suite, get_score_controller_test_case());
  suite_add_tcase(suite, get_time_controller_test_case());
  suite_add_tcase(suite, get_fcm_controller_test_case());
  suite_add_tcase(suite, get_game_controller_test_case());

  // services
  suite_add_tcase(suite, get_figure_service_test_case());
  suite_add_tcase(suite, get_board_service_test_case());

  // validators
  suite_add_tcase(suite, get_board_validators_test_case());

  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return number_failed != 0;
}