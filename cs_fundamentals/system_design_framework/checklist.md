# HLD Interview Framework — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (5-8 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What are the core features?
  - [ ] Who are the users and where are they located?
  - [ ] What scale are we designing for (users, requests/day)?
  - [ ] Read-heavy or write-heavy?
  - [ ] Consistency vs availability preference?
  - [ ] Strong/eventual consistency?
  - [ ] SLAs?
- [ ] List functional requirements (3-5 items)
- [ ] List non-functional requirements (latency, availability, scale)
- [ ] State your scale estimates (users, requests, storage):
  - [ ] Convert users to actions per day
  - [ ] Divide by 86,400 for average QPS
  - [ ] Apply 3-5x peak multiplier
  - [ ] Estimate payload size and storage needs
- [ ] Identify the first saturated resource (request rate, storage, bandwidth, etc.)
- [ ] Translate the saturation point into a design consequence

## Phase 2: API and Entities (4-6 min)
- [ ] Define key API endpoints (REST or event interfaces):
  - [ ] Method, path, request/response for each endpoint
  - [ ] Note read vs write QPS per endpoint
- [ ] Define core entities and rough schema:
  - [ ] What entities exist?
  - [ ] Key fields for each entity
  - [ ] Relationships between entities
- [ ] Note the read:write ratio and where caching helps
- [ ] Present the endpoints and data model and get alignment

## Phase 3: Core Design (10-15 min)
- [ ] Draw a simple box diagram showing request flow
- [ ] Walk through the main operations end-to-end:
  - [ ] Write path: how data flows in
  - [ ] Read path: how data is retrieved
  - [ ] Async paths: queues, background jobs
- [ ] Explain database selection with justification:
  - [ ] SQL vs NoSQL trade-off for each data type
  - [ ] Name the constraint that forces each choice (e.g., "write volume 100K/sec → Cassandra")
- [ ] Discuss partitioning/sharding strategy:
  - [ ] Shard key choice and why
  - [ ] How many shards, estimated size per shard
- [ ] Present the diagram and get alignment

## Phase 4: Escalation / Deep Dive (10-15 min)
- [ ] Pick 2-3 most interesting/challenging components (be guided by interviewer)
- [ ] Discuss caching strategy:
  - [ ] What to cache and where
  - [ ] Cache hit rate target (> 90%)
  - [ ] Invalidation strategy
- [ ] Discuss scaling/bottleneck solutions:
  - [ ] CDN for static/media content
  - [ ] Redis for hot reads
  - [ ] Connection pooling for DB
  - [ ] Async queues for slow writes
  - [ ] Estimate the improvement each optimization makes
- [ ] Address single points of failure:
  - [ ] Message queue (Kafka) to decouple services
  - [ ] Multi-AZ deployment
  - [ ] Retry with exponential backoff for failed operations
- [ ] Discuss trade-offs explicitly at each decision point

## Phase 5: Durability / Failure Modes (5-8 min)
- [ ] Walk through failure scenarios:
  - [ ] What happens when cache goes down?
  - [ ] What happens when DB primary fails?
  - [ ] What happens when a service crashes?
  - [ ] What happens during network partition?
- [ ] Discuss reliability patterns:
  - [ ] Retry with backoff
  - [ ] Circuit breakers
  - [ ] Fallback strategies
  - [ ] Data consistency during failures
- [ ] Mention how the system handles 10x growth
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
