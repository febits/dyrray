#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "dyrray.h"
#include "types.h"

int main(void) {

  dyrray_t *dr = dyrray_init(NULL);
  if (!dr) {
    printf("Dyrray init error!\n");
    return EXIT_FAILURE;
  }

  u32 _u32_ = UINT_MAX;

  for (int i = 0; i < 200000; i++) {
    dr->insert(dr, &_u32_, VOID_PTR, 0);
  }

  dr->kill(dr);
  return EXIT_SUCCESS;
}
