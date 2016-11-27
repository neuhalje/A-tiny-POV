#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"


/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

/* A test case that does nothing and succeeds. */
static void null_test_fail(void **state) {
    (void) state; /* unused */
    assert_string_equal("I should be","this");
}

int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(null_test_success),
            cmocka_unit_test(null_test_fail),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}