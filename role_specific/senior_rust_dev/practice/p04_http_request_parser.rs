/*
 * P04: HTTP/1.1 Request Parser
 *
 * Parse an HTTP request and extract method, path, version, headers, and body.
 * Zero-copy parsing using string slices where possible.
 *
 * Input: Raw HTTP request lines until empty line, then optional body line.
 * Output: Method, path, version, header count, each header, body info.
 *
 * Skills: String slicing, HTTP format knowledge, zero-copy parsing
 */

use wasm_libs::*;

struct HttpRequest {
    method: String,
    path: String,
    version: String,
    headers: Vec<(String, String)>,
    body: Option<String>,
}

fn parse_http_request(request_line: &str, header_lines: &[String], body: Option<String>) -> Option<HttpRequest> {
    todo!();
}

fn main() {
    let request_line = read_line();
    let mut header_lines: Vec<String> = Vec::new();
    loop {
        let line = read_line();
        if line.is_empty() {
            break;
        }
        header_lines.push(line);
    }
    let body_line = read_line();
    let body = if body_line.is_empty() { None } else { Some(body_line) };

    let request = parse_http_request(&request_line, &header_lines, body);
    if let Some(req) = request {
        write_string(&req.method);
        write_string(&req.path);
        write_string(&req.version);
        write_int(req.headers.len() as i32);
        for (key, value) in &req.headers {
            write_string(&format!("{}:{}", key, value));
        }
        match &req.body {
            Some(b) => write_string(&format!("BODY:{}", b.len())),
            None => write_string("NO_BODY"),
        }
    }
    std::process::exit(0);
}
