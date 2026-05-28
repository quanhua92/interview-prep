/**
 * P388: Longest Absolute File Path [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-absolute-file-path/
 * Topics: String, Stack, Depth-First Search
 */

import { readLine, writeInt } from '../../../wasm_libs/js/io.mjs';

function solve(input) {
  const stack = [0];
  let maxLen = 0;
  const parts = input.split("\n");
  for (const part of parts) {
    let depth = 0;
    let j = 0;
    while (j < part.length && part[j] === "\t") {
      depth++;
      j++;
    }
    const name = part.slice(j);
    while (stack.length > depth + 1) {
      stack.pop();
    }
    if (name.includes(".")) {
      maxLen = Math.max(maxLen, stack[stack.length - 1] + name.length);
    } else {
      stack.push(stack[stack.length - 1] + name.length + 1);
    }
  }
  return maxLen;
}

const lines = [];
while (true) {
  const line = readLine();
  if (!line) break;
  lines.push(line);
}
const input = lines.join("\n");
writeInt(solve(input));
