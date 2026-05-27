/**
 * P11: Container With Most Water (Medium)
 * https://leetcode.com/problems/container-with-most-water/
 * Topics: Array, Two Pointers, Greedy
 * 
 * You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
 * Find two lines that together with the x-axis form a container, such that the container contains the most water.
 * Return the maximum amount of water a container can store.
 * Notice that you may not slant the container.
 * 
 * Example 1:
 *     Input: height = [1,8,6,2,5,4,8,3,7]
 *     Output: 49
 *     Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
 * 
 * Example 2:
 *     Input: height = [1,1]
 *     Output: 1
 * 
 * Constraints:
 *     - n == height.length
 *     - 2 <= n <= 105
 *     - 0 <= height[i] <= 104
 * 
 * Hints:
 *     - If you simulate the problem, it will be O(n^2) which is not efficient.
 *     - Try to use two-pointers. Set one pointer to the left and one to the right of the array. Always move the pointer that points to the lower line.
 *     - How can you calculate the amount of water at each step?
 * 
 * Hint: Start with pointers at both ends and move the shorter one inward.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(height) {
  let left = 0, right = height.length - 1;
  let maxArea = 0;
  while (left < right) {
    const area = Math.min(height[left], height[right]) * (right - left);
    maxArea = Math.max(maxArea, area);
    if (height[left] < height[right]) {
      left++;
    } else {
      right--;
    }
  }
  return maxArea;
}

const height = readInts();
writeInt(solve(height));
