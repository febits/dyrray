#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dyrray.h"
#include "types.h"

#define NUMELEMENTS 200000

int main(void) {

  dyrray_t *dr = dyrray_init(NULL);
  if (!dr) {
    printf("Dyrray init error!\n");
    return EXIT_FAILURE;
  }

  clock_t begin = clock();
  u32 _u32_ = UINT_MAX;

  for (int i = 0; i < NUMELEMENTS; i++) {
    dr->append(dr, &_u32_, VOID_PTR);
  }

  clock_t end = clock();

  printf("append_benchmark(): %.2fs elapsed with 200,000 elements\n",
         (f64)(end - begin) / CLOCKS_PER_SEC);

  dr->kill(dr);
  return EXIT_SUCCESS;
}
