/**
 * P295: Find Median from Data Stream (Hard)
 * https://leetcode.com/problems/find-median-from-data-stream/
 * Topics: Two Heaps, Design, Sorting, Heap (Priority Queue), Data Stream
 *
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
 * Implement the MedianFinder class:
 *
 * Example 1:
 *     Input
 *     ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
 *     [[], [1], [2], [], [3], []]
 *     Output
 *     [null, null, null, 1.5, null, 2.0]
 *
 *     Explanation
 *     MedianFinder medianFinder = new MedianFinder();
 *     medianFinder.addNum(1);    // arr = [1]
 *     medianFinder.addNum(2);    // arr = [1, 2]
 *     medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
 *     medianFinder.addNum(3);    // arr[1, 2, 3]
 *     medianFinder.findMedian(); // return 2.0
 *
 * Constraints:
 *     - -10^5 <= num <= 10^5
 *     - There will be at least one element in the data structure before calling findMedian.
 *     - At most 5 * 10^4 calls will be made to addNum and findMedian.
 *
 * Template (python3):
 *     class MedianFinder:
 *
 *         def __init__(self):
 *
 *
 *         def addNum(self, num: int) -> None:
 *
 *
 *         def findMedian(self) -> float:
 *
 *
 *
 *     # Your MedianFinder object will be instantiated and called as such:
 *     # obj = MedianFinder()
 *     # obj.addNum(num)
 *     # param_2 = obj.findMedian()
 *
 * Hint: Use a max-heap for the lower half and a min-heap for the upper half.
 */

import { readInts } from '../../wasm_libs/js/io.mjs';

class MinHeap {
  constructor() {
    this.heap = [];
  }
  push(val) {
    this.heap.push(val);
    this._bubbleUp(this.heap.length - 1);
  }
  pop() {
    const top = this.heap[0];
    const last = this.heap.pop();
    if (this.heap.length > 0) {
      this.heap[0] = last;
      this._sinkDown(0);
    }
    return top;
  }
  get size() {
    return this.heap.length;
  }
  peek() {
    return this.heap[0];
  }
  _bubbleUp(i) {
    while (i > 0) {
      const parent = (i - 1) >> 1;
      if (this.heap[i] < this.heap[parent]) {
        [this.heap[i], this.heap[parent]] = [this.heap[parent], this.heap[i]];
        i = parent;
      } else break;
    }
  }
  _sinkDown(i) {
    const n = this.heap.length;
    while (true) {
      let smallest = i;
      const left = 2 * i + 1;
      const right = 2 * i + 2;
      if (left < n && this.heap[left] < this.heap[smallest]) smallest = left;
      if (right < n && this.heap[right] < this.heap[smallest]) smallest = right;
      if (smallest !== i) {
        [this.heap[smallest], this.heap[i]] = [this.heap[i], this.heap[smallest]];
        i = smallest;
      } else break;
    }
  }
}

function solve(stream) {
  const small = new MinHeap();
  const large = new MinHeap();
  const medians = [];

  for (const num of stream) {
    small.push(-num);
    large.push(-small.pop());
    if (large.size > small.size) {
      small.push(-large.pop());
    }

    if (small.size > large.size) {
      medians.push(-small.peek());
    } else if (large.size > small.size) {
      medians.push(large.peek());
    } else {
      medians.push((-small.peek() + large.peek()) / 2);
    }
  }
  return medians;
}

const stream = readInts();
const result = solve(stream);
for (const m of result) {
  console.log(m);
}
