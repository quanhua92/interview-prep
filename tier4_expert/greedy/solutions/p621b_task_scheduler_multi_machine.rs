/*
 * P621b: Task Scheduler with Multiple Machines (Hard)
 * https://leetcode.com/problems/task-scheduler/
 * Topics: Array, Hash Table, Greedy, Counting
 *
 * Given tasks, cooldown n, and m machines, return minimum time intervals.
 * Tasks are space-separated letters on line 1, n on line 2, m on line 3.
 */


fn least_interval_multi(tasks: &[char], n: i32, m: usize) -> i32 {
    let mut freq = [0i32; 26];
    for &t in tasks { freq[(t as u8 - b'A') as usize] += 1; }
    let mut cooldown = vec![[i32::MIN; 26]; m];
    let mut time = 0i32;
    let mut remaining = tasks.len();
    while remaining > 0 {
        let mut assigned = false;
        for mi in 0..m {
            let mut best_task = -1i32;
            let mut best_count = 0i32;
            for t in 0..26 {
                if freq[t] > best_count && cooldown[mi][t] <= time {
                    best_task = t as i32;
                    best_count = freq[t];
                }
            }
            if best_task >= 0 {
                let bt = best_task as usize;
                freq[bt] -= 1;
                cooldown[mi][bt] = time + n + 1;
                remaining -= 1;
                assigned = true;
            }
        }
        if assigned {
            time += 1;
        } else {
            let mut next_time = i32::MAX;
            for mi in 0..m {
                for t in 0..26 {
                    if cooldown[mi][t] > time && cooldown[mi][t] < next_time {
                        next_time = cooldown[mi][t];
                    }
                }
            }
            time = next_time;
        }
    }
    time
}

fn main() {
    let task_line = wasm_libs::read_line();
    let tasks: Vec<char> = task_line.chars().filter(|c| !c.is_whitespace()).collect();
    let n = wasm_libs::read_int();
    let m = wasm_libs::read_int() as usize;
    let result = least_interval_multi(&tasks, n, m);
    wasm_libs::write_int(result);
}
