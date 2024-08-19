#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dyrray.h"
#include "types.h"

#define NUMELEMENTS 200000
#define SIZE(arr) (sizeof((arr)) / sizeof((arr[0])))

enum bench_type {
  DYRRAY_APPEND_BENCH,
  DYRRAY_INSERT_AT_FRONT_BENCH,
  DYRRAY_INSERT_AT_MIDDLE_BENCH
};

struct bench_info {
  const char *bench_name;
  f64 total_elapsed;
};

f64 exec_bench(enum bench_type bt) {
  dyrray_t *dr = dyrray_init(NULL);
  if (dr == NULL) {
    perror("Dyrray init error");
  }

  clock_t start = clock();
  switch (bt) {
    case DYRRAY_APPEND_BENCH:
      for (size_t i = 0; i < NUMELEMENTS; i++) {
        dr->append(dr, NULL, VOID_PTR);
      }
      break;
    case DYRRAY_INSERT_AT_FRONT_BENCH:
      for (size_t i = 0; i < NUMELEMENTS; i++) {
        dr->insert(dr, NULL, VOID_PTR, 0);
      }
      break;
    case DYRRAY_INSERT_AT_MIDDLE_BENCH:
      for (size_t i = 0; i < NUMELEMENTS; i++) {
        dr->insert(dr, NULL, VOID_PTR, dr->csize / 2);
      }
      break;
  }
  clock_t end = clock();

  return (f64)(end - start) / CLOCKS_PER_SEC;
}

int main(void) {
  struct bench_info benchs[3] = {
      {"append", exec_bench(DYRRAY_APPEND_BENCH)},
      {"insert_at_front", exec_bench(DYRRAY_INSERT_AT_FRONT_BENCH)},
      {"insert_at_middle", exec_bench(DYRRAY_INSERT_AT_MIDDLE_BENCH)}};

  for (size_t i = 0; i < SIZE(benchs); i++) {
    printf("[benchmark] :: %s .. %.3fs elapsed with %d elements -- ~%.2f "
           "ns/iter\n",
           benchs[i].bench_name, benchs[i].total_elapsed, NUMELEMENTS,
           (benchs[i].total_elapsed * 1e12) / NUMELEMENTS);
  }

  return EXIT_SUCCESS;
}
