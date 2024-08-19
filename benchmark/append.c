#include <stdio.h>
#include <stdlib.h>

#include "dyrray.h"

#define NUMELEMENTS 200000

int main(void) {
  dyrray_t *dr = dyrray_init(NULL);
  if (dr == NULL) {
    perror("Dyrray init error");
  }

  for (int i = 0; i < NUMELEMENTS; i++) {
    dr->append(dr, NULL, VOID_PTR);
  }

  return EXIT_SUCCESS;
}