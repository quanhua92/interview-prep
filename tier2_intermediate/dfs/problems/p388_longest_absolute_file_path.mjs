/**
 * P388: Longest Absolute File Path [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-absolute-file-path/
 * Topics: String, Stack, Depth-First Search
 *
 * Given a string input representing the file system, return the length of the longest absolute path to a file.
 *
 * Example 1:
 *     Input: input = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
 *     Output: 20
 *
 * Example 2:
 *     Input: input = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
 *     Output: 32
 *
 * Example 3:
 *     Input: input = "a"
 *     Output: 0
 *
 * Constraints:
 *     - 1 <= input.length <= 10^4
 *
 * Template (javascript):
 *     function solve(input: string): number
 */

import { readLine, writeInt } from '../../../wasm_libs/js/io.mjs';

function solve(input) {
  throw new Error("NotImplementedError");
}

const lines = [];
while (true) {
  const line = readLine();
  if (!line) break;
  lines.push(line);
}
const input = lines.join("\n");
writeInt(solve(input));
