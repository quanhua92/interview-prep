"""
P02: BM25-like Keyword Scoring

Implement a simplified BM25 scoring function for document retrieval.
Given a query and a set of documents, score each document.

BM25 formula (simplified):
  score(D, Q) = sum over q in Q of: IDF(q) * (f(q,D) * (k1 + 1)) / (f(q,D) + k1)
  where IDF(q) = log((N - n(q) + 0.5) / (n(q) + 0.5) + 1)
  N = total documents, n(q) = docs containing term q, f(q,D) = term frequency

Input:
  Line 1: k1 * 10 (BM25 parameter, e.g. 12 means k1=1.2)
  Line 2: N (number of documents)
  Line 3: query terms (space-separated)
  Next N lines: each document as space-separated words

Output: For each document, print its BM25 score rounded to 4 decimal places.

Skills: TF-IDF, information retrieval, scoring functions
"""

from src.wasm_libs.py.io import read_int, read_line, write_string
import sys
import math


def bm25_score(query_terms, doc_terms, all_docs, k1):
    n = len(all_docs)
    doc_freq = {}
    for d in all_docs:
        for term in set(d):
            doc_freq[term] = doc_freq.get(term, 0) + 1

    doc_tf = {}
    for term in doc_terms:
        doc_tf[term] = doc_tf.get(term, 0) + 1

    score = 0.0
    for q in query_terms:
        if q not in doc_freq:
            continue
        nq = doc_freq[q]
        idf = math.log((n - nq + 0.5) / (nq + 0.5) + 1)
        fq = doc_tf.get(q, 0)
        tf_component = (fq * (k1 + 1)) / (fq + k1)
        score += idf * tf_component
    return score


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
