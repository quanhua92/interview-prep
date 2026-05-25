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
 *     Explanation
 *     MinStack minStack = new MinStack();
 *     minStack.push(-2);
 *     minStack.push(0);
 *     minStack.push(-3);
 *     minStack.getMin(); // return -3
 *     minStack.pop();
 *     minStack.top();    // return 0
 *     minStack.getMin(); // return -2
 * 
 * Constraints:
 *     - -231 <= val <= 231 - 1
 *     - Methods pop, top and getMin operations will always be called on non-empty stacks.
 *     - At most 3 * 104 calls will be made to push, pop, top, and getMin.
 * 
 * Hints:
 *     - Consider each node in the stack having a minimum value. (Credits to @aakarshmadhavan)
 * 
 * Template (python3):
 *     class MinStack:
 * 
 *         def __init__(self):
 * 
 * 
 *         def push(self, val: int) -> None:
 * 
 * 
 *         def pop(self) -> None:
 * 
 * 
 *         def top(self) -> int:
 * 
 * 
 *         def getMin(self) -> int:
 * 
 * 
 * 
 *     # Your MinStack object will be instantiated and called as such:
 *     # obj = MinStack()
 *     # obj.push(val)
 *     # obj.pop()
 *     # param_3 = obj.top()
 *     # param_4 = obj.getMin()
 * 
 * Hint: The solve method receives a list of operations and returns a list of outputs.
 */
#include "ctest.h"

typedef struct { int is_null; int value; } MSRes;

static int st_data[30000], mn_data[30000];
static int st_sz, mn_sz;

static void ms_init(void) {
    /* TODO: Implement */
    return 0;
}

static void ms_push(int val) {
    /* TODO: Implement */
    return 0;
}

static void ms_pop(void) {
    /* TODO: Implement */
    return 0;
}

static int ms_top(void) {
    /* TODO: Implement */
    return 0;
}

static int ms_get_min(void) {
    /* TODO: Implement */
    return 0;
}

static int ms_run(const char *ops, const int *vals, int n, MSRes *out) {
    /* TODO: Implement */
    return 0;
}

static int check_ms(const char *label, const char *ops, const int *vals, int nvals,
                    const MSRes *expected, int nexpected) {
    (void)nvals;
    MSRes got[100];
    int n = ms_run(ops, vals, (int)strlen(ops), got);
    if (n != nexpected) {
        printf("  (%s): FAIL (count %d vs %d)\n", label, n, nexpected);
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (got[i].is_null != expected[i].is_null ||
            (!got[i].is_null && got[i].value != expected[i].value)) {
            printf("  (%s): FAIL at idx %d\n", label, i);
            return 0;
        }
    }
    printf("  (%s): PASS\n", label);
    return 1;
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  155. Min Stack\n");
    printf("============================================================\n");

    int passed = 0;
    int total = 5;

    passed += check_ms("example 1", "IPPPMOTM",
        (const int[]){5, -2, 3}, 3,
        (const MSRes[]){{1,0},{1,0},{1,0},{1,0},{0,-2},{1,0},{0,-2},{0,-2}}, 8);

    passed += check_ms("negative values", "IPPMMPMTMOM",
        (const int[]){0, 1, -3}, 3,
        (const MSRes[]){{1,0},{1,0},{1,0},{0,0},{0,0},{1,0},{0,-3},{0,-3},{0,-3},{1,0},{0,0}}, 11);

    passed += check_ms("single push then replace", "IPMTOPM",
        (const int[]){42, 7}, 2,
        (const MSRes[]){{1,0},{1,0},{0,42},{0,42},{1,0},{1,0},{0,7}}, 7);

    passed += check_ms("duplicate min values", "IPPPPOMOMOM",
        (const int[]){2, 1, 3, 1}, 4,
        (const MSRes[]){{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{0,1},{1,0},{0,1},{1,0},{0,2}}, 11);

    passed += check_ms("INT boundary values", "IPPMOM",
        (const int[]){-2147483647 - 1, 2147483647}, 2,
        (const MSRes[]){{1,0},{1,0},{1,0},{0,-2147483647 - 1},{1,0},{0,-2147483647 - 1}}, 6);

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
