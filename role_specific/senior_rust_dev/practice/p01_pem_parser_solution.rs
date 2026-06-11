/*
 * P01: PEM Parser (SOLUTION)
 *
 * Parse PEM-formatted data and extract type + decoded byte length.
 * PEM format: -----BEGIN <TYPE>----- / base64 lines / -----END <TYPE>-----
 *
 * Skills: String parsing, base64 decoding, I/O handling
 */

use wasm_libs::*;

fn parse_pem_blocks(lines: &[String]) -> Vec<(String, usize)> {
    let mut results = Vec::new();
    let mut i = 0;
    while i < lines.len() {
        let line = &lines[i];
        if let Some(rest) = line.strip_prefix("-----BEGIN ") {
            if let Some(pem_type) = rest.strip_suffix("-----") {
                i += 1;
                let mut b64_data = String::new();
                while i < lines.len() && !lines[i].starts_with("-----END") {
                    b64_data.push_str(&lines[i]);
                    i += 1;
                }
                let decoded = decode_base64(&b64_data);
                results.push((pem_type.to_string(), decoded.len()));
            }
        }
        i += 1;
    }
    results
}

fn decode_base64(input: &str) -> Vec<u8> {
    let chars: Vec<char> = input.chars().filter(|c| !c.is_whitespace()).collect();
    let mut lookup = [0u8; 256];
    for (i, &c) in b"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
        .iter()
        .enumerate()
    {
        lookup[c as usize] = i as u8;
    }
    lookup[b'=' as usize] = 0xFF;

    let mut result = Vec::new();
    let mut buf = [0u8; 4];
    let mut count = 0;
    let mut pad_count = 0;

    for &ch in &chars {
        if ch == '=' {
            pad_count += 1;
            count += 1;
            continue;
        }
        let val = match ch {
            'A'..='Z' => (ch as u8 - b'A'),
            'a'..='z' => (ch as u8 - b'a') + 26,
            '0'..='9' => (ch as u8 - b'0') + 52,
            '+' => 62,
            '/' => 63,
            _ => continue,
        };
        buf[count] = val;
        count += 1;
        if count == 4 {
            result.push((buf[0] << 2) | (buf[1] >> 4));
            if pad_count < 2 {
                result.push(((buf[1] & 0x0F) << 4) | (buf[2] >> 2));
            }
            if pad_count < 1 {
                result.push(((buf[2] & 0x03) << 6) | buf[3]);
            }
            count = 0;
            pad_count = 0;
        }
    }

    result
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
