/**
 * P347: Top K Frequent Elements (Medium)
 * https://leetcode.com/problems/top-k-frequent-elements/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Heap (Priority Queue), Bucket Sort, Counting, Quickselect
 *
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
 *
 * Example 1:
 *     Input: nums = [1,1,1,2,2,3], k = 2
 *     Output: [1,2]
 *
 * Example 2:
 *     Input: nums = [1], k = 1
 *     Output: [1]
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - -104 <= nums[i] <= 104
 *     - k is in the range [1, the number of unique elements in the array].
 *     - It is guaranteed that the answer is unique.
 *
 * Follow up:
 *     - Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
 *
 * Hint: Use a frequency counter and a min-heap of size k.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

function solve(nums, k) {
  const count = new Map();
  for (const n of nums) {
    count.set(n, (count.get(n) || 0) + 1);
  }
  return [...count.entries()]
    .sort((a, b) => b[1] - a[1] || b[0] - a[0])
    .slice(0, k)
    .map((e) => e[0]);
}

const nums = readInts();
const k = readInt();
writeInts(solve(nums, k));
