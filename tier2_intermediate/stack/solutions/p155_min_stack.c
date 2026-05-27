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

static void ms_init(void) { st_sz = mn_sz = 0; }

static void ms_push(int val) {
    st_data[st_sz++] = val;
    mn_data[mn_sz] = val;
    if (mn_sz > 0 && mn_data[mn_sz - 1] < val) mn_data[mn_sz] = mn_data[mn_sz - 1];
    mn_sz++;
}

static void ms_pop(void) { st_sz--; mn_sz--; }

static int ms_top(void) { return st_data[st_sz - 1]; }

static int ms_get_min(void) { return mn_data[mn_sz - 1]; }

int main(void)
{
    int n = read_int();
    ms_init();
    for (int i = 0; i < n; i++) {
        char *op = read_line();
        int count = read_int();
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
