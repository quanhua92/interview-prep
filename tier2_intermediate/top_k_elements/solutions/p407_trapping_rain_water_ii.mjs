/**
 * P407: Trapping Rain Water II [PREMIUM] (Hard)
 * https://leetcode.com/problems/trapping-rain-water-ii/
 * Topics: Array, Breadth-First Search, Heap (Priority Queue), Matrix
 *
 * Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
 * Example 1:
 *     Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
 *     Output: 4
 *     Explanation: After the rain, water is trapped between the blocks.
 *     We have two small ponds 1 and 3 units trapped.
 *     The total volume of water trapped is 4.
 *
 * Example 2:
 *     Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
 *     Output: 10
 *
 * Constraints:
 *     - m == heightMap.length
 *     - n == heightMap[i].length
 *     - 1 <= m, n <= 200
 *     - 0 <= heightMap[i][j] <= 2 * 104
 */

import { readLine, readInts, readInt, writeInt, writeInts, writeString, writeBool } from '../../wasm_libs/js/io.mjs';

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
  _bubbleUp(i) {
    while (i > 0) {
      const parent = (i - 1) >> 1;
      if (this.heap[i][0] < this.heap[parent][0]) {
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
      if (left < n && this.heap[left][0] < this.heap[smallest][0]) smallest = left;
      if (right < n && this.heap[right][0] < this.heap[smallest][0]) smallest = right;
      if (smallest !== i) {
        [this.heap[i], this.heap[smallest]] = [this.heap[smallest], this.heap[i]];
        i = smallest;
      } else break;
    }
  }
}

function solve(heightMap) {
  if (!heightMap || !heightMap[0]) return 0;
  const m = heightMap.length;
  const n = heightMap[0].length;
  if (m < 3 || n < 3) return 0;

  const visited = Array.from({ length: m }, () => new Array(n).fill(false));
  const heap = new MinHeap();

  for (let r = 0; r < m; r++) {
    for (const c of [0, n - 1]) {
      heap.push([heightMap[r][c], r, c]);
      visited[r][c] = true;
    }
  }
  for (let c = 1; c < n - 1; c++) {
    for (const r of [0, m - 1]) {
      heap.push([heightMap[r][c], r, c]);
      visited[r][c] = true;
    }
  }

  let water = 0;
  const dirs = [[-1, 0], [1, 0], [0, -1], [0, 1]];

  while (heap.size > 0) {
    const [h, r, c] = heap.pop();
    for (const [dr, dc] of dirs) {
      const nr = r + dr;
      const nc = c + dc;
      if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
        visited[nr][nc] = true;
        water += Math.max(0, h - heightMap[nr][nc]);
        heap.push([Math.max(h, heightMap[nr][nc]), nr, nc]);
      }
    }
  }

  return water;
}

const dims = readInts();
const m = dims[0], n = dims[1];
const heightMap = [];
for (let i = 0; i < m; i++) heightMap.push(readInts());
writeInt(solve(heightMap));
