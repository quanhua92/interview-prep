# Design CI/CD Pipelines — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is this for a stateless service, stateful service, or ML model serving?
  - [ ] What is the target deployment frequency (multiple times per day, weekly)?
  - [ ] What is the acceptable downtime during deployments (zero, a few seconds, maintenance window)?
  - [ ] Is this a monorepo or multi-repo setup?
- [ ] List functional requirements (3-5 items):
  - [ ] Build, test, and deploy code artifacts through environments
  - [ ] Support zero-downtime deployments
  - [ ] Provide fast developer feedback (<10 min for main gate)
  - [ ] Handle database schema migrations safely
  - [ ] Support rollback within minutes
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Pipeline runtime under 15 minutes for standard deploys
  - [ ] Zero-downtime for production
  - [ ] MTTR < 5 minutes for bad deploys
  - [ ] Environment parity between staging and production
- [ ] State your scale estimates:
  - [ ] Number of deploys per day (e.g., 10-50)
  - [ ] Number of tests (unit, integration, E2E)
  - [ ] Database size (e.g., 500M+ rows for migrations)
  - [ ] ML model serving throughput if applicable (e.g., 50K predictions/sec)

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw the pipeline flow: Commit -> Build -> Test Gates -> Artifact Promotion -> Deploy
- [ ] Identify the main stages and their gates:
  - [ ] **Build**: compile, lint, type check, package into immutable artifact
  - [ ] **Test**: unit (fast, parallel) -> integration (sharded) -> E2E (full stack)
  - [ ] **Promote**: same artifact pushed to staging -> production (never rebuild)
  - [ ] **Deploy**: blue-green / canary / rolling / feature flags
- [ ] Note the test pyramid ratio and why: 70:20:10 (unit:integration:E2E)
  - [ ] Unit tests in milliseconds, parallelized across cores
  - [ ] Integration tests in seconds, constrained by test DB setup
  - [ ] E2E tests in minutes, often the pipeline bottleneck
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain artifact promotion strategy and justify:
  - [ ] Build once, promote the same artifact through all environments
  - [ ] Prevents "works in staging, breaks in prod" from build environment differences
  - [ ] Artifact is immutable: container image, wheel, or binary with versioned tag
- [ ] Define the test gate structure:
  - [ ] Stage 1 (fast gate, <3 min): lint + type check + unit tests, parallelized
  - [ ] Stage 2 (medium gate, <10 min): integration tests, sharded across runners
  - [ ] Stage 3 (slow gate, <15 min): E2E tests in ephemeral environment
  - [ ] Fast-failing on Stage 1 saves ~80% of wasted CI compute on broken PRs
- [ ] Explain environment parity approach:
  - [ ] Infrastructure-as-code (Terraform/Pulumi) for both staging and prod
  - [ ] Same container images, same secrets management
  - [ ] Ephemeral environments per PR eliminate staging drift (3-5x cost)
- [ ] Walk through the main flow end-to-end:
  - [ ] Developer pushes commit -> CI triggers build -> artifact created
  - [ ] Unit tests run in parallel -> integration tests sharded -> E2E in ephemeral env
  - [ ] Artifact promoted to staging -> smoke tests pass
  - [ ] Deployment strategy executes (canary/blue-green) -> monitoring validates health
  - [ ] If unhealthy: automated rollback within minutes

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss deployment strategy selection:
  - [ ] Blue-Green: stateless services, instant rollback, 2x infra cost
  - [ ] Canary: high-traffic services, small blast radius, needs traffic splitting
  - [ ] Feature Flags: risky features, A/B testing, decouples deploy from release
  - [ ] Rolling: K8s-native, mixed versions briefly, needs readiness probes
  - [ ] State that mature systems use multiple strategies for different risk tiers
- [ ] Explain how to fix an inverted test pyramid:
  - [ ] Front-load fast gates (lint, type check, unit tests first, in parallel)
  - [ ] Parallelize integration tests via sharding across runners
  - [ ] Quarantine flaky tests (>2% flakiness) to non-blocking job
  - [ ] Measure flakiness rate = failures on green code / total runs
- [ ] Address database migrations (stateful service problem):
  - [ ] Design migrations as expand-then-contract, never atomic changes
  - [ ] Step 1: Expand (add new column, write to both, read from old)
  - [ ] Step 2: Migrate (backfill new from old, batched updates)
  - [ ] Step 3: Switch (update reads to new column)
  - [ ] Step 4: Contract (drop old column)
  - [ ] Four deploys for one rename -- this is the cost of safe migrations
- [ ] Handle ML-specific CI/CD (if applicable):
  - [ ] Code gates: unit tests, linting, type checking (same as software)
  - [ ] Offline validation: new model must beat production by >=0.5-1% on primary metric
  - [ ] Shadow mode: deploy new model, log outputs alongside live, compare distributions (24-72 hours)
  - [ ] Canary validation: monitor online business metrics (CTR, conversion), 24-48 hour window
  - [ ] API versioning on serving endpoints (/v1/predict, /v2/predict) for co-deployment
- [ ] Discuss rollback and recovery design:
  - [ ] Feature flags: always rollback-safe (toggle off)
  - [ ] Blue-green: instant rollback (switch load balancer)
  - [ ] DB migrations: generally irreversible, forward-only design
  - [ ] Automated rollback on error rate spike for MTTR < 5 min

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (e.g., ephemeral envs vs cost, canary duration vs risk)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
