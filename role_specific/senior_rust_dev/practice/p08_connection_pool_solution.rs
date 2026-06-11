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
use std::collections::HashMap;

enum PoolEvent {
    Acquire(String),
    Release(String),
    Tick(i64),
    Status,
}

fn parse_event(line: &str) -> Option<PoolEvent> {
    let parts: Vec<&str> = line.splitn(2, ' ').collect();
    match parts[0] {
        "ACQUIRE" => Some(PoolEvent::Acquire(parts[1].to_string())),
        "RELEASE" => Some(PoolEvent::Release(parts[1].to_string())),
        "TICK" => Some(PoolEvent::Tick(parts[1].parse().ok()?)),
        "STATUS" => Some(PoolEvent::Status),
        _ => None,
    }
}

struct ConnectionPool {
    max_per_host: usize,
    idle_timeout: i64,
    current_time: i64,
    active: HashMap<String, usize>,
    idle: HashMap<String, Vec<i64>>,
}

impl ConnectionPool {
    fn new(max_per_host: usize, idle_timeout: i64) -> Self {
        ConnectionPool {
            max_per_host,
            idle_timeout,
            current_time: 0,
            active: HashMap::new(),
            idle: HashMap::new(),
        }
    }

    fn acquire(&mut self, host: &str) -> bool {
        let total = self.active.get(host).copied().unwrap_or(0)
            + self.idle.get(host).map(|v| v.len()).unwrap_or(0);
        if total >= self.max_per_host {
            return false;
        }
        if let Some(idle_times) = self.idle.get_mut(host) {
            idle_times.retain(|&t| self.current_time - t < self.idle_timeout);
            if let Some(&first_idle) = idle_times.first() {
                idle_times.remove(0);
                *self.active.entry(host.to_string()).or_insert(0) += 1;
                return true;
            }
        }
        if self.active.get(host).copied().unwrap_or(0) < self.max_per_host {
            *self.active.entry(host.to_string()).or_insert(0) += 1;
            true
        } else {
            false
        }
    }

    fn release(&mut self, host: &str) {
        let active = self.active.entry(host.to_string()).or_insert(0);
        if *active > 0 {
            *active -= 1;
            self.idle.entry(host.to_string()).or_insert_with(Vec::new).push(self.current_time);
        }
    }

    fn tick(&mut self, seconds: i64) {
        self.current_time += seconds;
        for idle_times in self.idle.values_mut() {
            idle_times.retain(|&t| self.current_time - t < self.idle_timeout);
        }
    }

    fn status(&self) -> Vec<String> {
        let mut hosts: Vec<String> = self.active.keys().chain(self.idle.keys()).cloned().collect();
        hosts.sort();
        hosts.dedup();
        let mut result = Vec::new();
        for host in &hosts {
            let a = self.active.get(host).copied().unwrap_or(0);
            let i = self.idle.get(host).map(|v| v.len()).unwrap_or(0);
            if a > 0 || i > 0 {
                result.push(format!("{}:active={} idle={}", host, a, i));
            }
        }
        result
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
