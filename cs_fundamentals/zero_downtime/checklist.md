# Zero-Downtime Deployments — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the service type: stateless API, stateful service, or monolith?
  - [ ] What is the rollback SLA: instant (seconds) or acceptable to wait minutes?
  - [ ] Does the deploy involve database schema changes?
  - [ ] What is the fleet size and acceptable infrastructure cost overhead?
  - [ ] Is this a single-service or multi-service coordinated change?
- [ ] List functional requirements (3-5 items):
  - [ ] Deploy new versions without user-visible downtime
  - [ ] Support rollback if the new version is defective
  - [ ] Validate with real production traffic before full exposure
  - [ ] Decouple code deployment from feature activation
  - [ ] Coordinate multi-service deployments safely
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] 99.9% uptime SLA (~8.7 hours downtime/year); a 60-minute bad deploy eats 11% of the budget
  - [ ] Rollback speed: instant (blue-green/feature flags) to minutes (rolling update)
  - [ ] Fleet size: 200-500+ instances per service
  - [ ] Mixed-version tolerance: schema and protocol must coexist during rollout
- [ ] State your scale estimates:
  - [ ] 500-replica fleet with rolling update takes ~20 minutes of mixed-version traffic
  - [ ] 100M+ row database tables where ALTER TABLE holds exclusive locks for minutes
  - [ ] Continuous deployment: hundreds of deploys per day at large companies

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB/Router -> [v1 Pods + v2 Pods] -> [Shared DB + Cache]
- [ ] Identify the four deployment strategies and their tradeoffs:
  - [ ] Blue-Green: two full environments, instant rollback, 2x cost, no mixed versions
  - [ ] Canary: 1-10% traffic to new version, statistical validation, ~5-10% extra capacity
  - [ ] Rolling Update: batch replacement, zero extra cost, longest mixed-version window
  - [ ] Feature Flags: runtime toggle, instant rollback, negligible cost, decouples deploy from release
- [ ] Note the key insight: deploying code and releasing a feature are different events
- [ ] Present the strategy comparison and get alignment on which fits the scenario

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain the chosen strategy's implementation in detail:
  - [ ] Blue-Green: two Deployments in Kubernetes, flip Service selector label, confirm healthy, tear down old
  - [ ] Canary: two Deployments sharing one Service (replica-ratio routing) or Istio VirtualService with weighted routing
  - [ ] Rolling Update: `maxUnavailable: 0` + `maxSurge: 25%` for safe production rollouts
  - [ ] Feature Flags: hash-based deterministic bucketing, progressive rollout (internal → beta → 1% → 100%)
- [ ] Address the database migration compatibility problem:
  - [ ] During mixed-version windows, both old and new code must work with the same schema
  - [ ] RENAME COLUMN is always breaking — requires expand-contract
  - [ ] ADD NOT NULL on large tables causes table rewrite — add as nullable first
  - [ ] DROP COLUMN cannot happen in the same release code stops using it — rollback target needs it
- [ ] Describe the expand-contract pattern (4 phases):
  - [ ] Phase 1: Expand — add new column nullable, dual-write to both old and new
  - [ ] Phase 2: Migrate — batched backfill (5K rows, 50ms sleep between batches)
  - [ ] Phase 3: Contract — switch reads to new column only, stop dual-write, then in next release DROP old
  - [ ] Phase 4: Verify — audit ORM models, run production query, document in schema changelog
- [ ] Walk through the main flow end-to-end:
  - [ ] Deploy starts → migration runs (forward-compatible) → pods replace in batches → health checks pass → rollout complete
  - [ ] If rollback needed → strategy determines speed (LB flip vs redeploy vs flag disable)

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss canary analysis automation:
  - [ ] Netflix Kayenta uses Mann-Whitney U test (non-parametric, no normality assumption)
  - [ ] Compare canary cohort vs baseline cohort on error rate, p50/p95/p99 latency, business metrics
  - [ ] Auto-rollback if statistically significant degradation (p-value < 0.05)
  - [ ] Business metrics (conversion, session duration) are most important and most often omitted
- [ ] Explain shadow traffic / dark launches:
  - [ ] Mirror production traffic to new service (Istio `mirror` directive), responses discarded
  - [ ] Twitter Diffy compares old vs new responses, clusters differences, filters non-deterministic fields
  - [ ] Facebook Gatekeeper: deployed to all machines, activated for 0% of users, dark period lasts days/weeks
- [ ] Address feature flag governance:
  - [ ] Every flag must have a removal date at creation (TTL enforcement via lint check)
  - [ ] Flags older than 90 days without owner block builds
  - [ ] Permanent config (pool sizes, timeouts) belongs in env vars, not feature flags
  - [ ] Multi-service coordination: deploy both with old behavior, enable flag in caller after both healthy
- [ ] Cover failure modes and common mistakes:
  - [ ] Blue-green shared cache poisoning: use key versioning or separate cache clusters
  - [ ] Canary session stickiness bias: assign cohorts by user ID, not session
  - [ ] Rolling update with non-forward-compatible migration: migration must work with old code
  - [ ] Readiness probe gap: probe must validate DB/cache connections, not just HTTP server
  - [ ] Canary for all-or-nothing changes: use feature flags for coordinated protocol flips instead

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
