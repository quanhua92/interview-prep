"""
P01: Text Chunking with Overlap

Split a document into fixed-size chunks with configurable overlap.
This is a fundamental operation in any RAG pipeline.

Input:
  Line 1: chunk_size overlap
  Line 2: N (number of words in document)
  Line 3: N words separated by spaces

Output: For each chunk, print the chunk as a space-separated string.

Skills: String manipulation, sliding window, RAG chunking strategies
"""

from src.wasm_libs.py.io import read_ints, read_line, write_string
import sys


def chunk_with_overlap(words, chunk_size, overlap):
    raise NotImplementedError


def main():
    params = read_ints()
    chunk_size = params[0]
    overlap = params[1]
    words = read_line().split()
    chunks = chunk_with_overlap(words, chunk_size, overlap)
    for chunk in chunks:
        write_string(" ".join(chunk))
    sys.exit(0)


if __name__ == "__main__":
    main()
