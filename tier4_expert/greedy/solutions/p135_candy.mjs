/**
 * P135: Candy (Hard)
 * https://leetcode.com/problems/candy/
 * Topics: Array, Greedy
 *
 * There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
 * You are giving candies to these children subjected to the following requirements:
 * Return the minimum number of candies you need to have to distribute the candies to the children.
 *
 * Example 1:
 *     Input: ratings = [1,0,2]
 *     Output: 5
 *
 * Example 2:
 *     Input: ratings = [1,2,2]
 *     Output: 4
 *
 * Constraints:
 *     - n == ratings.length
 *     - 1 <= n <= 2 * 10^4
 *     - 0 <= ratings[i] <= 2 * 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def candy(self, ratings: List[int]) -> int:
 *
 * Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
 */

import { readInts, writeInt } from "src/wasm_libs/js/io.mjs";

function solve(ratings) {
  const n = ratings.length;
  if (n === 1) return 1;

  const candies = new Array(n).fill(1);

  for (let i = 1; i < n; i++) {
    if (ratings[i] > ratings[i - 1]) {
      candies[i] = candies[i - 1] + 1;
    }
  }

  for (let i = n - 2; i >= 0; i--) {
    if (ratings[i] > ratings[i + 1]) {
      candies[i] = Math.max(candies[i], candies[i + 1] + 1);
    }
  }

  return candies.reduce((a, b) => a + b, 0);
}

const ratings = readInts();
writeInt(solve(ratings));
