"""
P08: Token Bucket Rate Limiter for LLM API

Implement a rate limiter for LLM API calls. Each request consumes tokens
from a budget that refills over time. Support per-minute and per-day limits.

Input: rate_per_minute daily_budget
       N (number of requests)
       Next N lines: timestamp(seconds) tokens_requested

Output: For each request, ALLOWED or REJECTED with remaining budget.

Skills: Rate limiting, LLM API cost management, token budgeting
"""

from src.wasm_libs.py.io import read_ints, read_line, write_string
import sys


class DualRateLimiter:
    def __init__(self, rate_per_minute, daily_budget):
        self.rate_per_minute = rate_per_minute
        self.daily_budget = daily_budget
        self.daily_used = 0
        self.current_minute = -1
        self.minute_used = 0

    def allow(self, timestamp, tokens_requested):
        current_minute = timestamp // 60
        if current_minute != self.current_minute:
            self.current_minute = current_minute
            self.minute_used = 0

        minute_ok = (self.minute_used + tokens_requested) <= self.rate_per_minute
        daily_ok = (self.daily_used + tokens_requested) <= self.daily_budget

        if minute_ok and daily_ok:
            self.minute_used += tokens_requested
            self.daily_used += tokens_requested
            minute_remaining = self.rate_per_minute - self.minute_used
            daily_remaining = self.daily_budget - self.daily_used
            return True, minute_remaining, daily_remaining
        else:
            minute_remaining = max(0, self.rate_per_minute - self.minute_used)
            daily_remaining = max(0, self.daily_budget - self.daily_used)
            return False, minute_remaining, daily_remaining


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
