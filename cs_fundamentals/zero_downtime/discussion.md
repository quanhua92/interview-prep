# Zero-Downtime Deployments

Source: [Zero-Downtime Deployments (CalibreOS)](https://www.calibreos.com/learn/hld-zero-downtime-deployments)

## One-Liner
Choose and execute a deployment strategy (blue-green, canary, rolling, or feature flags) that ships changes without downtime, accounting for rollback speed, cost, and database schema compatibility.

## Functional Requirements
- Deploy new application versions without any user-visible downtime
- Support instant or near-instant rollback if the new version is defective
- Validate new versions with real production traffic before full exposure
- Decouple code deployment from feature activation
- Coordinate multi-service deployments safely

## Non-Functional Requirements
- Rollback SLA: instant (~1s for blue-green/feature flags) to minutes (rolling update)
- 99.9% uptime SLA (~8.7 hours downtime budget per year); a single 60-minute botched deploy consumes 11% of that
- Mixed-version tolerance: any strategy with concurrent old+new pods must handle schema and protocol coexistence
- Infrastructure overhead: blue-green requires 2x fleet during swap window; canary requires ~5-10% extra capacity

## Key Scale Questions
- Fleet size: 200-500+ instances per service
- Rollout duration: a 500-replica rolling update with `maxSurge: 25%` takes ~20 minutes of mixed-version traffic
- Database tables: 100M+ rows where `ALTER TABLE` can take minutes and hold exclusive locks
- Deploy frequency: continuous deployment pipelines at Netflix/Facebook/Google deploy hundreds of times per day

## Core Components
- **Load Balancer / Router**: traffic switching mechanism (DNS flip, LB selector update, Istio VirtualService weighted routing)
- **Deployment Orchestrator**: Kubernetes Deployment controller, Spinnaker pipelines, AWS CodeDeploy
- **Canary Analysis Engine**: Spinnaker Kayenta for automated statistical comparison (Mann-Whitney U test)
- **Feature Flag Service**: LaunchDarkly, Flagsmith, or internal Gatekeeper for runtime feature toggling with targeting rules
- **Database Migration Runner**: batched backfill workers, expand-contract migration phases
- **Shadow Traffic Mirror**: Istio traffic mirroring, Twitter Diffy for response comparison

## Key Design Decisions

### Deployment Strategy Selection
- **Blue-Green**: Two full production environments; instant rollback via LB flip; 2x cost during swap; no mixed versions; schema must be bi-directionally compatible at flip instant
- **Canary**: Route 1-10% traffic to new version; automated statistical analysis (Mann-Whitney U); ~5-10% extra capacity; monitors error rate, p99 latency, business metrics; rollback = route 0% to canary
- **Rolling Update**: Replace pods in batches; zero extra cost; longest mixed-version window; slow rollback (must redeploy old version); Kubernetes default with `maxUnavailable` and `maxSurge` knobs
- **Feature Flags**: Deploy code to all instances, control activation via runtime config; instant rollback (disable flag); negligible infra cost; decouples deploy from release; requires flag lifecycle discipline

### Database Schema Migration Compatibility
- **Core constraint**: during any deployment with mixed versions, both old and new code must work with the current schema
- **RENAME COLUMN** is always breaking — requires expand-contract multi-phase migration
- **ADD COLUMN NOT NULL** on large tables causes full table rewrite — add as DEFAULT NULL first, backfill, then add constraint
- **DROP COLUMN** cannot happen in the same release that stops using it — rollback target still references the column
- **Expand-Contract Pattern**: (1) Add new column nullable, dual-write → (2) Backfill in batches → (3) Switch reads to new column, stop dual-write → (4) Drop old column in a subsequent release

### Feature Flag Lifecycle
- Flags are temporary, not permanent config — every flag must have a removal date at creation
- Progressive activation: internal users → beta → percentage rollout (1% → 10% → 50% → 100%) → full launch
- Deterministic rollout via hash-based bucketing: `bucket = hash(flag_name + user_id) % 100 < rollout_percentage`
- Permanent configuration (pool sizes, timeouts) belongs in environment variables or config service, not feature flags

## Strategy Comparison Table
| Strategy | Rollback Speed | Infra Cost | Traffic Mixing | DB Safety | Best Used When |
|----------|---------------|------------|----------------|-----------|----------------|
| Blue-Green | Instant (~1s) | 2x during swap | None | Hard — schema must be bi-directional | Stateless services, critical paths, schema pre-applied |
| Canary | Fast (~5s) | 5-10% extra | Yes (1-10%) | New version must be backward compatible | High-risk changes, ML model updates, new features |
| Rolling Update | Slow (minutes-hours) | None | Yes (entire window) | Most exposed — longest mixed-version window | Stateless services, backward-compatible changes, cost-sensitive |
| Feature Flags | Instant (ms) | Negligible | None | Safest — deploy separate from activation | Product launches, A/B tests, kill switches, multi-service coordination |

## Database Migration Anti-Patterns vs Safe Patterns
| Operation | Unsafe | Safe |
|-----------|--------|------|
| Rename column | Single `ALTER TABLE RENAME` | Expand-contract across 4+ releases |
| Add NOT NULL column | `ADD COLUMN NOT NULL DEFAULT` on large table | Add as DEFAULT NULL, batch backfill, add constraint separately |
| Drop column | DROP in same release code stops using it | Gap of one release between code removal and column drop |
| Add index | `CREATE INDEX` (blocking) | `CREATE INDEX CONCURRENTLY` (no write lock) |
| Migrate data format | Single `UPDATE` on entire table | Batched updates with sleep between batches (5K rows, 50ms sleep) |

## Deep Dive Topics
- Blue-green shared cache poisoning: use cache versioning (`v2:user:123`) or separate cache clusters during swap
- Canary session stickiness bias: sticky sessions skew canary toward new-user behavior; use user-ID-based cohort assignment
- Shadow traffic with Diffy: mirror production traffic to new service, compare responses, filter non-deterministic fields, wait for zero diff rate
- Istio traffic mirroring: `mirror` and `mirrorPercentage` in VirtualService for zero-risk production validation
- Readiness probe validation: probe must check all critical dependencies (DB connections, cache), not just HTTP server status
- Stripe production pattern: backfill jobs as low-priority workers with pause/resume and progress tracking table

## Follow-Up Variations
- How do you rename a column on a 200M-row table during a rolling update without any downtime?
- Your canary shows identical error rates but business conversion dropped 2% — what do you check?
- How do feature flags and canary deployment differ? Give a scenario where one works and the other fails.
- Two services share an API contract — how do you deploy changes to both without coordinated deploys?
- A migration runs for 60 seconds on a high-write table — describe the cascading failure and how to prevent it.
