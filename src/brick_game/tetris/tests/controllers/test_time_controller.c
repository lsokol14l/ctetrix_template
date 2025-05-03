#include <unistd.h>

#include "controllers/time_controller.h"
#include "test_controllers.h"

START_TEST(test_check_time_if_less_than_lvl_time) {
  struct timespec cur_time;
  update_time(&cur_time);
  ck_assert_int_eq(is_need_update_time(&cur_time, 10), false);
  sleep(1);
  ck_assert_int_eq(is_need_update_time(&cur_time, 10), true);
}
END_TEST;

TCase *get_time_controller_test_case() {
  TCase *tc = tcase_create("time_controller");

  tcase_add_test(tc, test_check_time_if_less_than_lvl_time);

  return tc;
}