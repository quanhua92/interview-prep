/*
 * P621: Task Scheduler (Medium)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting
 *
 * Given tasks and cooldown n, return minimum CPU intervals.
 * Tasks are space-separated letters on one line, followed by n on the next line.
 */

use wasm_libs::*;

fn least_interval(tasks: &[char], n: i32) -> i32 {
    todo!();
}

fn main() {
    let task_line = read_line();
    let tasks: Vec<char> = task_line.chars().filter(|c| !c.is_whitespace()).collect();
    let n = read_int();
    let result = least_interval(&tasks, n);
    write_int(result);
}
