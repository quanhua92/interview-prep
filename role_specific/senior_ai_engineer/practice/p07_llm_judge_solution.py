"""
P07: LLM-as-Judge Scoring with Debiasing

Simulate an LLM-as-judge evaluation with position and verbosity debiasing.

Multiple judges score responses. We need to:
  1. Normalize scores for verbosity bias (longer responses score higher)
  2. Average across judges
  3. Apply position debiasing (first position gets +0.1 bias)

Input: J (number of judges), R (number of responses)
  For each judge (J times):
    For each response (R times):
      line: raw_score response_length

Output: For each response, print the debiased average score across all judges.
  [OUT] response_idx debiased_score

Skills: LLM-as-judge, debiasing protocols, evaluation methodology
"""

from src.wasm_libs.py.io import read_ints, read_line, write_string
import sys
import math


def debias_score(raw_score, response_length, position):
    verbosity_factor = 1.0 + math.log(max(response_length, 1) / 100.0)
    normalized = raw_score / verbosity_factor
    position_bias = 0.1 if position == 0 else 0.0
    return normalized - position_bias


def main():
    params = read_ints()
    j = params[0]
    r = params[1]
    judge_scores = []
    for judge_idx in range(j):
        scores = []
        for resp_idx in range(r):
            parts = read_line().split()
            raw_score = float(parts[0])
            resp_length = int(parts[1])
            scores.append((raw_score, resp_length))
        judge_scores.append(scores)

    response_final = []
    for resp_idx in range(r):
        total = 0.0
        for judge_idx in range(j):
            raw_score, resp_length = judge_scores[judge_idx][resp_idx]
            total += debias_score(raw_score, resp_length, resp_idx)
        avg = total / j
        response_final.append(avg)

    for idx, score in enumerate(response_final):
        write_string(f"{idx} {score:.4f}")
    sys.exit(0)


if __name__ == "__main__":
    main()
