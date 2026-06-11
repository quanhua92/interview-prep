/*
 * P02: Certificate Expiry Checker
 *
 * Given domain names and days until certificate expiry, report
 * certificates expiring within a threshold. Sort by urgency.
 *
 * Skills: Sorting, filtering, string handling
 *
 * Input:
 *   Line 1: N (number of certs) and T (threshold in days)
 *   Next N lines: <domain> <days_until_expiry>
 *
 * Output:
 *   For each cert expiring within T days (sorted by days ascending):
 *   <domain> <days>
 */

use wasm_libs::*;

struct CertEntry {
    domain: String,
    days_remaining: i32,
}

fn check_certificates(entries: Vec<CertEntry>, threshold: i32) -> Vec<(String, i32)> {
    todo!();
}

fn main() {
    let first = read_ints();
    let n = first[0] as usize;
    let threshold = first[1];
    let mut entries = Vec::new();
    for _ in 0..n {
        let line = read_line();
        let parts: Vec<&str> = line.splitn(2, ' ').collect();
        let domain = parts[0].to_string();
        let days: i32 = parts[1].parse().unwrap();
        entries.push(CertEntry { domain, days_remaining: days });
    }
    let results = check_certificates(entries, threshold);
    for (domain, days) in &results {
        write_string(&format!("{} {}", domain, days));
    }
    std::process::exit(0);
}
