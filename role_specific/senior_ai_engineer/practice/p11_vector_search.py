"""
P11: Vector Similarity Search with Pre-filtering

Simulate a vector database search operation. Given pre-computed normalized
vector embeddings and document metadata, find the top-K most similar documents
to a query vector, filtered by metadata constraints.

Input:
  Line 1: D N K (D = dimensions, N = number of documents, K = results to return)
  Line 2: D floats (query vector, normalized)
  Line 3: M (number of filter constraints, 0 = no filter)
  If M > 0, Line 4: M space-separated "key=value" filter constraints
  Next N lines: each line has D floats (document vector, normalized),
    then a pipe separator "|", then metadata as space-separated key=value pairs
    Example: "0.1 0.2 0.3|type=spec dept=engineering"

Output: For each of the top-K results (filtered + sorted by similarity desc,
  ties broken by doc_id ascending), print:
  "doc_id=<index> similarity=<score rounded to 4 decimals> matches=<M>"

Skills: Cosine similarity, vector search, metadata filtering, sorting
"""

from src.wasm_libs.py.io import read_ints, read_line, write_string
import sys


def parse_document_line(line):
    raise NotImplementedError


def filter_and_search(query, documents, filters, k):
    raise NotImplementedError


def main():
    params = read_ints()
    _d = params[0]
    n = params[1]
    k = params[2]
    query = [float(x) for x in read_line().split()]
    m = read_ints()[0]
    filters = {}
    if m > 0:
        parts = read_line().split()
        for part in parts:
            key, value = part.split("=")
            filters[key] = value
    documents = []
    for _ in range(n):
        line = read_line()
        vec, meta = parse_document_line(line)
        documents.append((vec, meta))
    results = filter_and_search(query, documents, filters, k)
    for doc_id, similarity, matches in results:
        write_string(f"doc_id={doc_id} similarity={similarity:.4f} matches={matches}")
    sys.exit(0)


if __name__ == "__main__":
    main()
