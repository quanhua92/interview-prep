"""
P12: Table Extraction from Structured Text

Extract tabular data from semi-structured text that mimics PDF table output.
Tables are delimited by header rows starting with "TABLE:" and end with "END TABLE".
Parse rows into structured data and answer queries about the table.

Input:
  Line 1: Q (number of queries)
  Line 2: N (number of lines in the document)
  Next N lines: document content (may contain tables)
    Tables start with "TABLE: <table_name>"
    Next line: pipe-delimited header row: "col1|col2|col3"
    Following lines: pipe-delimited data rows
    Table ends with "END TABLE"
  After the document, Q query lines, each in format:
    "table_name column_name" — find the sum of numeric values in that column

Output: For each query, print the sum rounded to 2 decimal places.
  If table or column not found, print "NOT FOUND"

Skills: Text parsing, table extraction, data aggregation, structured extraction from unstructured text
"""

from src.wasm_libs.py.io import read_ints, read_line, write_string
import sys


def solve(queries, tables):
    raise NotImplementedError


def main():
    params = read_ints()
    q = params[0]
    n = params[1]
    tables = {}
    current_table = None
    current_headers = None
    current_rows = []
    for _ in range(n):
        line = read_line()
        if line.startswith("TABLE: "):
            current_table = line[len("TABLE: "):]
            current_headers = None
            current_rows = []
        elif line.startswith("TABLE:") and not line.startswith("TABLE: "):
            current_table = line[len("TABLE:"):].strip()
            current_headers = None
            current_rows = []
        elif line == "END TABLE":
            if current_table and current_headers:
                tables[current_table] = {
                    "headers": current_headers,
                    "rows": current_rows,
                }
            current_table = None
            current_headers = None
            current_rows = []
        elif current_table is not None and current_headers is None:
            current_headers = [h.strip() for h in line.split("|")]
        elif current_table is not None and current_headers is not None:
            vals = [v.strip() for v in line.split("|")]
            current_rows.append(vals)
    query_list = []
    for _ in range(q):
        parts = read_line().split()
        query_list.append((parts[0], parts[1]))
    results = solve(query_list, tables)
    for r in results:
        write_string(r)
    sys.exit(0)


if __name__ == "__main__":
    main()
