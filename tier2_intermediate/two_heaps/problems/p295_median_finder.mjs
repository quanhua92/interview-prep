/**
 * P295: Find Median from Data Stream (Hard)
 * https://leetcode.com/problems/find-median-from-data-stream/
 * Topics: Two Heaps, Design, Sorting, Heap (Priority Queue), Data Stream
 *
 * The median is the middle value in an ordered integer list. If the size of the list is even,
 * there is no middle value, and the median is the mean of the two middle values.
 *
 * Constraints:
 *     - -10^5 <= num <= 10^5
 *     - There will be at least one element in the data structure before calling findMedian.
 *     - At most 5 * 10^4 calls will be made to addNum and findMedian.
 *
 * Hint: Use a max-heap for the lower half and a min-heap for the upper half.
 */

import { readInts, writeString } from '../../wasm_libs/js/io.mjs';

function solve(stream) {
  throw new Error("NotImplementedError");
}

const stream = readInts();
const result = solve(stream);
for (const m of result) {
  writeString(m);
}
