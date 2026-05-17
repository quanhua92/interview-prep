# SQL Foundations — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] Restate the problem in your own words (what table(s), what output grain)
- [ ] Ask clarifying questions:
  - [ ] What is the expected output grain? (one row per user? per order? per day?)
  - [ ] Are there NULLs in join keys or aggregated columns?
  - [ ] Should unmatched rows be included or excluded?
  - [ ] Are there one-to-many relationships that could cause fanout?
- [ ] Identify the tables and relationships involved:
  - [ ] Which tables are needed?
  - [ ] What is the cardinality between them (1:1, 1:N, N:M)?
  - [ ] Which table is the "driving" (left) table?
- [ ] State expected edge cases:
  - [ ] NULL values in join columns
  - [ ] Users/entities with no matches in the other table
  - [ ] Duplicate rows from one-to-many joins

## Phase 2: High-Level Design (3-5 min)
- [ ] Choose your JOIN strategy:
  - [ ] INNER JOIN: both sides must match
  - [ ] LEFT JOIN + IS NULL: anti-join (find things that don't exist)
  - [ ] LEFT JOIN: include all left rows, NULL-fill missing right
  - [ ] Never use RIGHT JOIN; swap table order instead
- [ ] Decide filter placement:
  - [ ] Row-level filters (country = 'US', date range) -> WHERE
  - [ ] Aggregate filters (COUNT(*) > 5, SUM > 10000) -> HAVING
  - [ ] Know the execution order: FROM > JOIN > WHERE > GROUP BY > HAVING > SELECT > ORDER BY > LIMIT
- [ ] Choose query structure:
  - [ ] Use CTEs (WITH ... AS) for multi-step queries
  - [ ] Never use correlated subqueries (rewrite as JOIN or window function)
  - [ ] Name each CTE for what it computes
- [ ] Sketch the query outline before writing code

## Phase 3: Core Query Construction (5-8 min)
- [ ] Write the FROM/JOIN clause first:
  - [ ] State which table is left and which is right
  - [ ] State the JOIN type and why
  - [ ] Specify the ON condition explicitly
  - [ ] Note: avoid NOT IN with subqueries (NULLs poison it); use LEFT JOIN + IS NULL instead
- [ ] Add the WHERE clause:
  - [ ] Filter individual rows before grouping
  - [ ] Exclude NULLs explicitly where needed (col IS NOT NULL)
  - [ ] Apply date ranges and categorical filters
- [ ] Add GROUP BY:
  - [ ] Every SELECT column must be in GROUP BY or wrapped in an aggregate
  - [ ] COUNT(*) vs COUNT(col): * counts all rows, col counts non-NULL only
- [ ] Add HAVING:
  - [ ] Filter on aggregate values only
  - [ ] Examples: HAVING COUNT(*) > 5, HAVING SUM(revenue) > 10000
- [ ] Add ORDER BY and LIMIT:
  - [ ] ORDER BY runs after HAVING
  - [ ] LIMIT runs last

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Handle NULL traps explicitly:
  - [ ] COUNT(*) vs COUNT(col) difference
  - [ ] AVG ignores NULLs (denominator is non-NULL rows only)
  - [ ] SUM returns NULL if all values are NULL
  - [ ] NULL = NULL is FALSE, not TRUE
  - [ ] Use COALESCE(col, 0) to default NULLs
  - [ ] Use NULLIF(val, 0) to prevent divide-by-zero
- [ ] Debug wrong row counts:
  - [ ] Count rows before and after each JOIN to catch fanout
  - [ ] Validate output grain matches expectation
  - [ ] Check for one-to-many relationships inflating aggregates
- [ ] Discuss query performance:
  - [ ] Correlated subqueries run O(n^2) -- rewrite as JOINs or window functions
  - [ ] Modern optimizers treat CTEs and subqueries identically (PostgreSQL 12+, BigQuery, Snowflake)
  - [ ] Pre-aggregate before joining to avoid fanout
- [ ] Walk through a cohort retention or anti-join example:
  - [ ] Anti-join: LEFT JOIN + WHERE right_key IS NULL
  - [ ] Self-join: CTE for referral chains, joining table to itself
  - [ ] Retention: 4 CTEs (cohorts, activity, sizes, final rate)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the query logic in plain English (not SQL)
- [ ] State the edge cases you handled (NULLs, unmatched rows, fanout)
- [ ] Mention what you would improve with more time (performance, indexing, additional edge cases)
- [ ] Ask the interviewer if they have follow-up questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
