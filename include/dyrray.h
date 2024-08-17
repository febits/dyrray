#ifndef DYRRAY_H
#define DYRRAY_H

#include "types.h"

#define DYRRAY_INITIAL_CAPACITY 5
#define DYRRAY_REALLOC_FACTOR(x) ((u64)((x) * 0.5))

#define DYRRAY_GETAS_POINTER(dr, index, type)                                  \
  ((type)(dr)->get((dr), (index))->data)
#define DYRRAY_GETAS_VALUE(dr, index, type)                                    \
  (*(type *)(dr)->get((dr), (index))->data)

enum data_types {
  I8,
  U8,
  I16,
  U16,
  I32,
  U32,
  I64,
  U64,
  F32,
  F64,
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
  u64 capacity;
  u64 csize;

  void (*show)(struct dyrray_t *);
  object_t *(*insert)(struct dyrray_t *, void *, enum data_types, u64);
  object_t *(*append)(struct dyrray_t *, void *, enum data_types);
  object_t *(*delete)(struct dyrray_t *, u64);
  object_t *(*pop)(struct dyrray_t *);
  object_t *(*get)(struct dyrray_t *, u64);
  void (*kill)(struct dyrray_t *);
} dyrray_t;

dyrray_t *dyrray_init(const char *label);

object_t *dyrray_insert(dyrray_t *dr, void *data, enum data_types dt,
                        u64 index);

object_t *dyrray_append(dyrray_t *dr, void *data, enum data_types dt);

object_t *dyrray_delete(dyrray_t *dr, u64 index);

object_t *dyrray_pop(dyrray_t *dr);

object_t *dyrray_get(dyrray_t *dr, u64 index);

void dyrray_kill(dyrray_t *dr);

void dyrray_show(dyrray_t *dr);

#endif
