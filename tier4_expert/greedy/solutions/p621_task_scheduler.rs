/*
 * P621: Task Scheduler (Medium)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Sorting, Heap, Counting
 *
 * Given tasks and cooldown n, return minimum CPU intervals.
 * Tasks are space-separated letters on one line, followed by n on the next line.
 */


fn least_interval(tasks: &[char], n: i32) -> i32 {
    let mut freq = [0i32; 26];
    for &t in tasks { freq[(t as u8 - b'A') as usize] += 1; }
    let max_freq = *freq.iter().max().unwrap();
    let max_count = freq.iter().filter(|&&f| f == max_freq).count() as i32;
    let formula = (max_freq - 1) * (n + 1) + max_count;
    formula.max(tasks.len() as i32)
}

fn main() {
    let task_line = wasm_libs::read_line();
    let tasks: Vec<char> = task_line.chars().filter(|c| !c.is_whitespace()).collect();
    let n = wasm_libs::read_int();
    let result = least_interval(&tasks, n);
    wasm_libs::write_int(result);
}
