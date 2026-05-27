/**
 * P155: Min Stack (Medium)
 * https://leetcode.com/problems/min-stack/
 * Topics: Stack, Design
 *
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * You must implement a solution with O(1) time complexity for each function.
 *
 * Hint: stdin: n, then n blocks of (op_name, value_count, values...)
 *       stdout: one line per result, "null" or integer
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
