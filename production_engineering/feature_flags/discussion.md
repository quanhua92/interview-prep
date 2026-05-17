# Feature Flags: Safe Rollouts, Kill Switches, and the Dark Launch Pattern

Source: [Feature Flags: Safe Rollouts, Kill Switches, and the Dark Launch Pattern (CalibreOS)](https://www.calibreos.com/learn/prod-feature-flags)

## One-Liner
Decouple code deployment from feature release using a taxonomy of flag types (release, experiment, permission, ops), each with its own lifecycle, evaluation strategy, and cleanup discipline.

## Requirements
- Deploy code to production without exposing unfinished features to users
- Gradually ramp features from 0% to 100% of traffic with consistent user assignment
- Instantly disable degraded subsystems via kill switches (no rollback or redeploy)
- Validate new services under real production traffic without affecting user experience (dark launch)
- Keep flag evaluation overhead under 1ms per request at P99
- Prevent flag debt from accumulating through automated lifecycle management

## Key Concepts

### Core Value Proposition
Feature flags break the coupling between deployment and release. Before flags, a buggy feature meant rolling back the entire deploy (including unrelated fixes). With flags, you flip the flag off and behavior reverts instantly. High-deploy-frequency orgs (GitHub ~80/day, Netflix hundreds/day) rely on flags for progressive delivery.

### Four Flag Types

| Type | Lifecycle | Default | Targeting | Cleanup | Example |
|------|-----------|---------|-----------|---------|---------|
| **Release flag** | 2-8 weeks | Off, ramps to 100% | % rollout by `hash(user_id + flag_id)` | Delete after 100% + 2 weeks stable | `enable_new_checkout_flow` |
| **Experiment flag** | 2-6 weeks | 50/50 split or defined allocation | User segment, % split | Delete when experiment concludes | `checkout_cta_button_variant` |
| **Permission flag** | Permanent | Varies by user tier/role | User property (plan, role, country) | Never -- update targeting rules instead | `show_enterprise_analytics_tab` |
| **Ops flag (kill switch)** | Permanent | On (feature enabled); flip to disable | Global or service-level | Never -- the safety valve you will need again | `ops_disable_personalized_recs` |

### Release Flags
- Hide incomplete/untested features during development
- Naming: `enable_` prefix signals clear on/off semantic and planned deletion
- Create a deletion ticket at the same time as the flag
- Should not exist for more than 1-2 months

### Experiment Flags
- Control which users see which variant for A/B testing
- May have multiple values (control/variant A/variant B) rather than binary
- Typically managed by the experimentation platform, not manually

### Permission Flags
- Enable features based on plan, role, or entitlement (e.g., enterprise-tier analytics)
- Checked on every request for every user, so evaluation must be extremely fast (in-memory lookup)
- Disabling affects paying customers, so rollback story differs from other flags

### Ops Flags / Kill Switches
- Every external dependency should have one: allows graceful degradation when dependency is unavailable
- Naming: `ops_` prefix makes them discoverable and distinguishable from product flags
- Never delete -- you never know when you will need them again

## Decisions

### Gradual Rollout Strategy
- **Consistent hashing** is mandatory: `hash(user_id + flag_id) % 100 < rollout_percentage`
  - Same user sees same experience on every visit
  - Ramp from 10% to 20% preserves original 10% (no re-assignment)
  - Control group in metrics stays stable
  - Never use `Math.random() < 0.1` per-request
- **Recommended ramp schedule**: 1% (24h) -> 10% (48-72h) -> 50% (48-72h) -> 100%
  - Each stage checks error rates, latency, business metrics before proceeding
- **Ring deployments** (Microsoft, AWS): instead of random %, define rings by risk tier (internal -> beta -> small customers -> large customers). More complex but more precise control

### Kill Switch Design Principles
1. **Define fallback first**: A kill switch without a fallback is useless. Decide what users see instead (popular items? cached? empty state?)
2. **Default to on**: `disable_feature: false` so flag system failure keeps the feature enabled
3. **Fast propagation**: Streaming push (SSE/WebSocket), not polling. Target: visible in all instances within 30 seconds. LaunchDarkly achieves under 500ms
4. **Test quarterly**: Flip in staging, verify fallback, flip back. Unexercised kill switches tend to rot

### Dark Launch Pattern
- Send real production traffic to new code, but do not show results to users
- Shadow path must be **fire-and-forget**: cannot block primary response, cannot add latency, cannot propagate exceptions
- Use cases: validating new ranking models, testing new DB queries, load testing new services, validating new payment gateways
- Log divergence between old and new behavior for analysis

## Deep Dives

### Feature Flag System Architecture
- **Evaluation latency budget**: under 1ms at P99
- **In-memory flag state**: pre-fetch flag configuration into application memory; evaluate without network call
- **Streaming updates**: flag changes pushed via SSE/WebSocket to all serving instances (not polling)
- **Flag state propagation latency**: critical SLO for kill switches; target under 30 seconds globally
- **Build vs buy**: LaunchDarkly/Unleash for most teams; homegrown justified only at extreme scale or strict data-residency requirements

### Flag Debt (The Hidden Cost)
Three compounding costs of uncleaned flags:
1. **Code complexity**: 50 active flags = 50 code paths to understand, debug, and test
2. **Dead code paths**: Old `else` branches untested, unmaintained, confusing to new engineers
3. **Evaluation overhead**: 500 flags where 400 are dead still evaluated per request

Flag hygiene system:
- Every flag has a planned deletion date and a named owner (not a team)
- Monthly audit: flags at 0% or 100% for 30+ days get cleanup tickets
- Flags older than 90 days not marked permanent are auto-disabled in staging with Slack notification to owner
- "Stale flags" count tracked as engineering health metric by platform team

### Level Differentiation for Interviews
- **L4/Mid**: Knows flags, has used a flag system, understands gradual rollout as risk mitigation
- **L5/Senior**: Knows four flag types, kill switch implementation, dark launch, flag debt cleanup, in-memory evaluation
- **Staff**: Designs flag system architecture (evaluation service, caching, propagation SLO), build-vs-buy decision, measures flag evaluation P99 impact, systematic lifecycle process

## Follow-Ups
- How would you handle a flag that needs to be evaluated at the edge (CDN) rather than at the application layer?
- What happens when two flags interact and produce an untested code path combination?
- How do you ensure consistent hashing when migrating from one flag system to another?
- How would you design flag evaluation for a mobile client that may be offline for days?
- What is the blast radius if the flag evaluation service goes down entirely? How do you degrade?
