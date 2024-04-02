#ifndef DYRRAY_H
#define DYRRAY_H

#include "types.h"

#define INITIAL_CAPACITY 20
#define RESIZE_VALUE(x) ((u64)((x) * 0.25))

enum data_types {
  I8,
  U8,
  I16,
  U16,
  I32,
  U32,
  I64,
  U64,
  FLOAT,
  CHAR,
  CHAR_PTR,
  VOID_PTR
};

typedef struct object_t {
  enum data_types dt;
  void *data;
} object_t;

typedef struct dyrray_t {
  object_t **items;

  const char *label;
  u64 csize;

  void (*show)(struct dyrray_t *);
  object_t *(*insert)(struct dyrray_t *, void *, enum data_types, u64);
  object_t *(*append)(struct dyrray_t *, void *, enum data_types);
  object_t *(*delete)(struct dyrray_t *, u64);
  object_t *(*pop)(struct dyrray_t *);
  object_t *(*get)(struct dyrray_t *, u64);
} dyrray_t;

dyrray_t *dyrray_init(void);

object_t *dyrray_insert(dyrray_t *dr, void *data, enum data_types dt,
                        u64 index);

object_t *dyrray_append(dyrray_t *dr, void *data, enum data_types dt);

object_t *dyrray_delete(dyrray_t *dr, u64 index);

object_t *dyrray_pop(dyrray_t *dr);

object_t *dyrray_get(dyrray_t *dr, u64 index);

void dyrray_show(dyrray_t *dr);

#endif
