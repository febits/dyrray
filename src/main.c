#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "dyrray.h"

int main(void) {

  dyrray_t *dr = dyrray_init("Dyrray");
  if (!dr) {
    perror("Dyrray init failed!\n");
    return EXIT_FAILURE;
  }

  u64 _u64_ = ULONG_MAX;
  u32 _u32_ = UINT_MAX;
  u16 _u16_ = USHRT_MAX;
  u8 _u8_ = UCHAR_MAX;

  i64 _i64_ = LONG_MIN;
  i32 _i32_ = INT_MIN;
  i16 _i16_ = SHRT_MIN;
  i8 _i8_ = CHAR_MIN;

  f32 _float_ = FLT_MAX;
  f64 _double_ = DBL_MAX;

  char *str = "Felipe";
  char *str2 = "Febits";
  object_t obj = {VOID_PTR, NULL};

  dr->append(dr, &_u64_, U64);
  dr->append(dr, &_u32_, U32);
  dr->append(dr, &_u16_, U16);
  dr->append(dr, &_u8_, U8);
  dr->append(dr, &_i64_, I64);
  dr->append(dr, &_i32_, I32);
  dr->append(dr, &_i16_, I16);
  dr->append(dr, &_i8_, I8);
  dr->append(dr, &_float_, F32);
  dr->append(dr, &_double_, F64);
  dr->append(dr, str, CHAR_PTR);
  dr->append(dr, &obj, VOID_PTR);
  dr->append(dr, &obj, VOID_PTR);

  dr->show(dr);

  printf("\nPop operation: \n");
  free(dr->pop(dr));
  dr->show(dr);

  printf("\nDeleting at 0 index:\n");
  free(dr->delete (dr, 0));
  dr->show(dr);

  printf("\nDeleting at 2 index: \n");
  free(dr->delete (dr, 2));
  dr->show(dr);

  printf("\nInserting at 0 index: \n");
  dr->insert(dr, str2, CHAR_PTR, 0);
  dr->show(dr);

  printf("\nInserting at 2 index: \n");
  dr->insert(dr, str2, CHAR_PTR, 2);
  dr->show(dr);

  printf("\nGet operation: \n");
  printf("%e\n", DYRRAY_GETAS_VALUE(dr, 9, f64));

  dr->kill(dr);
  return EXIT_SUCCESS;
}
