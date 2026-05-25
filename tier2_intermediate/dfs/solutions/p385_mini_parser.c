/*
 * P385: Mini Parser [PREMIUM] (Medium)
 * https://leetcode.com/problems/mini-parser/
 * Topics: String, Stack, Depth-First Search
 *
 * Given a string s represents the serialization of a nested list, implement a parser to deserialize it and return the deserialized NestedInteger.
 * Each element is either an integer or a list whose elements may also be integers or other lists.
 * Example 1:
 *     Input: s = "324"
 *     Output: 324
 *     Explanation: You should return a NestedInteger object which contains a single integer 324.
 *
 * Example 2:
 *     Input: s = "[123,[456,[789]]]"
 *     Output: [123,[456,[789]]]
 *     Explanation: Return a NestedInteger object containing a nested list with 2 elements:
 *     1. An integer containing value 123.
 *     2. A nested list containing two elements:
 *     i.  An integer containing value 456.
 *     ii. A nested list with one element:
 *     a. An integer containing value 789
 *
 * Constraints:
 *     - 1 <= s.length <= 5 * 104
 *     - s consists of digits, square brackets "[]", negative sign '-', and commas ','.
 *     - s is the serialization of valid NestedInteger.
 *     - All the values in the input are in the range [-106, 106].
 *
 * Template (python3):
 *     # '''
 *     # This is the interface that allows for creating nested lists.
 *     # You should not implement it, or speculate about its implementation
 *     # '''
 *     #class NestedInteger:
 *     #    def __init__(self, value=None):
 *     #        '''
 *     #        If value is not specified, initializes an empty list.
 *     #        Otherwise initializes a single integer equal to value.
 *     #        '''
 *     #
 *     #    def isInteger(self):
 *     #        '''
 *     #        @return True if this NestedInteger holds a single integer, rather than a nested list.
 *     #        :rtype bool
 *     #        '''
 *     #
 *     #    def add(self, elem):
 *     #        '''
 *     #        Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
 *     #        :rtype void
 *     #        '''
 *     #
 *     #    def setInteger(self, value):
 *     #        '''
 *     #        Set this NestedInteger to hold a single integer equal to value.
 *     #        :rtype void
 *     #        '''
 *     #
 *     #    def getInteger(self):
 *     #        '''
 *     #        @return the single integer that this NestedInteger holds, if it holds a single integer
 *     #        Return None if this NestedInteger holds a nested list
 *     #        :rtype int
 *     #        '''
 *     #
 *     #    def getList(self):
 *     #        '''
 *     #        @return the nested list that this NestedInteger holds, if it holds a nested list
 *     #        Return None if this NestedInteger holds a single integer
 *     #        :rtype List[NestedInteger]
 *     #        '''
 *
 *     class Solution:
 *         def deserialize(self, s: str) -> NestedInteger:
 */


#include "ctest.h"
#include <stdlib.h>
#include <string.h>

enum NIType { NI_INT, NI_LIST };

struct NestedInteger {
    enum NIType type;
    int ival;
    struct NestedInteger **list;
    int list_size;
    int list_cap;
};

static void ni_init_int(struct NestedInteger *ni, int val) {
    ni->type = NI_INT; ni->ival = val; ni->list = NULL; ni->list_size = 0; ni->list_cap = 0;
}

static void ni_init_list(struct NestedInteger *ni) {
    ni->type = NI_LIST; ni->ival = 0; ni->list = NULL; ni->list_size = 0; ni->list_cap = 0;
}

static void ni_add(struct NestedInteger *ni, struct NestedInteger *elem) {
    if (ni->list_size >= ni->list_cap) {
        ni->list_cap = ni->list_cap ? ni->list_cap * 2 : 4;
        ni->list = realloc(ni->list, ni->list_cap * sizeof(struct NestedInteger*));
    }
    ni->list[ni->list_size++] = elem;
}

static void ni_free(struct NestedInteger *ni) {
    if (ni->type == NI_LIST) {
        for (int i = 0; i < ni->list_size; i++) ni_free(ni->list[i]);
        free(ni->list);
    }
}

static int ni_eq(struct NestedInteger *a, struct NestedInteger *b) {
    if (a->type != b->type) return 0;
    if (a->type == NI_INT) return a->ival == b->ival;
    if (a->list_size != b->list_size) return 0;
    for (int i = 0; i < a->list_size; i++) {
        if (!ni_eq(a->list[i], b->list[i])) return 0;
    }
    return 1;
}

static struct NestedInteger* deserialize(const char *s) {
    int len = (int)strlen(s);
    if (s[0] != '[') {
        struct NestedInteger *ni = malloc(sizeof(*ni));
        ni_init_int(ni, atoi(s));
        return ni;
    }
    struct NestedInteger *stack[5000];
    int sp = 0;
    struct NestedInteger *root = malloc(sizeof(*root));
    ni_init_list(root);
    stack[sp++] = root;
    int i = 1;
    while (i < len) {
        if (s[i] == '[') {
            struct NestedInteger *ni = malloc(sizeof(*ni));
            ni_init_list(ni);
            ni_add(stack[sp - 1], ni);
            stack[sp++] = ni;
            i++;
        } else if (s[i] == ']') {
            sp--;
            i++;
        } else if (s[i] == ',') {
            i++;
        } else {
            int j = i;
            if (s[j] == '-') j++;
            while (j < len && s[j] >= '0' && s[j] <= '9') j++;
            struct NestedInteger *ni = malloc(sizeof(*ni));
            ni_init_int(ni, atoi(s + i));
            ni_add(stack[sp - 1], ni);
            i = j;
        }
    }
    return root;
}

static void print_ni(struct NestedInteger *ni) {
    if (ni->type == NI_INT) { printf("%d", ni->ival); }
    else {
        printf("[");
        for (int i = 0; i < ni->list_size; i++) {
            if (i) printf(",");
            print_ni(ni->list[i]);
        }
        printf("]");
    }
}

static struct NestedInteger* make_int(int v) { struct NestedInteger *n = malloc(sizeof(*n)); ni_init_int(n, v); return n; }
static struct NestedInteger* make_list(void) { struct NestedInteger *n = malloc(sizeof(*n)); ni_init_list(n); return n; }
static void ml_add(struct NestedInteger *l, struct NestedInteger *e) { ni_add(l, e); }

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    printf("\n============================================================\n");
    printf("  385. Mini Parser\n");
    printf("============================================================\n");

    int passed = 0;

    struct { const char *label; const char *input; struct NestedInteger *expected; } tests[] = {
        {"example 1", "324", NULL},
        {"example 2", "[123,[456,[789]]]", NULL},
        {"negative in list", "[-1]", NULL},
        {"empty list", "[]", NULL},
        {"nested empty list", "[[]]", NULL},
        {"flat list", "[1,2,3]", NULL},
        {"negative integer", "-42", NULL},
    };

    {
        struct NestedInteger *n = make_int(324);
        tests[0].expected = n;
    }
    {
        struct NestedInteger *inner2 = make_list(); ml_add(inner2, make_int(789));
        struct NestedInteger *inner1 = make_list(); ml_add(inner1, make_int(456)); ml_add(inner1, inner2);
        struct NestedInteger *root = make_list(); ml_add(root, make_int(123)); ml_add(root, inner1);
        tests[1].expected = root;
    }
    {
        struct NestedInteger *root = make_list(); ml_add(root, make_int(-1));
        tests[2].expected = root;
    }
    {
        struct NestedInteger *root = make_list();
        tests[3].expected = root;
    }
    {
        struct NestedInteger *inner = make_list();
        struct NestedInteger *root = make_list(); ml_add(root, inner);
        tests[4].expected = root;
    }
    {
        struct NestedInteger *root = make_list(); ml_add(root, make_int(1)); ml_add(root, make_int(2)); ml_add(root, make_int(3));
        tests[5].expected = root;
    }
    {
        struct NestedInteger *n = make_int(-42);
        tests[6].expected = n;
    }

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    for (int i = 0; i < n; i++) {
        struct NestedInteger *got = deserialize(tests[i].input);
        if (ni_eq(got, tests[i].expected)) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n    Expected: ", i + 1, tests[i].label);
            print_ni(tests[i].expected); printf("\n    Got:      "); print_ni(got); printf("\n");
        }
        ni_free(got);
    }
    for (int i = 0; i < n; i++) ni_free(tests[i].expected);

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");

    return passed == n ? 0 : 1;
}
