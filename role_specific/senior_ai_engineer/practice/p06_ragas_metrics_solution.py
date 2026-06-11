"""
P06: RAG Evaluation Metrics (RAGAS-like)

Implement simplified RAGAS evaluation metrics for a RAG system.

Given golden answers, generated answers, and retrieved contexts, compute:
  1. Faithfulness: fraction of claims in answer supported by context
  2. Answer Relevance: keyword overlap between answer and golden answer
  3. Context Precision: fraction of retrieved chunks that contain golden answer keywords

For this exercise, use keyword-based heuristics (no LLM judge).

Input: N (number of test cases)
  For each test case:
    Line 1: golden_answer_keywords (space-separated)
    Line 2: generated_answer_keywords (space-separated)
    Line 3: M (number of retrieved chunks)
    Line 4: M chunk keywords (each chunk: space-separated keywords, chunks separated by |)

Output: For each test case, print:
  [OUT] faithfulness=<value> relevance=<value> precision=<value>

Skills: RAG evaluation, RAGAS metrics, retrieval quality assessment
"""

from src.wasm_libs.py.io import read_int, read_line, write_string
import sys


def compute_faithfulness(answer_keywords, context_keywords):
    if not answer_keywords:
        return 1.0
    supported = answer_keywords & context_keywords
    return len(supported) / len(answer_keywords)


def compute_relevance(answer_keywords, golden_keywords):
    if not golden_keywords:
        return 1.0
    overlap = answer_keywords & golden_keywords
    return len(overlap) / len(golden_keywords)


def compute_precision(golden_keywords, chunks_keywords):
    if not chunks_keywords:
        return 0.0
    relevant = sum(1 for c in chunks_keywords if c & golden_keywords)
    return relevant / len(chunks_keywords)


def main():
    n = read_int()
    for _ in range(n):
        golden = set(read_line().split())
        generated = set(read_line().split())
        _m = read_int()
        chunks_line = read_line()
        chunks = [set(c.split()) for c in chunks_line.split("|")]

        all_context = set()
        for c in chunks:
            all_context |= c

        faith = compute_faithfulness(generated, all_context)
        rel = compute_relevance(generated, golden)
        prec = compute_precision(golden, chunks)

        write_string(f"faithfulness={faith:.4f} relevance={rel:.4f} precision={prec:.4f}")
    sys.exit(0)


if __name__ == "__main__":
    main()
