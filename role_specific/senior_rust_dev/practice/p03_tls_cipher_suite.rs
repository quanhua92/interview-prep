/*
 * P03: TLS Cipher Suite Negotiation
 *
 * Implement cipher suite negotiation between client and server.
 * Client preference order takes priority.
 *
 * Input: C (client suites count) S (server suites count)
 *        C space-separated client cipher suite IDs
 *        S space-separated server cipher suite IDs
 * Output: First client suite that server supports, or NONE
 *
 * Skills: HashSet lookup, iteration, early exit
 */

use wasm_libs::*;
use std::collections::HashSet;

fn negotiate_cipher_suite(client_suites: &[i32], server_suites: &HashSet<i32>) -> Option<i32> {
    todo!();
}

fn main() {
    let first = read_ints();
    let _c = first[0] as usize;
    let _s = first[1] as usize;
    let client = read_ints();
    let server = read_ints();
    let server_set: HashSet<i32> = server.iter().cloned().collect();
    let result = negotiate_cipher_suite(&client, &server_set);
    match result {
        Some(suite) => write_int(suite),
        None => write_string("NONE"),
    }
    std::process::exit(0);
}
