/*
 * P07: Sliding Window Latency Percentiles
 *
 * Calculate p50, p95, and p99 latency percentiles from a stream of
 * request latencies using a sliding window of the last N requests.
 *
 * Input: window_size N, then latency values (one per line), terminated by "-1"
 * Output: After each latency reading, print p50 p95 p99 of the current window.
 *
 * Skills: Sorting, sliding window, percentile calculation
 */

use wasm_libs::*;

fn calculate_percentiles(window: &mut Vec<i32>) -> (i32, i32, i32) {
    todo!();
}

fn main() {
    let n = read_int();
    let mut window: Vec<i32> = Vec::new();
    loop {
        let line = read_line();
        let latency: i32 = match line.trim().parse() {
            Ok(v) => v,
            Err(_) => break,
        };
        if latency == -1 { break; }
        window.push(latency);
        if window.len() > n as usize {
            window.remove(0);
        }
        let (p50, p95, p99) = calculate_percentiles(&mut window);
        write_string(&format!("p50={} p95={} p99={}", p50, p95, p99));
    }
    std::process::exit(0);
}
