# Capacity Planning for Production Systems

Source: [Capacity Planning for Production Systems (CalibreOS)](https://www.calibreos.com/learn/prod-capacity-planning)

## One-Liner
Forecast load with uncertainty bands, set tier-based headroom policies, and validate through stress testing to balance reliability against cost.

## Functional Requirements
- Forecast traffic demand across baseline, seasonality, and event spikes
- Translate QPS forecasts into CPU, memory, disk, and network requirements
- Define headroom policies per service tier (critical vs batch)
- Validate capacity assumptions through load and failure testing
- Recalibrate forecasts on a regular cadence using measured error

## Non-Functional Requirements
- Critical services must stay within SLO under N-1 or N-2 failures
- Headroom must absorb bursts, dependency degradation, and host loss simultaneously
- Forecast error must be tracked and fed back into the next planning cycle
- Autoscaling policies must account for scale-up latency and quota limits

## Key Scale Questions
- What is the baseline QPS growth rate (e.g., 15% YoY)?
- What is the peak-to-average traffic ratio (e.g., 3x for fintech on tax day, 5x for retail on Black Friday)?
- How long does autoscaling take to provision a healthy new instance (30s-5min)?
- What happens to effective capacity when cache hit rate drops from 95% to 50%?

## Core Concepts

### The Five-Step Capacity Planning Loop
1. **Demand Forecast**: Model baseline growth + seasonality + event spikes. Output P50/P80/P95 scenarios, not a single point estimate.
2. **Service Envelope**: Translate QPS into CPU/memory/IO per request using profiling data. Build utilization-to-latency curves (the J-curve).
3. **Headroom Policy**: Set target utilization by tier -- critical at 50-60%, important at 65-75%, batch at 75-85%, experimental at 85-95%.
4. **Stress and Failure Tests**: Load test at 120% of provisioned capacity. Inject failures (cache down, DB slow, host kill). Validate SLO compliance.
5. **Review Cadence**: Update forecasts monthly/quarterly. Track forecast error and recalibrate assumptions.

### Demand Forecasting with Uncertainty Bands
- Point estimates fail because growth is non-linear, seasonality amplitude varies, and upstream coupling can multiply load.
- Use P50 (most likely), P80 (optimistic growth), P95 (pessimistic/viral) scenarios.
- Three sources of forecast error: growth trajectory non-linearity, seasonality amplitude surprises, and dependency coupling (e.g., client retry storms).
- Example: Netflix models baseline subscriber growth + time-of-day/week seasonality + content launch spikes. A flagship show can drive 10x regional traffic for 2-4 hours.

### Resource Translation (QPS to Resources)
- Profile each service: CPU time per request (mean, p95, p99), memory per connection, disk IOPS, network bandwidth, downstream query volume.
- The utilization-to-latency relationship is a J-curve: stable p99 up to ~60% CPU, then steep degradation above 80% due to queueing.
- Critical services target 50-60% utilization to stay on the flat part of the J-curve.
- Example: Uber dispatch service -- above 70% CPU, p99 latency degrades from 300ms to 1200ms due to lock contention and GC pauses. Headroom policy set to 60% target.

### Production Headroom Policy by Service Tier

| Tier | Target Utilization | Reserved Headroom | Reason | Example Services |
|------|-------------------|-------------------|--------|------------------|
| Critical online path | 50-60% | 40-50% | Absorb bursts and partial failures | API gateway, checkout, auth, payment |
| Important non-critical | 65-75% | 25-35% | Balanced cost and reliability | Feed generation, search, recommendations |
| Batch/offline | 75-85% | 15-25% | Tolerate queueing delay | Data pipelines, ML training, analytics |
| Best-effort/experimental | 85-95% | 5-15% | Low SLO, tolerate retry | Internal dashboards, dev/staging |

## Key Design Decisions

### Autoscaling Is Not a Substitute for Planning
- Autoscaling requires: minimum fleet size, scaling policy thresholds, and awareness of scale-up latency (30s-5min).
- Failure mode: traffic spike grows faster than scale-up latency, saturating existing fleet before new instances are healthy.
- Quota limits: cloud providers enforce account-level CPU/GPU/network limits; hitting a quota during a spike causes the same incident as under-provisioning.
- Hybrid approach: autoscaling + forecast-driven pre-scaling (e.g., Stripe pre-scales 3x for Black Friday with 40% minimum fleet at 50% utilization).

### Failure Scenario Modeling
- Dependency degradation: cache miss storm (10x effective capacity loss), slow DB queries, downstream saturation.
- Partial host failures: N-1 loss is non-linear because remaining hosts shift above the J-curve knee; rolling deployments take 20% offline at once.
- Correlated events: traffic burst coincides with cache migration; datacenter partition doubles load on remaining DC.
- Fix: model N-1/N-2 scenarios explicitly, assume cache hit rate drops during incidents, run chaos engineering tests.

### Advanced Techniques: Load Shaping and Graceful Degradation
- **Load shaping**: rate limiting by tier, request prioritization, admission control (503 when queues overflow), client backoff with jitter.
- **Graceful degradation**: feature shedding (disable personalization), simplified responses (partial results), read-only mode for write-heavy services.
- Example: Google Search uses tiered degradation -- drop freshness, disable personalization, shed expensive features (knowledge graph, image search) while keeping core search available.
- Economic argument: provisioning for 99.99% at P99 traffic costs ~3x more than 99.9% with graceful degradation.

## Common Capacity Planning Failures
1. Planning to averages instead of tails (p95/p99 bursts + failures)
2. Ignoring dependency bottlenecks (DB saturates before your service)
3. No failure scenario modeling (assumes all healthy, 95% cache hits)
4. One-time planning with no calibration (forecast drifts from reality)
5. Treating autoscaling as a substitute for planning (ignores latency and quotas)

## Follow-Up Variations
- How would you capacity plan for a stateful service (database) vs a stateless service?
- What changes when you move from on-premise to cloud with autoscaling?
- How do you handle capacity planning for a service with unpredictable viral traffic?
- How would you set headroom for a multi-tenant SaaS platform?
