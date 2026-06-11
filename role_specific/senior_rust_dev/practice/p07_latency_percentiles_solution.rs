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

fn percentile(sorted: &[i32], p: f64) -> i32 {
    if sorted.is_empty() { return 0; }
    let idx = ((p / 100.0) * (sorted.len() as f64 - 1.0)).round() as usize;
    sorted[idx.min(sorted.len() - 1)]
}

fn calculate_percentiles(window: &mut Vec<i32>) -> (i32, i32, i32) {
    window.sort();
    let p50 = percentile(window, 50.0);
    let p95 = percentile(window, 95.0);
    let p99 = percentile(window, 99.0);
    (p50, p95, p99)
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
