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


#include "cpptest.h"
#include <vector>
#include <string>

struct NestedInteger {
    bool is_int;
    int ival;
    std::vector<NestedInteger> list;
    NestedInteger() : is_int(false), ival(0) {}
    NestedInteger(int v) : is_int(true), ival(v) {}
    void add(const NestedInteger& elem) { list.push_back(elem); }
};

static bool ni_eq(const NestedInteger& a, const NestedInteger& b) {
    if (a.is_int != b.is_int) return false;
    if (a.is_int) return a.ival == b.ival;
    if (a.list.size() != b.list.size()) return false;
    for (size_t i = 0; i < a.list.size(); i++) {
        if (!ni_eq(a.list[i], b.list[i])) return false;
    }
    return true;
}

static void print_ni(const NestedInteger& ni) {
    if (ni.is_int) { printf("%d", ni.ival); }
    else {
        printf("[");
        for (size_t i = 0; i < ni.list.size(); i++) {
            if (i) printf(",");
            print_ni(ni.list[i]);
        }
        printf("]");
    }
}

static NestedInteger deserialize(const std::string& s) {
    int len = s.size();
    if (s[0] != '[') return NestedInteger(std::stoi(s));
    std::vector<NestedInteger*> stk;
    NestedInteger root;
    stk.push_back(&root);
    int i = 1;
    while (i < len) {
        if (s[i] == '[') {
            stk.back()->list.push_back(NestedInteger());
            stk.push_back(&stk.back()->list.back());
            i++;
        } else if (s[i] == ']') {
            stk.pop_back();
            i++;
        } else if (s[i] == ',') {
            i++;
        } else {
            int j = i;
            if (s[j] == '-') j++;
            while (j < len && s[j] >= '0' && s[j] <= '9') j++;
            stk.back()->list.push_back(NestedInteger(std::stoi(s.substr(i, j - i))));
            i = j;
        }
    }
    return root;
}

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  385. Mini Parser\n");
    printf("============================================================\n");

    int passed = 0;

    struct TC { const char *label; std::string input; NestedInteger expected; };
    TC tests[7];
    tests[0] = {"example 1", "324", NestedInteger(324)};
    tests[1] = {"example 2", "[123,[456,[789]]]", NestedInteger()};
    {
        NestedInteger inner2; inner2.list.push_back(NestedInteger(789));
        NestedInteger inner1; inner1.list.push_back(NestedInteger(456)); inner1.list.push_back(inner2);
        tests[1].expected.list.push_back(NestedInteger(123)); tests[1].expected.list.push_back(inner1);
    }
    tests[2] = {"negative in list", "[-1]", NestedInteger()};
    tests[2].expected.list.push_back(NestedInteger(-1));
    tests[3] = {"empty list", "[]", NestedInteger()};
    tests[4] = {"nested empty list", "[[]]", NestedInteger()};
    tests[4].expected.list.push_back(NestedInteger());
    tests[5] = {"flat list", "[1,2,3]", NestedInteger()};
    tests[5].expected.list.push_back(NestedInteger(1)); tests[5].expected.list.push_back(NestedInteger(2)); tests[5].expected.list.push_back(NestedInteger(3));
    tests[6] = {"negative integer", "-42", NestedInteger(-42)};

    for (int i = 0; i < 7; i++) {
        NestedInteger got = deserialize(tests[i].input);
        if (ni_eq(got, tests[i].expected)) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n    Expected: ", i + 1, tests[i].label);
            print_ni(tests[i].expected); printf("\n    Got:      "); print_ni(got); printf("\n");
        }
    }

    printf("\n  %d/7 passed\n", passed);
    printf("============================================================\n\n");

    return passed == 7 ? 0 : 1;
}
