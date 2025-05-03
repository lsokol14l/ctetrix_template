#include "time_controller.h"

#include <tetris_backend_defines.h>

bool is_need_update_time(const struct timespec *start_time, int level) {
  double extension_time_sec = ((MAX_LEVEL - level + 1) * STEP_SEC_BY_LEVEL);
  struct timespec current_time;

  timespec_get(&current_time, TIME_UTC);

  double elapsed_sec = (current_time.tv_sec - start_time->tv_sec) +
                       (current_time.tv_nsec - start_time->tv_nsec) / 1e9;

  return extension_time_sec <= elapsed_sec;
}

void update_time(struct timespec *start_time) {
  timespec_get(start_time, TIME_UTC);
}