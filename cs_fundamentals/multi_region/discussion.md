# Multi-Region Architecture

Source: [Multi-Region (CalibreOS)](https://www.calibreos.com/learn/hld-multi-region)

## One-Liner
Deploy services across multiple geographic regions to achieve low latency, high availability, and disaster recovery, while managing replication, conflict resolution, and data residency constraints.

## Why Multi-Region Is Not Just "Add Another Region"
Every large-scale system design eventually encounters the question: "What happens when us-east-1 goes down?" The instinct -- "add a second region" -- sounds simple. The implementation is one of the hardest problems in distributed systems because it forces every tradeoff to be decided explicitly.

Adding a second region means deciding: **who is authoritative for a write?** If both regions can accept writes simultaneously and a network partition separates them, you now have two nodes that each believe they are correct. When the partition heals, something must reconcile the divergence. This is not a technology problem -- it is a correctness problem. The technology (CRDTs, vector clocks, Raft consensus) merely enforces the decision you made about what "correct" means.

Multi-region design touches every layer of the stack:
- **DNS and traffic routing**: how does a client reach the nearest healthy region?
- **Replication**: synchronous (strong consistency, high latency) or asynchronous (low latency, possible data loss)?
- **Conflict resolution**: when two regions accept writes to the same record, which wins?
- **Data residency**: GDPR requires EU user data to stay in EU, which means replication alone is insufficient -- partitioning is required.
- **Failover**: what is the RTO (time to recover) and RPO (data loss window)? Are they tested? An untested failover is not a failover.

The three deployment topologies -- **active-passive**, **active-active**, and active-warm standby -- are not just marketing terms. They represent fundamentally different answers to these questions.

## Three Multi-Region Topologies Compared

| Topology | RTO | RPO | Cost vs Single Region | Complexity | When to Use |
|----------|-----|-----|-----------------------|------------|-------------|
| **Active-Passive (Hot Standby)** | Minutes (DNS TTL expiry + application warmup: 1-10 min) | Seconds to minutes (async replication lag at failure time) | ~2x (standby capacity sits idle) | Low | 99.9% SLA targets, regulated industries requiring DR, teams without distributed-systems expertise |
| **Active-Warm Standby** | 30-120 seconds (reduced capacity + scale-up time) | Seconds (same async replication; standby receives live traffic) | ~1.5x (standby runs at 50% capacity) | Medium | 99.99% SLA targets, cost-sensitive services that need faster recovery than hot standby |
| **Active-Active (Multi-Master)** | Seconds (traffic shifts immediately to healthy region) | Near-zero for sync replication; seconds for async | 2x (full capacity in both regions) | Very High | Five-nines availability, global user base requiring low-latency local writes, payment systems, real-time collaboration |

## Active-Passive Deep-Dive -- The Simplest Model That Still Fails Subtly
In active-passive, one region handles 100% of reads and writes. The secondary region runs a **warm replica**: it receives replicated data continuously but serves no production traffic. When the primary fails, the secondary is promoted.

**What "failover" actually means:** DNS records pointing to the primary region must be updated to point to the secondary. With a DNS TTL of 60 seconds, clients will continue hitting the dead primary for up to 60 seconds after the DNS change propagates. Applications with aggressive DNS caching (common in JVM-based services) can hold the stale record for minutes. Real RTO is often 5-15 minutes even with "instant" DNS failover.

**The replication lag RPO problem:** async replication means the secondary is always slightly behind the primary. Under normal load, the lag is typically 1-30 seconds. Under peak load (when the primary is most likely to fail), lag can grow to minutes. Any writes accepted by the primary but not yet replicated to the secondary are **lost on failover**. For a financial transaction, this is unacceptable. For a social media post, it may be acceptable. You must know which is true for your system and state it explicitly.

**Automatic vs manual promotion:** AWS RDS Multi-AZ provides automatic failover -- but it is within a single availability zone group (a single AWS region). For true cross-region failover, you must either: (a) use a service like Aurora Global Database which provides <1-minute cross-region failover, or (b) implement your own monitoring and promotion logic. The latter is almost always slower than teams expect in a real incident.

**Split-brain on failover:** if the primary is slow (not dead) and the secondary is promoted, you briefly have two active primaries. Both accept writes. When the original primary recovers, you have two diverged histories. Preventing this requires **STONITH** (Shoot The Other Node In The Head) -- an explicit mechanism to fence the old primary before promoting the secondary. In cloud environments, this means detaching the primary's load balancer or revoking its database credentials before promoting the secondary.

## Active-Active Deep-Dive -- The Conflict Resolution Problem
Active-active means both regions accept writes simultaneously. This enables two things: **zero-RTO failover** (healthy region already serves traffic) and **lower write latency** for globally distributed users (user in Tokyo writes to ap-northeast-1 instead of us-east-1, saving ~150ms round trip).

The hard problem is immediately apparent: if a user in New York and a user in London both update the same product inventory record at the same time, and each update is accepted by their local region, which update wins when the two regions sync?

**Last-write-wins (LWW) by wall clock timestamp** is the instinctive answer and is wrong. Wall clocks drift across distributed systems -- two servers may disagree on the current time by tens of milliseconds. An update that is causally newer (happened after) can have an earlier timestamp if the writing server's clock is slightly behind. LWW by wall clock silently discards writes in a way that is nearly impossible to detect or debug in production.

**The real options, ranked by correctness:**

1. **Geographic write partitioning** (most practical): assign every user to a home region. User A always writes to us-east-1; User B always writes to eu-west-1. Cross-region conflicts become structurally impossible because no two regions ever write to the same record. Replication across regions is now purely a read-availability mechanism, not a conflict-resolution mechanism. This is the approach used by **Stripe** for payments (US entities stay in US, EU entities stay in EU).

2. **CRDTs** (Conflict-free Replicated Data Types): mathematical data structures where concurrent updates can always be merged deterministically. A G-Counter (grow-only counter) is the canonical example -- two increments from different regions always merge correctly because addition is commutative and associative. Works for counters, sets, and flags. Does **not** work for arbitrary business logic (you cannot make a CRDT out of "deduct inventory only if quantity > 0").

3. **Operational Transforms / event ordering with vector clocks**: track causality explicitly. Each write carries a vector clock; the merge function uses causal history to order concurrent updates. Used by Google Docs for collaborative editing. Complex to implement correctly; most teams should not build this from scratch.

4. **LWW with application-level timestamps** (Cassandra default): accept that some writes will be silently discarded. Acceptable for user profile updates and settings where losing a concurrent update is tolerable, not acceptable for inventory or financial data.

## Conflict Resolution Strategy Comparison

| Strategy | Consistency Guarantee | Data Types Supported | Implementation Complexity | Real Systems | When NOT to Use |
|----------|----------------------|---------------------|--------------------------|-------------|-----------------|
| **LWW (wall clock)** | None -- silently loses writes | Any | Trivial | Cassandra (default), DynamoDB Global Tables | Any data where silent data loss is unacceptable -- inventory, payments, user settings |
| **LWW (vector clock)** | Causal ordering preserved; concurrent writes still lost | Any | Low | DynamoDB conditional writes, Riak | Concurrent cross-region writes to same key -- one will be lost |
| **CRDTs** | Eventual consistency with provably correct merge | Counters, sets, flags, maps of CRDTs | Medium (use library; avoid custom implementation) | Redis Enterprise, Riak, Cassandra counters | Business logic with preconditions ("deduct only if balance > 0") |
| **Geographic Partitioning** | Strong consistency within home region; no cross-region conflicts | Any (conflicts are architecturally prevented) | Medium (requires routing layer + home-region assignment) | Stripe, Cloudflare, LinkedIn cell architecture | Use cases where any user can legitimately own any record (e.g., shared documents) |
| **Operational Transform / CRDT-OT** | Causal consistency with merge semantics | Sequences, text documents | Very High (extremely difficult to implement correctly) | Google Docs, collaborative editors | Non-document data types; teams without distributed-systems specialists |

## Replication Lag -- The Invisible Bug That Breaks User Trust
Async replication means the secondary is always behind the primary. This lag is usually 1-30 seconds under normal conditions. It is not a bug -- it is an architectural property. The bug is when your application ignores it.

**The read-your-own-writes problem:** a user posts a comment. The write goes to the primary in us-east-1. The user immediately refreshes -- the request is load-balanced to a replica in eu-west-1. The replica hasn't received the replication event yet. The comment is gone. The user thinks the site is broken and posts again. Now you have a duplicate.

Solutions, in order of preference:

1. **Route reads to primary for a session window after a write:** after a user writes data, tag their session with a "wrote at T" timestamp. For the next 30-60 seconds, route reads for that user to the primary. After the window, return to replica reads. This is the approach used by most relational DB setups. Cost: primary handles more read load for recently active writers (often a small fraction of total users).

2. **Read your writes via monotonic read tokens:** after a write, the server returns the replication sequence number (LSN in Postgres, GTID in MySQL). Client sends this token with subsequent reads. Replicas check their current LSN -- if they haven't caught up to the token, they either wait or forward the read to the primary. More complex to implement but works across replica pools without sticky routing.

3. **Write-through cache for the writing user's session:** after a write, store the written value in a user-scoped cache (Redis with a 60-second TTL). Reads check the cache first. Clean to implement for simple data; breaks down for complex queries that aggregate across multiple records.

**Replication lag under load:** lag compounds under write pressure. If the primary is processing 10,000 writes/second and each replica can replicate 8,000/second, the replica is falling behind at 2,000 records/second. After 10 minutes, the lag is 1.2 million records. Monitoring replication lag (not just "is the replica up") is mandatory for any system with user-visible consistency requirements.

## Cell-Based Architecture -- Blast Radius Isolation at Scale
Active-active across two regions is the naive multi-region solution. It creates a system where a bug that corrupts data replicates to both regions simultaneously. A region-level active-active failure -- two regions with conflicting writes that cannot be reconciled -- affects 100% of users. Cell-based architecture solves this by introducing a smaller unit of failure.

**A cell is a self-contained deployment:** one complete stack (app servers, databases, caches, queues) serving a subset of users. Cells do not share state. A failure in Cell A does not affect Cell B because there is no shared infrastructure. Users are assigned to a cell at registration and their data lives entirely within that cell. Cross-cell operations (if needed at all) are explicit and synchronous.

**Cloudflare's cell architecture** runs across 275+ Points of Presence. Each PoP is effectively a cell. A configuration error that crashes one PoP affects the ~1% of users whose traffic routes through it -- not all users globally. This is the defining advantage of cell architecture: **blast radius is bounded by cell size, not region size**.

**Stripe's cell architecture** (called "data residency cells") assigns each merchant to a primary cell based on their legal entity's country. A US LLC is assigned to a US cell; an EU GmbH to an EU cell. Cells are self-contained enough to satisfy GDPR independently -- EU cell data never leaves EU infrastructure. Cross-cell operations (a US merchant paying an EU supplier) go through an explicit cross-cell payment coordinator with exactly-once guarantees enforced by idempotency keys.

**LinkedIn's cell architecture** (internal name: "Multi-Product Architecture") partitions members into cells of approximately 1 million members. Each cell handles the full social graph for its members. A cell failure affects 1M members, not 900M. New cells can be created for capacity expansion without resharding the entire database.

**The operational cost of cell architecture:** cells multiply your operational surface area. If you have 10 cells, you have 10 databases to monitor, 10 application deployments to manage, 10 sets of metrics to observe. Investment in infrastructure automation (Terraform, Kubernetes, centralized monitoring) is a prerequisite -- not an afterthought. Most teams should not build cells until they have exhausted two-region active-active.

## Database Comparison for Multi-Region Deployments

| Database | Multi-Region Model | Consistency Guarantee | Write Latency (cross-region) | Conflict Resolution | Cost Signal | Best Fit |
|----------|--------------------|-----------------------|------------------------------|-------------------|-------------|----------|
| **DynamoDB Global Tables** | Active-active, up to 10 regions | Eventual (LWW by internal timestamp) | ~1ms local write; async cross-region | LWW -- concurrent writes to same key: one is silently discarded | Pay per request; Global Tables adds ~50% cost | High-throughput workloads tolerant of LWW conflicts; gaming leaderboards, session stores |
| **CockroachDB Multi-Region** | Active-active with home region per table/row | Serializable (strongest available) | 60-150ms for cross-region consensus; 5-10ms for home-region writes | Consensus via Raft -- no conflicts, serializable ordering | Higher compute cost than Postgres; licensing for enterprise | Financial transactions, inventory, any use case requiring serializable global consistency |
| **Cassandra Multi-DC** | Active-active, configurable DC count | Tunable: QUORUM LOCAL_QUORUM EACH_QUORUM | ~1ms with LOCAL_QUORUM; 60-150ms with EACH_QUORUM | LWW with tunable consistency; application handles conflicts | Open source; operational complexity is high | Time-series data, IoT, high write volume where eventual consistency is acceptable |
| **Google Spanner** | Active-active across global datacenters | External consistency (stronger than linearizable) | ~5ms commit latency for 2-region synchronous replication | No conflicts -- TrueTime API provides global transaction ordering | Premium cloud pricing (~3-5x standard SQL) | Financial systems, global inventory requiring strong consistency at planetary scale |
| **Aurora Global Database** | Active-passive (1 primary, up to 5 secondaries) | Strong consistency on primary; eventual on secondaries | ~1ms primary write; secondaries replicate in <1s (typically) | No conflicts -- secondaries are read-only | ~20% higher cost than single-region Aurora | Active-passive DR with sub-second failover; read-heavy global workloads |

## Decision Framework -- Which Multi-Region Topology to Choose

### 01: Define Your RTO and RPO Requirements First
- Before choosing a topology, get the business requirements: "How long can the system be unavailable after a region failure?" (RTO) and "How much data can we afford to lose?" (RPO).
- RTO of hours -> active-passive is sufficient.
- RTO of minutes -> active-warm standby.
- RTO of seconds -> active-active.
- RPO of zero -> synchronous replication required; synchronous cross-region replication adds 60-150ms to every write.
- If the business cannot accept either the latency or the cost, the RPO requirement must be renegotiated.

### 02: Determine Whether Writes Conflict Across Regions
- Ask: "Can two users in different regions legitimately write to the same record at the same time?" If the answer is yes and you cannot resolve conflicts deterministically (via CRDT or OT), you must implement geographic write partitioning or use a strongly consistent multi-region database (Spanner, CockroachDB).
- If the answer is no (because your data is naturally user-scoped), active-active with async replication and LWW is acceptable -- conflicts won't occur in practice.

### 03: Check Data Residency Requirements
- GDPR requires that personal data of EU residents be stored and processed in the EU (or a country with adequacy status).
- This is a legal constraint, not a performance optimization.
- If your system stores EU user data, you cannot simply replicate it to US regions -- you must partition it.
- Cell architecture with an EU-only cell is the production answer.
- Design the cell boundary before choosing the replication strategy.

### 04: Choose the Topology
- Active-passive: RTO > 5 min is acceptable, RPO > 0 is acceptable, team has limited distributed-systems expertise, or cost is a primary constraint.
- Active-warm standby: need faster recovery than active-passive but cannot afford full active-active complexity; 50% standby capacity is acceptable; RTO of 1-3 minutes is sufficient.
- Active-active: need sub-minute RTO, global user base with latency-sensitive writes, team has the expertise to implement geographic partitioning or conflict resolution, budget allows 2x infrastructure cost.

### 05: Design the Failover Test Plan Before Launch
- An untested failover is not a failover -- it is a hope.
- Before any multi-region system goes to production, define and execute: (a) What is the trigger for failover -- automated health check, manual decision, or automatic after N consecutive failures? (b) What does promotion look like -- who runs it, how long does it take, what can go wrong? (c) Schedule a chaos engineering exercise: use Netflix Chaos Kong (region-level failure injection) or AWS Fault Injection Simulator to kill the primary region in a staging environment and measure actual RTO/RPO.
- Repeat quarterly.

### 06: Monitor Replication Lag as a First-Class SLI
- Replication lag is not an ops metric -- it is a product metric.
- Define a Service Level Indicator: "Replication lag must stay below Xms at P99." Alert at 3x the normal baseline.
- When lag spikes, route reads to primary to preserve read-your-own-writes consistency.
- Instrument your application to log when reads are served from a lagging replica -- this surfaces consistency bugs in production before users notice.

## Failure Modes and Misconceptions

**"I'll just use active-active with async replication and LWW."** This sentence ends interviews at E5+. LWW silently discards concurrent writes. The candidate who says this without specifying conflict avoidance (geographic partitioning) or a data type that tolerates LWW (counters, session tokens) is demonstrating that they haven't thought about correctness.

**"Multi-AZ is the same as multi-region."** AWS Multi-AZ deploys two nodes in the same AWS region across different physical availability zones (~1-5ms apart). Multi-region deploys across geographically separate regions (60-150ms apart). Multi-AZ provides HA within a region; multi-region provides DR across region failures. Confusing these is a junior-level mistake in a senior-level interview.

**"DNS failover is instant."** DNS TTL means clients cache the old IP for up to TTL seconds after you change the record. A 300-second TTL means some clients will hit the dead primary for up to 5 minutes after failover. For critical services, set TTL to 60s or less -- but remember that lower TTL increases DNS query volume and resolver cache pressure.

**"Synchronous replication gives you zero RPO."** Synchronous replication means the primary waits for the secondary to acknowledge before confirming the write to the client. If the cross-region network is partitioned, the primary blocks. You have strong consistency but zero availability during the partition. This is CAP theorem applied literally -- you cannot have both RPO=0 and 100% availability simultaneously.

**"Our failover is tested because we ran a drill in staging."** Staging traffic is an order of magnitude lower than production. A failover that completes in 2 minutes under staging load may take 15 minutes under production load because: auto-scaling groups need more time to launch instances, connection pools to the new database need warming, caches are cold. Test failover under realistic load -- use production traffic replay if possible.

## What to Say in the Interview -- The E6 Answer
When a multi-region question comes up, lead with requirements, not topology:

**Step 1:** "Before I choose a topology, I need to understand two things: what RTO and RPO the business can tolerate, and whether we have data residency requirements. These constraints narrow the design space significantly."

**Step 2:** State the topology and immediately justify the tradeoff: "Given a 99.99% SLA and a global user base with EU operations, I'd propose active-active with geographic write partitioning. This gives us sub-minute RTO and near-zero RPO. The key constraint I'm imposing is that each user has a home region -- their writes always go to their home region's primary, which eliminates cross-region write conflicts entirely."

**Step 3:** Address replication lag proactively: "Async cross-region replication introduces ~1-5s lag. To preserve read-your-own-writes, I'll route reads to the home region for 30 seconds after any write in that user's session. After 30 seconds, reads can be served from the nearest region."

**Step 4:** Address failure modes: "For split-brain prevention during failover, I'll use a quorum-based health check -- a region declares the other dead only after 3 consecutive missed health checks AND confirmation from an independent third-party monitor. The fencing step revokes database credentials for the old primary before promoting the secondary."

**Step 5 (E6 signal):** "For compliance, I'd implement cell architecture with a dedicated EU cell. EU user data never replicates to US cells. The global router maintains a user-to-cell mapping in a low-latency store -- Redis with ~1ms lookup time -- so routing decisions don't add meaningful latency."

This five-step structure demonstrates requirements-first thinking, topological knowledge, consistency awareness, failure mode handling, and compliance design -- the full E6 surface area in under three minutes.

## Follow-Up Variations
- Design the multi-region architecture for a global e-commerce platform that must handle Black Friday peaks and cannot afford more than 30 seconds of downtime during a region failure.
- Explain split-brain in a multi-region system and how you prevent it.
- A senior engineer proposes: "We can satisfy GDPR by replicating EU user data to an EU region." Is this correct?
- How would you handle a scenario where a region goes down during peak traffic and the standby is 30 seconds behind in replication?
- What happens when two regions accept conflicting writes to the same user's account settings?
- How would you design a multi-region system for a real-time collaborative document editor?
