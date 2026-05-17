# Feature Flags: Safe Rollouts, Kill Switches, and the Dark Launch Pattern — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem in your own words: decoupling deployment from feature release
- [ ] Ask clarifying questions:
  - [ ] What types of flags do we need? (release, experiment, permission, ops)
  - [ ] What is the target evaluation latency? (under 1ms at P99)
  - [ ] Do we need streaming propagation or is polling acceptable?
  - [ ] Are we building a flag system or using a vendor (LaunchDarkly, Unleash)?
- [ ] List functional requirements (3-5 items):
  - [ ] Deploy code with features hidden behind flags (off by default)
  - [ ] Gradually ramp features from 0% to 100% with consistent user assignment
  - [ ] Kill switches to instantly disable degraded subsystems
  - [ ] Dark launch: shadow traffic to validate new code without affecting users
  - [ ] Flag lifecycle management: creation, rollout, cleanup, deletion
- [ ] List non-functional requirements:
  - [ ] Flag evaluation under 1ms at P99 (in-memory, no network call)
  - [ ] Kill switch propagation within 30 seconds to all instances
  - [ ] Support thousands of concurrent flags across hundreds of services
  - [ ] Consistent hashing: same user always sees same variant
- [ ] State scale estimates:
  - [ ] Hundreds of services, thousands of flags
  - [ ] Millions of flag evaluations per second across the fleet
  - [ ] Flag configuration changes a few times per day

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw the architecture: Flag Admin UI -> Flag Service -> [Streaming (SSE/WS)] -> App Servers (in-memory SDK) -> Flag Evaluation (local, no network)
- [ ] Identify the main operations:
  - [ ] Create/update flag (admin, low QPS)
  - [ ] Evaluate flag (application, high QPS, in-memory)
  - [ ] Propagate flag change (streaming push to all instances)
  - [ ] Audit/cleanup stale flags (scheduled job)
- [ ] Note the evaluation path: SDK evaluates locally from memory (sub-ms), no network call on the hot path
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain the four flag types and justify each:
  - [ ] Release flags: short-lived (2-8 weeks), `enable_` prefix, deleted after 100% rollout
  - [ ] Experiment flags: 2-6 weeks, multi-variant, managed by experimentation platform
  - [ ] Permission flags: permanent, per-user entitlement, must be ultra-fast to evaluate
  - [ ] Ops flags (kill switches): permanent, `ops_` prefix, never deleted, fast propagation required
- [ ] Define the consistent hashing formula:
  - [ ] `hash(user_id + flag_id) % 100 < rollout_percentage`
  - [ ] Why not `Math.random()`: same user could flip between variants, invalidates metrics
- [ ] Sketch the rollout ramp schedule:
  - [ ] 1% (24h) -> 10% (48-72h) -> 50% (48-72h) -> 100%
  - [ ] At each stage: check error rates, latency, business metrics
- [ ] Describe the kill switch pattern:
  - [ ] Define fallback behavior first (popular items, cached results, empty state)
  - [ ] Default to on (`disable_feature: false`) so flag system failure keeps feature enabled
  - [ ] Propagate via streaming (SSE/WebSocket), not polling
  - [ ] Test quarterly in staging
- [ ] Describe the dark launch pattern:
  - [ ] Shadow traffic to new code, compare results in background
  - [ ] Fire-and-forget: cannot block primary, cannot add latency, cannot propagate exceptions
- [ ] Walk through end-to-end flows:
  - [ ] Flag creation: admin creates flag with type, rollout %, targeting rules -> flag service stores -> streams to all SDKs
  - [ ] Flag evaluation: request arrives -> SDK checks in-memory flag state -> returns variant -> no network call
  - [ ] Kill switch activation: on-call flips flag -> flag service streams change -> all instances update within 30s

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss flag evaluation architecture:
  - [ ] In-memory SDK: flag state loaded at startup, updated via streaming
  - [ ] No network call on evaluation path (sub-ms)
  - [ ] Fallback to last-known-good state if streaming connection drops
  - [ ] Build vs buy: LaunchDarkly/Unleash vs homegrown (justify based on scale, data residency, cost)
- [ ] Explain flag debt and lifecycle management:
  - [ ] Every flag has an owner (named engineer) and planned deletion date
  - [ ] Monthly audit: flags at 0%/100% for 30+ days get cleanup tickets
  - [ ] 90-day stale flags auto-disabled in staging, Slack notification to owner
  - [ ] Stale flag count as engineering health metric
- [ ] Address edge cases:
  - [ ] Flag system outage: serve last-known-good flag state (cached in memory)
  - [ ] Flag interaction: two flags producing untested code paths (flag combination testing)
  - [ ] Mobile offline: SDK caches flag state locally, serves stale until reconnected
  - [ ] Migration between flag systems: ensure consistent hashing compatibility
- [ ] Discuss ring deployments as alternative to percentage rollout:
  - [ ] Rings by risk tier: internal -> beta -> small customers -> large customers
  - [ ] More precise control, more complex implementation

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (build vs buy, streaming vs polling, default-on vs default-off)
- [ ] Mention what you would improve with more time (automated flag cleanup, flag combination testing, evaluation latency monitoring)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
