#ifndef __TIME_CONTROLLER_H__
#define __TIME_CONTROLLER_H__

#include <stdbool.h>
#include <time.h>

bool is_need_update_time(const struct timespec *start_time, int level);
void update_time(struct timespec *start_time);

#endif  // __TIME_CONTROLLER_H__
