/**
 * P621: Task Scheduler (Medium)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting
 * 
 * You are given an array of CPU tasks, each labeled with a letter from A to Z, and a number n.
 * Each CPU interval can be idle or allow the completion of one task. Tasks can be completed in any order, but there's a constraint: there has to be a gap of at least n intervals between two tasks with the same label.
 * Return the minimum number of CPU intervals required to complete all tasks.
 * 
 * Example 1:
 *     Input: tasks = ["A","A","A","B","B","B"], n = 2
 *     Output: 8
 *     Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.
 *     After completing task A, you must wait two intervals before doing A again. The same applies to task B. In the 3rd interval, neither A nor B can be done, so you idle.
 * 
 * Example 2:
 *     Input: tasks = ["A","C","A","B","D","B"], n = 1
 *     Output: 6
 *     Explanation: A possible sequence is: A -> B -> C -> D -> A -> B.
 * 
 * Example 3:
 *     Input: tasks = ["A","A","A", "B","B","B"], n = 3
 *     Output: 10
 *     Explanation: A possible sequence is: A -> B -> idle -> idle -> A -> B -> idle -> idle -> A -> B.
 * 
 * Constraints:
 *     - 1 <= tasks.length <= 104
 *     - tasks[i] is an uppercase English letter.
 *     - 0 <= n <= 100
 * 
 * Template (python3):
 *     class Solution:
 *         def leastInterval(self, tasks: List[str], n: int) -> int:
 * 
 * Hint: The idle slots are determined by the most frequent task. Formula: max((maxFreq - 1) * (n + 1) + countMaxFreq, len(tasks)).
 */
function solve(tasks, n)
  const freq = {};
  for (const t of tasks)
    freq[t] = (freq[t] || 0) + 1;
  }
  const maxFreq = Math.max(...Object.values(freq));
  const maxCount = Object.values(freq).filter((v) => v === maxFreq).length;
  return Math.max(tasks.length, (maxFreq - 1) * (n + 1) + maxCount); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [["A", "A", "A", "B", "B", "B"], 2], expected: 8 },
  { label: "example 2", input: [["A", "C", "A", "B", "D", "B"], 1], expected: 6 },
  { label: "example 3", input: [["A", "A", "A", "B", "B", "B"], 3], expected: 10 },
  { label: "tasks fill all idle slots", input: [["A", "A", "A", "B", "B", "B", "C", "C", "D"], 2], expected: 9 },
  { label: "single task type with long cooldown", input: [["A", "A"], 2], expected: 4 },
  { label: "no cooldown", input: [["A", "A", "B", "B"], 0], expected: 4 },
  { label: "single task", input: [["A"], 5], expected: 1 },
  { label: "all same task", input: [["A", "A", "A", "A"], 2], expected: 10 },
  { label: "unique tasks large n", input: [["A", "B", "C"], 100], expected: 3 },
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
