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
