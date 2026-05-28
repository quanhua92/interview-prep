/*
 * P621b: Task Scheduler with Multiple Machines (Hard)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Counting
 *
 * Given tasks, cooldown n, and m machines, return minimum time intervals.
 * Tasks are space-separated letters on line 1, n on line 2, m on line 3.
 */

use wasm_libs::*;

fn least_interval_multi(tasks: &[char], n: i32, m: usize) -> i32 {
    todo!();
}

fn main() {
    let task_line = read_line();
    let tasks: Vec<char> = task_line.chars().filter(|c| !c.is_whitespace()).collect();
    let n = read_int();
    let m = read_int() as usize;
    let result = least_interval_multi(&tasks, n, m);
    write_int(result);
}
