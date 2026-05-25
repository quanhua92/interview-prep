/*
 * cpptest.h - Shared test runner for C++ solution files.
 *
 * Define a solve function and TEST_CASES, then call RUN_TESTS().
 *
 * Compile: g++ -std=c++17 -O2 -Wall -Wextra -Isrc/runners -o out solution.cpp
 */

#ifndef CPPTEST_H
#define CPPTEST_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <functional>

struct TestCase {
    std::string label;
    std::vector<int> input_arr;
    int target = 0;
    std::vector<int> expected;
};

static void print_arr(const std::vector<int> &a)
{
    printf("[");
    for (size_t i = 0; i < a.size(); i++) {
        if (i) printf(",");
        printf("%d", a[i]);
    }
    printf("]");
}

#define RUN_TESTS(name, solve_fn, tc_array, tc_count)                         \
    do {                                                                       \
        printf("\n============================================================\n"); \
        printf("  %s\n", name);                                               \
        printf("============================================================\n"); \
        int _passed = 0;                                                      \
        for (int _i = 0; _i < (tc_count); _i++) {                             \
            const TestCase &_tc = (tc_array)[_i];                              \
            std::vector<int> _got = solve_fn(_tc.input_arr, _tc.target);       \
            if (_got == _tc.expected) {                                        \
                _passed++;                                                    \
                printf("  Test %d (%s): PASS\n", _i + 1, _tc.label.c_str());     \
            } else {                                                          \
                printf("  Test %d (%s): FAIL\n", _i + 1, _tc.label.c_str());     \
                printf("    Expected: "); print_arr(_tc.expected); printf("\n"); \
                printf("    Got:      "); print_arr(_got); printf("\n");        \
            }                                                                 \
        }                                                                     \
        printf("\n  %d/%d passed\n", _passed, (tc_count));                     \
        printf("============================================================\n\n"); \
        return _passed == (tc_count) ? 0 : 1;                                 \
    } while (0)

#endif
