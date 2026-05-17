# SQL Window Functions

Source: [Window Functions for Analytics: ROW_NUMBER, RANK, LAG/LEAD, and Running Totals (CalibreOS)](https://www.calibreos.com/learn/sql-window-functions)

## One-Liner
Compute aggregated values across a set of related rows without collapsing results -- every input row produces an output row annotated with window-level information.

## Requirements
- Understand OVER() clause anatomy: PARTITION BY, ORDER BY, frame clause
- Know when to use each ranking function (ROW_NUMBER, RANK, DENSE_RANK) and their tie-handling differences
- Apply LAG/LEAD for time-series analysis, session detection, and period-over-period comparisons
- Build running totals and moving averages with the frame clause
- Distinguish ROWS BETWEEN from RANGE BETWEEN semantics
- Use NTILE for percentile bucketing and ML feature engineering

## Key Concepts

### Window Functions vs GROUP BY
- GROUP BY collapses rows into one per group; window functions annotate every row without removing any
- Window functions appear in ~70% of hard SQL interview questions at major tech companies
- Common interview patterns: gaps-and-islands, cohort retention, running totals, top-N per group, YoY comparisons

### OVER() Clause Anatomy
```
FUNCTION() OVER (
  PARTITION BY partition_cols
  ORDER BY order_col [ASC|DESC]
  ROWS BETWEEN start AND end
)
```
Three components: partition (what group), ordering (sequence within group), frame (how many rows contribute).

### What Interviewers Actually Test
1. **Pattern recognition**: Can you identify that a problem needs a window function vs GROUP BY or self-join?
2. **Frame clause precision**: Do you know ROWS BETWEEN vs RANGE BETWEEN?
3. **NULL handling**: LAG returns NULL for the first row in each partition -- do you handle it?

## Decisions

### ROW_NUMBER vs RANK vs DENSE_RANK

| Function | Tie Behavior | Example on [100, 100, 80, 60] | When to Use |
|----------|-------------|-------------------------------|-------------|
| ROW_NUMBER | Unique numbers, arbitrary tie-break | 1, 2, 3, 4 | Deduplication, latest record per user |
| RANK | Same number for ties, skip after | 1, 1, 3, 4 | "Tied for 2nd place" semantics |
| DENSE_RANK | Same number for ties, no skip | 1, 1, 2, 3 | "Nth highest" problems |

- **Second-highest salary trap**: RANK fails when two people share the top salary (rank 2 doesn't exist). DENSE_RANK always works.
- **Deduplication trap**: Use ROW_NUMBER for "most recent per user" -- RANK/DENSE_RANK can return duplicates when timestamps tie.

### LAG and LEAD for Time-Series
- `LAG(col, n, default)`: look back n rows in the partition
- `LEAD(col, n, default)`: look forward n rows
- Always handle NULL at partition boundaries with the three-argument form or COALESCE
- Key patterns: YoY change, day-over-day change, session detection, consecutive-day streaks

### Gaps-and-Islands Pattern
1. Use LAG to find the gap between current and previous row
2. Flag boundary rows where the gap exceeds a threshold
3. Cumulative SUM of flags creates a group ID for each island
4. GROUP BY the group ID to aggregate per island

### Frame Clause: ROWS vs RANGE
- **ROWS BETWEEN**: counts by physical row position. Deterministic.
- **RANGE BETWEEN**: counts by value range. Can include unexpected rows with ties or gaps.
- **Rule**: For time-series analytics, always use ROWS BETWEEN.

| Pattern | Frame Clause | Use Case |
|---------|-------------|----------|
| Running total | `ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW` | Cumulative revenue, signups |
| 7-day rolling avg | `ROWS BETWEEN 6 PRECEDING AND CURRENT ROW` | Smoothed daily metrics |
| Full partition aggregate | `ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING` | % of total per group |
| Centered 3-row avg | `ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING` | Signal smoothing |
| Default (with ORDER BY) | `RANGE BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW` | Same as running total but ties differ |

### NTILE for Percentiles
- `NTILE(n)` divides partition into n roughly equal buckets
- NTILE(4) = quartiles, NTILE(10) = deciles, NTILE(100) = percentiles
- Earlier buckets get slightly more rows when uneven (10 rows / NTILE(3) = 4, 3, 3)
- For exact percentiles: PERCENTILE_CONT / PERCENTILE_DISC (PostgreSQL, BigQuery, Snowflake)
- ML feature engineering uses: revenue deciles, risk tiers, rank-based normalization

## Deep Dives

### Session Detection
```sql
-- Gaps-and-islands: new session when gap > 30 minutes
WITH event_gaps AS (
  SELECT user_id, event_time,
    LAG(event_time) OVER (PARTITION BY user_id ORDER BY event_time) AS prev_event_time
  FROM page_events
),
session_flags AS (
  SELECT user_id, event_time,
    CASE WHEN prev_event_time IS NULL
         OR DATEDIFF('minute', prev_event_time, event_time) > 30
    THEN 1 ELSE 0 END AS is_session_start
  FROM event_gaps
)
SELECT user_id, event_time,
  SUM(is_session_start) OVER (
    PARTITION BY user_id ORDER BY event_time
    ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW
  ) AS session_num
FROM session_flags;
```

### Week-over-Week Revenue Change
- Aggregate to weekly grain first, then LAG to get prior week
- Use NULLIF to prevent division by zero when computing percentage change
- Always PARTITION BY category (or equivalent dimension) in LAG

### Consecutive Days Streak
- Classic gaps-and-islands variant: subtract ROW_NUMBER from date to get a constant group ID
- All consecutive dates in the same island produce the same `date - ROW_NUMBER()` value
- GROUP BY that derived value to get streak start, end, and length

### Top-N Per Group
- Wrap ranking function in a CTE, then filter with WHERE rn <= N
- Use DENSE_RANK if ties at position N should be included
- Use ROW_NUMBER if you need exactly N rows regardless of ties

## Follow-Ups
- How would you detect sessions when events can arrive out of order?
- How do you handle months with zero activity in MoM growth calculations? (date spine)
- Can you compute a running median using only window functions?
- How would you implement decile-based user segmentation for an ML feature pipeline?
- What is the performance impact of multiple window functions with different PARTITION BY clauses in the same query?
