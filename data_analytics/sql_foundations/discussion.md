# SQL Foundations: JOINs, Aggregations, and NULL Semantics

Source: [SQL Foundations for Data & ML Interviews: JOINs, Aggregations, and Window Functions (CalibreOS)](https://www.calibreos.com/learn/sql-foundations)

## One-Liner
Master the SQL patterns that trip up strong engineers: JOIN row survival, WHERE vs HAVING placement, NULL poisoning of aggregates, and why CTEs always beat subqueries.

## Requirements

### Functional (What Interviewers Test)
- Predict query output before running it (JOIN row counts, aggregate values)
- Choose the correct JOIN type for anti-joins, self-joins, and retention queries
- Place filters correctly: WHERE for row-level, HAVING for aggregate-level
- Handle NULLs explicitly in join keys, aggregates, and GROUP BY
- Structure multi-step queries with CTEs instead of nested subqueries

### Non-Functional (What Separates 9/10 from 6/10)
- A 6/10 candidate writes queries that work on the happy path
- A 9/10 candidate asks: "What happens when this column has NULLs? What if there's no match on the right side of the JOIN? What if a user appears in multiple cohorts?"
- Always narrate NULL handling and JOIN direction choice out loud

## Key Concepts

### SQL JOIN Types
- **INNER JOIN**: keeps rows where ON condition is TRUE (both sides match)
- **LEFT JOIN**: keeps all left rows; NULL-fills right columns when no match
- **RIGHT JOIN**: just a LEFT JOIN with swapped table order -- never use it, swap manually instead
- **FULL OUTER JOIN**: keeps everything; NULLs on both sides for non-matches

### Anti-Join Pattern
- Goal: "find users who have never placed an order"
- Correct: `LEFT JOIN ... WHERE right_key IS NULL`
- Wrong: `NOT IN (subquery)` -- breaks if the subquery returns even one NULL (returns zero rows)
- Appears in cohort analysis, churn detection, and feature engineering

### GROUP BY / HAVING
- GROUP BY collapses rows sharing the same key into one output row
- Every column in SELECT must appear in GROUP BY or be wrapped in an aggregate
- SQL execution order: FROM > JOIN > WHERE > GROUP BY > HAVING > SELECT > ORDER BY > LIMIT
- WHERE filters individual rows before grouping
- HAVING filters aggregate results after grouping
- Cannot use HAVING for non-aggregated columns not in GROUP BY

### Subqueries vs CTEs
- CTEs win on every dimension: readability (named, top-down), debuggability (test each independently), reusability (reference multiple times), performance (modern optimizers treat them identically)
- Always rewrite correlated subqueries as JOINs, CTEs, or window functions (correlated = O(n^2))

### NULL Behavior
- `NULL = NULL` is FALSE in SQL (not TRUE)
- `COUNT(*)` counts all rows; `COUNT(col)` counts only non-NULL values
- `AVG(col)` ignores NULLs (denominator is only non-NULL rows)
- `SUM(col)` ignores NULLs but returns NULL if ALL values are NULL
- NULLs in GROUP BY are grouped together
- Safe patterns: `COALESCE(col, 0)`, `NULLIF(val, 0)` (prevents divide-by-zero), explicit `WHERE col IS NOT NULL`

## Decisions

### JOIN Direction Choice
- Use INNER JOIN when unmatched rows are irrelevant or unwanted
- Use LEFT JOIN when you need all left-side rows (anti-join, optional relationships)
- Default to LEFT JOIN + IS NULL for "find things that don't exist" queries
- Never use RIGHT JOIN; just swap table order and use LEFT JOIN

### WHERE vs HAVING
- Filter individual rows (e.g., country = 'US') -> WHERE (before GROUP BY)
- Filter on aggregates (e.g., COUNT(*) > 5) -> HAVING (after GROUP BY)
- Mixing them up produces plausible but wrong totals
- Example: "products ordered >100 times, only by US users" -> WHERE country='US' before GROUP BY, HAVING COUNT(*) > 100 after

### CTEs over Subqueries
- Always prefer WITH ... AS over nested SELECT
- Each CTE is a named, testable step
- Particularly important for retention/cohort queries with 3-4 logical stages

## Deep Dives

### Self-Join for Referral Chains
- Join a table to itself using CTEs for clarity
- Chain referrals across multiple levels (referrer -> referred -> their referrals)
- CTE makes the self-join readable and debuggable

### Cohort Retention Query Pattern
1. Define user cohorts (first activity month per user)
2. Map each user's monthly activity back to their cohort
3. Compute cohort sizes
4. Calculate retention rate per cohort per month-since-join
- 4 CTEs, each independently testable, fully debuggable

### Production Debug Order for Wrong SQL Results
1. Validate output grain first (one row per user/day/order?)
2. Check join fanout before aggregates (count rows before/after each JOIN)
3. Audit NULL behavior on key columns
4. Reconcile WHERE vs HAVING placement
5. Run a minimal slice sanity check on one known case

### Interview Answer Template
Before writing a query, verbalize:
1. What is the grain of the result? (one row per user? per order? per day?)
2. What JOIN type do I need? (does inner drop unmatched rows I need?)
3. Are there NULLs in join keys or aggregated columns?
4. Does my WHERE filter go before or after grouping?
5. Is there a correlated subquery I can replace with a window function or CTE?

## Follow-Ups
- A colleague's query returns fewer rows than expected -- walk through the debug steps
- Write a query to find the second-highest salary (multiple approaches and tradeoffs)
- Explain SQL execution order and why it matters for writing correct queries
- How would you write a cohort retention query that handles users with multiple sign-up events?
- What happens to your aggregates when a LEFT JOIN produces duplicate rows from a one-to-many relationship?
