# HLD Interview Framework: CIRCLE Method
Source: [HLD Framework (CalibreOS)](https://www.calibreos.com/learn/hld-framework)

## One-Liner
A repeatable 6-step framework (CIRCLE) for high-level design interviews with timing guidance, back-of-envelope estimation references, and the exact questions to ask at each step.

## What Interviewers Actually Evaluate
FAANG HLD rubrics grade five signals regardless of company:
- **Structured thinking under ambiguity**: do you ask requirements *before* designing?
- **Trade-off reasoning**: can you explain *"I chose X over Y because..."*?
- **Back-of-envelope estimation**: can you derive numbers that drive design choices?
- **Failure mode awareness**: what happens when *each component* fails?
- **Communication**: do you drive the conversation clearly and concisely?

"Design Twitter" is not a test of whether you know Twitter's architecture. It is a test of whether you can navigate ambiguity, make decisions under incomplete information, and articulate trade-offs coherently.

Three failure modes account for most senior-level downgrades:
- **Drawing before clarifying.** A candidate sketching boxes in the first 2 minutes has signaled a missing process. The first 5 minutes are requirements and scale, even if you think you know the answer.
- **Conclusions without reasoning.** Proposing the wrong technology is recoverable if you explain your thinking. Proposing *anything* without naming the constraint that forced it is not. Every choice should sound like: *"Cassandra over MySQL: write volume 100K/sec, key-value lookup, no joins. If queries got relational, I'd reconsider."*
- **Ignoring scale until it is too late.** 100 QPS and 100K QPS are different systems for the same product. 1MB per user times 1M users fits on one server; the same system at 1B users needs distributed storage. Estimate first; the numbers determine every downstream choice.

## CIRCLE — The 6-Step Framework

### C — Clarify Requirements (5 min)
- Never assume
- Ask: What are the core features?
- Who are the users and where are they located?
- What scale are we designing for (users, requests/day)?
- Read-heavy or write-heavy?
- Consistency vs availability preference?
- Strong/eventual consistency?
- SLAs?

### I — Identify Scale with Estimation (5 min)
- Calculate: QPS (requests per second), storage needs (GB/TB/PB), bandwidth
- Use these numbers to drive decisions: "At 10,000 QPS a single DB won't cut it, so we need read replicas." Numbers make abstract problems concrete

### R — Rough Design: API + Data Model + Flow (10 min)
- Define: Key APIs (REST endpoints or event interfaces)
- Core data model (what entities, what fields, rough schema)
- High-level request flow — draw boxes and arrows
- This is the skeleton; details come later

### C — Core Components Deep Dive (15 min)
- Pick 2-3 most interesting/challenging components and deep-dive
- Be guided by the interviewer
- Common deep dives: caching strategy, database choice and sharding, message queue design, CDN usage
- Always explain WHY you chose each technology

### L — Latency & Bottleneck Analysis (10 min)
- Where are the hot paths?
- What are the slowest operations?
- Apply solutions: CDN for static content, Redis for hot reads, connection pooling for DB, async queues for slow writes
- Estimate the improvement each optimization makes

### E — Edge Cases & Failure Modes (5 min)
- What happens when: cache goes down? DB primary fails? A service crashes? Network partition occurs?
- Discuss: retry with backoff, circuit breakers, fallback strategies, data consistency during failures

## Back-of-Envelope Estimation Cheat Sheet
| Metric | Rule of Thumb |
|--------|---------------|
| 1M requests/day | ~ 12 QPS |
| 100M requests/day | ~ 1,200 QPS |
| 1B requests/day | ~ 12,000 QPS |
| Peak factor | 3-5x average QPS |
| 1 KB per record, 1B records | = 1 TB storage |
| Average tweet | 280 bytes text + metadata ~ 1 KB |
| Read from memory | 0.1 ms |
| Read from SSD | 1 ms |
| Network round trip (same region) | 1-5 ms |
| Network round trip (cross-region) | 30-150 ms |
| Single DB server | handles ~1,000-5,000 QPS |
| Cache hit rate target | > 90% |

## Database Selection Guide
| Use Case | Best Choice | Why |
|----------|-------------|-----|
| User profiles, relationships | PostgreSQL / MySQL | Strong consistency, rich queries, ACID |
| Session cache, leaderboards | Redis | In-memory, sub-ms latency, sorted sets |
| Time-series (metrics, logs) | Cassandra / InfluxDB | Write-optimized, excellent time-range queries |
| Document store (flexible schema) | MongoDB | Schemaless, horizontal scale |
| Graph relationships | Neo4j / Amazon Neptune | Native graph traversal, relationship-heavy queries |
| Full-text search | Elasticsearch | Inverted index, relevance scoring |
| Real-time location/geo queries | Redis with GEO | GEORADIUS commands, in-memory speed |
| Blob storage (images, video) | S3 / GCS | Cheap, durable, CDN-ready |

## The Most Common Mistake
Jumping to solutions before clarifying requirements. Interviewers deliberately leave requirements ambiguous to see if you ask. The first 5 minutes of clarification often change the entire design. For example: "is this read-heavy?" might reveal that 90% of traffic is reads — you need aggressive caching, not write optimization.

## Full Back-of-Envelope: Design Instagram (Worked Example)

### Scale Assumptions
1B total users, 100M DAU. 50M photos uploaded/day. 500M photo views/day. Average photo = 3MB original, 200KB compressed. Average request = 400 bytes.

### Write QPS
50M uploads/day / 86400 seconds = 580 uploads/sec. Peak = 3x average = 1,740 uploads/sec. At 200KB each: 1,740 x 200KB = 348MB/sec upload bandwidth.

### Read QPS
- 500M photo views/day / 86400 = 5,800 reads/sec
- Peak = 3x = 17,400 reads/sec
- At 200KB each: 17,400 x 200KB = 3.48GB/sec
- A CDN must serve this — a single server can't deliver 3.5GB/sec

### Storage
- New photos: 50M/day x 200KB = 10TB/day
- 3 years x 365 days x 10TB = 10.95PB
- Add 3 sizes (original, medium, thumbnail) = 30PB in 3 years
- S3 cost: $30PB x $0.023/GB/month = ~$700K/month storage alone

### Database
- Metadata (photo_id, user_id, caption, timestamp): 50M rows/day x 365 x 3 = 55B rows at 500 bytes each = 27TB
- PostgreSQL handles up to ~10TB with good tuning → need sharding after year 1
- Shard by user_id
- 10 shards initially with 2TB each

### CDN Sizing
- 3.5GB/sec average, 10GB/sec peak
- CloudFront: ~$0.085/GB in US → 3.5GB/sec x 86400 x 30 days = 9PB/month → $765K/month CDN cost
- Cache hit rate target: 95% (popular photos served from CDN, not origin)
- With 95% hit rate, origin servers see 5% x 17,400 reads/sec = 870 reads/sec — a single server handles this easily

## Latency Numbers Every Engineer Should Know (2025)
| Operation | Latency | Notes |
|-----------|---------|-------|
| L1 cache access | ~0.5 ns | CPU registers + L1 cache |
| L2 cache access | ~7 ns | |
| L3 cache access | ~40 ns | |
| Main memory (RAM) read | ~100 ns = 0.1 us | 100x slower than L1 |
| SSD sequential read (4KB) | ~150 us = 0.15 ms | |
| HDD read (seek + rotation) | ~5-10 ms | 50,000x slower than RAM |
| Network: same datacenter | ~0.5 ms RTT | |
| Network: US cross-country | ~40 ms RTT | |
| Network: US to Europe | ~80 ms RTT | |
| Network: US to Asia-Pacific | ~150 ms RTT | |
| Redis GET | ~0.5-1 ms | Network + hash lookup |
| PostgreSQL query (indexed) | ~1-5 ms | SSD read + query planning |
| PostgreSQL query (seq scan, large table) | ~100ms-seconds | Avoid in hot paths |
| Object storage (S3 GET) | ~50-200 ms | Varies by region |
| HTTP request to external API | ~50-500 ms | Includes DNS + TLS |

## Interview Scenario: Design a Global Notification System
**Problem**: send push notifications to 500M mobile users. 10M notifications/day normally, spikes to 100M during major events (sports scores, breaking news).

**Scale**: 100M/day peak = 1,160/sec average, 10,000/sec peak. Each notification = 500 bytes = 50MB/sec peak.

**Architecture**:
- **(1) API Gateway + notification service**: accepts notification requests, validates, enriches with user preferences (do not disturb, language). Writes to Kafka topic 'notifications'. Does NOT send directly (decoupling).
- **(2) Kafka cluster**: buffer for notification bursts. If push provider is slow (Apple APNS/Google FCM), the Kafka topic accumulates and is drained at a steady rate. Topic partition by user_id for ordering guarantees.
- **(3) Fan-out service**: reads from Kafka, looks up user's device tokens from Redis/DynamoDB (<5ms lookup). Routes to correct push provider. Handles retry with exponential backoff.
- **(4) Device token store**: Redis Hash per user. user:{user_id}:devices → hash of {device_id: push_token}. DynamoDB for persistence. Redis for hot cache.

**Scaling for 100M/event spike**: Kafka handles the burst (consumer lag is acceptable). Fan-out service scales horizontally to 50 workers. Rate limit push provider calls (APNS: 1M/sec limit). Pre-warm connections to APNS/FCM.

**Deduplication**: notification_id in Redis SET with 24h TTL. If notification_id already in set, skip. Prevents duplicate sends during retry.

**Key trade-offs to mention**: delivery guarantees (at-most-once vs at-least-once), message expiry (don't send "game just started" 6 hours later), respect user time zones.

## RACED as the HLD Control Loop
After working through CIRCLE, the faster execution model is **RACED**: Requirements, API and Entities, Core Design, Escalation, Durability. RACED mirrors how strong candidates actually control a 45-minute interview. Requirements define the target. API and Entities force concrete data ownership before any box gets drawn. Core Design proves the happy paths with technology choices attached to numbers. Escalation is where you spend depth on the actual bottlenecks, not random components. Durability shows the system survives production reality.

CIRCLE and RACED are not contradictory. CIRCLE is the memory device you internalize; RACED is the execution loop you narrate out loud to the interviewer. Capacity estimation belongs in Requirements because the estimate decides whether a single PostgreSQL node, read replicas, sharding, or a write-optimized store is even relevant to consider. Failure modes belong in Durability, but collect them as you draw the Core Design because every box you add creates a failure case the interviewer may probe.

Use RACED aloud at minute 5: "I'll pin requirements and scale, define API and entities, draw core flows, deep-dive bottlenecks, then close with failure modes and evolution." That sentence buys structure and gives you explicit permission to defer details until the right phase, which also prevents the interviewer from pulling you into a premature deep dive.

## Capacity Instincts: Find What Saturates First
Back-of-envelope estimation is not about memorizing numbers. It is about finding the first saturated resource: request rate, storage, memory, disk I/O, network egress, queue lag, or operational complexity. Read-dominant QPS is a caching and replica problem. Heavy writes are a partitioning and durability problem. Petabytes of media is a blob storage and CDN problem even at modest QPS. Knowing which resource saturates first tells you where to spend your design effort.

The fastest reliable method: convert users to actions per day, divide by 86,400 for average QPS, apply a 3x peak multiplier, estimate payload size, then ask which component actually sees that load. Do not stop at the final number. Translate it into a design consequence: "At this write rate, the relational primary is the risky component. At this egress, app servers cannot proxy media. At this fan-out, precomputed feeds are worth considering."

Staff-level answers also acknowledge uncertainty rather than hiding it. If the interviewer gives no DAU, pick a round assumption and state it explicitly. If the design changes meaningfully at a certain scale, name the inflection point: "Below roughly 5K writes per second I would keep PostgreSQL; above that I would evaluate sharding or a wide-column store." Naming where the architecture breaks is more impressive than pretending one design covers all scales.

## RACED Interview Time Budget
| Phase | Time | Output | Common failure |
|-------|------|--------|----------------|
| Requirements | 5-8 min | Scope, NFRs, scale assumptions, above/below line | Designing before scale is known |
| API and Entities | 4-6 min | Core endpoints and 3-5 entities | Drawing infrastructure with no data model |
| Core Design | 10-15 min | Happy-path flows and technology choices | Listing tools without justifying tradeoffs |
| Escalation | 10-15 min | Two or three bottleneck deep dives | Deep-diving random components instead of NFR-driven risks |
| Durability | 5-8 min | Failure modes, observability, 10x evolution | Ending with no reliability story |

---

## The 7 Mindset Rules for HLD Interviews

Source: [How to Approach an HLD (CalibreOS)](https://www.calibreos.com/learn/hld-how-to-approach)

### Rule 1 -- Treat ambiguity as a signal, not a bug
- The vague prompt "design Twitter" is deliberate -- the interviewer is testing whether you ask scope questions or fill in assumptions silently
- Silent assumptions = senior-level failure
- Always say: "Before I design, I want to confirm a few things -- is the feed chronological or ranked? Are we including DMs in scope? What's the user count we're sizing for?"

### Rule 2 -- Numbers come before architecture
- 100 QPS and 100K QPS are different systems even for the same product
- Estimate read QPS, write QPS, and storage *first* -- every technology choice downstream is justified by these numbers
- A candidate who says "use Cassandra" without naming the write rate is guessing; one who says "50K writes/sec, leaderless multi-region -> Cassandra" is reasoning

### Rule 3 -- Drive the conversation; do not wait to be led
- Interviewers expect senior candidates to propose the agenda
- Say at minute 5: "Now that requirements are clear, I'll spend ~10 min on rough design, then deep dive on the feed pipeline since that's the most interesting part -- does that work?" This signals ownership

### Rule 4 -- Every component decision = 1 metric + 1 alternative
- Anchor each choice: the metric that forced it (write rate, latency budget, consistency requirement) and the alternative you ruled out (and why)
- "Redis here for <1ms reads. Memcached works but I want sorted sets for the leaderboard view."

### Rule 5 -- Pick 2-3 deep dives, not 5
- Your deep dives are where depth is graded -- two thorough dives on hard parts (celebrity fan-out, cache invalidation) outperform five shallow dives
- Decline the trap: "I could go deep on the CDN, but I think the timeline service is the more interesting design -- happy to switch if you'd rather."

### Rule 6 -- Surface failure modes unprompted
- Don't wait for "what about reliability?" -- proactively say "before I move on, the failure mode for this component is X, the detection signal is Y, recovery takes Z seconds"
- This is the L5+ signal that distinguishes you from candidates who design only the happy path

### Rule 7 -- Watch the clock; abandon perfection
- At minute 35 of a 45-minute interview, stop adding components
- Wrap up with explicit prioritization: "Given the time, here's what I'd cover next if we had 15 more minutes -- failover for the primary DB, the analytics pipeline, and rate limiting at the gateway." This signals you understand engineering tradeoffs in real time

## Anti-Patterns That Lose Points (and the Senior Fix)

| Anti-pattern | Why it costs points | Senior fix |
|---|---|---|
| Drawing a diagram in the first 2 minutes | Signals you skip requirements gathering -- L5+ red flag | Spend the first 5 min asking scope and confirming assumptions out loud |
| Listing "I'd use Redis, Kafka, Cassandra, Spark..." upfront | Pattern-matching, not reasoning -- interviewers downgrade vocabulary dumps | Introduce each technology only when a specific metric forces the choice |
| Designing for 1M users when the prompt implies 1B | Fundamental mis-sizing -- every downstream decision is wrong | Anchor scale early: "I'll size for 100M DAU; tell me if you'd rather a different scale" |
| Skipping back-of-envelope to "save time" | Without numbers, every choice looks arbitrary | Numbers ARE the time-saver -- they let you pre-empt 80% of follow-up questions |
| Deep-diving on whatever you know best | Often the easiest, least differentiating component (CDN, load balancer) | Pick the genuinely hard part -- what would actually be argued about in a real design review |
| Saying "add a cache" without strategy | Half-answer: doesn't address invalidation, fallback, hit rate | Always cover: write strategy, TTL, eviction, miss path, failure path, target hit rate |
| Treating failure modes as an afterthought | Reads as "designs only the happy path" | Surface failure modes per component as you introduce them, unprompted |
| Going silent during whiteboarding | Interviewer can't grade what they can't hear | Narrate every decision: "I see two options here -- A and B. Picking B because..." |
| Refusing to abandon a component when steered | Reads as inflexible, defensive | "Happy to pivot -- let me close the loop on this point first, then I'll switch to X" |
| Building "just in case" over-engineered systems | Reads as junior -- assumes everything must scale to billions | Explicitly state: "For 100K DAU this is overkill -- I'd start with a single Postgres and revisit at 10x scale" |

## The Most Expensive Mistake -- Silent Assumptions
- The highest-leverage failure mode: making an assumption in your head and never voicing it
- Example: interviewer says "design a chat system." You silently assume 1:1 chat. At minute 30 the interviewer asks: "how do groups of 10K members work?" Your fan-out is wrong, message storage is wrong, indexing is wrong. Cost: 5-10 minutes of recovery plus the perception you should have asked
- Fix: state every assumption out loud, even obvious ones. "I'm assuming 1:1 chat -- should I include group chat with up to 10K members?" takes 4 seconds. Cost of asking and being told "yes, 1:1 only" is zero. Cost of not asking and being wrong is the entire interview

## Recovery Patterns When Things Go Wrong

### When you realize at minute 25 you missed a requirement
- Acknowledge cleanly: "Stepping back -- I should have asked about <X> at the start. Let me confirm: <question>?" Then walk through what changes in the design
- This recovers more credit than pretending you accounted for it

### When the interviewer asks about a topic you haven't thought about
- Buy 30 seconds of thinking time without going silent: "Good call -- let me think through that out loud." Then work through it systematically
- Silence reads as panic; structured reasoning under pressure reads as senior

### When you propose a technology and the interviewer pushes back
- Do not defend; reason. Say "Fair point -- let me reconsider." Walk through the tradeoff again
- Often the interviewer is testing whether you'll commit defensively or reason -- the right move is the second

### When the interviewer wants you to deep dive on a component you barely sketched
- 60 seconds to establish the contract first: "Before I dive in, the interface for this is <X>; latency budget <Y>; throughput <Z>. Now the internals..."
- This shows you don't deep dive without context

### When you're 5 minutes from the end with major gaps
- Don't try to cover everything -- explicit prioritization is itself the signal: "In the remaining 5 min, I'll do a fast pass on failure modes since that's most differentiating; the analytics and CDN I'd cover next if we had more time."

### When you give a wrong answer and realize it 30 seconds later
- Self-correct out loud: "Actually, what I just said about <X> isn't right -- the correct way is <Y>." Self-correction is a positive signal; it shows reflection
- Pretending it didn't happen is far worse

## The Decision-Making Loop (Run on Every Choice)
For every component decision, follow this loop:
1. Name the metric that forces the choice (e.g., write rate, latency budget)
2. State the alternative you considered
3. Explain why the alternative was ruled out
4. Acknowledge the trade-off of your chosen option

## What Different Interview Levels Actually Test

| Level | Primary signal | How to demonstrate |
|---|---|---|
| L4 / Mid (E4) | Can you build a working system from a clear spec? | Get the rough design right; reasonable technology choices; some tradeoff awareness |
| L5 / Senior (E5) | Can you make defensible decisions under ambiguity? | Quantified tradeoffs, proactive failure modes, clean communication, drives the conversation |
| L6 / Staff (E6) | Can you identify the highest-leverage architectural decision and reason about it? | Names the *one* decision the rest of the system depends on, debates the alternative seriously, discusses long-term evolution |
| L7 / Senior Staff (E7) | Can you connect technical choices to business and org constraints? | Discusses cost, team operability, data sovereignty, multi-year migration paths, alignment with broader infra strategy |

## How to Practice (and What to Practice)
- **Wrong practice**: solving 50 problems shallowly
- **Right practice**: 5-10 problems *deeply* -- friend playing interviewer, real whiteboard, 45-minute timer, narrating every decision

What to drill:
- **Estimation reflexes**: pick 5 scales (1M, 100M, 1B DAU) and have QPS, storage, bandwidth math automatic. Speed of recall creates space for design thinking
- **The decision loop**: practice it out loud on every choice (DB, cache, queue, replication). Run it on systems you've actually worked with
- **Failure mode coverage**: for the 8 common components (LB, gateway, service, cache, primary DB, replica, queue, object store), memorize failure + detection + recovery. Mental checklist
- **Recovery patterns**: have your partner ambush you at minute 25 with hard questions. Practice recovering from interviews going badly

What NOT to over-practice: memorizing specific architectures (Twitter, Instagram, Uber). Interviewers expect you to *derive* an architecture from requirements, not recite one. Memorization fails the moment the variant question lands.
