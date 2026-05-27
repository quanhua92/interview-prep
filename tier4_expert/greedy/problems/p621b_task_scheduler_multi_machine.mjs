/**
 * P621b: Task Scheduler with Multiple Machines (Hard)
 * Extension of LeetCode 621 - Task Scheduler
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Counting
 *
 * Given tasks, cooldown n, and m machines, return minimum time intervals.
 */

import { readLine, readInt, writeInt } from "src/wasm_libs/js/io.mjs";

function solve(tasks, n, m) {
  throw new Error("NotImplementedError");
}

const taskLine = readLine();
const tasks = taskLine.split(/\s+/).filter(Boolean);
const n = readInt();
const m = readInt();
writeInt(solve(tasks, n, m));
