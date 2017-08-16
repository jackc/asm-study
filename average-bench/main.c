#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "avg.h"
#include "avg_simd.h"

double* generate_doubles(size_t count) {
  double *nums = malloc(sizeof(double) * count);

  for (size_t i = 0; i < count; i++) {
    nums[i] = (double) i;
  }

  return nums;
}

int main(int argc, char const *argv[])
{
  if (argc != 4) {
    fprintf(stderr, "usage: avg TYPE COUNT LOOPS\n");
    exit(1);
  }

  double (*fn)(double*, size_t);

  if (strcmp(argv[1], "c") == 0) {
    fn = avg;
  } else {
    fn = avg_simd;
  }

  size_t count = atoi(argv[2]);
  if (!count) {
    fprintf(stderr, "count must be a positive integer\n");
    exit(1);
  }

  if (count % 8 != 0) {
    fprintf(stderr, "count must be evenly divisible by 8\n");
    exit(1);
  }

  size_t loops = atoi(argv[3]);
  if (loops < 1) {
    fprintf(stderr, "loops must be a positive integer\n");
    exit(1);
  }

  double *nums = generate_doubles(count);
  double avg_num;
  for (size_t i = 0; i < loops; i++) {
    avg_num = fn(nums, count);
  }
  free(nums);

  printf("%s: average of %zu numbers: %f\n", argv[1], count, avg_num);
}


