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
  throw new Error("NotImplementedError");
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
