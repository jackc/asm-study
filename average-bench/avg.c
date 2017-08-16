#include <avg.h>

double avg(double *nums, size_t count) {
  double n = 0;

  for (size_t i = 0; i < count; i++) {
    n += nums[i];
  }

  return n / ((double) count);
}
