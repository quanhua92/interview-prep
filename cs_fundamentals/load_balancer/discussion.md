# Load Balancer Design

Source: [Load Balancer (CalibreOS)](https://www.calibreos.com/learn/hld-load-balancer)

## One-Liner
Distribute incoming traffic across multiple backends using intelligent routing, health checks, and failover to achieve horizontal scaling, failure isolation, and policy-based traffic management.

## Functional Requirements
- Distribute HTTP/TCP/UDP traffic across N backend instances
- Health-check backends and auto-remove unhealthy ones from the pool
- Route based on policy: path-based, header-based, weighted, or affinity-based
- Drain connections during deployments for zero-downtime updates
- Support sticky sessions (session affinity) where required
- Terminate TLS at the LB for L7 routing

## Non-Functional Requirements
- Throughput: 100K-10M req/sec depending on L4 vs L7 choice
- Latency overhead: <1ms for L4, <5ms for L7 (including TLS termination)
- Availability: 99.99% (requires active-active LB pair, no SPOF at LB tier)
- Observability: per-backend error rate, connection count, queue depth
- Health check detection window must be shorter than client retry budget

## Key Scale Questions
- L4 handles 10M+ concurrent connections on commodity hardware (HAProxy)
- L7 handles ~100K req/sec/core (Nginx/Envoy) due to TLS + HTTP parsing overhead
- Health check failure window: interval x unhealthy_threshold (e.g., 10s x 3 = 30s of degraded traffic)
- Global failover: GeoDNS TTL 60-300s vs Anycast BGP reconvergence in seconds
- Thundering herd risk: round-robin sends full traffic share to a just-recovered backend

## Core Components
- **Listener**: `{protocol, port, default_target_group}` -- accepts incoming connections
- **Target Group**: `{backends[], health_check_config, routing_algorithm}` -- pool of healthy backends
- **Routing Rule**: `{priority, conditions: [path_pattern, header_match], target_group}` -- L7 routing logic
- **Health Checker**: independent threads per LB instance, maintaining real-time backend health state
- **Connection Drainer**: manages graceful backend removal during deploys
- **Control Plane**: LB configuration stored in etcd/ZooKeeper; data plane is stateless

## Key Design Decisions

### L4 vs L7
- **L4 (Transport Layer)**: Routes by source/destination IP + port. Never inspects HTTP payload or TLS. Extremely fast (10M+ connections). Use for: raw TCP/UDP throughput (gaming, streaming, large-file transfer). Examples: AWS NLB, HAProxy in TCP mode.
- **L7 (Application Layer)**: Terminates TLS, reads full HTTP request (headers, path, body). Enables path-based routing, canary deployments via headers, WebSocket upgrade, gRPC routing, request-level observability. Use for: HTTP/gRPC APIs needing routing flexibility. Examples: AWS ALB, Nginx, Envoy.
- **Rule of thumb**: L4 for raw throughput, L7 for anything HTTP/gRPC where routing flexibility or observability matters. Most internet-facing APIs use L7; internal service-to-service uses L4 or service mesh.

### Routing Algorithm Selection
- **Round Robin**: Sequential assignment. Zero state. Works for identical backends with uniform request cost. Fails when backends have different capacity or variable request duration.
- **Weighted Round Robin**: Adds weights for heterogeneous hardware and canary deployments (new version at 5% weight). Zero state but config lag on weight changes.
- **Least Connections**: Routes to backend with fewest active connections. Better for variable-length requests. Requires O(N) state per request. Degrades with very large pools (N > 1000).
- **Power of Two Choices (P2C)**: Randomly sample 2 backends, pick the one with fewer connections. Near-optimal load distribution with O(1) overhead. Avoids thundering herd. Best default for stateless APIs.
- **Consistent Hashing**: Hash request key (client IP, session ID) to a ring for affinity. Required for WebSocket/game servers and cache-warming. ~1/N keys remap on topology changes. Not for stateless APIs.

### Health Check Design
- **TCP connect (L4)**: Verifies port accepts connections. Does not detect app-level failures.
- **HTTP 200 (L7 shallow)**: GET `/health` returns 200. Fast but surface-level.
- **Readiness probe (L7 deep)**: `/ready` pings DB, cache, dependencies. Returns 200 only when backend can actually serve.
- **Detection window**: `interval x unhealthy_threshold`. With 10s interval and 3 strikes = 30s of traffic to a failing backend. Client retry budget must cover this window.

### Connection Draining for Zero-Downtime Deploys
- On backend removal: stop new requests immediately, wait `drain_timeout` (30-60s) for in-flight requests, then force-close.
- Without draining: deploys cause in-flight request failures (TCP RST), the most common source of deploy-time 502/503 errors.
- Tune drain timeout to p99 request duration + buffer.

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /health | LB health check endpoint (shallow) |
| GET | /ready | Backend readiness probe (deep, checks dependencies) |
| GET | /status | LB control plane status, backend pool membership |
| POST | /config/routing-rules | Update routing rules (path/header-based routing) |
| POST | /config/target-groups | Modify target group (add/remove backends) |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| listener_id | UUID | PK, listener config |
| protocol | ENUM | TCP, UDP, HTTP, HTTPS |
| port | INT | Listening port |
| target_group_id | UUID | FK to target group |
| backend_id | UUID | PK, backend instance |
| address | VARCHAR | IP:port of backend |
| weight | INT | Traffic weight (weighted round robin) |
| health_status | ENUM | HEALTHY, UNHEALTHY, DRAINING |
| active_connections | INT | Current connection count (for least-conn) |
| last_health_check | TIMESTAMP | Most recent health check time |

## Deep Dive Topics
- **Slow-fail backends**: Not dead but slow (high p99). Round-robin treats them equally. P2C naturally routes less traffic because slow backends accumulate connections. Or use health checks with latency thresholds (Envoy outlier detection).
- **LB tier SPOF**: Single LB = single point of failure. Active-active pair with Anycast VIP or floating IP (VRRP). Cloud providers run managed LBs across multiple AZs automatically.
- **Thundering herd on recovery**: Backend recovers, round-robin gives it full traffic share immediately, possibly crashing it. Use slow-start (gradual warm-up over 30-60s).
- **Sticky sessions**: Cookie-based (AWS ALB `AWSALB`, HAProxy `SERVERID`) or IP-hash. Creates uneven load and complicates deploys. Prefer stateless backends with session state in Redis; use sticky only for legacy apps or WebSocket.
- **Global load balancing**: GeoDNS (DNS-based, 60-300s failover due to TTL, misroutes via non-local resolvers) vs Anycast (BGP-based, seconds reconvergence, requires AS number and IP blocks). Cloudflare and Google Cloud LB use Anycast.
- **Active-Active vs Active-Passive regions**: Active-active for lower latency (requires read-correct data replication). Active-passive for write-heavy workloads where conflict resolution is expensive.

## Follow-Up Variations
- How would you load balance WebSocket connections that must maintain server-side state?
- What happens when a backend is slow (2000ms p99) but passes health checks?
- How do you implement canary deployments using only LB routing rules?
- How would you design global failover for a multi-region deployment without Anycast?
- What changes when moving from a single LB to a service mesh (Envoy/Linkerd)?
