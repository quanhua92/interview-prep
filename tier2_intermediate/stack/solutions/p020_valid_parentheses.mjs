/**
 * P20: Valid Parentheses (Easy)
 * https://leetcode.com/problems/valid-parentheses/
 * Topics: String, Stack
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 *
 * Hint: Use a stack to match opening and closing brackets.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(s) {
  const mapping = { ")": "(", "]": "[", "}": "{" };
  const stack = [];
  for (const ch of s) {
    if (ch in mapping) {
      if (stack.length === 0 || stack[stack.length - 1] !== mapping[ch]) {
        return false;
      }
      stack.pop();
    } else {
      stack.push(ch);
    }
  }
  return stack.length === 0;
}

const s = readLine();
writeBool(solve(s));
