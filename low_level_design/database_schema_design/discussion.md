# Database Schema Design for LLD

Source: [Database Schema Design (CalibreOS)](https://www.calibreos.com/learn/lld-database-schema-design)

## One-Liner
Master ER modeling, normalization tradeoffs, B-tree indexing strategy, and online schema migrations -- the four pillars every FAANG LLD interview tests when it pivots from class diagrams to "how would you persist this?"

## Why Schema Design Is an LLD Topic, Not Just a DB Topic
LLD interviews at Amazon, Google, and Stripe almost always pivot from class diagrams to schema design within the first 20 minutes. The interviewer asks: "How would you persist this?", and the candidate's response separates engineers who have actually shipped systems from those who have only studied OOP.

Schema design *is* low-level design. Your tables, columns, foreign keys, and indexes are the durable contract of the system, far more durable than your class hierarchy. A class can be refactored in an afternoon; a schema migration on a 10-billion-row table takes weeks of planning, requires online DDL tooling, and has its own risk envelope. **The schema you draw on the whiteboard will outlive every other LLD decision in the design.**

The interviewer is testing four things in sequence:
1. Can you model entities and relationships correctly (ER modeling)?
2. Do you know when to normalize and when to denormalize (3NF vs read-optimized)?
3. Can you reason about indexes from the actual query patterns (not "add an index on every column")?
4. Do you understand schema evolution under load -- that you cannot just `ALTER TABLE ADD COLUMN NOT NULL` on a billion-row table at 3pm on Tuesday?

## What Earns Each Level

**6/10:** Draws tables with primary keys. Knows what a foreign key is. Adds an index on every "WHERE column" they see. Cannot articulate normalization beyond "splitting tables".

**8/10:** Designs 3NF schemas correctly. Justifies each foreign key with a query pattern. Picks composite index column order using the leftmost-prefix rule. Knows that indexes hurt write throughput. Discusses denormalization as a deliberate read-optimization tradeoff.

**10/10:** Treats schema as a production contract. Designs indexes from the actual query mix (read:write ratio, selectivity). Cites the ~5% selectivity threshold for B-tree usefulness. Walks through an online migration: add nullable column -> backfill in batches -> make NOT NULL -> switch reads -> drop old. Names pt-online-schema-change, gh-ost, and PostgreSQL's CONCURRENTLY. Explains why Stripe-style high-throughput systems sometimes skip foreign keys (the FK enforcement cost on writes outweighs the integrity benefit at their scale).

## The 5-Step Schema Design Framework

### Step 1: Extract entities and relationships from the problem
- Read the requirements and circle the nouns: User, Order, OrderItem, Product, Address.
- These become tables (each entity -> one table; each strong noun is usually an entity, not just an attribute).
- Identify relationships: User has many Orders (1:N), Order has many OrderItems (1:N), Order references one shipping Address (N:1), Product appears in many OrderItems (M:N already resolved by OrderItem).

### Step 2: Define columns, types, and primary keys
- Each entity gets a primary key, prefer surrogate keys (UUID v4 or BIGSERIAL) over natural keys (email, SSN) which can change and cause expensive cascading updates.
- Pick types carefully: VARCHAR(255) is *not* a default, choose precise constraints.
- TIMESTAMPTZ over TIMESTAMP for any time anyone will see.
- NUMERIC(precision, scale) for money, never FLOAT.
- Add NOT NULL aggressively; nullable columns force every query to handle three-valued logic.

### Step 3: Resolve relationships with foreign keys and junction tables
- 1:N relationships -> foreign key on the N side (`orders.user_id REFERENCES users(id)`).
- M:N relationships -> junction table with both foreign keys as a composite primary key (`order_items.order_id + product_id`, or an explicit BIGSERIAL id when the junction has its own attributes like quantity, price).
- Decide ON DELETE behavior explicitly: CASCADE for owned children (order -> order_items), RESTRICT for referenced lookups (order -> user, never auto-delete user data), SET NULL for optional references.

### Step 4: Index from the query mix, not the column list
- List the top 5-10 queries the system runs.
- For each, identify the WHERE/JOIN/ORDER BY columns.
- Build composite indexes that cover the common queries, column order matters (leftmost-prefix rule).
- Add covering indexes (PostgreSQL INCLUDE clause) for hot read paths to avoid heap fetches.
- Skip indexes on low-selectivity columns (gender, status with 3 values) where the optimizer will full-scan anyway.
- Every index costs ~10-30% write throughput and disk space -- the budget is real.

### Step 5: Plan for evolution -- schema is not static
- Assume every column you ship will need to change.
- Use additive migrations (add nullable column -> backfill -> make NOT NULL -> switch reads).
- For online DDL on large tables, use pt-online-schema-change (MySQL), gh-ost (GitHub's MySQL tool), or PostgreSQL's `CREATE INDEX CONCURRENTLY`.
- Avoid DROP COLUMN until all readers have rolled out -- old binaries will break on missing columns.
- The expand-contract pattern is your default migration shape.

## Deep Dive 1: ER Modeling -- From Problem Statement to Tables

ER modeling is the translation step from prose requirements to a relational schema. The discipline: every entity becomes one table; every attribute becomes one column; every relationship becomes either a foreign key or a junction table. Get this right, and the rest of schema design follows mechanically. Get it wrong, and you'll fight the data model for the lifetime of the product.

**Walk-through with the parking-lot domain.** The problem mentions: parking lots, floors, parking spots, vehicles, tickets, payments. Six entities. Each becomes a table. Relationships: a lot has many floors (1:N -> `floors.lot_id`); a floor has many spots (1:N -> `parking_spots.floor_id`); a vehicle parks at one spot at a time and gets one ticket per parking event (1:1 active or 1:N over time -> `tickets.spot_id`, `tickets.vehicle_plate`); a ticket has zero or one payment (1:1 -> `payments.ticket_id` with UNIQUE constraint).

**Counterintuitive insight: most candidates over-normalize.** They split `vehicles` into `vehicles` + `vehicle_owners` + `vehicle_models` + `vehicle_colors` + `vehicle_makes`, creating 6 joins to read a license plate. The interviewer wants to see you justify each FK with a *real query pattern*. If no query needs `vehicle_color` joined to a color taxonomy table, color is just a VARCHAR column on `vehicles`. Premature normalization is as wrong as premature denormalization.

**Naming conventions matter.** Tables are plural lowercase (`parking_spots`, not `ParkingSpot`). Foreign keys are `<referenced_table_singular>_id` (`spot_id`, not `parking_spot_id_fk`). Timestamps end in `_at` (`created_at`, `closed_at`). Booleans are `is_*` or `has_*` (`is_active`). Consistency is more valuable than any single rule.

### Parking Lot Schema (Production-Grade CREATE TABLE)

```sql
-- PostgreSQL. Use BIGSERIAL or UUID v4, pick one and stay consistent.
-- Surrogate keys (id) over natural keys; natural keys belong in UNIQUE constraints.

CREATE TABLE parking_lots (
    id          uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    name        text NOT NULL,
    address     text NOT NULL,
    created_at  timestamptz NOT NULL DEFAULT now()
);

CREATE TABLE floors (
    id            uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    lot_id        uuid NOT NULL REFERENCES parking_lots(id) ON DELETE RESTRICT,
    floor_number  int  NOT NULL,
    total_spots   int  NOT NULL CHECK (total_spots > 0),
    UNIQUE (lot_id, floor_number)            -- no two floors with same number per lot
);

CREATE TABLE parking_spots (
    id          uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    floor_id    uuid NOT NULL REFERENCES floors(id) ON DELETE RESTRICT,
    spot_number text NOT NULL,
    size        text NOT NULL CHECK (size IN ('compact', 'standard', 'large')),
    is_active   boolean NOT NULL DEFAULT true,
    UNIQUE (floor_id, spot_number)
);

CREATE TABLE vehicles (
    plate         text PRIMARY KEY,           -- natural key acceptable here (plates are stable)
    size          text NOT NULL CHECK (size IN ('compact', 'standard', 'large')),
    owner_phone   text,
    first_seen_at timestamptz NOT NULL DEFAULT now()
);

CREATE TABLE tickets (
    id             uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    spot_id        uuid NOT NULL REFERENCES parking_spots(id) ON DELETE RESTRICT,
    vehicle_plate  text NOT NULL REFERENCES vehicles(plate)    ON DELETE RESTRICT,
    issued_at      timestamptz NOT NULL DEFAULT now(),
    closed_at      timestamptz,
    status         text NOT NULL CHECK (status IN ('active','closed','disputed')),

    -- Business invariant: only one ACTIVE ticket per spot at a time.
    -- Partial unique index, only enforces uniqueness for active rows.
    CONSTRAINT one_active_ticket_per_spot UNIQUE (spot_id, status)
        DEFERRABLE INITIALLY IMMEDIATE
);

CREATE TABLE payments (
    id            uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    ticket_id     uuid NOT NULL UNIQUE REFERENCES tickets(id) ON DELETE RESTRICT,
    amount_cents  bigint NOT NULL CHECK (amount_cents >= 0),
    currency      text   NOT NULL CHECK (currency IN ('USD','EUR','INR','GBP')),
    method        text   NOT NULL,
    paid_at       timestamptz NOT NULL DEFAULT now()
);

-- Indexes for the queries we actually run:
CREATE INDEX idx_tickets_vehicle_plate ON tickets (vehicle_plate, issued_at DESC);
CREATE INDEX idx_tickets_active        ON tickets (spot_id) WHERE status = 'active';
CREATE INDEX idx_payments_paid_at      ON payments (paid_at DESC);
```

## Deep Dive 2: Normalization vs Denormalization -- When Each Wins

Normalization is the discipline of removing redundancy. The classical forms -- 1NF (atomic columns), 2NF (no partial-key dependencies), 3NF (no transitive dependencies), BCNF (every determinant is a candidate key) -- are not academic exercises; each form prevents a specific update anomaly that would corrupt your data.

**3NF in one sentence per form.** *1NF*: each cell holds one atomic value (no comma-separated lists in a column). *2NF*: every non-key column depends on the *whole* primary key, not a subset (only relevant when you have composite keys). *3NF*: no non-key column depends on another non-key column (if `customer_address` and `customer_country` both live on `orders`, country depends on address, not on order -- extract `addresses` into its own table). **BCNF** is a stricter 3NF; rare to need explicitly in OLTP.

**The classical 3NF example.** An `orders` table with `(order_id, product_id, product_name, product_price, quantity)` violates 3NF -- `product_name` and `product_price` depend on `product_id`, not on `order_id`. Update anomaly: changing the product name requires updating every order row that references it; if you miss one, the data is inconsistent. Fix: extract `products(product_id, name, price)` and store only `product_id` on orders.

**When to *denormalize* deliberately.** Read-heavy workloads with strict latency budgets (social feeds, leaderboards, search-result pages) often denormalize because the join cost dominates the read latency. Twitter's home-timeline service famously denormalizes by *fanning out* tweets to follower inboxes at write time -- a write-time fan-out trades write amplification for O(1) read latency on the hottest path. Facebook's TAO does the same for the social graph: `friend_count` is materialized on the user row, not computed via `COUNT(*)` on every profile load.

**The interview-grade rule.** Default to 3NF. *Then* identify the 1-3 read paths where the join cost is unacceptable and denormalize *those* explicitly, with a documented invariant: "this column is a materialized cache of X; it is updated by Y; it is reconciled by job Z if it drifts." Naive denormalization without this discipline is technical debt. Deliberate denormalization with reconciliation is engineering.

**Counterintuitive insight.** Most candidates think denormalization is "advanced" and over-apply it. In reality, modern OLTP databases (PostgreSQL, MySQL on InnoDB) execute 3-table joins on indexed columns in <5ms for warm cache. Most read paths *do not* need denormalization. The interviewer wants to see you measure (or estimate) the join cost before paying the consistency tax of denormalized data.

### Normalization to 3NF and a Deliberate Denormalization

```sql
-- VIOLATION: 3NF broken. product_name and product_price depend on product_id,
-- not on order_id. Updating a product name requires touching every order row.
CREATE TABLE orders_bad (
    order_id      uuid PRIMARY KEY,
    user_id       uuid NOT NULL,
    product_id    uuid NOT NULL,
    product_name  text NOT NULL,        -- depends on product_id, not order_id
    product_price numeric(10,2) NOT NULL, -- same
    quantity      int  NOT NULL,
    created_at    timestamptz NOT NULL
);

-- 3NF: extract products into its own table. order_items references product_id only.
CREATE TABLE products (
    id     uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    name   text NOT NULL,
    price  numeric(10,2) NOT NULL CHECK (price >= 0)
);

CREATE TABLE orders (
    id         uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    user_id    uuid NOT NULL REFERENCES users(id) ON DELETE RESTRICT,
    created_at timestamptz NOT NULL DEFAULT now(),
    status     text NOT NULL
);

CREATE TABLE order_items (
    id         bigserial PRIMARY KEY,
    order_id   uuid NOT NULL REFERENCES orders(id)   ON DELETE CASCADE,
    product_id uuid NOT NULL REFERENCES products(id) ON DELETE RESTRICT,
    quantity   int  NOT NULL CHECK (quantity > 0),

    -- DELIBERATE DENORMALIZATION: snapshot the price at order time.
    -- Reason: when the product price changes tomorrow, today's order total
    -- must NOT recompute. Historical price IS part of the order record.
    -- This is not a 3NF violation, unit_price_at_order is a fact about
    -- THIS order, not about THIS product.
    unit_price_at_order numeric(10,2) NOT NULL CHECK (unit_price_at_order >= 0),

    UNIQUE (order_id, product_id)
);

-- READ-PATH DENORMALIZATION (intentional, for latency):
-- The order detail page renders 50,000 times/second. Joining 4 tables every
-- request is wasteful. Materialize a read-optimized view:
CREATE MATERIALIZED VIEW order_summary AS
SELECT  o.id              AS order_id,
        o.user_id,
        u.email           AS user_email,
        COUNT(oi.id)      AS item_count,
        SUM(oi.unit_price_at_order * oi.quantity) AS total_amount,
        o.status,
        o.created_at
FROM orders o
JOIN users  u  ON u.id = o.user_id
JOIN order_items oi ON oi.order_id = o.id
GROUP BY o.id, u.email;

CREATE UNIQUE INDEX ON order_summary (order_id);
-- Refresh strategy: REFRESH MATERIALIZED VIEW CONCURRENTLY order_summary;
-- run from cron every 60s, or on transactional triggers for stricter freshness.
```

## Deep Dive 3: Indexing Strategy -- B-tree, Composite, and Covering Indexes

Indexes are the single most-tested LLD topic at FAANG schema rounds. The naive answer -- "add an index on every WHERE column" -- is exactly what interviewers reject. Strong candidates reason from the query mix, the data cardinality, and the write/read ratio.

**B-tree is the default.** PostgreSQL, MySQL InnoDB, and most OLTP engines use B+tree as the default index structure. A B-tree on a 1-billion-row table has depth ~3-4 -- three to four disk seeks (mostly cached) for any point lookup. Range scans are O(log n + k) where k is the result size. Hash indexes (PostgreSQL hash, hash partitioning) are faster for equality but cannot serve range queries or ORDER BY. LSM-tree indexes (Cassandra, RocksDB-backed engines) optimize write-heavy workloads at the cost of read amplification -- a different tradeoff entirely.

**Composite indexes and the leftmost-prefix rule.** An index on `(user_id, status, created_at)` can serve queries with WHERE clauses that use the columns *as a prefix from the left*: `WHERE user_id = ?`, `WHERE user_id = ? AND status = ?`, `WHERE user_id = ? AND status = ? AND created_at > ?` -- all served. But `WHERE status = ?` alone *cannot* use this index; the optimizer would need a separate index on `(status, ...)`. Column order is therefore the most important index design choice. Rule: put the highest-selectivity column (most distinct values) and the columns that appear in *every* relevant query first.

**Covering indexes.** PostgreSQL's `INCLUDE` clause and MySQL's covering-index trick let you embed extra columns in the index leaf nodes so the query never has to fetch the heap row. For a hot read path that selects just a few columns, this is a massive latency win -- the database serves the entire query from the index pages alone, skipping the table scan that would otherwise follow. Example: `CREATE INDEX ... ON orders (user_id, created_at) INCLUDE (status, total_amount)` -- a query selecting status and total_amount for a user's recent orders is fully covered.

### The 5% Rule -- When NOT to Index

**The 5% rule.** For PostgreSQL, when a query's predicate is selective enough to match less than ~5% of the table rows, the planner uses the index. When the predicate matches more than ~5%, sequential scan is faster (more cache-friendly, no random I/O for heap fetches). This is a planner heuristic, not a hard threshold, but it's the right mental model for "is an index worth it on this column?" Cite this number in interviews; it's a staff-level signal.

**When NOT to index.** Tables with <10K rows -- full scan is faster than index lookup. Columns with very low cardinality (gender = 2 values, status = 3 values) -- the planner will scan anyway when the predicate matches > ~5% of rows. Write-heavy workloads where the index maintenance overhead (typically 10-30% throughput cost per index) exceeds the read benefit. Logging tables that are written orders of magnitude more than read.

**Counterintuitive insight.** Every index costs disk space (often 20-50% the size of the indexed columns) and write throughput (~10-30% per index, more for unique indexes). A table with 8 indexes is paying 80%+ extra write cost. Senior engineers *delete* indexes that don't pay rent -- they audit `pg_stat_user_indexes` for unused indexes and drop them. Indexes are a budget, not a checklist.

**The interview-grade rule.** Every index in your schema design should be motivated by a specific query and a specific selectivity calculation. "I'd add an index on `(vehicle_plate, issued_at DESC)` because the 'show vehicle history' query runs ~1K times/sec, the predicate's selectivity is ~5e-7 on a 180M-row table, and the trailing issued_at supports the ORDER BY without an additional sort step." That is the staff-grade index justification. Anything less specific reads as guessing.

### Indexing Decisions for the Parking-Lot Workload

```sql
-- The query mix (top 5, ~95% of traffic):
-- Q1: SELECT ... FROM tickets WHERE vehicle_plate = ? ORDER BY issued_at DESC LIMIT 10;
-- Q2: SELECT ... FROM tickets WHERE spot_id = ? AND status = 'active';
-- Q3: SELECT ... FROM payments WHERE paid_at >= now() - interval '24 hours';
-- Q4: SELECT COUNT(*) FROM tickets WHERE status = 'active';   -- dashboard
-- Q5: SELECT ... FROM order_items WHERE order_id = ?;          -- order detail page

-- Q1: composite index, leftmost prefix (vehicle_plate), then sort key (issued_at DESC)
CREATE INDEX idx_tickets_plate_issued
    ON tickets (vehicle_plate, issued_at DESC);
-- Selectivity: a typical plate has <100 tickets in 1B-row tickets table -> ~1e-7. Excellent.

-- Q2: partial index on the hot subset only, 'active' tickets are <1% of total.
-- Partial index is smaller, faster, and updated only when status='active'.
CREATE INDEX idx_tickets_active_spot
    ON tickets (spot_id) WHERE status = 'active';

-- Q3: time-range query. B-tree on paid_at supports range scans efficiently.
-- BRIN index alternative: 1000x smaller, fine for append-only time-series tables.
CREATE INDEX idx_payments_paid_at_brin
    ON payments USING brin (paid_at) WITH (pages_per_range = 64);

-- Q4: status='active' has ~1% selectivity, BUT this is COUNT(*), full scan on
-- 1B rows is unacceptable. Use the partial index from Q2: count its entries.
-- Better: maintain a counter in a small stats table, updated by trigger or job.
-- DO NOT index just for COUNT(*) on low-cardinality columns.

-- Q5: single FK column, high selectivity (one order has <50 items, table has 100M).
CREATE INDEX idx_order_items_order_id ON order_items (order_id);

-- COVERING INDEX example (PostgreSQL 11+) for hot read path:
-- Q1 actually selects (vehicle_plate, issued_at, status, spot_id). Cover them:
CREATE INDEX idx_tickets_plate_covering
    ON tickets (vehicle_plate, issued_at DESC)
    INCLUDE (status, spot_id);
-- Now the query never reads the heap row, index-only scan.
-- EXPLAIN ANALYZE should show "Heap Fetches: 0" for fully-vacuumed pages.

-- AUDIT: drop unused indexes monthly.
SELECT schemaname, relname, indexrelname, idx_scan
FROM   pg_stat_user_indexes
WHERE  idx_scan = 0
ORDER BY pg_relation_size(indexrelid) DESC;
-- An index with 0 scans for 30+ days is dead weight, drop it.
```

## Deep Dive 4: Foreign Keys, Constraints, and When to Skip Them

Foreign keys enforce *referential integrity* -- the database guarantees that an `orders.user_id` always points to an existing `users.id`. CHECK constraints enforce column-level invariants (`amount_cents >= 0`, `status IN (...)`). UNIQUE constraints prevent duplicate values. NOT NULL prevents three-valued logic surprises. Together they form the database's *immune system* -- the last line of defense against invalid state, regardless of which application code wrote the row.

**The cascade vs restrict decision.** Every foreign key has an ON DELETE behavior. `CASCADE` (delete the child when the parent goes) is right for *owned* children: `order -> order_items`, `user -> user_sessions`, `parent_comment -> child_comment`. `RESTRICT` (refuse to delete the parent if children exist) is right for *referenced* lookups: `order -> user` (never auto-delete user data because of an order constraint), `order_item -> product` (never delete products that have historical orders). `SET NULL` is right for *optional* references where the child can survive without the parent. Default to RESTRICT -- it's the safest; explicit cascading is a deliberate decision.

**When to skip foreign keys.** This is where senior signal lives. High-throughput systems sometimes drop FK enforcement at the database level because:
1. FK checks add a row-level lock on the parent row during inserts, which becomes a hot-spot bottleneck at >10k writes/sec.
2. Sharded systems where the parent row may live on a different shard cannot enforce FKs across shards.
3. Event-sourced systems write events, not state, and reconstruct integrity from the event log.

Engineering teams in high-throughput systems (large payment processors, ad-serving platforms) sometimes skip database-level FKs and enforce integrity in the application layer or via async reconciliation jobs.

**The interview-grade rule.** Default to FKs in OLTP -- the integrity benefit outweighs the cost on workloads up to single-shard scale. Justify dropping FKs only when you can articulate the specific bottleneck (hot-spot write contention on a high-fanout parent, cross-shard reference, event-sourced architecture). "We dropped FKs for performance" without that specificity is the wrong answer. **Citing the tradeoff specifically -- "we measured 18% write throughput improvement at 50K writes/sec, justified by application-layer integrity checks plus a daily reconciliation job" -- is the staff-level answer.**

**Counterintuitive insight.** Most OLTP systems should keep FKs. The performance cost is real but small (~5-10% on writes); the cost of corrupted referential state at 3am, debugged by tracing through application logs, is much higher. Don't drop FKs as a default optimization -- drop them as a documented, measured, scope-limited decision.

### Constraints and Cascade Decisions in a Real Schema

```sql
-- CASCADE for owned children, order_items belong to the order. Delete order, lose items.
CREATE TABLE order_items (
    id         bigserial PRIMARY KEY,
    order_id   uuid NOT NULL REFERENCES orders(id) ON DELETE CASCADE,
    product_id uuid NOT NULL REFERENCES products(id) ON DELETE RESTRICT,
    quantity   int  NOT NULL CHECK (quantity > 0)
);

-- RESTRICT for referenced lookups, never auto-delete a user because of an order.
-- Forces the application to soft-delete or transfer ownership before allowing deletion.
CREATE TABLE orders (
    id         uuid PRIMARY KEY DEFAULT gen_random_uuid(),
    user_id    uuid NOT NULL REFERENCES users(id) ON DELETE RESTRICT,
    status     text NOT NULL CHECK (status IN ('pending','paid','shipped','cancelled')),
    total_cents bigint NOT NULL CHECK (total_cents >= 0),
    created_at timestamptz NOT NULL DEFAULT now(),
    paid_at    timestamptz,
    -- Cross-column CHECK: paid_at exists iff status is paid/shipped/cancelled
    CHECK ((status = 'pending') = (paid_at IS NULL))
);

-- SET NULL for optional references, referrer can be deleted without losing the order.
CREATE TABLE referrals (
    order_id     uuid PRIMARY KEY REFERENCES orders(id) ON DELETE CASCADE,
    referrer_id  uuid REFERENCES users(id) ON DELETE SET NULL,
    commission_cents bigint NOT NULL CHECK (commission_cents >= 0)
);

-- DEFERRABLE constraints, checked at COMMIT, not statement-time.
-- Useful for cyclic references during a multi-statement transaction.
ALTER TABLE orders
    ADD CONSTRAINT fk_orders_payment
    FOREIGN KEY (latest_payment_id) REFERENCES payments(id)
    DEFERRABLE INITIALLY DEFERRED;

-- WHEN TO SKIP FKs (high-throughput, sharded, event-sourced):
-- Example: ad-impressions table at 100K writes/sec across 64 shards.
-- ad_id may live on shard A, impression on shard B -- cross-shard FK impossible.
-- Trade: enforce ad_id validity in the application's ad-fetch path; reconcile orphans
-- in a daily job that flags ad_ids with no matching ad row.
CREATE TABLE ad_impressions (
    id          bigint PRIMARY KEY,
    ad_id       uuid NOT NULL,           -- NO foreign key constraint at DB level
    user_id     uuid NOT NULL,
    served_at   timestamptz NOT NULL,
    -- Application enforces ad_id validity; daily reconciliation finds orphans.
    INDEX (ad_id, served_at)
);
```

## Deep Dive 5: Schema Evolution -- Online Migrations on Live Tables

Every column you ship will need to change. Schema evolution under load is a senior-level skill because the naive `ALTER TABLE` is often catastrophic on production-sized tables -- it can hold an `ACCESS EXCLUSIVE` lock for minutes or hours, blocking all reads and writes.

**The expand-contract pattern.** The canonical safe-migration shape has four steps, deployable independently:
1. **Expand**: add the new column as nullable. Zero risk -- `ADD COLUMN ... NULL` with no default is fast metadata-only on PostgreSQL >=11 and MySQL with online DDL.
2. **Backfill**: populate the column in batches of 1K-10K rows. Run during off-peak. Each batch commits independently; lock pressure is negligible.
3. **Switch reads**: deploy app code that reads the new column (still nullable in DB, but fully populated). Old binaries still work -- they ignore the new column.
4. **Contract**: make NOT NULL, drop the old column once *all* readers have rolled out. Often skipped -- many teams leave columns nullable forever rather than risk the contract step.

**Online DDL tooling.** For multi-billion-row tables, you can't even do a simple `ADD COLUMN NOT NULL DEFAULT` safely. The tools:
- **pt-online-schema-change** (Percona Toolkit, MySQL): creates a shadow table with the new schema, backfills via triggers, swaps the names atomically. Battle-tested at GitHub-scale and Box-scale.
- **gh-ost** (GitHub's tool, MySQL): same idea as pt-osc but reads from the binary log instead of using triggers, which avoids trigger overhead on the hot table. GitHub uses it for every production schema change.
- **PostgreSQL CONCURRENTLY**: `CREATE INDEX CONCURRENTLY` builds an index without blocking writes. Slower (2-3x) than non-concurrent build, but doesn't take the table offline. Use it for *every* index addition on a production table.

**The non-negotiable rule.** Never run `ALTER TABLE ... ADD COLUMN ... NOT NULL DEFAULT ...` on a large table without thinking. On older MySQL versions and PostgreSQL pre-11, this rewrites the entire table -- minutes-to-hours of downtime. Modern versions handle constant defaults as metadata-only operations, but check your version. When in doubt, use the four-step expand-contract.

**Counterintuitive insight: most schema migrations should be deployed in pieces, not as one PR.** Step 1 (expand) and step 2 (backfill) deploy weeks before step 3 (switch reads). The application code stays compatible with both old and new schemas during the transition. This is the *backward-compatibility window* -- production traffic flows through whichever shape is currently active, and rollback at any step is safe. Treating a migration as one atomic event ("deploy schema + code together") creates an unrecoverable failure mode.

### Online Migration Walkthrough: Adding a NOT NULL Column to a Billion-Row Table

```sql
-- TASK: Add 'plan_tier' (NOT NULL, default 'basic') to a 1.2B-row users table.
-- Naive: ALTER TABLE users ADD COLUMN plan_tier text NOT NULL DEFAULT 'basic';
-- Risk: pre-PG-11 rewrites the whole table; even on PG >=11, evaluate carefully.

-- STEP 1: EXPAND (instant on PG >=11; metadata only, no rewrite)
ALTER TABLE users ADD COLUMN plan_tier text;

-- STEP 2: BACKFILL in batches of 10,000 rows
DO $$
DECLARE batch_size int := 10000;
        last_id uuid := '00000000-0000-0000-0000-000000000000';
        rows_updated int;
BEGIN
    LOOP
        UPDATE users SET plan_tier = 'basic'
        WHERE  id > last_id AND plan_tier IS NULL
        ORDER BY id
        LIMIT batch_size
        RETURNING id INTO last_id;
        GET DIAGNOSTICS rows_updated = ROW_COUNT;
        EXIT WHEN rows_updated = 0;
        COMMIT;                              -- one transaction per batch
        PERFORM pg_sleep(0.1);               -- throttle to spare replicas
    END LOOP;
END $$;

-- STEP 3: DUAL-WRITE, deploy app code that writes plan_tier on every INSERT/UPDATE.
-- Old code paths still work; plan_tier is nullable for now.

-- STEP 4: SWITCH READS, deploy app code that reads plan_tier (no fallback).
-- Confirm: SELECT COUNT(*) FROM users WHERE plan_tier IS NULL;  -- expect 0

-- STEP 5: CONTRACT, make NOT NULL once all rows are populated.
-- Pre-PG-12: this scans the whole table to validate (expensive).
-- PG 12+: ALTER COLUMN ... SET NOT NULL is fast if a CHECK constraint already exists.
ALTER TABLE users ADD CONSTRAINT users_plan_tier_not_null CHECK (plan_tier IS NOT NULL) NOT VALID;
ALTER TABLE users VALIDATE CONSTRAINT users_plan_tier_not_null;  -- O(n) but no rewrite, no AccessExclusiveLock
ALTER TABLE users ALTER COLUMN plan_tier SET NOT NULL;            -- now fast (uses the validated CHECK)
ALTER TABLE users DROP CONSTRAINT users_plan_tier_not_null;       -- redundant now

-- Tools for MySQL equivalents:
-- pt-online-schema-change --alter "ADD COLUMN plan_tier VARCHAR(32) NOT NULL DEFAULT 'basic'" D=app,t=users
-- gh-ost --alter "ADD COLUMN plan_tier VARCHAR(32) NOT NULL DEFAULT 'basic'" --table users --execute

-- Index addition on PostgreSQL: ALWAYS use CONCURRENTLY on production tables.
CREATE INDEX CONCURRENTLY idx_users_plan_tier ON users (plan_tier) WHERE plan_tier != 'basic';
```

## OLTP vs OLAP Schemas -- Don't Mix Them

OLTP and OLAP schemas are designed for *opposite* workloads. Mixing them on the same database is the single most common mistake junior teams make.

**OLTP** (Online Transaction Processing) -- your application database. Optimized for high-frequency, low-latency, single-row reads and writes. Schema: highly normalized (3NF), narrow tables, heavy indexing on lookup columns. Examples: PostgreSQL, MySQL, Aurora. Workload: 100K-1M small queries/sec, each touching <100 rows.

**OLAP** (Online Analytical Processing) -- your analytics warehouse. Optimized for low-frequency, high-throughput, scan-heavy aggregations over millions of rows. Schema: denormalized into a *star schema* (one fact table joined to many dimension tables) or *snowflake schema* (dimensions further normalized). Examples: Snowflake, BigQuery, Redshift, ClickHouse. Workload: 10-1000 large queries/sec, each scanning millions to billions of rows.

**The integration pattern.** The OLTP database is the system of record. Data flows from OLTP to OLAP via *change-data capture* (CDC) -- Debezium reading the WAL/binlog, Fivetran/Airbyte for batch ETL, or built-in replication into a column-store replica. The analytics queries run on the OLAP side, never on the OLTP side. Running a `SELECT COUNT(*) FROM orders WHERE created_at > now() - interval '7 days'` on the OLTP database during peak traffic *will* destabilize the production system.

**The interview-grade rule.** When the interviewer asks about reporting or analytics, the strong answer is: *"OLTP holds the source of truth; analytics queries run on a separate read replica or, better, a columnar warehouse fed via CDC. We never run scan-heavy aggregations on the OLTP cluster."* This signals you've operated production systems and know the failure mode.

## Index Type Cheat Sheet -- When to Use Each

| Index Type | Best For | Cost | Skip When |
|------------|----------|------|-----------|
| **B-tree (default)** | Equality, range, ORDER BY, LIKE 'prefix%' | 10-30% write throughput, 20-50% data size | Tables <10K rows; predicates matching >5% of rows |
| **Hash (PostgreSQL)** | Pure equality lookups (=, no range) | Slightly less write cost than B-tree | Range queries, sorting needs |
| **GIN (PostgreSQL)** | JSONB containment, full-text search, arrays | Slower writes (multiple keys per row) | Simple equality on scalar columns |
| **BRIN (PostgreSQL)** | Append-only time-series (paid_at, created_at) | 1000x smaller than B-tree, lossy lookups | Random-access patterns; tables not naturally sorted |
| **Partial index** | Hot subset of rows (status='active' <1%) | Smaller, faster updates on the indexed subset | Queries that need the entire table |
| **Covering (INCLUDE)** | Hot read paths selecting few columns | Larger leaf pages; same write cost as B-tree | Wide SELECT * queries; storage-constrained systems |
| **Multicolumn (composite)** | Multi-predicate queries with consistent leftmost prefix | Same as B-tree | Queries that filter on trailing columns alone |

## Common Schema-Design Mistakes Candidates Make in Interviews

1. **Indexing every WHERE column.** This is the most common failure. Indexes cost 10-30% write throughput each. A table with 8 indexes is paying massive write tax. Index from the *query mix*, not the column list, and audit `pg_stat_user_indexes` to drop unused ones.

2. **Using FLOAT/DOUBLE for money.** `0.1 + 0.2 != 0.3` in IEEE 754 floats. Always use `NUMERIC(precision, scale)` (PostgreSQL) or `DECIMAL` (MySQL). Better: store amounts as integer minor units (cents) and let the application format. Stripe, PayPal, and every serious payments system stores integers, never floats.

3. **VARCHAR(255) as default.** This length came from MySQL 4's row-format limit and means nothing today. Choose a *meaningful* length -- `VARCHAR(64)` for emails, `TEXT` (PostgreSQL) for unbounded strings, `CHAR(36)` only if you have fixed-length UUIDs as strings. Defaulting to 255 is a tell.

4. **Adding NOT NULL DEFAULT on a billion-row table during business hours.** Pre-PostgreSQL-11 rewrites the entire table. Modern versions handle constant defaults as metadata-only, but only constants. A `DEFAULT now()` or `DEFAULT some_function()` still rewrites. Use the expand-contract pattern.

5. **Using natural keys (email, SSN, username) as primary keys.** Natural keys change -- users update emails, SSNs are reissued, usernames change. Cascading the change through every foreign-key reference is a nightmare. Use surrogate keys (UUID v4 or BIGSERIAL); store natural keys in UNIQUE columns where they belong.

6. **Running analytics queries on the OLTP database.** A `GROUP BY` over millions of rows on the production database during peak traffic will tank latency for everyone. Replicate to a warehouse (BigQuery, Snowflake, Redshift) or a columnar replica (ClickHouse) and run analytics there.

7. **Forgetting timezone-aware timestamps.** `TIMESTAMP` (without timezone) is a footgun. Different replicas in different regions interpret it differently. Always use `TIMESTAMPTZ` (PostgreSQL) or store UTC explicitly with the timezone in a separate column.

## Interview Walkthrough -- From Class Diagram to Schema in 15 Minutes

**Setup:** the interviewer has just walked you through your parking-lot class diagram and now asks: "How would you persist this? Walk me through the schema."

**Strong answer trajectory:**

*Step 1, entities.* "I see six entities: ParkingLot, Floor, ParkingSpot, Vehicle, Ticket, Payment. Each becomes a table. I'll use UUID primary keys for all of them so we can shard later if traffic grows; vehicle is the exception, license plate is a stable natural key, so plate is the PK there."

*Step 2, relationships.* "ParkingLot -> Floors is 1:N, foreign key on floors.lot_id with ON DELETE RESTRICT (we never want to lose floor data because someone deleted a lot). Floor -> Spots same. Spot -> Tickets is 1:N over time. Vehicle -> Tickets is 1:N. Ticket -> Payment is 1:1, enforced by UNIQUE on payments.ticket_id."

*Step 3, invariants.* "Critical business rule: only one *active* ticket per spot at a time. I'll enforce this with a partial UNIQUE index on `tickets(spot_id) WHERE status = 'active'`. This makes invalid state structurally unreachable from any caller."

*Step 4, indexes from the query mix.* "Top query: 'show me a vehicle's recent tickets' -- composite index on `(vehicle_plate, issued_at DESC)`. Hot operational query: 'find the active ticket for this spot' -- partial index on `(spot_id) WHERE status = 'active'`. I'd skip indexing on `status` alone because cardinality is too low -- under 5% selectivity is the rule for the planner to actually use the index."

*Step 5, evolution.* "When we add a new column like loyalty_tier, I'd use the expand-contract pattern: nullable column -> backfill in batches of 10K -> switch reads -> make NOT NULL. On a billion-row table I'd use pt-online-schema-change for MySQL or PostgreSQL's CONCURRENTLY for indexes. We'd never lock the table on a production deploy."

*Step 6, analytics.* "All this lives in OLTP. For dashboards and reporting, we'd CDC into a warehouse -- BigQuery or Snowflake -- and run analytics there. We never run aggregations on the OLTP database during peak traffic."

This is the answer that earns 9-10. It (a) goes from entities to invariants to indexes to evolution in one coherent walk, (b) names production tools (pt-osc, gh-ost, CONCURRENTLY) by name, (c) cites the 5% selectivity rule, (d) explicitly addresses OLTP/OLAP separation.

## Interview Delivery Summary -- The Schema Design Vocabulary That Wins

Schema rounds at FAANG reward exact production vocabulary. The phrases that earn senior signal:

- *"3NF by default; I'll denormalize the order_summary materialized view because the join is on the hot read path."*
- *"Composite index on (user_id, status, created_at DESC), leftmost prefix is user_id because every relevant query filters by user."*
- *"Partial index on `WHERE status = 'active'`, the active subset is <1% of rows, so the index is tiny and the writes only update on state transitions."*
- *"PostgreSQL's planner uses an index when selectivity is roughly under 5%, above that it's a sequential scan, so I'm not adding an index here."*
- *"Online migration via expand-contract: nullable -> backfill in 10K-row batches -> switch reads -> set NOT NULL using a NOT VALID CHECK then VALIDATE, never AccessExclusiveLock."*
- *"For MySQL we'd run pt-online-schema-change or gh-ost; for PostgreSQL, CREATE INDEX CONCURRENTLY for every production index."*
- *"OLTP holds source of truth; analytics queries run on a Snowflake/BigQuery replica fed via Debezium CDC, we never run scan-heavy aggregations on the application database."*

**Staff signal:** end the design with *"I'd add `pg_stat_user_indexes` audits to our weekly DB hygiene runbook so unused indexes get dropped within 30 days, and I'd require every new index to come with the query that motivates it documented in the migration."* This connects the schema decisions to the operational discipline that maintains them, which is the difference between a senior schema design and a staff-level schema design.

## Key Design Decisions

### ER Modeling Approach
- **Option A: Over-normalize** (split every attribute into its own table): Pure, but 6+ joins for basic reads. Poor latency.
- **Option B: Match entities to query patterns**: Table per entity, FK per relationship, justify each with a real query. Balanced.
- **Option C: Under-normalize** (fat tables, duplicate data): Fast reads, consistency nightmare. Only for proven hot paths.

### Normalization Strategy
- **Option A: Always 3NF**: Safe default. Most read paths are fine with indexed joins.
- **Option B: 3NF + deliberate denormalization**: Default to 3NF, then denormalize the 1-3 hottest paths with documented invariants and reconciliation.
- **Option C: Denormalize first**: High risk, maintenance burden. Only for specific ultra-low-latency systems.

### Index Strategy
- **Option A: Index every column**: Massive write tax, no selectivity reasoning. Rejected at FAANG.
- **Option B: Index from query mix**: List top queries, build composites with leftmost-prefix, use covering/partial where justified. The strong answer.
- **Option C: Minimal indexes**: Under-indexed, slow reads. Misses the optimization opportunity.

## Follow-Up Variations
- How would you handle a schema migration on a sharded database where FKs cross shard boundaries?
- What happens when a denormalized counter (e.g., friend_count) drifts from the truth?
- How would you design the schema for a system that needs both OLTP and real-time analytics?
- How do you handle schema changes when multiple services share the same database?
- What index strategy would you use for a table with 90% writes and 10% reads?
