/**
 * P493: Reverse Pairs [PREMIUM] (Hard)
 * https://leetcode.com/problems/reverse-pairs/
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set
 *
 * Given an integer array nums, return the number of reverse pairs in the array.
 *
 * Example 1:
 *     Input: nums = [1,3,2,3,1]
 *     Output: 2
 *
 * Example 2:
 *     Input: nums = [2,4,3,5,1]
 *     Output: 3
 *
 * Hint: Use the merge-sort technique.
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../../wasm_libs/js/io.mjs';

function solve(nums) {
  function mergeSort(arr) {
    if (arr.length <= 1) return 0;
    const mid = Math.floor(arr.length / 2);
    const left = arr.slice(0, mid);
    const right = arr.slice(mid);
    let count = mergeSort(left) + mergeSort(right);

    let j = 0;
    for (const num of left) {
      while (j < right.length && num > 2 * right[j]) {
        j++;
      }
      count += j;
    }

    const merged = [];
    let li = 0;
    let ri = 0;
    while (li < left.length && ri < right.length) {
      if (left[li] <= right[ri]) {
        merged.push(left[li++]);
      } else {
        merged.push(right[ri++]);
      }
    }
    while (li < left.length) merged.push(left[li++]);
    while (ri < right.length) merged.push(right[ri++]);

    for (let k = 0; k < arr.length; k++) {
      arr[k] = merged[k];
    }
    return count;
  }

  return mergeSort([...nums]);
}

const nums = readInts();
writeInt(solve(nums));
