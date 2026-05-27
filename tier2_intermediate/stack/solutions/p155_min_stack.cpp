/*
 * P155: Min Stack (Medium)
 * https://leetcode.com/problems/min-stack/
 * Topics: Stack, Design
 *
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * Implement the MinStack class:
 * You must implement a solution with O(1) time complexity for each function.
 *
 * Hint: stdin: n, then n blocks of (op_name, value_count, values...)
 *       stdout: one line per result, "null" or integer
 */

#include "io.h"
#include <algorithm>
#include <vector>
#include <string>

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

int main(void)
{
    int n = read_int();
    MinStack ms;
    for (int i = 0; i < n; i++) {
        std::string op = read_line();
        int count = read_int();
        int val = 0;
        if (count > 0) {
            std::vector<int> vals = read_ints();
            val = vals[0];
        }

        if (op == "push") {
            ms.push(val);
            write_string("null");
        } else if (op == "pop") {
            ms.pop();
            write_string("null");
        } else if (op == "top") {
            write_int(ms.top());
        } else if (op == "getMin") {
            write_int(ms.getMin());
        } else {
            write_string("null");
        }
    }
    return 0;
}
