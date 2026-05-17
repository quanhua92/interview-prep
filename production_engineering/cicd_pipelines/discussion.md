# Design CI/CD Pipelines

Source: [CI/CD Pipelines: Designing Safe, Fast Delivery for ML and SDE Systems (CalibreOS)](https://www.calibreos.com/learn/craft-cicd-pipelines)

## One-Liner
Design a CI/CD pipeline from scratch with structured test gates, artifact promotion, deployment strategies, and rollback planning -- including ML-specific gates like shadow mode and offline validation.

## Functional Requirements
- Build, test, and deploy code artifacts through environments (dev -> staging -> production)
- Support multiple deployment strategies (blue-green, canary, rolling, feature flags)
- Provide fast feedback to developers (<10 min for unit/integration gate)
- Handle database schema migrations without downtime
- Support ML model versioning, validation, and staged rollout

## Non-Functional Requirements
- Pipeline total runtime under 15 minutes for standard deploys
- Zero-downtime deployments for production services
- Rollback capability with MTTR < 5 minutes for bad deploys
- Environment parity between staging and production

## Key Scale Questions
- 50K predictions/sec for ML model serving
- 500M+ row tables requiring zero-downtime schema migrations
- Flaky test rate must stay below 2%
- Canary windows: 1-4 hours for software, 24-48 hours for ML models

## Core Components
- **Build Stage**: compile/package artifact once, produce immutable container image or binary
- **Test Gates**: lint + type check + unit tests (fast), integration tests (medium), E2E tests (slow)
- **Artifact Registry**: store versioned artifacts, promote same artifact across environments
- **Deployment Engine**: orchestrate blue-green, canary, rolling, or feature flag deployments
- **Migration Runner**: execute expand-then-contract database migrations across deploys
- **ML Validation Gate**: offline metric comparison, shadow mode logging, canary business metric checks

## Key Design Decisions

### Test Pyramid Structure
- **Option A: 70:20:10 (unit:integration:E2E)**: Industry benchmark. Fast feedback, parallelized unit tests in milliseconds, integration in seconds, E2E in minutes. Front-load fast gates to save 80% of wasted CI compute.
- **Option B: Inverted pyramid**: Accumulates E2E tests over time, pipeline takes 45+ minutes, flaky rate >5%, engineers bypass tests locally. Anti-pattern to fix, not a design choice.

### Artifact Promotion Strategy
- **Option A: Build once, promote**: Same artifact passes gates at each stage (dev -> staging -> prod). Prevents "works in staging, breaks in prod" from build environment differences.
- **Option B: Rebuild per environment**: Fragile, introduces environment-specific build differences. Anti-pattern.

### Deployment Strategy
- **Option A: Blue-Green**: Two identical environments, instant switch via load balancer. 2x infrastructure cost. Best for stateless services with tight MTTR SLOs. Requires DB migration compatibility between blue and green.
- **Option B: Canary**: Route N% traffic to new version, monitor, gradually increase. Small blast radius. Requires traffic splitting infra (Nginx, Envoy, service mesh). Logs/metrics split across versions during rollout.
- **Option C: Feature Flags**: Code deployed everywhere, visibility controlled by flag service at runtime. Most flexible, decouples deploy from release. Flag technical debt accumulates over time.
- **Option D: Rolling**: Replace instances one-by-one (K8s default). Mixed-version state during rollout can expose API compatibility bugs.

### Rollback and Recovery
- **Rollback must be designed before deployment, not after an incident**
- Feature flags: always rollback-safe (toggle off)
- Blue-green: instant rollback (switch load balancer back)
- Database migrations: generally irreversible, design forward-only with expand-then-contract
- Target MTTR < 5 min requires automated rollback on error rate spike

## Pipeline Stage Flow
| Stage | Actions | Gate |
|-------|---------|------|
| Build | Compile, lint, type check, package artifact | Artifact produced |
| Unit Tests | Run unit test suite in parallel across cores | All pass, <3 min |
| Integration Tests | Shard across runners, test DB interactions | All pass, <10 min |
| E2E Tests | Full stack tests in ephemeral environment | All pass, <15 min |
| Artifact Promotion | Push to staging, run smoke tests | Staging validated |
| Deploy to Prod | Blue-green/canary/rolling deploy | Monitoring confirms healthy |

## Database Migration Strategy
| Step | Action | Deploy |
|------|--------|--------|
| Expand | Add new column, write to both old and new, read from old | Deploy 1 |
| Migrate | Backfill new column from old column (batched) | Background job |
| Switch | Update reads to use new column | Deploy 2 |
| Contract | Drop old column | Deploy 3 |

## ML-Specific Gates
| Gate Type | Description | Duration |
|-----------|-------------|----------|
| Offline Validation | New model must beat production model on held-out eval set by >=0.5-1% | Minutes |
| Shadow Mode | Deploy new model, log outputs alongside live model, compare distributions | 24-72 hours |
| Canary Validation | Monitor online business metrics (CTR, conversion), not just error rate | 24-48 hours |

## Deep Dive Topics
- Ephemeral environments per PR: eliminate staging drift, but 3-5x pipeline cost
- Flaky test quarantine: route tests above 2% flakiness to non-blocking job
- Trunk-based development vs long-lived feature branches for CI velocity
- Infrastructure-as-code (Terraform/Pulumi) for environment parity
- API versioning on ML serving endpoints (/v1/predict, /v2/predict) for co-deployment

## Follow-Up Variations
- How would you design a pipeline for a monorepo with 50+ services?
- How do you handle a canary that shows degraded business metrics but no error rate increase?
- What happens when a database migration takes hours on a 500M-row table?
- How would you design CI/CD for an ML model that retrains weekly?
- How do you prevent "works on my machine" across a large engineering team?
