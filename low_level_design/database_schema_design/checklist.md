# Database Schema Design for LLD -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What entities are in scope? (e.g., for parking lot: lots, floors, spots, vehicles, tickets, payments)
  - [ ] What are the key relationships? (1:N, M:N, 1:1)
  - [ ] What is the expected scale? (rows per table, QPS for top queries)
  - [ ] Are there analytics/reporting requirements? (OLTP vs OLAP separation)
- [ ] List the entities (each entity -> one table):
  - [ ] Identify strong nouns from the problem statement
  - [ ] Identify relationships (1:N -> FK on N side, M:N -> junction table)
  - [ ] Identify business invariants (e.g., "only one active ticket per spot")
- [ ] List the top 5 queries the system will run (query mix drives everything):
  - [ ] Q1: ____________
  - [ ] Q2: ____________
  - [ ] Q3: ____________
  - [ ] Q4: ____________
  - [ ] Q5: ____________
- [ ] State your scale estimates (rows, QPS, read:write ratio):
  - [ ] ~___M rows in the largest table
  - [ ] ~___K reads/sec, ~___K writes/sec
  - [ ] Read:write ratio ~___:___

## Phase 2: ER Modeling & Schema Design (3-5 min)
- [ ] Draw tables with primary keys:
  - [ ] Prefer surrogate keys (UUID v4 or BIGSERIAL) over natural keys
  - [ ] Natural keys belong in UNIQUE constraints, not as PKs
- [ ] Define columns with precise types:
  - [ ] TIMESTAMPTZ (not TIMESTAMP without timezone)
  - [ ] NUMERIC(precision, scale) for money (never FLOAT)
  - [ ] Meaningful VARCHAR lengths (not default VARCHAR(255))
  - [ ] NOT NULL aggressively; justify every nullable column
- [ ] Resolve relationships:
  - [ ] 1:N -> FK on the N side (e.g., `orders.user_id REFERENCES users(id)`)
  - [ ] M:N -> junction table with composite PK or BIGSERIAL id
  - [ ] 1:1 -> FK with UNIQUE constraint
- [ ] Choose ON DELETE behavior for every FK:
  - [ ] CASCADE for owned children (order -> order_items)
  - [ ] RESTRICT for referenced lookups (order -> user)
  - [ ] SET NULL for optional references (referral -> referrer)
- [ ] Add CHECK constraints for column-level invariants:
  - [ ] Enum-like constraints (`status IN ('active','closed','disputed')`)
  - [ ] Range constraints (`amount_cents >= 0`, `quantity > 0`)
  - [ ] Cross-column constraints if applicable
- [ ] Add UNIQUE constraints for business rules:
  - [ ] Composite UNIQUEs (e.g., `(lot_id, floor_number)`)
  - [ ] Partial unique indexes for invariants (e.g., `UNIQUE (spot_id) WHERE status = 'active'`)
- [ ] Present the schema and get alignment

## Phase 3: Indexing Strategy (5-8 min)
- [ ] List the WHERE/JOIN/ORDER BY columns for each top query
- [ ] Build composite indexes from the query mix:
  - [ ] Apply the leftmost-prefix rule (highest selectivity + always-present columns first)
  - [ ] One composite can serve multiple queries if they share the same leftmost prefix
  - [ ] Column order matters: (user_id, status, created_at) != (status, user_id, created_at)
- [ ] Consider specialized index types:
  - [ ] Partial index for hot subsets (e.g., `WHERE status = 'active'`, <1% of rows)
  - [ ] Covering index (INCLUDE) for hot read paths selecting few columns
  - [ ] BRIN index for append-only time-series columns
  - [ ] GIN index for JSONB, full-text search, or array containment
- [ ] Justify each index with selectivity:
  - [ ] Cite the ~5% selectivity rule (planner uses index when predicate matches <5% of rows)
  - [ ] Skip indexes on low-cardinality columns (gender, 3-value status) where selectivity is too low
  - [ ] Skip indexes on tables with <10K rows (full scan is faster)
- [ ] Account for index costs:
  - [ ] Each index costs ~10-30% write throughput
  - [ ] Each index costs 20-50% of indexed column data size
  - [ ] Audit unused indexes via `pg_stat_user_indexes`
- [ ] Discuss normalization vs denormalization:
  - [ ] Default to 3NF (justify with update anomaly prevention)
  - [ ] Identify 1-3 hot read paths where join cost is unacceptable
  - [ ] Denormalize those explicitly with documented invariants and reconciliation
  - [ ] Materialized views as a structured denormalization option

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss foreign key tradeoffs:
  - [ ] Default: keep FKs for referential integrity (~5-10% write cost is worth it)
  - [ ] When to skip: >10K writes/sec hot-spot, cross-shard references, event-sourced systems
  - [ ] Staff answer: "measured X% throughput improvement, justified by app-layer checks + daily reconciliation"
- [ ] Walk through an online migration (expand-contract pattern):
  - [ ] Step 1: Expand -- add nullable column (metadata-only, instant on PG >=11)
  - [ ] Step 2: Backfill in batches of 1K-10K rows (off-peak, throttled)
  - [ ] Step 3: Dual-write -- deploy app code that writes new column on INSERT/UPDATE
  - [ ] Step 4: Switch reads -- deploy app code that reads new column
  - [ ] Step 5: Contract -- make NOT NULL using NOT VALID CHECK -> VALIDATE -> SET NOT NULL
  - [ ] Name tools: pt-online-schema-change (MySQL), gh-ost (MySQL), CREATE INDEX CONCURRENTLY (PostgreSQL)
- [ ] Explain OLTP vs OLAP separation:
  - [ ] OLTP: 3NF, narrow tables, heavy indexing, 100K-1M small queries/sec
  - [ ] OLAP: star/snowflake schema, columnar storage, 10-1000 large queries/sec
  - [ ] Integration: CDC via Debezium, Fivetran/Airbyte into warehouse
  - [ ] Rule: never run scan-heavy aggregations on OLTP during peak
- [ ] Address common pitfalls:
  - [ ] FLOAT for money (use NUMERIC or integer cents)
  - [ ] VARCHAR(255) as default (choose meaningful lengths)
  - [ ] TIMESTAMP without timezone (use TIMESTAMPTZ)
  - [ ] NOT NULL DEFAULT on billion-row table (use expand-contract)
  - [ ] Natural keys as PKs (use surrogate keys + UNIQUE)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the schema design in 2-3 sentences (entities -> relationships -> invariants -> indexes)
- [ ] State the trade-offs you made and why:
  - [ ] 3NF default with X deliberate denormalizations for hot paths
  - [ ] Y indexes motivated by specific queries with selectivity calculations
  - [ ] FKs kept/dropped with specific justification
- [ ] Mention what you would improve with more time:
  - [ ] `pg_stat_user_indexes` audit in weekly runbook
  - [ ] Require every new index to document the motivating query in the migration
  - [ ] Add CDC pipeline to analytics warehouse
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
