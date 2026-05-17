# Design a Coding Platform — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What languages must be supported? (each needs its own runtime image and time multiplier)
  - [ ] Is this practice-only or does it include live contests? (different capacity/priority needs)
  - [ ] What are the execution limits? (memory, CPU time, wall-clock, process count)
  - [ ] Are test cases visible, hidden, or mixed? (affects API security and storage design)
  - [ ] Global or single-region? (affects CDN and worker distribution)
- [ ] List functional requirements (4-5 items):
  - [ ] Users submit code in multiple languages and get it executed against test cases
  - [ ] Untrusted code runs in a sandboxed environment without escaping to host
  - [ ] System returns one of six verdicts: ACCEPTED, WA, TLE, MLE, RE, CE
  - [ ] Users see real-time feedback on their submission status
  - [ ] Contest leaderboard ranks by problems solved then penalty time
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Judge latency: p50 ~3-5s at normal load; p99 ~30s during contest peaks
  - [ ] Throughput: ~200/sec practice peak; ~2,000/sec contest peak
  - [ ] Availability: 99.9% general; 99.99% contest infrastructure
  - [ ] Security: sandbox escape must not compromise host or neighbors
- [ ] State your scale estimates:
  - [ ] ~15M total users, ~100K concurrent during contests
  - [ ] ~2M submissions/day, ~30-200 test cases per problem
  - [ ] ~5KB per submission metadata, code in S3 (~100KB max)
  - [ ] Storage: ~3.6TB/year for submission metadata

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Submission API] -> [Kafka judge-queue] -> [Judge Workers] -> [Sandbox] -> [Verdict Writer] -> [Postgres + Redis pub/sub] -> [SSE Server] -> Client
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/submissions` — submit code (write, bursty during contests)
  - [ ] `GET /api/submissions/{id}/events` — SSE stream for verdict (long-lived connection)
  - [ ] `GET /api/problems/{id}` — fetch problem (read-heavy, cacheable)
  - [ ] `GET /api/contests/{id}/leaderboard` — leaderboard (read-heavy during contests)
- [ ] Note the write-heavy burst pattern during contests (unlike typical read-heavy web apps):
  - [ ] Contest opening spike: 100K users, ~2K submissions/sec for 30-60 min
  - [ ] Pre-scaling mandatory — K8s node provisioning takes 2-5 min
  - [ ] Priority lanes separate contest and practice traffic
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain sandbox isolation choice and justify:
  - [ ] Docker alone shares host kernel — insufficient (kernel exploits escape containers)
  - [ ] gVisor: user-space kernel intercepts syscalls, ~10ms startup, ~20% CPU overhead
  - [ ] Firecracker: KVM microVM, separate kernel, ~125ms startup, ~1-2% overhead
  - [ ] Pre-warmed Firecracker VMs: strongest isolation + amortized startup cost
  - [ ] Defense in depth: seccomp + cgroup + namespace + sandbox runtime + network block + isolated nodes
- [ ] Explain cgroup resource limits (all four):
  - [ ] `memory.max` (256MB) — OOM kill → MLE verdict
  - [ ] `cpu.max` (language-specific) — CPU budget exhaustion → TLE verdict
  - [ ] `pids.max = 1` — fork bomb prevention
  - [ ] Network namespace — no egress, ENETUNREACH on any network call
  - [ ] Wall-clock watchdog (CPU limit + 2s) catches sleep-based evasion
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/submissions` → `{"submission_id": "...", "status": "PENDING"}`
  - [ ] `GET /api/submissions/{id}/events` → SSE stream with verdict
  - [ ] `GET /api/problems/{id}` → `{"title": "...", "description": "...", "test_cases": [...]}`
  - [ ] `GET /api/contests/{id}/leaderboard?page=0` → `[{"rank": 1, "user": "...", "solved": 4, "penalty": 1800}]`
- [ ] Sketch the database schema:
  - [ ] Table `submissions`: `id UUID PK`, `user_id`, `problem_id`, `contest_id (nullable)`, `language`, `status`, `source_code_s3_key`, `runtime_ms`, `memory_kb`, `submitted_at`, `judged_at`
  - [ ] Table `user_problem_status`: `user_id`, `problem_id`, `best_status`, `attempt_count`, `last_submitted_at` (upserted on every verdict)
  - [ ] Indexes: `(user_id, problem_id, status)`, `(contest_id, user_id)`, `(problem_id, status)`
- [ ] Walk through the main flow end-to-end:
  - [ ] Submit: user submits code → API stores in S3, enqueues metadata to Kafka → returns submission_id
  - [ ] Judge: worker pulls from Kafka, fetches code from S3, compiles (if needed), runs test cases in sandbox, produces verdict
  - [ ] Feedback: worker writes verdict to Postgres, publishes to Redis pub/sub → SSE server pushes to client
  - [ ] Leaderboard: leaderboard service consumes results topic, updates Redis sorted set on ACCEPTED

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss judge queue design in detail:
  - [ ] Kafka partitioned by language — workers specialized, auto-scale independently
  - [ ] Two consumer groups per language: contest priority lane + normal lane
  - [ ] Source code in S3 (not in Kafka message) — keep messages ~1KB
  - [ ] Pre-scale contest workers 30 min before event; HPA on consumer lag for normal
- [ ] Explain leaderboard implementation:
  - [ ] Redis sorted set: score = `-(solved_count * 10^9 - penalty_seconds)` — two sort keys in one float
  - [ ] ZADD O(log N) per update; ZREVRANGE O(log N + K) for top-K
  - [ ] Snapshot to Postgres at contest close; 7-day TTL on Redis keys
  - [ ] CDN cache 5s on top-100; user's own rank bypasses CDN
- [ ] Discuss contest operational challenges:
  - [ ] Pre-scaling: scheduled K8s scale-up (node provisioning too slow for reactive scaling)
  - [ ] Fairness: server-side timestamp at queue entry, not judge completion
  - [ ] Rate limiting: Redis token bucket — 1 submission per problem per 10s during contests
  - [ ] Penalty time: 5 min per wrong submission (only if problem eventually accepted)
  - [ ] Queue depth signaling: show warning when lag > 30s to prevent re-submission floods
- [ ] Address failure modes:
  - [ ] Sandbox escape: defense in depth — network block + isolated nodes + syscall monitoring + daily rotation
  - [ ] Stuck PENDING submission: background scan for PENDING > 60s, re-enqueue once, then JUDGE_ERROR
  - [ ] Sleep-based infinite loop: wall-clock watchdog (external to cgroup) kills process
  - [ ] Memory bomb just under limit: cgroup triggers on RSS (resident set), not virtual memory
- [ ] Discuss language-specific concerns:
  - [ ] Time multipliers: Python 5x, Java 2x, JS 3x relative to C++ baseline
  - [ ] Compilation phase for C++/Java/Go/Rust (separate from execution)
  - [ ] Verdict precedence: CE → TLE → MLE → RE → WA → ACCEPTED

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why:
  - [ ] gVisor vs Firecracker tradeoff (startup latency vs CPU overhead vs isolation strength)
  - [ ] SSE vs WebSocket (unidirectional, one-shot result delivery — SSE is simpler)
  - [ ] Priority lanes vs single queue (contest isolation at cost of complexity)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
