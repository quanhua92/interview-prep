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
#[allow(unused_imports)]
use rstest;

struct MinStack {
    st: Vec<i32>,
    mn: Vec<i32>,
}

impl MinStack {
    fn new() -> Self { MinStack { st: Vec::new(), mn: Vec::new() } }
    fn push(&mut self, val: i32) {
        todo!()
    }
    fn pop(&mut self) { todo!() }
    fn top(&self) -> i32 { todo!() }
    fn get_min(&self) -> i32 { todo!() }
}

fn main() {
    println!("\n============================================================");
    println!("  155. Min Stack");
    println!("============================================================");

    let mut passed = 0;
    let total = 5;

    {
        let mut ms = MinStack::new();
        ms.push(5); ms.push(-2); ms.push(3);
        let ok = ms.get_min() == -2;
        ms.pop();
        let ok = ok && ms.top() == -2 && ms.get_min() == -2;
        passed += ok as i32;
        println!("  Test 1 (example 1): {}", if ok { "PASS" } else { "FAIL" });
    }
    {
        let mut ms = MinStack::new();
        ms.push(0); ms.push(1);
        let ok = ms.get_min() == 0 && ms.get_min() == 0;
        ms.push(-3);
        let ok = ok && ms.get_min() == -3 && ms.top() == -3 && ms.get_min() == -3;
        ms.pop();
        let ok = ok && ms.get_min() == 0;
        passed += ok as i32;
        println!("  Test 2 (negative values): {}", if ok { "PASS" } else { "FAIL" });
    }
    {
        let mut ms = MinStack::new();
        ms.push(42);
        let ok = ms.get_min() == 42 && ms.top() == 42;
        ms.pop(); ms.push(7);
        let ok = ok && ms.get_min() == 7;
        passed += ok as i32;
        println!("  Test 3 (single push then replace): {}", if ok { "PASS" } else { "FAIL" });
    }
    {
        let mut ms = MinStack::new();
        ms.push(2); ms.push(1); ms.push(3); ms.push(1);
        ms.pop();
        let ok = ms.get_min() == 1;
        ms.pop();
        let ok = ok && ms.get_min() == 1;
        ms.pop();
        let ok = ok && ms.get_min() == 2;
        passed += ok as i32;
        println!("  Test 4 (duplicate min values): {}", if ok { "PASS" } else { "FAIL" });
    }
    {
        let mut ms = MinStack::new();
        ms.push(i32::MIN); ms.push(i32::MAX);
        let ok = ms.get_min() == i32::MIN;
        ms.pop();
        let ok = ok && ms.get_min() == i32::MIN;
        passed += ok as i32;
        println!("  Test 5 (INT boundary values): {}", if ok { "PASS" } else { "FAIL" });
    }

    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");

    std::process::exit(if passed == total { 0 } else { 1 });
}
