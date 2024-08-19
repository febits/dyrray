#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>

#include "dyrray.h"
#include "types.h"

static int _cmocka_setup(void **state) {
  dyrray_t *dr = dyrray_init(NULL);
  if (dr == NULL) {
    return -1;
  }

  *state = dr;
  return 0;
}

static int _cmocka_teardown(void **state) {
  dyrray_t *dr = *state;
  dr->kill(dr);
  return 0;
}

static void append_test(void **state) {
  dyrray_t *dr = *state;

  i32 num = 10;
  dr->append(dr, &num, I32);

  assert_int_equal(10, DYRRAY_GETAS_VALUE(dr, 0, i32));
  assert_int_not_equal(20, DYRRAY_GETAS_VALUE(dr, 0, i32));
}

static void insert_test(void **state) {
  dyrray_t *dr = *state;

  i32 num = 10;
  dr->insert(dr, &num, I32, 0);

  assert_int_equal(10, DYRRAY_GETAS_VALUE(dr, 0, i32));
  assert_int_not_equal(20, DYRRAY_GETAS_VALUE(dr, 0, i32));

  i32 num2 = 30;
  dr->insert(dr, &num2, I32, 0);

  assert_int_equal(30, DYRRAY_GETAS_VALUE(dr, 0, i32));
  assert_int_not_equal(40, DYRRAY_GETAS_VALUE(dr, 0, i32));

  i32 num3 = 50;
  dr->insert(dr, &num3, I32, 0);

  assert_int_equal(50, DYRRAY_GETAS_VALUE(dr, 0, i32));
  assert_int_not_equal(60, DYRRAY_GETAS_VALUE(dr, 0, i32));
}

static void pop_test(void **state) {
  dyrray_t *dr = *state;

  i32 num = 10;
  i32 num2 = 20;
  i32 num3 = 30;
  i32 num4 = 40;

  dr->append(dr, &num, I32);
  dr->append(dr, &num2, I32);
  dr->append(dr, &num3, I32);
  dr->append(dr, &num4, I32);

  object_t *result = dr->pop(dr);
  assert_int_equal(40, *(i32 *)result->data);
  assert_int_not_equal(50, *(i32 *)result->data);
  free(result);

  assert_int_equal(30, DYRRAY_GETAS_VALUE(dr, 2, i32));
  assert_int_not_equal(40, DYRRAY_GETAS_VALUE(dr, 2, i32));
}

static void delete_test(void **state) {
  dyrray_t *dr = *state;
  
  i32 num = 10;
  i32 num2 = 20;
  i32 num3 = 30;
  i32 num4 = 40;

  dr->append(dr, &num, I32);
  dr->append(dr, &num2, I32);
  dr->append(dr, &num3, I32);
  dr->append(dr, &num4, I32);

  object_t *result = dr->delete(dr, 2);
  assert_int_equal(30, *(i32 *)result->data);
  assert_int_not_equal(40, *(i32 *)result->data);
  free(result);

  assert_int_equal(40, DYRRAY_GETAS_VALUE(dr, 2, i32));
  assert_int_not_equal(30, DYRRAY_GETAS_VALUE(dr, 2, i32));
}

static void get_test(void **state) {
  dyrray_t *dr = *state;

  i32 num = 10;
  dr->append(dr, &num, I32);

  assert_int_equal(10, DYRRAY_GETAS_VALUE(dr, 0, i32));
  assert_int_not_equal(20, DYRRAY_GETAS_VALUE(dr, 0, i32));
}

static void out_of_bound_test(void **state) {
  dyrray_t *dr = *state;

  i32 num = 10;
  assert_null(dr->insert(dr, &num, I32, dr->csize + 1));
}

int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test_setup_teardown(append_test, _cmocka_setup, _cmocka_teardown),
    cmocka_unit_test_setup_teardown(insert_test, _cmocka_setup, _cmocka_teardown),
    cmocka_unit_test_setup_teardown(pop_test, _cmocka_setup, _cmocka_teardown),
    cmocka_unit_test_setup_teardown(delete_test, _cmocka_setup, _cmocka_teardown),
    cmocka_unit_test_setup_teardown(get_test, _cmocka_setup, _cmocka_teardown),
    cmocka_unit_test_setup_teardown(out_of_bound_test, _cmocka_setup, _cmocka_teardown)
  };

  return cmocka_run_group_tests_name("Dyrray Test", tests, NULL, NULL);
}
