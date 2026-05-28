/**
 * P621b: Task Scheduler with Multiple Machines (Hard)
 * Extension of LeetCode 621 - Task Scheduler
 * https://leetcode.com/problems/task-scheduler/
 *
 * Topics: Array, Hash Table, Greedy, Counting
 *
 * You are given an array of CPU tasks, each labeled with a letter from A to Z,
 * a cooldown period n, and m identical parallel machines.
 *
 * Each machine can execute at most one task per time interval. Tasks can be
 * completed in any order across the machines. Cooldown is tracked per-machine:
 * if machine M runs task A at time t, that machine M cannot run task A again
 * until time t + n + 1. Other machines are unaffected and may run task A at
 * any time (including simultaneously with M).
 *
 * Return the minimum number of time intervals required to complete all tasks
 * across all m machines.
 *
 * Example 1:
 *     Input: tasks = ["A","A","A","B","B","B"], n = 2, m = 1
 *     Output: 8
 *     Explanation: This is the original LeetCode 621 problem.
 *     A -> B -> idle -> A -> B -> idle -> A -> B
 *
 * Example 2:
 *     Input: tasks = ["A","A","A","B","B","B"], n = 2, m = 2
 *     Output: 4
 *     Explanation: Cooldown is per-machine, so machines can swap tasks.
 *     t=0: M1=A, M2=B | t=1: M1=B, M2=A | t=2: idle | t=3: M1=A, M2=B
 *     At t=1, M1 can run B (M1 never ran B) and M2 can run A (M2 never ran A).
 *
 * Example 3:
 *     Input: tasks = ["A","C","A","B","D","B"], n = 1, m = 2
 *     Output: 3
 *     Explanation: Each task appears at most twice. With 2 machines:
 *     t=0: M1=A, M2=B | t=1: M1=C, M2=D | t=2: M1=A, M2=B | Done in 3.
 *
 * Example 4:
 *     Input: tasks = ["A","A","A","B","B","B"], n = 3, m = 2
 *     Output: 5
 *     Explanation: Machines swap tasks at t=1, then wait for cooldown.
 *     t=0: M1=A, M2=B | t=1: M1=B, M2=A | t=2-3: idle | t=4: M1=A, M2=B
 *
 * Example 5:
 *     Input: tasks = ["A"], n = 5, m = 3
 *     Output: 1
 *     Explanation: Only one task, completed in a single interval regardless of
 *     cooldown or number of machines.
 *
 * Constraints:
 *     - 1 <= tasks.length <= 10^4
 *     - tasks[i] is an uppercase English letter.
 *     - 0 <= n <= 100
 *     - 1 <= m <= 26
 *
 * Hint: At each time step, greedily assign the highest-frequency remaining task
 * to each machine, respecting that machine's per-task cooldown. When no machine
 * can run any remaining task, jump directly to the next cooldown expiry.
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
