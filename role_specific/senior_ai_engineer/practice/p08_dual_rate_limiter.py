"""
P08: Token Bucket Rate Limiter for LLM API

Implement a rate limiter for LLM API calls. Each request consumes tokens
from a budget that refills over time. Support per-minute and per-day limits.

Input: rate_per_minute daily_budget
       N (number of requests)
       Next N lines: timestamp(Seconds) tokens_requested

Output: For each request, ALLOWED or REJECTED with remaining budget.

Rate logic:
  - Per-minute: tokens_per_minute = rate_per_minute
  - Per-day: tokens_per_day = daily_budget
  - A request must pass BOTH limits to be allowed
  - Track minute windows: tokens_used_in_current_minute
  - Track total daily usage

Skills: Rate limiting, LLM API cost management, token budgeting
"""

from src.wasm_libs.py.io import read_ints, read_line, write_string
import sys


class DualRateLimiter:
    def __init__(self, rate_per_minute, daily_budget):
        raise NotImplementedError

    def allow(self, timestamp, tokens_requested):
        raise NotImplementedError


def main():
    params = read_ints()
    rate_per_minute = params[0]
    daily_budget = params[1]
    n = read_int()
    limiter = DualRateLimiter(rate_per_minute, daily_budget)
    for _ in range(n):
        parts = read_line().split()
        timestamp = int(parts[0])
        tokens = int(parts[1])
        allowed, minute_remaining, daily_remaining = limiter.allow(timestamp, tokens)
        status = "ALLOWED" if allowed else "REJECTED"
        write_string(f"{status} minute_left={minute_remaining} daily_left={daily_remaining}")
    sys.exit(0)


if __name__ == "__main__":
    main()
