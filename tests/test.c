#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../lib.h"

#include <stdbool.h>
#include <printf.h>

/* A test case that does nothing and succeeds. */
static void canary_test(void **state) {
    (void) state; /* unused */
    assert_int_equal(0, 0);
}

static void register_non_existing_username(void **state) {
    register_clear();
    assert_int_equal(true, register_user("pepe"));
}

static void register_existing_username(void **state) {
    register_clear();
    assert_int_equal(true, register_user("pepe"));
    assert_int_equal(false, register_user("pepe"));
}

static void follow_another_user(void **state) {
    register_clear();
    register_user("pepe");
    assert_int_equal(true, follow_user("pepe", "juan"));

    char **followees = user_is_following("pepe");
    assert_string_equal(followees[0], "juan");
    assert_null(followees[1]);
}


static void follow_multiple_users(void **state) {
    register_clear();
    register_user("pepe");
    assert_int_equal(true, follow_user("pepe", "juan"));
    assert_int_equal(true, follow_user("pepe", "jose"));

    char **followees = user_is_following("pepe");
    assert_string_equal(followees[0], "juan");
    assert_string_equal(followees[1], "jose");
    assert_null(followees[2]);
}

static void persist_users_and_followees(void **state){
    register_clear();
    register_user("pepe");
    follow_user("pepe", "juan");
    follow_user("pepe", "jose");
    register_user("juan");
    follow_user("juan", "pepe");
    follow_user("juan", "miguel");

    char **export = export_contents();
    assert_string_equal(export[0], "pepe: juan,jose,");
    assert_string_equal(export[1], "juan: pepe,miguel,");
    assert_null(export[2]);
}

int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(canary_test)
            , cmocka_unit_test(register_non_existing_username)
            , cmocka_unit_test(register_existing_username)
            , cmocka_unit_test(follow_another_user)
            , cmocka_unit_test(follow_multiple_users)
            , cmocka_unit_test(persist_users_and_followees)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

