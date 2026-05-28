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
 *     # Your MinStack object will be instantiated and called as such:
 *     # obj = MinStack()
 *     # obj.push(val)
 *     # obj.pop()
 *     # param_3 = obj.top()
 *     # param_4 = obj.getMin()
 *
 * Hint: The solve method receives a list of operations and returns a list of outputs.
 */

use wasm_libs::*;

struct MinStack {
    st: Vec<i32>,
    mn: Vec<i32>,
}

impl MinStack {
    fn new() -> Self { MinStack { st: Vec::new(), mn: Vec::new() } }
    fn push(&mut self, val: i32) {
        self.st.push(val);
        self.mn.push(if self.mn.is_empty() { val } else { val.min(*self.mn.last().unwrap()) });
    }
    fn pop(&mut self) { self.st.pop(); self.mn.pop(); }
    fn top(&self) -> i32 { *self.st.last().unwrap() }
    fn get_min(&self) -> i32 { *self.mn.last().unwrap() }
}

fn main() {
    let n = read_int();
    let mut ms = MinStack::new();
    for _ in 0..n {
        let op = read_line();
        let count = read_int();
        let val = if count > 0 { read_ints()[0] } else { 0 };

        if op == "push" {
            ms.push(val);
            write_string("null");
        } else if op == "pop" {
            ms.pop();
            write_string("null");
        } else if op == "top" {
            write_int(ms.top());
        } else if op == "getMin" {
            write_int(ms.get_min());
        } else {
            write_string("null");
        }
    }
    std::process::exit(0);
}
