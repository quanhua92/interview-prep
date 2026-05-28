/*
 * P155: Min Stack (Medium)
 * https://leetcode.com/problems/min-stack/
 * Topics: Stack, Design
 *
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * Implement the MinStack class:
 * You must implement a solution with O(1) time complexity for each function.
 *
 * Example 1:
 *     Input
 *     ["MinStack","push","push","push","getMin","pop","top","getMin"]
 *     [[],[-2],[0],[-3],[],[],[],[]]
 *
 *     Output
 *     [null,null,null,null,-3,null,0,-2]
 *
 * Hint: stdin: n, then n blocks of (op_name, value_count, values...)
 *       stdout: one line per result, "null" or integer
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int st_data[30000], mn_data[30000];
static int st_sz, mn_sz;

static void ms_init(void) {
    abort();
}

static void ms_push(int val) {
    abort();
}

static void ms_pop(void) {
    abort();
}

static int ms_top(void) {
    abort();
}

static int ms_get_min(void) {
    abort();
}

int main(void)
{
    int cn; int *ca = read_ints(&cn); int n = ca[0]; free(ca);
    ms_init();
    for (int i = 0; i < n; i++) {
        char *op = read_line();
        int cc; int *ca = read_ints(&cc); int count = ca[0]; free(ca);
        int val = 0;
        if (count > 0) {
            int dummy;
            int *vals = read_ints(&dummy);
            val = vals[0];
            free(vals);
        }

        if (strcmp(op, "push") == 0) {
            ms_push(val);
            write_string("null");
        } else if (strcmp(op, "pop") == 0) {
            ms_pop();
            write_string("null");
        } else if (strcmp(op, "top") == 0) {
            write_int(ms_top());
        } else if (strcmp(op, "getMin") == 0) {
            write_int(ms_get_min());
        } else {
            write_string("null");
        }
        free(op);
    }
    return 0;
}
