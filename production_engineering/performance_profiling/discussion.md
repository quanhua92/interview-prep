# Performance Profiling & Optimization

Source: [Performance Profiling & Optimization: Python, JVM, Flame Graphs, and APM (CalibreOS)](https://www.calibreos.com/learn/prod-performance-profiling)

## One-Liner

Systematically identify and resolve production latency regressions by classifying the bottleneck, choosing the right profiler, reading flame graphs correctly, and correlating with distributed traces.

## Requirements

### The Problem

Production latency spikes are almost impossible to reproduce locally. Production has different concurrency levels, JIT compilation states, CPU cache warmth, OS scheduling contention, and real network round-trips to dependent services that are stubbed out locally.

The fundamental tension: the most accurate profilers (deterministic, like cProfile) add 10-40% overhead and cannot safely run on production traffic. The safest profilers (sampling, like py-spy) are statistically accurate but can miss short-lived hot paths. Understanding **which** profiler to use, **when**, and **for how long** is what separates engineers who can actually tune production systems from those who know the theory.

### What Interviewers Test

- **L4/Mid:** Can you name the tools (cProfile, py-spy, Datadog APM)? Can you distinguish CPU-bound from I/O-bound? Can you read a basic flame graph?
- **L5/Senior:** Do you know **why** py-spy over cProfile in production (overhead)? Can you design a profiling strategy that doesn't cause a second incident? Can you interpret a flame graph to find the actual hot path, not just the widest top-level block?
- **Staff:** Can you correlate per-service profiles with distributed traces? Do you know G1GC vs ZGC GC pause characteristics well enough to recommend a switch? Can you design an observability strategy with production visibility without overhead?

The most common senior-level miss: candidates describe what a flame graph looks like but cannot explain that the **x-axis is sample frequency, not elapsed time** -- this leads to completely wrong diagnoses.

## Key Concepts

### Production Profiling Triage: 5-Step Protocol

1. **Classify the bottleneck type** (5 min): Check CPU% under load. CPU >80% means CPU-bound (profile computation). CPU <20% but high latency means I/O-bound (profile DB queries, network calls, lock contention). Monotonic memory growth means memory leak (profile allocations). These require completely different tools -- profiling CPU on an I/O-bound service tells you nothing.

2. **Choose the right profiler** (2 min): For Python on live production: py-spy only (never cProfile). For JVM: JFR (zero overhead, built-in since JDK 11). For memory: tracemalloc (Python) or JFR heap profiling (JVM). For distributed: OpenTelemetry or Datadog APM. Rule: sampling profilers for production, deterministic profilers for dev/staging.

3. **Capture under realistic load** (5-15 min): Attach to live PID with py-spy or jcmd JFR. Profile during actual traffic, not synthetic benchmarks. Hot paths often only appear at production concurrency. Short profiles (<30s) miss periodic work like GC cycles and cache evictions.

4. **Read the flame graph top-down** (10 min): Bottom row is process entry point. Top of each stack is actual running code. X-axis = sample frequency (wider = more CPU). Look for widest blocks near the **top** of the stack within your code boundary -- that is the hotspot.

5. **Correlate with distributed trace for I/O cases** (10 min): If flame graph shows idle code (thin stacks, socket.recv), time is spent waiting. Open the distributed trace; look at span breakdown to see which downstream call is the culprit. Profile does not tell you this.

### Python Profiling: cProfile vs py-spy

- **cProfile** (deterministic): Instruments every function call at bytecode level. 100% accuracy, but 10-40% overhead. Use in dev/staging only. Sort by `cumtime` for cumulative time; `tottime` for time inside a function excluding callees. High `cumtime` + low `tottime` = passthrough (hotspot is in what it calls).

- **py-spy** (sampling): Polls Python interpreter stack at 100Hz from a separate process. Under 1% overhead. Attaches to live PID without restart. Limitation: at 100Hz, functions running <5ms may be statistically invisible. Use `--rate 1000` for tight loops (~3% overhead).

- **Key insight**: py-spy's biggest advantage is not low overhead -- it's visibility into C extensions. cProfile sees only the Python-to-C boundary as an opaque black box. py-spy sees the native stack, giving the full picture including NumPy or SQLAlchemy internals.

### Memory Leak Diagnosis (Python)

Common production leaks are **unbounded caches**, **global state accumulation**, and C extension memory mismanagement -- not circular references (GC handles those).

Diagnostic workflow:
1. Confirm leak vs. normal growth: sawtooth pattern (rises between GC, drops) = normal. Staircase pattern (rises, never drops) = leak. Use `process_resident_memory_bytes` in Prometheus.
2. Use `tracemalloc` with two snapshots: start, run N requests, snapshot A; run N more, snapshot B. Compare with `snapshot_b.compare_to(snapshot_a, "lineno")`. Lines with increasing allocations are leak sources.
3. Common culprits: module-level dict/list cache with no eviction, global event handlers accumulating closures, `functools.lru_cache(maxsize=None)` with unbounded arguments.

Note: `sys.getsizeof()` only counts shallow size. Use `pympler.asizeof()` or `tracemalloc` instead.

### JVM Profiling: JFR and async-profiler

- **JFR (JVM Flight Recorder)**: Built into HotSpot since JDK 11. <1% overhead. Records CPU samples, GC events, thread locking, I/O waits, class loading, heap allocation. Can start/stop on a running JVM via `jcmd <pid> JFR.start duration=60s filename=profile.jfr`. Open in JDK Mission Control.

- **async-profiler**: Solves JFR's **safepoint bias problem** -- most JVM profilers only sample at safepoints (where JVM pauses all threads). Code between safepoints is invisible. async-profiler uses `AsyncGetCallTrace` + Linux `perf_events` to sample anywhere, including inside JIT-compiled native code. Generates flame graphs: `./profiler.sh -d 60 -f profile.html <pid>`.

- **Production decision**: JFR for always-on monitoring (ring-buffer mode, dumps on OOM). async-profiler for targeted CPU profiling when you need native-level accuracy.

### G1GC vs ZGC

- **G1GC** (default since JDK 9): Generational, region-based. Pauses typically 10-200ms, configurable via `MaxGCPauseMillis`. Works well under 10GB heap. Beyond that, pause times grow unpredictably.

- **ZGC** (production-ready since JDK 15): Concurrent collector. Stop-the-world pauses <1ms at any heap size (tested at ~16TB). Cost: 15-20% more CPU, 5-10% lower throughput.

- **Decision rule**: Heap <10GB + latency SLO >50ms = G1GC. Heap >10GB OR latency SLO <10ms = ZGC. Diagnose GC issues by enabling GC logging (`-Xlog:gc*:file=/tmp/gc.log`) and looking for pause duration events.

### Flame Graphs

Invented by Brendan Gregg (Netflix, 2011). Encodes an entire profile in a single image.

- **Y-axis**: Call stack depth. Bottom = process entry point. Top = actual running code at sample moment.
- **X-axis**: Sample frequency, **not** elapsed time. Functions sorted alphabetically. Width = proportion of total CPU time.

Reading for hotspots:
1. Ignore bottom 3-5 rows (framework boilerplate).
2. Find widest block near the **top** of any stack = code consuming most CPU.
3. A **wide plateau** (no taller children) = hot path with no further delegation = optimization target.
4. Wide block with many equal-width children = work split across sub-functions, go deeper.
5. Ctrl+F to highlight your service module.

Key nuance: a wide block in the **middle** of a stack may be a hot **caller**, not a hot function. The caller is expensive because of what it calls, not its own instructions.

### APM and Distributed Tracing

Critical insight: in a typical microservices architecture, **80% of end-user-perceived latency is in the network, serialization, and downstream service calls** -- not in the computation of the service being profiled. Profiling the Python computation of a service that makes 5 synchronous HTTP calls at ~100ms P99 each tells you nothing about the actual 520ms problem.

**OpenTelemetry (OTel)**: CNCF standard. Data model: a **trace** = complete record of a request (DAG of spans). A **span** = single unit of work (service handling, DB query, HTTP call) with start time, duration, status, attributes. **Context propagation** passes trace/span IDs between services via `traceparent` HTTP header (W3C format).

**Datadog APM**: Builds on OTel-compatible traces. Adds service maps with P50/P99 latency on each edge, error rate heatmaps, and smart sampling (100% of slow traces, downsample fast ones).

## Key Decisions

### Profiler Selection Matrix

| Scenario | Tool | Why |
|----------|------|-----|
| Python production CPU profiling | py-spy | <1% overhead, attaches to live PID |
| Python dev/staging profiling | cProfile | 100% deterministic accuracy |
| Python memory leak | tracemalloc | Shows allocation sources with line-level detail |
| JVM always-on monitoring | JFR | <1% overhead, ring-buffer mode |
| JVM targeted CPU profiling | async-profiler | No safepoint bias, sees JIT-compiled code |
| Cross-service latency | OpenTelemetry + Datadog APM | Distributed traces with span breakdown |

### Bottleneck Diagnosis Matrix

| Symptom | Type | Tool | Likely Root Cause |
|---------|------|------|-------------------|
| CPU pegged at 100% | CPU-bound | py-spy / async-profiler | Inefficient algorithm, regex abuse, unvectorized loops |
| CPU low, high latency | I/O-bound | Distributed trace | N+1 queries, sequential HTTP calls, slow DNS |
| Memory grows monotonically | Memory leak | tracemalloc / JFR heap | Unbounded cache, global state, C extension mismanagement |
| Regular latency spikes (30-120s), JVM | GC pressure | JFR GC events | Long G1GC pauses on large heap |
| Spikes correlate with deploys | Hot path regression | Flame graph diff | New code in hot path, disabled caching |
| High latency for specific requests | Downstream dependency | Distributed trace per-operation | Specific slow DB query, external API, cache miss pattern |

## Deep Dives

### Profiling Failure Modes That Cause Incidents

- **Running cProfile in production**: At ~70% CPU, cProfile adds 15-30% overhead, pushing service into saturation. Latency can jump from 200ms to 2000ms. Never use cProfile on live traffic.
- **Profiling the wrong process**: Gunicorn/uWSGI masters are not workers. `py-spy --pid <master>` misses request-serving workers. Confirm with `/proc/<pid>/cmdline` or use `--subprocesses`.
- **Treating flame graph x-axis as time**: Width is sample share, not chronology. Sort order is alphabetical, not call order.
- **Profiling at toy concurrency**: 10 connections can hide severe GIL contention that appears at 100+. Match production concurrency.
- **Broken trace propagation**: If any hop drops `traceparent`, traces fragment and wall-clock debugging lies. Validate OpenTelemetry propagation end-to-end.

### Interview Answer Structure (The Senior Signal)

1. **Classify before you profile**: "First I'd check CPU% under load. If high, CPU-bound, reach for py-spy. If low but latency is high, I/O-bound, go straight to the distributed trace."
2. **Name the right tool with the right reason**: "py-spy over cProfile because py-spy has <1% overhead and can attach to a live PID. cProfile adds 10-40% overhead -- in production that can cause a second incident."
3. **Demonstrate flame graph reading**: "Looking for the widest plateau near the top of the stack. X-axis is sample frequency, not time."
4. **Connect to the distributed system**: "If the flame graph shows idle code with lots of socket.recv, latency is downstream. Pull up the APM service map for P99 contribution per edge."
5. **Quantify expected improvement**: "Baseline P99 before profiling, set a target, measure after each change. Optimization without measurement is guessing."

## Follow-Ups

- How would you profile a latency issue that only manifests at P99 but not at P50?
- A JVM service has regular 500ms pauses every 60 seconds -- walk through GC diagnosis.
- How do you profile a Python service that uses async/await (asyncio) -- does py-spy handle this correctly?
- How would you set up always-on profiling that doesn't impact production performance?
- What happens when a distributed trace is incomplete (missing spans) -- how do you debug the gaps?
- How do you differentiate between a genuine memory leak and legitimate cache warm-up in a service that just started?
