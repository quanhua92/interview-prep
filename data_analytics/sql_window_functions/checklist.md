# SQL Window Functions -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is this a per-group ranking problem or a global ranking?
  - [ ] Do ties need special handling (dedup vs "Nth highest" semantics)?
  - [ ] Is this a time-series problem requiring LAG/LEAD or session detection?
  - [ ] What granularity is the data at, and are there gaps in dates/times?
- [ ] Identify which window function pattern applies:
  - [ ] Top-N per group (ROW_NUMBER or DENSE_RANK + CTE filter)
  - [ ] Period-over-period comparison (LAG with PARTITION BY dimension)
  - [ ] Running total / moving average (SUM or AVG with frame clause)
  - [ ] Session detection / streak counting (gaps-and-islands)
  - [ ] Percentile bucketing (NTILE or PERCENTILE_CONT)
- [ ] State assumptions about data:
  - [ ] Are there duplicate timestamps that could cause tie issues?
  - [ ] Can dates have gaps (zero-activity days)?
  - [ ] Are events guaranteed to be in chronological order?

## Phase 2: High-Level Design (3-5 min)
- [ ] Identify the three OVER() components:
  - [ ] PARTITION BY: what column defines the group (user_id, category, etc.)
  - [ ] ORDER BY: what defines sequence within the group (date, timestamp, revenue DESC)
  - [ ] Frame clause: how many rows contribute to each calculation (if aggregate function)
- [ ] Choose the correct ranking function:
  - [ ] ROW_NUMBER: deduplication, exactly one row per position, arbitrary tie-break
  - [ ] RANK: tied positions with gaps after ties [1,1,3,4]
  - [ ] DENSE_RANK: tied positions without gaps [1,1,2,3] -- correct for "Nth highest"
- [ ] Sketch the CTE structure:
  - [ ] CTE 1: compute window function values (rank, lag, running sum)
  - [ ] CTE 2+: apply gaps-and-islands logic if needed (flag + cumulative SUM)
  - [ ] Final SELECT: filter (WHERE rn = 1) and return results
- [ ] Present the query skeleton and get alignment

## Phase 3: Core Query Construction (5-8 min)
- [ ] Write the window function with all three components:
  - [ ] `FUNCTION() OVER (PARTITION BY ... ORDER BY ... ROWS BETWEEN ...)`
  - [ ] Never omit PARTITION BY in multi-entity queries (LAG without partition leaks across users)
- [ ] Handle NULLs at partition boundaries:
  - [ ] Use three-argument form: `LAG(col, 1, default_value)`
  - [ ] Or wrap in COALESCE: `COALESCE(LAG(col) OVER (...), fallback)`
  - [ ] Narrate: "LAG returns NULL for the first row per partition, so I handle it with..."
- [ ] Apply the correct frame clause for running aggregates:
  - [ ] Running total: `ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW`
  - [ ] 7-row rolling: `ROWS BETWEEN 6 PRECEDING AND CURRENT ROW`
  - [ ] Full partition: `ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING`
  - [ ] Use ROWS BETWEEN (not RANGE) for time-series to avoid tie surprises
- [ ] Filter on window function results via CTE (not WHERE on outer query):
  - [ ] Wrong: `SELECT *, ROW_NUMBER() OVER (...) AS rn FROM t WHERE rn = 1`
  - [ ] Right: `WITH r AS (SELECT *, ROW_NUMBER() OVER (...) AS rn FROM t) SELECT * FROM r WHERE rn = 1`
- [ ] Walk through the query with a small example dataset

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss the gaps-and-islands pattern:
  - [ ] Step 1: LAG to get previous value, compute gap
  - [ ] Step 2: Flag boundary rows (gap exceeds threshold) as 1, else 0
  - [ ] Step 3: Cumulative SUM of flags creates group/island ID
  - [ ] Step 4: GROUP BY island ID to aggregate
- [ ] Handle edge cases:
  - [ ] Zero-activity periods: join to a date spine to fill gaps before windowing
  - [ ] Division by zero in % change: use NULLIF(denominator, 0)
  - [ ] Out-of-order events: sort explicitly in ORDER BY, don't assume insertion order
- [ ] Explain ROWS vs RANGE distinction:
  - [ ] ROWS: physical row count, deterministic
  - [ ] RANGE: value-based, includes all rows with same ORDER BY value
  - [ ] RANGE with ties can produce larger windows than expected
- [ ] Discuss NTILE for ML feature engineering:
  - [ ] Decile bucketing for user revenue segments
  - [ ] Risk tier assignment from model scores
  - [ ] Rank-based normalization for skewed distributions
  - [ ] Note: NTILE distributes unevenly (earlier buckets get more rows)
- [ ] Address performance considerations:
  - [ ] Multiple window functions with same PARTITION BY + ORDER BY can share one sort
  - [ ] Different PARTITION BY or ORDER BY triggers separate sorts
  - [ ] Index on (partition_col, order_col) helps window function queries

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the query logic in 2-3 sentences
- [ ] State the key decision (which ranking function, ROWS vs RANGE, NULL handling)
- [ ] Mention what you would optimize with more time (date spine, indexing, materialized view)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
