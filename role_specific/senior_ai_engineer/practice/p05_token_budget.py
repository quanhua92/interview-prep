"""
P05: Token Budget Calculator

Estimate token counts for LLM API calls. Different models tokenize text
differently. Implement a simple BPE-like approximation.

For this exercise, use a rough heuristic:
  - Average English: ~4 characters per token
  - Code: ~3.5 characters per token
  - Each message has 4 tokens overhead (role, separators)

Input: M (model cost per 1K input tokens * 100 as integer),
       N (number of messages in conversation)
  Next N lines: message_type text
    message_type: "system", "user", or "assistant"
    text: the message content

Output:
  [OUT] estimated_tokens
  [OUT] estimated_cost (in the same unit as M, i.e. M/100 per 1K tokens)

Skills: Token estimation, cost calculation, LLM API economics
"""

from src.wasm_libs.py.io import read_int, read_ints, read_line, write_string
import sys


def estimate_tokens(text):
    raise NotImplementedError


def calculate_cost(total_tokens, cost_per_1k):
    raise NotImplementedError


def main():
    params = read_ints()
    cost_per_1k = params[0] / 100.0
    n = read_int()
    total_tokens = 0
    for _ in range(n):
        parts = read_line().split(" ", 1)
        text = parts[1] if len(parts) > 1 else ""
        msg_tokens = estimate_tokens(text) + 4
        total_tokens += msg_tokens
    cost = calculate_cost(total_tokens, cost_per_1k)
    write_string(f"tokens={total_tokens}")
    write_string(f"cost={cost:.4f}")
    sys.exit(0)


if __name__ == "__main__":
    main()
