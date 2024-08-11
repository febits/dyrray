#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dyrray.h"
#include "types.h"

int main(void) {

  dyrray_t *dr = dyrray_init(NULL);
  if (!dr) {
    printf("Dyrray init error!\n");
    return EXIT_FAILURE;
  }

  u32 _u32_ = UINT_MAX;
  clock_t begin = clock();

  for (int i = 0; i < 200000; i++) {
    dr->insert(dr, &_u32_, VOID_PTR, 0);
  }

  clock_t end = clock();

  printf("insert_benchmark(): %.2fs elapsed with 200,000 elements\n",
         (double)(end - begin) / CLOCKS_PER_SEC);

  dr->kill(dr);
  return EXIT_SUCCESS;
}
