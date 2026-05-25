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
 * Template (python3):
 *     class Solution:
 *         def leastInterval(self, tasks: List[str], n: int, m: int) -> int:
 *
 * Hint: At each time step, greedily assign the highest-frequency remaining task
 * to each machine, respecting that machine's per-task cooldown. When no machine
 * can run any remaining task, jump directly to the next cooldown expiry.
 */

function solve(tasks, n, m) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "LC621 ex1 m=1", input: [["A", "A", "A", "B", "B", "B"], 2, 1], expected: 8 },
  { label: "LC621 ex2 m=1", input: [["A", "C", "A", "B", "D", "B"], 1, 1], expected: 6 },
  { label: "LC621 ex3 m=1", input: [["A", "A", "A", "B", "B", "B"], 3, 1], expected: 10 },
  { label: "fill idle slots m=1", input: [["A", "A", "A", "B", "B", "B", "C", "C", "D"], 2, 1], expected: 9 },
  { label: "single task type m=1", input: [["A", "A"], 2, 1], expected: 4 },
  { label: "basic parallelism m=2", input: [["A", "A", "A", "B", "B", "B"], 2, 2], expected: 4 },
  { label: "unique tasks m=2", input: [["A", "C", "A", "B", "D", "B"], 1, 2], expected: 3 },
  { label: "large cooldown m=2", input: [["A", "A", "A", "B", "B", "B"], 3, 2], expected: 5 },
  { label: "very many machines m=10", input: [["A", "A", "A", "B", "B", "B"], 2, 10], expected: 1 },
  { label: "single task n=5 m=1", input: [["A"], 5, 1], expected: 1 },
  { label: "single task n=5 m=3", input: [["A"], 5, 3], expected: 1 },
  { label: "more machines than tasks n=0", input: [["A", "B", "C"], 0, 5], expected: 1 },
  { label: "n=0 same task m=2 (per-machine cooldown)", input: [["A", "A", "A", "A"], 0, 2], expected: 2 },
  { label: "m=3 n=1 four unique tasks", input: [["A", "B", "C", "D"], 1, 3], expected: 2 },
  { label: "all same task m=2", input: [["A", "A", "A", "A"], 1, 2], expected: 3 },
  { label: "all same task m=3", input: [["A", "A", "A", "A", "A", "A"], 1, 3], expected: 3 },
  { label: "unique tasks no cooldown m=2", input: [["A", "B", "C", "D", "E"], 0, 2], expected: 3 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(...t.input);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
