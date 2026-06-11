"""
P10: Multi-Model Routing Cost Optimizer

Given multiple LLM providers with different costs and latency,
route requests to minimize cost while meeting latency SLOs.

Input: P (number of providers)
  Next P lines: provider_name cost_per_1k_input cost_per_1k_output max_latency_ms
  Line: R (number of requests)
  Next R lines: input_tokens output_tokens max_allowed_latency_ms

Output: For each request, select the cheapest provider that meets the latency SLO.
  If no provider meets the SLO, select the fastest provider with "SLO_VIOLATION".

Skills: Model routing, cost optimization, SLO management, LLM serving economics
"""

from src.wasm_libs.py.io import read_int, read_line, write_string
import sys


def route_request(providers, input_tokens, output_tokens, max_latency):
    candidates = []
    for p in providers:
        req_cost = (input_tokens / 1000.0) * p["cost_in"] + (output_tokens / 1000.0) * p["cost_out"]
        candidates.append((p, req_cost))

    feasible = [(p, c) for p, c in candidates if p["max_latency"] <= max_latency]
    if feasible:
        feasible.sort(key=lambda x: x[1])
        return feasible[0][0]["name"], feasible[0][1], False

    candidates.sort(key=lambda x: x[0]["max_latency"])
    return candidates[0][0]["name"], candidates[0][1], True


def main():
    p = read_int()
    providers = []
    for _ in range(p):
        parts = read_line().split()
        name = parts[0]
        cost_in = float(parts[1])
        cost_out = float(parts[2])
        max_latency = int(parts[3])
        providers.append({
            "name": name,
            "cost_in": cost_in,
            "cost_out": cost_out,
            "max_latency": max_latency,
        })
    r = read_int()
    total_cost = 0.0
    for req_idx in range(r):
        parts = read_line().split()
        input_tokens = int(parts[0])
        output_tokens = int(parts[1])
        max_latency = int(parts[2])
        provider_name, cost, slo_violation = route_request(
            providers, input_tokens, output_tokens, max_latency
        )
        total_cost += cost
        suffix = " SLO_VIOLATION" if slo_violation else ""
        write_string(f"{req_idx} {provider_name} {cost:.6f}{suffix}")
    write_string(f"TOTAL_COST {total_cost:.6f}")
    sys.exit(0)


if __name__ == "__main__":
    main()
