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

#include "cpptest.h"
#include <vector>
#include <string>
#include <climits>

class MinStack {
    std::vector<int> st, mn;
public:
    MinStack() {}
    void push(int val) {
        st.push_back(val);
        mn.push_back(mn.empty() ? val : std::min(val, mn.back()));
    }
    void pop() { st.pop_back(); mn.pop_back(); }
    int top() { return st.back(); }
    int getMin() { return mn.back(); }
};

int main() {
    (void)print_arr;

    printf("\n============================================================\n");
    printf("  155. Min Stack\n");
    printf("============================================================\n");

    int passed = 0;
    int total = 5;

    {
        MinStack ms;
        ms.push(5); ms.push(-2); ms.push(3);
        int ok = ms.getMin() == -2;
        ms.pop();
        ok = ok && ms.top() == -2 && ms.getMin() == -2;
        passed += ok;
        printf("  Test 1 (example 1): %s\n", ok ? "PASS" : "FAIL");
    }
    {
        MinStack ms;
        ms.push(0); ms.push(1);
        int ok = ms.getMin() == 0 && ms.getMin() == 0;
        ms.push(-3);
        ok = ok && ms.getMin() == -3 && ms.top() == -3 && ms.getMin() == -3;
        ms.pop();
        ok = ok && ms.getMin() == 0;
        passed += ok;
        printf("  Test 2 (negative values): %s\n", ok ? "PASS" : "FAIL");
    }
    {
        MinStack ms;
        ms.push(42);
        int ok = ms.getMin() == 42 && ms.top() == 42;
        ms.pop(); ms.push(7);
        ok = ok && ms.getMin() == 7;
        passed += ok;
        printf("  Test 3 (single push then replace): %s\n", ok ? "PASS" : "FAIL");
    }
    {
        MinStack ms;
        ms.push(2); ms.push(1); ms.push(3); ms.push(1);
        ms.pop();
        int ok = ms.getMin() == 1;
        ms.pop();
        ok = ok && ms.getMin() == 1;
        ms.pop();
        ok = ok && ms.getMin() == 2;
        passed += ok;
        printf("  Test 4 (duplicate min values): %s\n", ok ? "PASS" : "FAIL");
    }
    {
        MinStack ms;
        ms.push(INT_MIN); ms.push(INT_MAX);
        int ok = ms.getMin() == INT_MIN;
        ms.pop();
        ok = ok && ms.getMin() == INT_MIN;
        passed += ok;
        printf("  Test 5 (INT boundary values): %s\n", ok ? "PASS" : "FAIL");
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
