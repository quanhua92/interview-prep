# Databases

SQL vs NoSQL, ACID properties, indexing, normalization, joins, transactions, and CAP theorem for SWE interviews.

## Key Concepts

- **SQL vs NoSQL**: SQL databases (PostgreSQL, MySQL) use structured schemas with tables and relations, enforcing strong consistency via ACID. NoSQL databases (MongoDB, Cassandra, Redis) use flexible schemas with document, key-value, column-family, or graph models, trading some consistency for availability and partition tolerance.
- **ACID Properties**: Atomicity (a transaction is all-or-nothing), Consistency (the database transitions between valid states), Isolation (concurrent transactions do not interfere), Durability (committed transactions persist even after crashes). These guarantee reliable transaction processing.
- **B-Tree Index**: A self-balancing tree structure where each node can have multiple keys and children, keeping data sorted and enabling O(log n) search, insertion, and deletion. Most relational databases use B+ trees (a variant where all data resides in leaf nodes linked sequentially) for both primary and secondary indexes.
- **Normalization**: The process of organizing data to reduce redundancy and dependency. First normal form (1NF) eliminates repeating groups, 2NF removes partial dependencies, and 3NF removes transitive dependencies. Denormalization intentionally reintroduces redundancy to improve read performance.
- **CAP Theorem**: States that a distributed database can provide at most two of three guarantees: Consistency (all nodes see the same data), Availability (every request receives a response), and Partition Tolerance (system works despite network splits). In practice, partition tolerance is required, so the choice is between consistency and availability.

## Common Questions with Brief Answer Outlines

**Q: When would you choose NoSQL over a relational database?**
- When the data schema is evolving or unstructured (e.g., user profiles with varying fields).
- When you need horizontal scalability across many commodity servers.
- When the workload is read-heavy with simple access patterns (e.g., caching with Redis).
- When you need high write throughput on large datasets (e.g., time-series data with Cassandra).
- When relationships between entities are minimal (e.g., document storage in MongoDB).

**Q: Explain the difference between clustered and non-clustered indexes.**
- A clustered index determines the physical order of data in a table; there can be only one per table.
- A non-clustered index is a separate structure that points to the clustered index or heap, enabling multiple per table.
- Clustered indexes are faster for range queries since data is stored sequentially.
- Non-clustered indexes add write overhead since they must be maintained on every insert, update, or delete.
- In PostgreSQL, all indexes are non-clustered; in MySQL/InnoDB, the primary key is a clustered index.

**Q: What are the different types of SQL joins?**
- INNER JOIN returns only rows that have matching values in both tables.
- LEFT (OUTER) JOIN returns all rows from the left table and matched rows from the right; unmatched right columns are NULL.
- RIGHT (OUTER) JOIN is the reverse of LEFT JOIN.
- FULL (OUTER) JOIN returns all rows from both tables, with NULLs where there is no match.
- CROSS JOIN produces the Cartesian product of both tables (every combination of rows).

**Q: How does database indexing work and what are the trade-offs?**
- An index creates a sorted data structure (typically B+ tree or hash table) that allows O(log n) lookups instead of O(n) table scans.
- B-tree indexes are optimal for range queries and sorting; hash indexes are optimal for exact match lookups.
- Trade-offs include increased storage, slower writes (index maintenance on every modification), and the risk of the query planner choosing a suboptimal index.
- Composite indexes (multiple columns) can cover queries but are only effective when the leftmost prefix is used (leftmost prefix rule).

**Q: Explain the CAP theorem with real-world examples.**
- CP systems (consistent + partition tolerant) like HBase and MongoDB (with strong consistency) may reject requests during a partition to maintain consistency.
- AP systems (available + partition tolerant) like Cassandra and DynamoDB return possibly stale data during a partition but remain available.
- CA systems are essentially single-node databases (e.g., standalone PostgreSQL) since network partitions are unavoidable in distributed systems.
- Most real-world systems are eventually consistent (AP) or offer tunable consistency (e.g., Cassandra allows choosing consistency level per query).

**Q: What is connection pooling and why is it important?**
- Connection pooling maintains a set of reusable database connections so that applications do not need to open and close a new connection for every query.
- Opening a connection is expensive (TCP handshake, authentication, TLS negotiation); reusing an existing connection avoids this overhead.
- The pool manages connection lifecycle: creating connections on demand up to a maximum, keeping idle connections alive with periodic heartbeats, and closing connections that have been idle too long or become stale.
- Most web frameworks and ORMs (HikariCP in Java, connection pools in Django/SQLAlchemy) provide built-in connection pooling with configurable parameters (min/max pool size, timeout, validation query).

**Q: How does a SELECT query get executed inside a database?**
- Parsing: the SQL string is parsed into an abstract syntax tree (AST) and checked for syntax errors.
- Binding/Semantic analysis: the database validates table and column names, checks permissions, and resolves types.
- Query planning/optimization: the optimizer generates multiple possible execution plans and selects the most efficient one based on cost estimates (considering indexes, table statistics, join order, and access methods). It may rewrite the query (e.g., pushing down predicates, simplifying subqueries).
- Execution: the executor follows the chosen plan, fetching data from storage via the buffer pool, applying filters, performing joins, and returning results to the client.

## Quick Reference Table

| Feature | SQL (Relational) | NoSQL (Non-Relational) |
|---|---|---|
| Schema | Fixed, predefined | Flexible, dynamic |
| Scaling | Primarily vertical | Primarily horizontal |
| Query language | SQL | Varies (API, query language) |
| Transactions | Full ACID support | Varies (some support multi-document) |
| Data model | Tables with relations | Documents, key-value, graph, column-family |
| Examples | PostgreSQL, MySQL, Oracle | MongoDB, Redis, Cassandra, Neo4j |

## Storage Engines — B-Tree vs LSM-Tree

- **B-Tree** (PostgreSQL, MySQL, SQLite): data organized as a balanced tree of fixed-size pages (4-8 KB each). Pages hold sorted key-value pairs; writes update pages *in-place*. Reads and writes are both O(log n) -- traverse from root to leaf, write to WAL first, then update in-place. Strengths: fast point and range queries, ideal for OLTP read/write balance. Weaknesses: random writes cause write amplification and disk seeks on HDDs.
- **LSM-Tree** (Cassandra, RocksDB, LevelDB, ClickHouse): Log-Structured Merge tree. All writes land in an in-memory **MemTable**, flushed to immutable SSTables on disk when full. A background compaction process merges SSTables, purging duplicates and tombstones. Writes are always sequential -- no random I/O -- for extremely high write throughput. Reads must check MemTable + all SSTables; Bloom filters eliminate most unnecessary lookups. Strengths: write-optimized, perfect for time-series, logs, and append-heavy workloads. Weaknesses: read amplification -- multiple SSTables must be checked per read.

### B-Tree vs LSM-Tree Comparison

| Aspect | B-Tree (PostgreSQL / MySQL) | LSM-Tree (Cassandra / RocksDB) |
|---|---|---|
| Write pattern | Random in-place page writes | Sequential writes (MemTable to SSTables) |
| Read pattern | O(log n) single lookup | MemTable + multiple SSTables (mitigated by Bloom filters) |
| Write amplification | Low-Medium (WAL + page update) | High (data written multiple times through compaction levels) |
| Read amplification | Low (1-2 disk reads typically) | Moderate (several SSTables checked per read) |
| Space amplification | Low-Medium (dead rows via MVCC, vacuumed) | Moderate (compaction lag leaves duplicates temporarily) |
| Best workload | OLTP: balanced read/write, complex queries | Write-heavy: time-series, logs, IoT, large-scale append |
| Examples | PostgreSQL, MySQL, SQLite, Oracle | Cassandra, ScyllaDB, RocksDB, LevelDB, ClickHouse (parts) |

## Advanced Indexing Strategies

- **Composite Index**: an index on `(A, B, C)` satisfies queries on `(A)`, `(A, B)`, or `(A, B, C)` -- but *cannot* be used for queries on `(B)` or `(C)` alone (the **leftmost prefix rule**). Put the most selective (highest-cardinality) column first, equality-filtered columns next, range-filtered columns last. Example: for `WHERE country = 'US' AND age BETWEEN 18 AND 25`, index on `(country, age)` is optimal; `(age, country)` would not be used.
- **Covering Index**: an index that contains *all* columns the query needs, so the database answers the query from the index alone (**index-only scan**), without touching the main table. Example: `SELECT user_id, email FROM users WHERE created_at > '2024-01-01'` is covered by `CREATE INDEX ON users(created_at, user_id, email)`. Result: 3-10x faster for read-heavy workloads. Trade-off: larger index size on disk.
- **Partial Index**: index only a *subset* of rows using a `WHERE` clause on the index definition. Example: `CREATE INDEX ON users(email) WHERE is_active = TRUE` -- indexes only ~10% of rows, making it far smaller and faster than a full index. Limitation: only used when the query predicate matches the index's `WHERE` clause exactly.
- **Hash Index**: in-memory hash table providing O(1) equality lookups. Cannot support range queries or `ORDER BY` -- purely for exact-match access. Use only for very hot exact-match columns where range queries are never needed.
- **Full-Text Search Index (GIN/GiST)**: for queries like "find all documents containing the word X." **GIN** (Generalized Inverted Index) maps each word to the rows containing it; fast reads, slow to update. **GiST** is better for spatial data and custom operators. For production full-text search at scale, Elasticsearch is usually a better fit than PostgreSQL's built-in FTS.

## Sharding Strategies

- **Hash sharding** (most common): `shard = hash(partition_key) % N` -- distributes keys evenly across N shards. Good for user data (`user_id`), session data, key-value access patterns. Pitfalls: adding/removing shards requires rehashing *all* keys (use **consistent hashing** to reduce remapping to O(K/N)); cross-shard range queries require *scatter-gather* -- fan out to all N shards and merge results.
- **Range sharding**: keys divided into sorted ranges (e.g., shard 1 handles `user_id` 1-10M, shard 2 handles 10M-20M). Good for time-series data (partition by date range), sorted scans. Pitfall -- hotspot: all new writes go to the "current" shard (today's timestamp). Fix: *salting* -- prepend a random prefix to keys to spread writes across multiple shards.
- **Choosing the partition key** -- three required properties: (1) **high cardinality** -- distributes data evenly; avoid booleans or low-cardinality enums, (2) **present in most queries** -- otherwise you cannot route without a full scatter-gather, (3) **no natural hotspots** -- avoid keys that concentrate traffic (celebrity IDs, trending items). Common choices: `user_id` for user-centric apps, `content_id` for content, `timestamp + random salt` for event streams.
- **Handling hotspot shards**: (1) **shard key salting** -- append a random suffix (0-99) to spread the key across virtual shards (reads must fan-out and merge), (2) **dedicated shard** -- route known hot accounts to a high-capacity dedicated shard cluster, (3) **application-layer caching** -- put Redis in front of the hot shard; serve 99%+ of reads from cache, (4) **read replicas** -- add replicas specifically to the hot shard to distribute read load.

## Replication Patterns

- **Synchronous replication**: the primary waits for *at least one* replica to confirm the write before acknowledging success to the client. Guarantees: zero data loss on primary failure. Trade-off: higher write latency (replica network round-trip); reduced availability if a replica is slow or down. Use for: financial transactions, any workload where losing even one write is unacceptable.
- **Asynchronous replication**: the primary acknowledges the write immediately after writing locally. Replicas catch up in the background, potentially seconds behind. Guarantees: lowest possible write latency. Trade-off: replication lag means replicas may serve stale data; data loss possible if primary fails before replicas catch up. Use for: read replicas for analytics, content delivery, non-critical data.
- **Semi-synchronous**: wait for exactly *one* replica (out of N) to confirm. Guarantees at least one copy always exists. Middle ground between full sync (wait all) and async (wait none). MySQL's default mode.
- **RPO (Recovery Point Objective)**: the maximum tolerable data loss. RPO = 0 means synchronous replication is required. RPO = seconds means async is fine. RPO = minutes means eventual consistency is acceptable. Always ask "what is the RPO?" before designing the replication topology.

### Replication Topologies

| Topology | Description | Use Case | Trade-offs |
|---|---|---|---|
| Single-leader | One primary accepts writes. N replicas serve reads. | Read-heavy OLTP: 90% reads, 10% writes | Write bottleneck on single primary. Primary failure requires leader election (Raft/Paxos). |
| Multi-leader | Multiple primaries each accept writes. Leaders sync with each other. | Multi-datacenter active-active, offline-capable apps | Write conflicts must be resolved (last-write-wins, CRDTs, application logic). Complex. |
| Leaderless (Quorum) | Any node accepts reads and writes. Quorum W + R > N guarantees overlap. | Cassandra, DynamoDB. Ultra-high write throughput. | Eventual consistency (may read stale data). Last-write-wins creates risk. Anti-entropy for repair. |
| Quorum reads/writes | Write to W of N nodes. Read from R of N nodes. W + R > N ensures at least one node has latest write. | Configurable consistency/availability tradeoff | W=N, R=1: strong consistency, slow writes. W=1, R=N: fast writes, slow reads. |

## Interview Scenario: Design Database for Instagram

Scale: 1B users, 100M photos/day, 5B likes/day.

- **User profiles and follows** -> PostgreSQL + read replicas. Structured data with complex queries (mutual followers, graph traversal). Shard by `user_id`. Replicate to 3 read replicas per region.
- **Photo metadata** -> Cassandra. Wide-column schema: `(user_id, photo_id, timestamp, url, likes_count)`. Partition by `user_id` so all of a user's photos are on one shard for fast timeline lookups. LSM-tree handles 100M photos/day (~1,200 writes/sec) without write bottleneck.
- **Likes** -> Cassandra + Redis. Counter stored in Cassandra (`COUNTER` column for exact count). Redis `ZADD` maintains a sorted set of recent likers per photo. `INCR` in Redis for hot photos, batch-write to Cassandra every 10 seconds.
- **Feed generation** -> DynamoDB. Pre-materialized feed (fan-out on write). Partition key = `user_id`, sort key = `timestamp`. Low-latency reads; high write throughput for fan-out.
- **Celebrity fan-out problem**: a celebrity with 100M followers posts a photo. Naive fan-out = 100M writes. Solution: **hybrid fan-out** -- push to regular users' feeds at write time, but serve celebrity posts on-demand at read time. Redis caches celebrity posts separately to absorb read spikes.
