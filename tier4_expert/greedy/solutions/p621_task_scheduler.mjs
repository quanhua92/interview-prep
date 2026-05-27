/**
 * P621: Task Scheduler (Medium)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting
 *
 * Given tasks and cooldown n, return minimum CPU intervals.
 * Tasks are space-separated letters on one line, followed by n on the next line.
 */

import { readLine, readInt, writeInt } from "src/wasm_libs/js/io.mjs";

function solve(tasks, n) {
  const freq = {};
  for (const t of tasks) {
    freq[t] = (freq[t] || 0) + 1;
  }
  const maxFreq = Math.max(...Object.values(freq));
  const maxCount = Object.values(freq).filter((v) => v === maxFreq).length;
  return Math.max(tasks.length, (maxFreq - 1) * (n + 1) + maxCount);
}

const taskLine = readLine();
const tasks = taskLine.split(/\s+/).filter(Boolean);
const n = readInt();
writeInt(solve(tasks, n));
