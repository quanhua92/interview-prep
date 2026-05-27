/**
 * P621: Task Scheduler (Medium)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting
 *
 * Given tasks and cooldown n, return minimum CPU intervals.
 */

import { readLine, readInt, writeInt } from "src/wasm_libs/js/io.mjs";

function solve(tasks, n) {
  throw new Error("NotImplementedError");
}

const taskLine = readLine();
const tasks = taskLine.split(/\s+/).filter(Boolean);
const n = readInt();
writeInt(solve(tasks, n));
