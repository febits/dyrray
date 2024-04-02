#include <stdio.h>
#include <stdlib.h>

#include "dyrray.h"
#include "types.h"

dyrray_t *dyrray_init(void) {}

object_t *dyrray_insert(dyrray_t *dr, void *data, enum data_types dt,
                        u64 index) {}

object_t *dyrray_append(dyrray_t *dr, void *data, enum data_types dt) {}

object_t *dyrray_delete(dyrray_t *dr, u64 index) {}

object_t *dyrray_pop(dyrray_t *dr) {}

object_t *dyrray_get(dyrray_t *dr, u64 index) {}

void dyrray_show(dyrray_t *dr) {}
