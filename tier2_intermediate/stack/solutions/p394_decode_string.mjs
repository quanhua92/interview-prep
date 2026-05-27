/**
 * P394: Decode String (Medium)
 * https://leetcode.com/problems/decode-string/
 * Topics: String, Stack, Recursion
 *
 * Given an encoded string, return its decoded string.
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.
 *
 * Hint: Use a stack to handle nested k[encoded] patterns.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(s) {
  const stack = [];
  let currNum = 0;
  let currStr = "";

  for (const ch of s) {
    if (ch >= "0" && ch <= "9") {
      currNum = currNum * 10 + parseInt(ch);
    } else if (ch === "[") {
      stack.push([currNum, currStr]);
      currNum = 0;
      currStr = "";
    } else if (ch === "]") {
      const [repeat, prefix] = stack.pop();
      currStr = prefix + currStr.repeat(repeat);
    } else {
      currStr += ch;
    }
  }

  return currStr;
}

const s = readLine();
writeString(solve(s));
