"""
P02: BM25-like Keyword Scoring

Implement a simplified BM25 scoring function for document retrieval.
Given a query and a set of documents, score each document.

BM25 formula (simplified):
  score(D, Q) = sum over q in Q of: IDF(q) * (f(q,D) * (k1 + 1)) / (f(q,D) + k1)
  where IDF(q) = log((N - n(q) + 0.5) / (n(q) + 0.5) + 1)
  N = total documents, n(q) = docs containing term q, f(q,D) = term frequency

Input:
  Line 1: k1 (BM25 parameter, typically 1.2-2.0)
  Line 2: N (number of documents)
  Line 3: query terms (space-separated)
  Next N lines: each document as space-separated words

Output: For each document, print its BM25 score rounded to 4 decimal places.
  Order matches input order.

Skills: TF-IDF, information retrieval, scoring functions
"""

from src.wasm_libs.py.io import read_int, read_line, write_string
import sys


def bm25_score(query_terms, doc_terms, all_docs, k1):
    raise NotImplementedError


def main():
    k1 = read_int() / 10.0
    n = read_int()
    query_terms = read_line().split()
    docs = []
    for _ in range(n):
        docs.append(read_line().split())
    for i, doc in enumerate(docs):
        score = bm25_score(query_terms, doc, docs, k1)
        write_string(f"{score:.4f}")
    sys.exit(0)


if __name__ == "__main__":
    main()
