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

fn process_tunnel_attempts(n: usize, read_all_lines: &[String]) -> Vec<TunnelResult> {
    todo!();
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
