/**
 * P621b: Task Scheduler with Multiple Machines (Hard)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Counting
 *
 * Given tasks, cooldown n, and m machines, return minimum time intervals.
 * Tasks are space-separated letters on line 1, n on line 2, m on line 3.
 */

import { readLine, readInt, writeInt } from "src/wasm_libs/js/io.mjs";

function solve(tasks, n, m) {
  const freq = {};
  for (const t of tasks) {
    freq[t] = (freq[t] || 0) + 1;
  }

  const cooldown = Array.from({ length: m }, () => ({}));

  let time = 0;
  let remaining = tasks.length;

  while (remaining > 0) {
    let assigned = false;
    for (let i = 0; i < m; i++) {
      let bestTask = null;
      let bestCount = 0;
      for (const [task, count] of Object.entries(freq)) {
        if (count > 0 && count > bestCount && (cooldown[i][task] || 0) <= time) {
          bestTask = task;
          bestCount = count;
        }
      }
      if (bestTask !== null) {
        freq[bestTask]--;
        cooldown[i][bestTask] = time + n + 1;
        remaining--;
        assigned = true;
      }
    }

    if (assigned) {
      time++;
    } else {
      let nextTime = Infinity;
      for (const mc of cooldown) {
        for (const t of Object.values(mc)) {
          if (t > time && t < nextTime) {
            nextTime = t;
          }
        }
      }
      time = nextTime;
    }
  }

  return time;
}

const taskLine = readLine();
const tasks = taskLine.split(/\s+/).filter(Boolean);
const n = readInt();
const m = readInt();
writeInt(solve(tasks, n, m));
