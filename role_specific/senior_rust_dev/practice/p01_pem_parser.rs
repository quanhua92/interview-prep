/*
 * P01: PEM Parser
 *
 * Parse PEM-formatted data and extract type + decoded byte length.
 * PEM format: -----BEGIN <TYPE>----- / base64 lines / -----END <TYPE>-----
 *
 * Skills: String parsing, base64 decoding, I/O handling
 *
 * Input:
 *   Line 1: N (number of PEM blocks)
 *   Then N PEM blocks, each with BEGIN line, base64 lines, END line
 *
 * Output:
 *   For each block: <TYPE> <decoded_byte_length>
 */

use wasm_libs::*;

fn parse_pem_blocks(lines: &[String]) -> Vec<(String, usize)> {
    todo!();
}

fn decode_base64(input: &str) -> Vec<u8> {
    todo!();
}

fn main() {
    let n = read_int();
    let mut lines: Vec<String> = Vec::new();
    for _ in 0..n {
        loop {
            let line = read_line();
            lines.push(line.clone());
            if line.starts_with("-----END") {
                break;
            }
        }
    }
    let results = parse_pem_blocks(&lines);
    for (pem_type, byte_len) in &results {
        write_string(&format!("{} {}", pem_type, byte_len));
    }
    std::process::exit(0);
}
