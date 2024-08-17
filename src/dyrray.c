#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dyrray.h"
#include "types.h"

enum shift_type { LEFT, RIGHT };

dyrray_t *dyrray_init(const char *label) {
  dyrray_t *dr = malloc(sizeof(dyrray_t));

  if (dr == NULL)
    return NULL;

  dr->items = calloc(DYRRAY_INITIAL_CAPACITY, sizeof(object_t *));

  if (dr->items == NULL)
    return NULL;

  dr->label = label ? strdup(label) : NULL;
  dr->capacity = DYRRAY_INITIAL_CAPACITY;
  dr->csize = 0;

  dr->insert = dyrray_insert;
  dr->append = dyrray_append;
  dr->delete = dyrray_delete;
  dr->pop = dyrray_pop;
  dr->get = dyrray_get;
  dr->kill = dyrray_kill;
  dr->show = dyrray_show;

  return dr;
}

static inline void _shift(dyrray_t *dr, u64 init, u64 end, enum shift_type st) {
  if (st == LEFT) {
    memmove(&dr->items[init - 1], &dr->items[init],
            (end - init + 1) * sizeof(dr->items[0]));
  } else {
    memmove(&dr->items[init + 1], &dr->items[init],
            (end - init + 1) * sizeof(dr->items[0]));
  }
}

object_t *dyrray_insert(dyrray_t *dr, void *data, enum data_types dt,
                        u64 index) {
  if (index == dr->csize) {
    return dr->append(dr, data, dt);
  } else {
    if (dr->csize >= dr->capacity) {
      dr->capacity += DYRRAY_REALLOC_FACTOR(dr->capacity);
      dr->items = realloc(dr->items, dr->capacity * sizeof(object_t *));

      if (dr->items == NULL)
        return NULL;
    }

    object_t *obj = malloc(sizeof(object_t));

    if (obj == NULL || index > dr->csize)
      return NULL;

    obj->dt = dt;
    obj->data = data;

    _shift(dr, index, dr->csize - 1, RIGHT);
    dr->items[index] = obj;
    dr->csize++;

    return dr->items[index];
  }
}

object_t *dyrray_append(dyrray_t *dr, void *data, enum data_types dt) {
  object_t *obj = malloc(sizeof(object_t));

  if (obj == NULL)
    return NULL;

  obj->dt = dt;
  obj->data = data;

  if (dr->csize >= dr->capacity) {
    dr->capacity += DYRRAY_REALLOC_FACTOR(dr->capacity);
    dr->items = realloc(dr->items, dr->capacity * sizeof(object_t *));

    if (dr->items == NULL)
      return NULL;
  }

  dr->items[dr->csize++] = obj;
  return dr->items[dr->csize - 1];
}

object_t *dyrray_delete(dyrray_t *dr, u64 index) {
  if (index > dr->csize)
    return NULL;

  if (index == dr->csize) {
    return dr->pop(dr);
  } else {
    object_t *tmp = dr->items[index];
    _shift(dr, index + 1, dr->csize, LEFT);
    dr->items[--dr->csize] = NULL;

    return tmp;
  }
}

object_t *dyrray_pop(dyrray_t *dr) {
  if (dr->csize == 0)
    return NULL;

  object_t *tmp = dr->items[--dr->csize];
  dr->items[dr->csize] = NULL;

  return tmp;
}

object_t *dyrray_get(dyrray_t *dr, u64 index) {
  if (dr->csize < index)
    return NULL;

  return dr->items[index];
}

void dyrray_kill(dyrray_t *dr) {
  for (u64 i = 0; i < dr->capacity; i++) {
    free(dr->items[i]);
  }
  free(dr->items);
  free((char *)dr->label);
  free(dr);
}

void dyrray_show(dyrray_t *dr) {
  printf("%s:%lu [", dr->label ? dr->label : "---", dr->csize);

  for (u64 i = 0; i < dr->csize; i++) {
    switch (dr->items[i]->dt) {
      case F32: printf("%e", DYRRAY_GETAS_VALUE(dr, i, f32)); break;
      case F64: printf("%e", DYRRAY_GETAS_VALUE(dr, i, f64)); break;
      case I8: printf("%d", DYRRAY_GETAS_VALUE(dr, i, i8)); break;
      case I16: printf("%d", DYRRAY_GETAS_VALUE(dr, i, i16)); break;
      case I32: printf("%d", DYRRAY_GETAS_VALUE(dr, i, i32)); break;
      case U8: printf("%u", DYRRAY_GETAS_VALUE(dr, i, u8)); break;
      case U16: printf("%u", DYRRAY_GETAS_VALUE(dr, i, u16)); break;
      case U32: printf("%u", DYRRAY_GETAS_VALUE(dr, i, u32)); break;
      case I64: printf("%ld", DYRRAY_GETAS_VALUE(dr, i, i64)); break;
      case U64: printf("%lu", DYRRAY_GETAS_VALUE(dr, i, u64)); break;
      case VOID_PTR: printf("%p", DYRRAY_GETAS_POINTER(dr, i, void *)); break;
      case CHAR_PTR: printf("\"%s\"", DYRRAY_GETAS_POINTER(dr, i, char *)); break;
    }
    if (i != dr->csize - 1)
      printf(", ");
  }
  printf("] (%lu)\n", dr->capacity);
}
