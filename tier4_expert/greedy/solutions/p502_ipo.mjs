/**
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 *
 * Given k, w, profits[], capital[], return maximized capital after at most k projects.
 */

import { readInt, readInts, writeInt } from "src/wasm_libs/js/io.mjs";

function solve(k, w, profits, capital) {
  const projects = capital.map((c, i) => [c, profits[i]]).sort((a, b) => a[0] - b[0]);
  const maxHeap = [];
  let idx = 0;

  for (let round = 0; round < k; round++) {
    while (idx < projects.length && projects[idx][0] <= w) {
      maxHeap.push(projects[idx][1]);
      maxHeap.sort((a, b) => b - a);
      idx++;
    }
    if (maxHeap.length === 0) break;
    w += maxHeap.shift();
  }
  return w;
}

const k = readInt();
const w = readInt();
const profits = readInts();
const capital = readInts();
writeInt(solve(k, w, profits, capital));
