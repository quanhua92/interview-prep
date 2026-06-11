/*
 * P08: Connection Pool Manager
 *
 * Simulate a connection pool for an HTTP proxy. Track connections
 * per host, enforce max connections, handle idle timeout and eviction.
 *
 * Input: max_per_host (global max per host), idle_timeout (seconds)
 *        then events (one per line) until "END":
 *   - ACQUIRE host
 *   - RELEASE host
 *   - TICK seconds (advance time)
 *   - STATUS (print pool state)
 *
 * Output: For each ACQUIRE: ALLOWED or REJECTED
 *         For each STATUS: host -> active/idle counts
 *
 * Skills: HashMap, state management, pool eviction
 */

use wasm_libs::*;

enum PoolEvent {
    Acquire(String),
    Release(String),
    Tick(i64),
    Status,
}

fn parse_event(line: &str) -> Option<PoolEvent> {
    todo!();
}

struct ConnectionPool {
    max_per_host: usize,
    idle_timeout: i64,
    current_time: i64,
    active: std::collections::HashMap<String, usize>,
    idle: std::collections::HashMap<String, Vec<i64>>,
}

impl ConnectionPool {
    fn new(max_per_host: usize, idle_timeout: i64) -> Self {
        todo!();
    }

    fn acquire(&mut self, host: &str) -> bool {
        todo!();
    }

    fn release(&mut self, host: &str) {
        todo!();
    }

    fn tick(&mut self, seconds: i64) {
        todo!();
    }

    fn status(&self) -> Vec<String> {
        todo!();
    }
}

fn main() {
    let params = read_ints();
    let max_per_host = params[0] as usize;
    let idle_timeout = params[1] as i64;
    let mut pool = ConnectionPool::new(max_per_host, idle_timeout);

    loop {
        let line = read_line();
        if line == "END" { break; }
        let event = parse_event(&line).unwrap();
        match event {
            PoolEvent::Acquire(host) => {
                let allowed = pool.acquire(&host);
                if allowed {
                    write_string(&format!("ACQUIRE {} ALLOWED", host));
                } else {
                    write_string(&format!("ACQUIRE {} REJECTED", host));
                }
            }
            PoolEvent::Release(host) => {
                pool.release(&host);
                write_string(&format!("RELEASE {} OK", host));
            }
            PoolEvent::Tick(seconds) => {
                pool.tick(seconds);
                write_string(&format!("TICK {} OK", seconds));
            }
            PoolEvent::Status => {
                let lines = pool.status();
                for l in &lines {
                    write_string(l);
                }
            }
        }
    }
    std::process::exit(0);
}
