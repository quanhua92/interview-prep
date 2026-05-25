/*
 * test_harness.h - Minimal shared test runner for C solution files.
 *
 * Define your solve function and TEST_CASES array, then call RUN_TESTS().
 *
 * The solve function signature varies per problem - adapt as needed.
 * For functions returning heap-allocated arrays, free the result in RUN_TESTS.
 *
 * Compile: gcc -O2 -Wall -Wextra -I. -o out solution.c
 */

#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void th_print_arr(const int *a, int n)
{
    printf("[");
    for (int i = 0; i < n; i++) {
        if (i) printf(",");
        printf("%d", a[i]);
    }
    printf("]");
}

static int th_arr_eq(const int *a, int an, const int *b, int bn)
{
    if (!a || !b || an != bn) return 0;
    for (int i = 0; i < an; i++)
        if (a[i] != b[i]) return 0;
    return 1;
}

typedef struct {
    const char *label;
    int input_arr[30000];
    int input_arr_n;
    int target;
    int expected[30000];
    int expected_n;
} TestCase;

#define RUN_TESTS(name, solve_fn, tc_array, tc_count)                     \
    do {                                                                   \
        printf("\n============================================================\n"); \
        printf("  %s\n", name);                                            \
        printf("============================================================\n"); \
        int _passed = 0;                                                   \
        for (int _i = 0; _i < (tc_count); _i++) {                          \
            TestCase *_tc = &(tc_array)[_i];                               \
            int _ret_size = 0;                                              \
            int *_got = solve_fn(_tc->input_arr, _tc->input_arr_n,         \
                                 _tc->target, &_ret_size);                 \
            if (_got && th_arr_eq(_got, _ret_size, _tc->expected,          \
                                   _tc->expected_n)) {                    \
                _passed++;                                                  \
                printf("  Test %d (%s): PASS\n", _i + 1, _tc->label);       \
            } else {                                                        \
                printf("  Test %d (%s): FAIL\n", _i + 1, _tc->label);       \
                printf("    Expected: "); th_print_arr(_tc->expected,        \
                                                       _tc->expected_n);   \
                printf("\n    Got:      ");                                  \
                if (_got) th_print_arr(_got, _ret_size);                    \
                else printf("NULL");                                        \
                printf("\n");                                                \
            }                                                               \
            free(_got);                                                     \
        }                                                                   \
        printf("\n  %d/%d passed\n", _passed, (tc_count));                  \
        printf("============================================================\n\n"); \
        return _passed == (tc_count) ? 0 : 1;                              \
    } while (0)

#endif /* TEST_HARNESS_H */
