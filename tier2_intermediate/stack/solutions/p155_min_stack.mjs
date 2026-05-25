/**
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

function solve(ops, values) {
  const stack = [];
  const minStack = [];
  const result = [];

  for (let i = 0; i < ops.length; i++) {
    const op = ops[i];
    const val = values[i];
    if (op === "MinStack") {
      result.push(null);
    } else if (op === "push") {
      stack.push(val[0]);
      const minVal = minStack.length === 0 ? val[0] : Math.min(val[0], minStack[minStack.length - 1]);
      minStack.push(minVal);
      result.push(null);
    } else if (op === "pop") {
      stack.pop();
      minStack.pop();
      result.push(null);
    } else if (op === "top") {
      result.push(stack[stack.length - 1]);
    } else if (op === "getMin") {
      result.push(minStack[minStack.length - 1]);
    }
  }

  return result;
}

const tests = [
  {
    label: "example 1",
    input: [
      ["MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"],
      [[], [5], [-2], [3], [], [], [], []],
    ],
    expected: [null, null, null, null, -2, null, -2, -2],
  },
  {
    label: "negative values",
    input: [
      ["MinStack", "push", "push", "getMin", "getMin", "push", "getMin", "top", "getMin", "pop", "getMin"],
      [[], [0], [1], [], [], [-3], [], [], [], [], []],
    ],
    expected: [null, null, null, 0, 0, null, -3, -3, -3, null, 0],
  },
  {
    label: "single push then replace",
    input: [["MinStack", "push", "getMin", "top", "pop", "push", "getMin"], [[], [42], [], [], [], [7], []]],
    expected: [null, null, 42, 42, null, null, 7],
  },
  {
    label: "duplicate min values",
    input: [
      ["MinStack", "push", "push", "push", "push", "pop", "getMin", "pop", "getMin", "pop", "getMin"],
      [[], [2], [1], [3], [1], [], [], [], [], [], []],
    ],
    expected: [null, null, null, null, null, null, 1, null, 1, null, 2],
  },
  {
    label: "INT boundary values",
    input: [["MinStack", "push", "push", "getMin", "pop", "getMin"], [[], [-2147483648], [2147483647], [], [], []]],
    expected: [null, null, null, -2147483648, null, -2147483648],
  },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(...t.input);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
