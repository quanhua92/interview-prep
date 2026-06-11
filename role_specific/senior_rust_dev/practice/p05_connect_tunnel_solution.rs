/*
 * P05: CONNECT Tunnel Simulation
 *
 * Simulate HTTP CONNECT tunnel establishment between client-proxy-upstream.
 * Parse the handshake and data transfer events.
 *
 * Input: N attempts, each with CONNECT line, response line,
 *        optional data lines (C/S prefix) until "---" separator.
 * Output: Tunnel status and data events for each attempt.
 *
 * Skills: State machine, string parsing, protocol understanding
 */

use wasm_libs::*;

enum TunnelStatus {
    Open,
    Rejected,
    Error,
}

struct TunnelResult {
    target: String,
    status: TunnelStatus,
    data_events: Vec<(char, usize)>,
}

fn parse_connect_target(line: &str) -> Option<String> {
    let parts: Vec<&str> = line.splitn(2, ' ').collect();
    if parts.len() < 2 || parts[0] != "CONNECT" {
        return None;
    }
    Some(parts[1].split_whitespace().next().unwrap_or("").to_string())
}

fn parse_status_code(line: &str) -> i32 {
    let parts: Vec<&str> = line.split_whitespace().collect();
    if parts.len() >= 2 {
        parts[1].parse().unwrap_or(0)
    } else {
        0
    }
}

fn process_tunnel_attempts(n: usize, read_all_lines: &[String]) -> Vec<TunnelResult> {
    let mut results = Vec::new();
    let mut idx = 0;

    for _ in 0..n {
        let mut result = TunnelResult {
            target: String::new(),
            status: TunnelStatus::Error,
            data_events: Vec::new(),
        };

        if idx >= read_all_lines.len() { break; }
        result.target = parse_connect_target(&read_all_lines[idx]).unwrap_or_default();
        idx += 1;

        if idx >= read_all_lines.len() { break; }
        let status_code = parse_status_code(&read_all_lines[idx]);
        idx += 1;

        match status_code {
            200 => {
                result.status = TunnelStatus::Open;
                while idx < read_all_lines.len() && read_all_lines[idx] != "---" {
                    let line = &read_all_lines[idx];
                    if !line.is_empty() {
                        let direction = line.chars().next().unwrap_or(' ');
                        let msg_len = if line.len() > 2 { line[2..].len() } else { 0 };
                        if direction == 'C' || direction == 'S' {
                            result.data_events.push((direction, msg_len));
                        }
                    }
                    idx += 1;
                }
            }
            403 => result.status = TunnelStatus::Rejected,
            502 => result.status = TunnelStatus::Rejected,
            _ => result.status = TunnelStatus::Error,
        }

        if idx < read_all_lines.len() && read_all_lines[idx] == "---" {
            idx += 1;
        }

        results.push(result);
    }

    results
}

fn main() {
    let n = read_int();
    let mut all_lines: Vec<String> = Vec::new();
    let mut attempts_done = 0;
    while attempts_done < n {
        let line = read_line();
        all_lines.push(line);
        let last = all_lines.last().unwrap();
        if last == "---" {
            attempts_done += 1;
        }
    }
    let results = process_tunnel_attempts(n as usize, &all_lines);
    for result in &results {
        let status_str = match result.status {
            TunnelStatus::Open => "TUNNEL_OPEN",
            TunnelStatus::Rejected => "REJECTED",
            TunnelStatus::Error => "ERROR",
        };
        write_string(&format!("{} {}", result.target, status_str));
        for (direction, len) in &result.data_events {
            write_string(&format!("DATA {} {}", direction, len));
        }
    }
    std::process::exit(0);
}
