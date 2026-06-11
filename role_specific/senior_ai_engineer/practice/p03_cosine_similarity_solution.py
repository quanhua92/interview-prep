"""
P03: Cosine Similarity Search

Compute cosine similarity between a query vector and document vectors,
then return top-K results by similarity.

cosine_sim(A, B) = dot(A, B) / (norm(A) * norm(B))

Input:
  Line 1: K (number of top results to return), D (vector dimension)
  Line 2: query vector (D space-separated floats)
  Line 3: N (number of documents)
  Next N lines: document vectors (D space-separated floats each)

Output: Top-K document indices (0-based) sorted by similarity descending.
  Print one index per line. In case of ties, lower index first.

Skills: Vector math, similarity search, ANN index fundamentals
"""

from src.wasm_libs.py.io import read_ints, read_int, read_line, write_int
import sys
import math


def cosine_similarity(a, b):
    dot = sum(x * y for x, y in zip(a, b))
    norm_a = math.sqrt(sum(x * x for x in a))
    norm_b = math.sqrt(sum(x * x for x in b))
    if norm_a == 0 or norm_b == 0:
        return 0.0
    return dot / (norm_a * norm_b)


def top_k_similar(query, documents, k):
    scores = []
    for i, doc in enumerate(documents):
        sim = cosine_similarity(query, doc)
        scores.append((-sim, i))
    scores.sort()
    return [idx for _, idx in scores[:k]]


def main():
    params = read_ints()
    k = params[0]
    _dim = params[1]
    query = [float(x) for x in read_line().split()]
    n = read_int()
    docs = []
    for _ in range(n):
        docs.append([float(x) for x in read_line().split()])
    results = top_k_similar(query, docs, k)
    for idx in results:
        write_int(idx)
    sys.exit(0)


if __name__ == "__main__":
    main()
