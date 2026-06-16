#!/usr/bin/env python3
"""LLM-as-judge eval: compare two models (e.g. base vs fine-tuned) on the held-out
gold set. Both models must be served at OpenAI-compatible endpoints (vLLM/Ollama);
a stronger model judges pairwise which answer is better, with position-bias swap.

Gold set: build/sft_eval.jsonl (rows with a "user" message used as the prompt).
Serve the candidates first, e.g.:
  vllm serve Qwen/Qwen2.5-7B-Instruct --max-model-len 4096            # base
  vllm serve qwen-finance-sft-merged --max-model-len 4096 --port 8001  # fine-tuned
  export JUDGE_KEY=sk-...   # OpenRouter/OpenAI for the judge
"""
from __future__ import annotations
import argparse
import json
import os
from pathlib import Path

from openai import OpenAI

RUBRIC = (
    "You are grading market analyses. Compare Answer A and B on: correctness, "
    "grounding in the evidence, clarity, and format. Return STRICT JSON: "
    '{"a": {"correctness":0-5,"grounding":0-5,"clarity":0-5,"format":0-5}, '
    '"b": {...}, "winner": "a" | "b" | "tie", "reason": "..."}.'
)


def gen(client, model, prompt, system):
    r = client.chat.completions.create(
        model=model, temperature=0.0, max_tokens=800,
        messages=[{"role": "system", "content": system}, {"role": "user", "content": prompt}])
    return r.choices[0].message.content or ""


def judge(jclient, jmodel, prompt, a, b):
    user = f"Question:\n{prompt}\n\nAnswer A:\n{a}\n\nAnswer B:\n{b}\n\n{RUBRIC}"
    r = jclient.chat.completions.create(model=jmodel, temperature=0.0, max_tokens=400,
                                        messages=[{"role": "user", "content": user}])
    try:
        return json.loads(r.choices[0].message.content)
    except Exception:
        return {"winner": "tie"}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--gold", default="build/sft_eval.jsonl")
    ap.add_argument("--base-url-a", required=True)
    ap.add_argument("--model-a", required=True)
    ap.add_argument("--base-url-b", required=True)
    ap.add_argument("--model-b", required=True)
    ap.add_argument("--judge-base-url", required=True)
    ap.add_argument("--judge-model", required=True)
    ap.add_argument("--system", default="You are a senior Wyckoff / price-action analyst.")
    args = ap.parse_args()

    ca = OpenAI(base_url=args.base_url_a, api_key=os.getenv("EVAL_KEY_A", "dummy"))
    cb = OpenAI(base_url=args.base_url_b, api_key=os.getenv("EVAL_KEY_B", "dummy"))
    cj = OpenAI(base_url=args.judge_base_url, api_key=os.getenv("JUDGE_KEY", "dummy"))

    gold = [json.loads(line) for line in Path(args.gold).read_text().splitlines() if line.strip()]
    prompts = [next(m["content"] for m in r["messages"] if m["role"] == "user") for r in gold]

    win_a = win_b = tie = 0
    for i, p in enumerate(prompts, 1):
        a = gen(ca, args.model_a, p, args.system)
        b = gen(cb, args.model_b, p, args.system)
        swapped = (i % 2 == 0)
        if swapped:
            a, b = b, a
        res = judge(cj, args.judge_model, p, a, b)
        w = res.get("winner", "tie")
        if swapped:
            w = {"a": "b", "b": "a", "tie": "tie"}.get(w, "tie")
        win_a += w == "a"
        win_b += w == "b"
        tie += w == "tie"
        print(f"[{i}/{len(prompts)}] winner={w}")

    print(f"\nA ({args.model_a}) wins: {win_a} | B ({args.model_b}) wins: {win_b} | ties: {tie}")


if __name__ == "__main__":
    main()
