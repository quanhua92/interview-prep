# Design a Coding Platform

Source: [Coding Platform (CalibreOS)](https://www.calibreos.com/learn/hld-coding-platform)

## One-Liner
Design an online judge platform (LeetCode / HackerRank) that safely executes arbitrary untrusted user code against test cases, returns verdicts in seconds, and supports live contest leaderboards at scale.

## Functional Requirements
- Submit code in 20+ languages; compile and execute against test cases
- Secure sandbox isolation — untrusted code must not escape or access the host
- Return verdicts: ACCEPTED, WRONG_ANSWER, TLE, MLE, RE (runtime error), CE (compile error)
- Real-time submission status feedback to the client
- Contest leaderboard ranked by problems solved then penalty time
- Problem management — descriptions, visible/hidden test cases, editorials

## Non-Functional Requirements
- Practice throughput: ~200 submissions/sec peak; Contest peak: ~2,000/sec
- End-to-end judge latency p50: ~3-5s at normal load; p99: ~30s during contest peaks
- Availability: 99.9% uptime; contest infrastructure 99.99%
- Storage: ~5KB/submission x 2M/day ≈ 3.6TB/year
- Sandbox startup: gVisor ~10ms, Firecracker ~125ms

## Key Scale Questions
- ~15M users (LeetCode-scale), ~100K concurrent during weekly contests
- 2K submissions/sec contest spike lasting 30-60 minutes
- 30-200 test cases per problem, each requiring a separate sandbox execution
- Read:write ratio heavily write-skewed during contests (unlike typical web apps)
- Source code stored in S3 (~100KB max per submission), not in queue messages

## Core Components
- **Submission API**: receives code, stores in S3, enqueues to judge queue
- **Judge Queue (Kafka)**: partitioned by language, priority lanes for contest vs practice
- **Judge Workers**: pull submissions, execute in sandbox, produce verdicts
- **Sandbox Runtime (gVisor / Firecracker)**: isolated code execution with cgroup limits
- **Verdict Writer**: writes results to Postgres, publishes to Redis pub/sub
- **SSE Server**: streams real-time verdicts to clients via Server-Sent Events
- **Leaderboard Service**: updates Redis sorted sets on accepted submissions
- **Problem Service**: CMS for problem content, test case storage in S3

## Key Design Decisions

### Sandbox Isolation
- Docker alone is insufficient — it shares the host kernel; kernel exploits can escape containers
- **gVisor**: user-space kernel (Sentry) intercepts ~200 syscalls; ~10ms startup, ~20% CPU overhead. Good for practice where fast startup matters
- **Firecracker**: lightweight KVM microVM with separate kernel per execution; ~125ms startup, ~1-2% overhead. Strongest isolation, used by Codeforces and AWS Lambda
- **Pre-warmed Firecracker VMs**: keep a pool of ready VMs to amortize startup cost — gives ~10ms effective startup with strongest isolation
- Defense in depth: seccomp-BPF syscall filtering + cgroup limits + network namespace (no egress) + dedicated isolated worker nodes

### cgroup Resource Limits (mandatory even with sandbox)
- **memory.max** (256MB): kernel OOM killer fires on breach → MLE verdict
- **cpu.max** (language-specific): e.g., `2000000 500000` for 2s CPU per 500ms period → TLE verdict
- **pids.max = 1**: prevents fork bombs
- **Wall-clock watchdog**: external timeout (CPU limit + 2s) catches sleep-based evasion
- **Network namespace**: no routes configured, any network call gets ENETUNREACH

### Judge Queue Design
- Kafka topic `judge-queue` partitioned by language (Python, C++, Java, JS, Go, etc.)
- Workers are specialized per language — only load the relevant runtime image
- Two consumer groups per language: `judge-contest-{lang}` (pre-scaled, reserved capacity) and `judge-normal-{lang}` (standard pool)
- Source code stored in S3; Kafka message only carries metadata (~1KB)
- K8s HPA on consumer lag; pre-scale 30 min before known contests (node provisioning takes 2-5 min)

### Real-Time Feedback
- SSE + Redis pub/sub (not polling, not WebSockets)
- Client opens SSE connection → server subscribes to Redis channel `submission:{id}` → judge publishes verdict → SSE server pushes to client
- Eliminates 50K Postgres reads/sec at peak; SSE is unidirectional and one-shot (perfect for this pattern)
- ~10K concurrent SSE connections per server pod; 5-10 pod fleet for peak load

### Leaderboard Scoring Trick
- Redis sorted set with score = `-(solved_count * 10^9 - penalty_seconds)`
- Negation lets ZREVRANGE return descending by solved count; within same count, lower penalty ranks higher
- ZADD: O(log N) per update; ZREVRANGE: O(log N + K) for top-K read
- 2K writes/sec at peak contest; frontend polls every 30s; CDN cache 5s TTL on top-100 page
- Snapshot final rankings to Postgres at contest close; Redis key gets 7-day TTL

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/submissions | Submit code (returns submission_id) |
| GET | /api/submissions/{id}/events | SSE stream for real-time verdict |
| GET | /api/submissions/{id} | Get submission result |
| GET | /api/problems | List problems (paginated) |
| GET | /api/problems/{id} | Get problem description + visible test cases |
| GET | /api/contests/{id}/leaderboard | Contest leaderboard (Redis-backed) |
| POST | /api/contests/{id}/submit | Contest submission (rate-limited) |

## Database Schema
### submissions (Postgres, append-only)
| Column | Type | Notes |
|--------|------|-------|
| id | UUID | PK |
| user_id | BIGINT | NOT NULL |
| problem_id | BIGINT | NOT NULL |
| contest_id | BIGINT | NULL for practice |
| language | VARCHAR(20) | python3, cpp17, java21, etc. |
| status | VARCHAR(20) | PENDING / ACCEPTED / WA / TLE / MLE / RE / CE |
| source_code_s3_key | TEXT | Code stored in S3 |
| runtime_ms | INT | Execution time |
| memory_kb | INT | Peak memory |
| submitted_at | TIMESTAMPTZ | Server receipt time (for fairness) |
| judged_at | TIMESTAMPTZ | Verdict time |

Indexes: `(user_id, problem_id, status)`, `(contest_id, user_id)`, `(problem_id, status)`

### user_problem_status (materialized view)
| Column | Type | Notes |
|--------|------|-------|
| user_id | BIGINT | PK (composite) |
| problem_id | BIGINT | PK (composite) |
| best_status | VARCHAR(20) | ACCEPTED if ever accepted |
| attempt_count | INT | Total attempts |
| last_submitted_at | TIMESTAMPTZ | Last activity |

Updated via `ON CONFLICT DO UPDATE` upsert on every verdict — O(1) per problem per user.

## Deep Dive Topics
- Sandbox escape defense in depth: network block + isolated worker nodes + syscall monitoring + daily node rotation
- Stuck submission recovery: background job scans PENDING > 60s, re-enqueue once, then mark JUDGE_ERROR
- Language-specific time multipliers: Python ~5x, Java ~2x, JS ~3x relative to C++ baseline
- Contest pre-scaling: scheduled K8s scale-up 30 min before contest; 200 replicas for Python contest pool
- Server-side timestamping for fairness: scored at queue entry time, not judge completion time
- Rate limiting during contests: Redis token bucket `SET contest:{id}:ratelimit:{uid}:{pid} 1 EX 10 NX` → HTTP 429 if exists
- Penalty time: 5 min per wrong submission on a problem (only counted if eventually accepted)
- Test case storage: ~100KB each in S3, not Postgres; worker-side local disk caching

## Follow-Up Variations
- How would you support collaborative coding (real-time multi-user editor) on this platform?
- What if you need to judge not just correctness but code style and complexity (AI-assisted review)?
- How would you handle a user who submits a program that tries to mine cryptocurrency?
- Design the system to support "virtual contests" where users replay past contests asynchronously.
- How would you implement problem recommendations and skill tracking across attempts?
