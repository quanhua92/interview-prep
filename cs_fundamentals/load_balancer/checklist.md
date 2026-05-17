# Load Balancer Design — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Are we routing HTTP/HTTPS (L7) or raw TCP/UDP (L4)?
  - [ ] What is the expected throughput (100K vs 10M req/sec)?
  - [ ] Do backends have state (WebSocket, game servers) or are they stateless APIs?
  - [ ] Is this single-region or multi-region (global load balancing)?
  - [ ] What is the availability target (99.9% vs 99.99%)?
- [ ] List functional requirements (3-5 items):
  - [ ] Distribute traffic across N backend instances
  - [ ] Health-check backends and auto-remove unhealthy ones
  - [ ] Route based on policy (path, headers, weights)
  - [ ] Drain connections during deployments
  - [ ] Support sticky sessions where needed
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: <1ms overhead for L4, <5ms for L7 including TLS
  - [ ] High availability: 99.99% (active-active LB pair)
  - [ ] Throughput: 100K-10M req/sec depending on layer
  - [ ] Observability: per-backend error rates, connection counts
- [ ] State your scale estimates:
  - [ ] L4: 10M+ concurrent connections on commodity hardware
  - [ ] L7: ~100K req/sec/core (TLS + HTTP parsing overhead)
  - [ ] Health check detection window: interval x unhealthy_threshold (e.g., 30s)
  - [ ] Backend pool size: typically 5-100 instances per target group

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB (L4/L7) -> [Backend Pool] -> [DB/Cache]
- [ ] Identify the main operations and their access patterns:
  - [ ] Client -> LB -> Backend: request routing (read, highest QPS)
  - [ ] LB -> Backend: health check probes (periodic, independent per LB)
  - [ ] Deploy -> LB: remove/add backend from pool (infrequent, config change)
  - [ ] LB -> LB: active-active failover (continuous health monitoring)
- [ ] Note the L4 vs L7 trade-off and where each fits:
  - [ ] L4 for raw throughput, no HTTP awareness, microsecond latency
  - [ ] L7 for path/header routing, TLS termination, canary deployments, observability
  - [ ] Most internet-facing APIs: L7. Internal service-to-service: L4 or service mesh.
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain L4 vs L7 choice and justify:
  - [ ] L4 (Transport): routes by IP+port, never inspects payload, 10M+ connections, use for TCP/UDP
  - [ ] L7 (Application): terminates TLS, reads HTTP, enables path/header routing, ~100K req/sec/core
  - [ ] State your choice based on traffic type (HTTP API = L7, raw TCP = L4)
- [ ] Select routing algorithm and justify:
  - [ ] Round Robin: identical backends, uniform cost -- zero state
  - [ ] Weighted Round Robin: canary deploys, heterogeneous hardware -- zero state
  - [ ] Least Connections: variable-duration requests -- O(N) per request
  - [ ] P2C (Power of Two Choices): best default for stateless APIs -- O(1), avoids thundering herd
  - [ ] Consistent Hashing: stateful backends (WebSocket, caches) -- O(log N) ring lookup
- [ ] Define health check strategy:
  - [ ] TCP connect (L4): port open check, baseline only
  - [ ] HTTP 200 (L7 shallow): GET /health, fast but surface-level
  - [ ] Readiness probe (L7 deep): GET /ready with DB/cache ping, production-ready
  - [ ] Config: interval=10s, unhealthy_threshold=3, healthy_threshold=2, timeout=5s
- [ ] Sketch the core entities:
  - [ ] Listener: `{protocol, port, default_target_group}`
  - [ ] Target Group: `{backends[], health_check_config, routing_algorithm}`
  - [ ] Routing Rule: `{priority, conditions, target_group}`
  - [ ] Health Check Config: `{path, interval_sec, healthy_threshold, unhealthy_threshold, timeout_sec}`
- [ ] Walk through the main flow end-to-end:
  - [ ] Request flow: client -> LB listener -> routing algorithm selects backend -> forward request -> return response
  - [ ] Health check flow: LB health threads periodically probe backends -> update health state -> remove/add from pool
  - [ ] Deploy flow: mark backend as DRAINING -> stop new requests -> wait drain_timeout -> force close -> remove from pool

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss connection draining for zero-downtime deploys:
  - [ ] Stop new requests immediately on backend removal
  - [ ] Wait drain_timeout (30-60s) for in-flight requests to complete
  - [ ] Force-close remaining connections after timeout
  - [ ] Without draining: in-flight requests fail with TCP RST (deploy-time 502/503)
  - [ ] Tune drain timeout to p99 request duration + buffer
- [ ] Explain scaling and HA of the LB tier itself:
  - [ ] LB is a SPOF unless designed for HA: active-active pair with Anycast VIP or VRRP floating IP
  - [ ] Control plane config in etcd/ZooKeeper; data plane is stateless
  - [ ] Cloud-managed LBs (AWS ALB/NLB) run across multiple AZs automatically
  - [ ] Health state is local to each LB instance -- no shared state for routing
- [ ] Address slow-fail backends:
  - [ ] Backend slow (high p99) but not dead: passes TCP health checks
  - [ ] Round-robin sends equal traffic to slow backend
  - [ ] Fix: P2C naturally reduces traffic to slow backends (they accumulate connections)
  - [ ] Fix: latency-threshold health checks (Envoy outlier detection)
- [ ] Handle thundering herd on backend recovery:
  - [ ] Recovered backend gets full traffic share immediately with round-robin
  - [ ] Use slow-start: gradual traffic warm-up over 30-60s (Nginx upstream, AWS ALB)
- [ ] Discuss sticky sessions trade-offs:
  - [ ] Cookie-based (AWSALB, SERVERID) or IP-hash
  - [ ] Uneven load distribution, complicates deploys (draining strands sessions)
  - [ ] Prefer stateless backends with session in Redis; sticky only for WebSocket/legacy
- [ ] Cover global load balancing:
  - [ ] GeoDNS: DNS returns different A records by client resolver location. Failover 60-300s (TTL). Misroutes via non-local resolvers (8.8.8.8).
  - [ ] Anycast: same IP advertised from multiple PoPs via BGP. Failover in seconds. Requires AS number and IP blocks. Used by Cloudflare, Google Cloud LB.
  - [ ] Active-Active regions: lower latency, requires data replication. Active-Passive: simpler failover, higher latency on failover.

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made (L4 vs L7, algorithm choice, health check timing)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
