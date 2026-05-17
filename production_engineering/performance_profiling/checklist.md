# Performance Profiling & Optimization -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is this a latency regression, throughput issue, or memory problem?
  - [ ] What runtime is the service (Python, JVM, other)?
  - [ ] Is this a single-service issue or does it span multiple services?
  - [ ] What are the latency SLOs (P50, P99)?
- [ ] Identify the bottleneck class before touching any profiler:
  - [ ] CPU >80% under load = CPU-bound (profile computation)
  - [ ] CPU <20% but high latency = I/O-bound (profile DB/network/locks)
  - [ ] Memory growing monotonically = memory leak (profile allocations)
  - [ ] Regular spikes in JVM service = GC pressure (check GC logs)
- [ ] State why classification matters: "Profiling CPU on an I/O-bound service tells you nothing"

## Phase 2: Tool Selection (2-3 min)
- [ ] Select the right profiler for the runtime and environment:
  - [ ] Python production: py-spy (<1% overhead, attaches to live PID)
  - [ ] Python dev/staging: cProfile (100% accuracy, 10-40% overhead)
  - [ ] Python memory: tracemalloc (allocation source tracking)
  - [ ] JVM always-on: JFR (<1% overhead, built-in since JDK 11)
  - [ ] JVM targeted CPU: async-profiler (no safepoint bias, sees JIT code)
  - [ ] Cross-service: OpenTelemetry + Datadog APM (distributed traces)
- [ ] Explain why NOT the wrong tool:
  - [ ] Never cProfile in production (overhead can cause second incident)
  - [ ] JFR misses code between safepoints (use async-profiler instead)
  - [ ] py-spy at 100Hz may miss functions running <5ms (use --rate 1000)
- [ ] State the production profiling rule: sampling profilers for production, deterministic for dev/staging
- [ ] Get alignment on the approach before proceeding

## Phase 3: Capture and Analysis (3-5 min)
- [ ] Explain how to capture a profile under realistic load:
  - [ ] py-spy: `py-spy record -o profile.svg --pid 12345 --duration 60`
  - [ ] JFR: `jcmd <pid> JFR.start duration=60s filename=profile.jfr`
  - [ ] Profile during actual traffic, not synthetic benchmarks
  - [ ] Duration >30s to catch GC cycles and periodic work
  - [ ] Confirm profiling the right process (workers, not master)
- [ ] Explain flame graph reading:
  - [ ] Y-axis = call stack depth (bottom = entry, top = running code)
  - [ ] X-axis = sample frequency, NOT elapsed time (alphabetical sort)
  - [ ] Width = proportion of total CPU time
  - [ ] Ignore bottom 3-5 rows (framework boilerplate)
  - [ ] Find widest plateau near the top of the stack = hotspot
  - [ ] Ctrl+F to highlight your service code
- [ ] For I/O-bound cases, explain distributed trace correlation:
  - [ ] If flame graph shows idle (socket.recv, futex), latency is downstream
  - [ ] Open trace in Datadog/Jaeger
  - [ ] Look at span breakdown: your service vs downstream services
  - [ ] Identify which downstream call has highest P99 contribution
- [ ] Present your diagnosis of the bottleneck

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss GC tuning for JVM services (if relevant):
  - [ ] G1GC: default, pauses 10-200ms, best under 10GB heap
  - [ ] ZGC: concurrent, pauses <1ms at any heap size, 15-20% more CPU
  - [ ] Decision rule: <10GB heap + >50ms SLO = G1GC; >10GB or <10ms SLO = ZGC
  - [ ] Diagnose: `-Xlog:gc*:file=/tmp/gc.log` for pause duration events
- [ ] Explain memory leak diagnosis workflow:
  - [ ] Sawtooth memory pattern = normal GC; staircase = leak
  - [ ] tracemalloc two-snapshot technique (snapshot A, run requests, snapshot B, compare)
  - [ ] Common culprits: unbounded caches, global state, lru_cache(maxsize=None)
  - [ ] `sys.getsizeof()` is shallow; use `pympler.asizeof()` or tracemalloc
- [ ] Address profiling safety:
  - [ ] cProfile overhead can tip 70% CPU service into saturation
  - [ ] Profile wrong process (master vs worker) wastes time
  - [ ] Toy concurrency hides GIL contention
  - [ ] Broken trace propagation fragments traces
- [ ] Discuss the 80% rule: most latency is network/serialization/downstream, not computation
- [ ] Explain py-spy's key advantage: visibility into C extensions (NumPy, SQLAlchemy internals)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the diagnosis in 2-3 sentences
- [ ] State the fix direction and expected improvement
- [ ] Explain how you'd verify the fix (baseline P99, measure after each change)
- [ ] Mention what you would improve with more time (always-on profiling, automated flame graph diffing, etc.)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
