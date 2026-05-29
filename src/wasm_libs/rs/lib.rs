use std::io::{self, BufRead, Write};

pub fn read_ints() -> Vec<i32> {
    let stdin = io::stdin();
    let line = stdin.lock().lines().next().unwrap().unwrap();
    line.split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
}

pub fn read_line() -> String {
    let stdin = io::stdin();
    stdin.lock().lines().next().unwrap().unwrap()
}

pub fn read_int() -> i32 {
    let stdin = io::stdin();
    let line = stdin.lock().lines().next().unwrap().unwrap();
    line.trim().parse().unwrap()
}

pub fn write_int(val: i32) {
    let mut out = io::stdout().lock();
    writeln!(out, "[OUT] {}", val).unwrap();
}

pub fn write_ints(arr: &[i32]) {
    let mut out = io::stdout().lock();
    write!(out, "[OUT] ").unwrap();
    for (i, v) in arr.iter().enumerate() {
        if i > 0 {
            write!(out, " ").unwrap();
        }
        write!(out, "{}", v).unwrap();
    }
    writeln!(out).unwrap();
}

pub fn write_string(s: &str) {
    let mut out = io::stdout().lock();
    writeln!(out, "[OUT] {}", s).unwrap();
}

pub fn write_bool(b: bool) {
    let mut out = io::stdout().lock();
    writeln!(out, "[OUT] {}", b).unwrap();
}
