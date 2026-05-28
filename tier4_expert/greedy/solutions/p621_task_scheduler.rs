/*
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

use wasm_libs::*;

fn least_interval(tasks: &[char], n: i32) -> i32 {
    let mut freq = [0i32; 26];
    for &t in tasks { freq[(t as u8 - b'A') as usize] += 1; }
    let max_freq = *freq.iter().max().unwrap();
    let max_count = freq.iter().filter(|&&f| f == max_freq).count() as i32;
    let formula = (max_freq - 1) * (n + 1) + max_count;
    formula.max(tasks.len() as i32)
}

fn main() {
    let task_line = read_line();
    let tasks: Vec<char> = task_line.chars().filter(|c| !c.is_whitespace()).collect();
    let n = read_int();
    let result = least_interval(&tasks, n);
    write_int(result);
}
