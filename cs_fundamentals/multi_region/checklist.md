# Multi-Region Architecture -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What RTO (Recovery Time Objective) is acceptable -- seconds, minutes, hours?
  - [ ] What RPO (Recovery Point Objective) is acceptable -- zero data loss, seconds, minutes?
  - [ ] Are there data residency requirements (GDPR, CCPA, data sovereignty)?
  - [ ] Is the user base globally distributed or concentrated in one region?
  - [ ] What is the read:write ratio and does it vary by region?
- [ ] List functional requirements (3-5 items):
  - [ ] System must survive a full region failure
  - [ ] Users in different regions should experience low-latency reads and writes
  - [ ] Data must comply with regional regulations (e.g., EU data stays in EU)
  - [ ] Failover should be automatic and tested, not manual
  - [ ] Replication lag must be monitored and bounded
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Target availability: 99.99% or 99.999% (determines topology)
  - [ ] Latency: <100ms for reads in user's home region, <200ms for writes
  - [ ] Scale: number of regions, users per region, cross-region traffic volume
  - [ ] Consistency: strong vs eventual for different data types
- [ ] State your scale estimates:
  - [ ] Cross-region latency: 60-150ms round trip
  - [ ] Replication lag: 1-30s under normal load, minutes under peak
  - [ ] DNS TTL: 60s minimum for responsive failover
  - [ ] Cost: ~2x for active-active, ~1.5x for active-warm standby

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> DNS/Traffic Router -> [Region A: App + DB] <-> [Region B: App + DB]
- [ ] Identify the topology choice and justify it:
  - [ ] Active-Passive: RTO > 5 min acceptable, low complexity, 2x cost
  - [ ] Active-Warm Standby: RTO 1-3 min, medium complexity, 1.5x cost
  - [ ] Active-Active: RTO seconds, very high complexity, 2x cost
  - [ ] Cell-Based: blast radius isolation, highest complexity, Nx cost
- [ ] Note the key tradeoffs for your chosen topology:
  - [ ] Synchronous replication: zero RPO but adds 60-150ms write latency
  - [ ] Asynchronous replication: low latency but seconds of RPO
  - [ ] Geographic write partitioning: eliminates conflicts architecturally
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain traffic routing and failover mechanism:
  - [ ] DNS-based failover (simple, TTL-bound: 1-5 min RTO)
  - [ ] Anycast / global load balancer (faster: seconds-level RTO)
  - [ ] Client-side region selection (lowest latency, requires smart clients)
- [ ] Define replication strategy:
  - [ ] Synchronous cross-region: strong consistency, high write latency
  - [ ] Asynchronous: low write latency, potential data loss on failover
  - [ ] Semi-synchronous: primary confirms locally, replicates async with monitoring
- [ ] Explain conflict resolution approach:
  - [ ] Geographic write partitioning (preferred): assign users to home regions, no cross-region conflicts
  - [ ] CRDTs: for counters, sets, flags -- deterministic merge
  - [ ] LWW (last-write-wins): acceptable only for data that tolerates silent loss
  - [ ] Operational transforms: for collaborative editing, extremely complex
- [ ] Sketch the database selection with justification:
  - [ ] DynamoDB Global Tables: eventual consistency, LWW, high throughput
  - [ ] CockroachDB: serializable, Raft consensus, medium latency
  - [ ] Google Spanner: external consistency, TrueTime, premium cost
  - [ ] Cassandra Multi-DC: tunable consistency, LWW, open source
  - [ ] Aurora Global Database: active-passive, strong on primary, fast failover
- [ ] Walk through the main flow end-to-end:
  - [ ] Write flow: client -> traffic router -> home region -> primary DB -> async replication to other regions
  - [ ] Read flow: client -> traffic router -> nearest region -> replica DB (or primary for read-your-own-writes window)
  - [ ] Failover flow: health check failure -> fencing old primary -> DNS update -> traffic shifts to healthy region

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss replication lag handling:
  - [ ] Read-your-own-writes: route reads to primary for 30-60s after write
  - [ ] Monotonic read tokens: client carries replication LSN, replicas check before serving
  - [ ] Write-through cache: cache recent writes for the writing user's session
  - [ ] Monitor lag as a first-class SLI: alert at 3x normal baseline
- [ ] Explain split-brain prevention:
  - [ ] Quorum-based health checks with odd number of arbiters
  - [ ] Fencing tokens / STONITH: revoke old primary's credentials before promotion
  - [ ] External arbiter or consensus service for region health decisions
- [ ] Handle data residency and compliance:
  - [ ] GDPR: EU data must be partitioned to EU cells, not merely replicated
  - [ ] Cell architecture with regional cells for legal compliance
  - [ ] User-to-cell mapping in low-latency store (Redis ~1ms lookup)
- [ ] Discuss cell-based architecture for blast radius isolation:
  - [ ] Self-contained stacks (app + DB + cache + queue) per cell
  - [ ] Users assigned to cells at registration
  - [ ] Cross-cell operations are explicit and synchronous
  - [ ] Tradeoff: Nx operational surface area, requires heavy automation
- [ ] Address failure modes:
  - [ ] Multi-AZ vs multi-region distinction (same region ~1-5ms vs cross-region 60-150ms)
  - [ ] DNS failover is not instant (TTL-bound caching)
  - [ ] Staging failover tests do not prove production failover (different load profiles)
  - [ ] Synchronous replication gives zero RPO but zero availability during partition (CAP)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
