/*
 * P06: Token Bucket Rate Limiter
 *
 * Implement a token bucket rate limiter that processes a stream of
 * timestamped requests and determines allow/reject.
 *
 * Token bucket: starts with `capacity` tokens. Between requests,
 * refill = (current_time - last_time) * refill_rate, capped at capacity.
 * Each allowed request consumes 1 token.
 *
 * Input: capacity, refill_rate, N, then N timestamps.
 * Output: For each request, ALLOWED or REJECTED.
 *
 * Skills: State machine, time-based arithmetic, rate limiting
 */

use wasm_libs::*;

struct TokenBucket {
    capacity: i64,
    tokens: f64,
    refill_rate: f64,
    last_time: i64,
}

impl TokenBucket {
    fn new(capacity: i64, refill_rate: f64) -> Self {
        TokenBucket {
            capacity,
            tokens: capacity as f64,
            refill_rate,
            last_time: 0,
        }
    }

    fn allow(&mut self, timestamp: i64) -> bool {
        if timestamp > self.last_time {
            let elapsed = (timestamp - self.last_time) as f64;
            let refill = elapsed * self.refill_rate;
            self.tokens = (self.tokens + refill).min(self.capacity as f64);
            self.last_time = timestamp;
        }
        if self.tokens >= 1.0 {
            self.tokens -= 1.0;
            true
        } else {
            false
        }
    }
}

fn main() {
    let params = read_ints();
    let capacity = params[0] as i64;
    let refill_rate = params[1] as f64;
    let n = read_int();
    let timestamps = read_ints();

    let mut bucket = TokenBucket::new(capacity, refill_rate);
    for ts in &timestamps {
        let allowed = bucket.allow(*ts as i64);
        if allowed {
            write_string(&format!("{} ALLOWED", ts));
        } else {
            write_string(&format!("{} REJECTED", ts));
        }
    }
    std::process::exit(0);
}
