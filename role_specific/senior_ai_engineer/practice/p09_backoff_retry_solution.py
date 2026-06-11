"""
P09: Exponential Backoff with Jitter Simulator

Simulate retry logic with exponential backoff and jitter for LLM API calls.

backoff_delay = min(base * 2^attempt + jitter, max_delay)
jitter = (attempt * 7 + call_id * 13) % (base // 2 + 1)

Input: base_delay max_delay max_retries
       C (number of API calls)
       Next C lines: call_id success_attempt

Output: For each call, print each retry attempt and total.

Skills: Retry logic, backoff strategies, LLM API error handling
"""

from src.wasm_libs.py.io import read_ints, read_line, write_string
import sys


def compute_delay(base, attempt, call_id, max_delay):
    jitter = (attempt * 7 + call_id * 13) % (base // 2 + 1)
    raw = base * (2 ** attempt) + jitter
    return min(raw, max_delay)


def simulate_call(base, max_delay, max_retries, call_id, fails_before):
    attempts_log = []
    total_delay = 0

    for attempt in range(max_retries + 1):
        if attempt == fails_before:
            attempts_log.append((attempt, 0, "OK"))
            return attempts_log, total_delay, True

        delay = compute_delay(base, attempt, call_id, max_delay)
        total_delay += delay
        attempts_log.append((attempt, delay, "RETRY"))

    return attempts_log, total_delay, False


def main():
    params = read_ints()
    base = params[0]
    max_delay = params[1]
    max_retries = params[2]
    c = read_int()
    for _ in range(c):
        parts = read_line().split()
        call_id = int(parts[0])
        fails_before = int(parts[1])
        attempts, total_delay, success = simulate_call(base, max_delay, max_retries, call_id, fails_before)
        for attempt, delay, result in attempts:
            write_string(f"{call_id} {attempt} {delay}ms {result}")
        write_string(f"{call_id} total={total_delay}ms {'OK' if success else 'FAILED'}")
    sys.exit(0)


if __name__ == "__main__":
    main()
