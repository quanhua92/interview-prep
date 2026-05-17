# Capacity Planning for Production Systems — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What service tier is this (critical, important, batch)?
  - [ ] What is the traffic pattern: steady-state, seasonal, or bursty?
  - [ ] Are there known upcoming events (product launches, marketing campaigns)?
  - [ ] What dependencies does the service rely on (cache, DB, downstream services)?
- [ ] List functional requirements (3-5 items):
  - [ ] Forecast traffic demand with uncertainty bands (P50/P80/P95)
  - [ ] Translate QPS into resource requirements (CPU, memory, IO, network)
  - [ ] Define headroom policy by service tier
  - [ ] Validate through load and failure testing
  - [ ] Establish a recalibration cadence
- [ ] List non-functional requirements (latency, availability, cost):
  - [ ] SLO compliance under N-1 or N-2 failures
  - [ ] Headroom absorbs burst + dependency degradation + host loss simultaneously
  - [ ] Forecast error tracked and fed back into next cycle
  - [ ] Autoscaling accounts for scale-up latency and quota limits
- [ ] State your scale estimates:
  - [ ] Baseline QPS and growth rate (e.g., 10K QPS, 15% YoY growth)
  - [ ] Peak-to-average ratio (e.g., 3x seasonal, 5x event spikes)
  - [ ] Autoscaling provision time (e.g., 30s-5min per instance)
  - [ ] Dependency capacity limits (e.g., DB max 5K QPS, cache hit rate 95%)

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw the capacity planning loop: Forecast -> Translate -> Headroom Policy -> Stress Test -> Review -> (back to Forecast)
- [ ] Identify the main inputs and outputs:
  - [ ] Input: historical traffic data, growth projections, event calendar, service profiles
  - [ ] Output: per-service resource requirements with uncertainty bands, headroom targets
- [ ] Note the key relationships:
  - [ ] Traffic (QPS) maps to resources via service profiling (CPU/request, memory/connection)
  - [ ] Utilization maps to latency via the J-curve (stable below 60%, spikes above 80%)
  - [ ] Headroom must cover: traffic bursts + dependency degradation + host failures
- [ ] Present the loop and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain demand forecasting approach:
  - [ ] Three layers: baseline growth + seasonality + event spikes
  - [ ] Output P50/P80/P95 scenarios, not point estimates
  - [ ] Three sources of error: growth non-linearity, seasonality amplitude, dependency coupling
- [ ] Define resource translation:
  - [ ] Profile: CPU time per request (mean, p95, p99), memory per connection, disk IOPS, network BW
  - [ ] Build utilization-to-latency J-curve for each critical service
  - [ ] Note non-linearity: 60% to 80% CPU can mean 10ms to 200ms p99 latency jump
- [ ] Set headroom policy by tier:
  - [ ] Critical online path: 50-60% target, 40-50% headroom (API gateway, checkout, auth)
  - [ ] Important non-critical: 65-75% target, 25-35% headroom (feed, search, recommendations)
  - [ ] Batch/offline: 75-85% target, 15-25% headroom (pipelines, ML training, analytics)
  - [ ] Best-effort: 85-95% target, 5-15% headroom (dashboards, dev/staging)
- [ ] Walk through the main flow end-to-end:
  - [ ] Collect historical traffic data -> model three layers -> generate P50/P80/P95 forecast
  - [ ] Profile service resource usage per request -> translate forecast QPS to CPU/memory/IO
  - [ ] Apply headroom policy by tier -> derive provisioned capacity with headroom
  - [ ] Load test at 120% + inject failures -> validate SLO compliance -> recalibrate

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss failure scenario modeling:
  - [ ] Cache miss storm: 95% hit rate drops to 50%, effective capacity drops 10x
  - [ ] Slow DB: query latency from 10ms to 200ms, service capacity drops 10x
  - [ ] N-1 host failure in 10-host fleet: naive 10% loss, actual 40-50% due to J-curve
  - [ ] Rolling deployment: 20% offline, remaining 80% at 87.5% if baseline was 70%
  - [ ] Correlated events: traffic burst + cache migration or DC partition
- [ ] Explain autoscaling integration:
  - [ ] Autoscaling does not eliminate planning; minimum fleet must handle baseline + short bursts
  - [ ] Scale-up latency gap: fleet saturates before new instances are healthy
  - [ ] Quota limits: cloud provider account limits can block scale-up during spikes
  - [ ] Hybrid approach: forecast-driven pre-scaling + autoscaling for elasticity
- [ ] Address advanced techniques:
  - [ ] Load shaping: rate limiting by tier, request prioritization, admission control, client backoff
  - [ ] Graceful degradation: feature shedding, simplified responses, read-only mode
  - [ ] Economic tradeoff: 99.99% at P99 costs ~3x vs 99.9% with graceful degradation
- [ ] Discuss common failures to avoid:
  - [ ] Planning to averages (incidents happen at tails)
  - [ ] Ignoring dependency bottlenecks (DB saturates first)
  - [ ] No failure scenario modeling (assumes all healthy)
  - [ ] One-time planning with no recalibration (forecast drifts)
  - [ ] Treating autoscaling as a planning substitute (ignores latency and quotas)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the approach in 2-3 sentences
- [ ] State the trade-offs you made and why (cost vs reliability, P80 vs P95 provisioning)
- [ ] Mention what you would improve with more time (automated profiling, chaos engineering pipeline)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
