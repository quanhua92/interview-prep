"""
P09: Exponential Backoff with Jitter Simulator

Simulate retry logic with exponential backoff and jitter for LLM API calls.

backoff_delay = min(base * 2^attempt + jitter, max_delay)
jitter = random value in [0, base * 0.5]

Use a deterministic "random" via formula: jitter = (attempt * 7 + call_id * 13) % (base // 2 + 1)

Input: base_delay max_delay max_retries
       C (number of API calls)
       Next C lines: call_id success_attempt (0 = immediate success, 1+ = fails N-1 times then succeeds)
         If success_attempt > max_retries, the call permanently fails.

Output: For each call, print each retry attempt:
  [OUT] call_id attempt# delay_ms result
  Final line: [OUT] call_id total_delay_ms

Skills: Retry logic, backoff strategies, LLM API error handling
"""

from src.wasm_libs.py.io import read_ints, read_line, write_string
import sys


def compute_delay(base, attempt, call_id, max_delay):
    raise NotImplementedError


def simulate_call(base, max_delay, max_retries, call_id, fails_before_success):
    raise NotImplementedError


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
