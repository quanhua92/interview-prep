"""
P13: SQL Validation and Result Parsing for NL2SQL Pipeline

Given a SQL query, a table schema whitelist, and query result data,
validate the SQL and format the results for LLM consumption.

Validation rules:
  1. Must be a SELECT query (starts with SELECT, case-insensitive)
  2. Must only reference whitelisted tables
  3. Must not contain DDL/DML keywords (INSERT, UPDATE, DELETE, DROP, ALTER, CREATE, TRUNCATE)
  4. Must contain a LIMIT clause (or add LIMIT 100)

Input:
  Line 1: T (number of whitelisted tables)
  Next T lines: table names
  Line T+2: SQL query (single line, may be multi-word)
  Line T+3: R (number of result rows)
  Line T+4: column names (pipe-separated)
  Next R lines: values (pipe-separated, matching column count)

Output:
  If VALID:
    Line 1: VALID
    Line 2: Columns: <comma-separated column names>
    Line 3: Rows: <R>
    Line 4: Summary: <for each numeric column, print min=<val> max=<val> avg=<val rounded to 2 decimals>, separated by semicolons>
  If INVALID:
    Line 1: INVALID:<reason>
      "not_select" - not a SELECT query
      "unauthorized_table:<name>" - references non-whitelisted table
      "contains_dml" - contains DDL/DML keywords
      "missing_limit" - no LIMIT clause

Skills: SQL validation, text parsing, data aggregation, security (injection prevention)
"""

from src.wasm_libs.py.io import read_ints, read_line, write_string
import sys
import re


DML_KEYWORDS = re.compile(
    r"\b(INSERT|UPDATE|DELETE|DROP|ALTER|CREATE|TRUNCATE)\b", re.IGNORECASE
)


def validate_sql(sql, whitelist):
    if not sql.strip().upper().startswith("SELECT"):
        return ("INVALID", "INVALID:not_select")

    for match in DML_KEYWORDS.finditer(sql):
        upper_sql = sql.upper()
        before = upper_sql[:match.start()].rstrip()
        if not before.endswith("SELECT") and not before.endswith(","):
            return ("INVALID", "INVALID:contains_dml")

    tokens = re.findall(r"\bFROM\s+(\w+)", sql, re.IGNORECASE)
    tokens += re.findall(r"\bJOIN\s+(\w+)", sql, re.IGNORECASE)
    all_tables = [t.lower() for t in tokens]
    for tbl in all_tables:
        if tbl not in whitelist:
            return ("INVALID", f"INVALID:unauthorized_table:{tbl}")

    if not re.search(r"\bLIMIT\b", sql, re.IGNORECASE):
        return ("INVALID", "INVALID:missing_limit")

    return ("VALID", "VALID")


def format_results(columns, rows):
    output = []
    output.append(f"Columns: {', '.join(columns)}")
    output.append(f"Rows: {len(rows)}")

    summaries = []
    for col_idx, col_name in enumerate(columns):
        numeric_vals = []
        for row in rows:
            try:
                numeric_vals.append(float(row[col_idx]))
            except (ValueError, IndexError):
                continue
        if numeric_vals:
            mn = min(numeric_vals)
            mx = max(numeric_vals)
            avg = sum(numeric_vals) / len(numeric_vals)
            if mn == int(mn) and mx == int(mx):
                summaries.append(f"{col_name}: min={int(mn)} max={int(mx)} avg={avg:.2f}")
            else:
                summaries.append(f"{col_name}: min={mn} max={mx} avg={avg:.2f}")

    if summaries:
        output.append("Summary: " + "; ".join(summaries))
    else:
        output.append("Summary:")

    return output


def main():
    t = read_ints()[0]
    whitelist = set()
    for _ in range(t):
        whitelist.add(read_line().strip().lower())
    sql = read_line().strip()
    r = read_ints()[0]
    columns = [c.strip() for c in read_line().split("|")]
    rows = []
    for _ in range(r):
        vals = [v.strip() for v in read_line().split("|")]
        rows.append(vals)

    status = validate_sql(sql, whitelist)
    if status[0] == "VALID":
        write_string(status[0])
        output = format_results(columns, rows)
        for line in output:
            write_string(line)
    else:
        write_string(status[1])
    sys.exit(0)


if __name__ == "__main__":
    main()
