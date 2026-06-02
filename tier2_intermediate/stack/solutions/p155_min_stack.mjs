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
 *     - -2^31 <= val <= 2^31 - 1
 *     - Methods pop, top and getMin operations will always be called on non-empty stacks.
 *     - At most 3 * 10^4 calls will be made to push, pop, top, and getMin.
 *
 * Hint: Consider each node in the stack having a minimum value. (Credits to @aakarshmadhavan)
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

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

const n = readInt();
const ops = [];
const values = [];
for (let i = 0; i < n; i++) {
  const op = readLine();
  ops.push(op);
  const count = readInt();
  if (count > 0) {
    values.push(readInts());
  } else {
    values.push([]);
  }
}
const results = solve(ops, values);
for (const r of results) {
  if (r === null) {
    writeString("null");
  } else {
    writeInt(r);
  }
}
