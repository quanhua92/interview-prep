# Design an AI Agent Platform — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements Gathering (3-5 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What types of agents will the platform host (single-agent, multi-agent, or both)?
  - [ ] What is the expected scale: number of tenants, concurrent users, agents per tenant?
  - [ ] What is the latency budget: real-time (interactive) or batch (async workflows)?
  - [ ] What LLM providers must be supported (OpenAI, Anthropic, open-source self-hosted)?
  - [ ] Is code execution required inside agent workflows (sandboxing needed)?
  - [ ] What are the security requirements: multi-tenant data isolation, tool access control?
- [ ] List functional requirements (3-5 items):
  - [ ] Register, configure, and deploy multiple AI agents
  - [ ] Orchestrate agent workflows (sequential, concurrent, handoff, etc.)
  - [ ] Provide a tool registry with discovery, validation, and permission policies
  - [ ] Execute untrusted code in isolated sandboxes
  - [ ] Track cost per agent, per tenant, per workflow
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] End-to-end latency under SLA (e.g., p95 <5s for interactive agents)
  - [ ] Fault tolerance with checkpointing and state recovery
  - [ ] Multi-tenant isolation with per-tenant rate limits and budgets
  - [ ] Observability with OpenTelemetry traces, metrics, and logs
- [ ] State your scale estimates (agents, QPS, storage):
  - [ ] ~100 tenants, ~10 agents each, ~1000 concurrent agent sessions
  - [ ] ~500 agent invocations/sec at peak
  - [ ] LLM calls: ~5-15 per agent workflow, mix of model tiers

## Phase 2: High-Level Architecture (5-8 min)
- [ ] Draw a simple box diagram: Client -> API Gateway -> Orchestrator (Pattern Router) -> [Agent A, Agent B, Agent C] -> Tool Registry -> Sandbox Manager -> [State/Checkpoints (Postgres), Cache/Queue (Redis), Object Storage] -> OTel Collector -> [Prometheus, Jaeger, Grafana]
- [ ] Identify the main components and their responsibilities:
  - [ ] API Gateway: auth, rate limiting, request routing
  - [ ] Orchestrator: pattern selection, agent coordination, workflow execution
  - [ ] Agent Runtime: LLM calls, tool invocation, state management
  - [ ] Tool Registry: discovery, schema validation, permission policies
  - [ ] Sandbox Manager: container/microVM lifecycle for code execution
  - [ ] State Management: checkpointing, persistence, cross-thread memory
  - [ ] Observability: OTel instrumentation, dashboards, alerting
  - [ ] Cost Metering: token tracking, per-tenant billing, budget enforcement
- [ ] Define the main API operations and access patterns:
  - [ ] `POST /api/agents` — register/configure an agent (write, low frequency)
  - [ ] `POST /api/workflows` — submit a workflow invocation (read-write, latency-sensitive)
  - [ ] `POST /api/tools` — register a tool in the registry (write, low frequency)
  - [ ] `GET /api/workflows/{id}/stream` — stream agent output (SSE, high QPS)
- [ ] Present the diagram and get alignment

## Phase 3: Deep Dive on Key Components (10-15 min)
- [ ] Explain orchestration pattern selection and justify:
  - [ ] Sequential: pipeline workflows with linear dependencies
  - [ ] Concurrent (fan-out/fan-in): independent analysis, latency-sensitive
  - [ ] Handoff: dynamic routing to emerging specialist
  - [ ] Group Chat: consensus-building, maker-checker validation
  - [ ] ReAct: single-agent iterative reasoning with tools
  - [ ] Magentic/Hierarchical: open-ended, multi-level task decomposition
  - [ ] State your default choice and when you would use alternatives
- [ ] Explain state management and checkpointing:
  - [ ] Super-steps: checkpoints at each graph tick boundary
  - [ ] Pending writes: only failed nodes re-execute on resume
  - [ ] Thread-scoped vs. cross-thread (Store) persistence
  - [ ] Durability modes (sync, async, exit) and trade-offs
  - [ ] DeltaChannel optimization for large accumulated state
  - [ ] AES encryption for sensitive checkpoint data
- [ ] Explain sandboxing strategy and justify:
  - [ ] Threat level assessment: low (containers) vs. medium/high (microVMs)
  - [ ] Docker: shared kernel, ~500ms startup, sufficient for internal tools
  - [ ] Firecracker/E2B: independent kernel, pre-warmed pools, ~150ms
  - [ ] ZeroBoot: CoW KVM fork, 0.79ms startup, 265KB memory (cutting-edge)
  - [ ] Wasm: language-level sandbox, JS/TS only, minimal overhead
  - [ ] Network isolation, resource limits, audit logging
- [ ] Discuss tool registry and MCP:
  - [ ] JSON Schema validation for all tool inputs/outputs
  - [ ] Permission policies: agent-level, tenant-level, user-level, parameter-level
  - [ ] MCP architecture: Hosts, Clients, Servers
  - [ ] MCP server capabilities: Tools, Resources, Prompts
  - [ ] MCP security: user consent, tool safety, LLM sampling controls

## Phase 4: Scalability & Reliability (5-8 min)
- [ ] Discuss scaling strategies:
  - [ ] LLM inference: horizontal scaling of model replicas, model routing by task complexity
  - [ ] Agent runtime: horizontal pod scaling, task queue for async processing
  - [ ] State/checkpoints: distributed PostgreSQL cluster, connection pooling
  - [ ] Sandbox pool: pre-warmed containers/microVMs, size based on concurrency
  - [ ] Orchestration: distributed graph execution, circuit breakers
- [ ] Explain observability architecture:
  - [ ] OTel SDK auto-instruments agent runtime
  - [ ] Three pillars: traces (LLM calls, tool invocations, agent transitions), metrics (tokens, latency, cost, errors), logs (reasoning steps, state transitions)
  - [ ] GenAI semantic conventions for standard attributes
  - [ ] Grafana + Prometheus + Jaeger/Datadog for visualization
- [ ] Discuss cost management:
  - [ ] Token counting at API level, per-agent and per-tenant tracking
  - [ ] Model routing: cheaper models for classification/formatting tasks
  - [ ] Context compaction to reduce token volume (30-50% savings)
  - [ ] Per-tenant budget enforcement with graceful degradation
  - [ ] Per-orchestration-pattern cost awareness
- [ ] Address common production failures:
  - [ ] CPU starvation from under-provisioned NIM microservices
  - [ ] Timeout cascading from LLM call failures
  - [ ] Rate limit hitting from parallel agents on shared endpoints
  - [ ] Unbounded memory growth in long-running agents
  - [ ] Token blowup from growing context windows

## Phase 5: Edge Cases & Trade-offs (3-5 min)
- [ ] Discuss security edge cases:
  - [ ] Prompt injection escape via malicious content triggering attacker-controlled code
  - [ ] Lateral movement: sandbox escape reading other tenants' credentials
  - [ ] Resource abuse: fork bombs, infinite loops, disk exhaustion
  - [ ] Mitigation: multi-layer defense (network, execution, tool, data, content safety)
- [ ] Discuss failure modes:
  - [ ] Infinite handoff loops: require handoff limits
  - [ ] Magentic stall on ambiguous goals: require timeout/iteration caps
  - [ ] Checkpoint recovery with stale LLM context: context compaction strategy
  - [ ] Tool registry schema mismatch after tool version upgrade: versioning and deprecation
- [ ] State the trade-offs you made and why:
  - [ ] Single-agent vs. multi-agent: added coordination overhead, latency, cost
  - [ ] Container vs. microVM: performance vs. isolation strength
  - [ ] Sync vs. async durability: data safety vs. performance
  - [ ] Shared tool registry vs. per-tenant: reuse vs. isolation
- [ ] Mention what you would improve with more time

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
