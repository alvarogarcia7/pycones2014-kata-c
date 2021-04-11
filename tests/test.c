#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../lib.h"

#include <stdbool.h>

/* A test case that does nothing and succeeds. */
static void canary_test(void **state) {
    (void) state; /* unused */
    assert_int_equal(0, 0);
}

static void register_non_existing_username(void **state) {
    assert_int_equal(true, register_user("pepe"));
}

static void register_existing_username(void **state) {
    assert_int_equal(true, register_user("pepe"));
    assert_int_equal(false, register_user("pepe"));
}

int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(canary_test)
            , cmocka_unit_test(register_non_existing_username)
            , cmocka_unit_test(register_existing_username)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

