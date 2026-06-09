# Multi-Model API Gateway & Provider Integration — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Framing (2-3 min)
- [ ] State the problem: teams adopt multiple LLM providers and face routing complexity, provider-specific errors, cost sprawl, and reliability challenges
- [ ] Frame why gateways exist:
  - [ ] LLM calls are long-running (30-300s), streaming, token-billed — generic API gateways don't suffice
  - [ ] Each provider has different APIs, error codes, rate limits, and output formats
  - [ ] Multi-provider strategy is standard (70%+ orgs use 3+ models) but integration overhead is high
- [ ] State the value prop: unified API, automatic failover, smart routing, cost tracking, rate limit management

## Phase 2: Gateway Architecture (3-4 min)
- [ ] Explain three deployment patterns:
  - [ ] Sidecar Proxy: per-service, minimal latency (~1-5ms), no cross-service visibility
  - [ ] Centralized Gateway: dedicated service, unified config, cross-service visibility, 5-50ms overhead
  - [ ] Edge Routing: CDN/edge, data residency enforcement, higher complexity
- [ ] Explain when you need a gateway:
  - [ ] <3 services, <$3K/month → no gateway (SDK calls sufficient)
  - [ ] 3+ services or multi-provider → centralized gateway
  - [ ] Multi-provider + compliance → full routing gateway
- [ ] Discuss build vs adopt:
  - [ ] Start with LiteLLM in proxy mode (easiest, OpenAI-compatible, YAML config, 40K stars)
  - [ ] Custom gateway rarely justified unless extreme latency or regulatory needs
  - [ ] If building: Go or Rust, not Python

## Phase 3: Open-Source Implementations & Routing (3-4 min)
- [ ] Compare key gateways:
  - [ ] LiteLLM (Python, MIT, easiest adoption, built-in cost tracking)
  - [ ] Bifrost (Go, ~8μs overhead, 5K+ RPS)
  - [ ] TensorZero (Rust, <1ms overhead, 10K+ QPS, ML-based routing)
  - [ ] Portkey (TypeScript, guardrails, semantic caching, Apache 2.0)
  - [ ] OpenRouter (SaaS, 300+ models, 5.5% fee)
- [ ] Explain routing strategies:
  - [ ] Cost-based: classification → Haiku, generation → Sonnet, reasoning → Opus (80% savings)
  - [ ] Capability-based: vision, long-context, structured output, code
  - [ ] Latency-based: streaming → fastest, batch → cheapest
  - [ ] A/B testing: % traffic to new model candidate
- [ ] Explain fallback chains:
  - [ ] Model-level: claude-opus → claude-sonnet → claude-haiku → cached
  - [ ] Provider-level: Anthropic → OpenAI → Cohere → local model
  - [ ] Key challenge: output format differences break downstream parsers

## Phase 4: Error Handling & Resilience (4-5 min)
- [ ] Explain circuit breaker state machine:
  - [ ] CLOSED → OPEN → HALF-OPEN → CLOSED
  - [ ] OPEN_EXTENDED for flapping scenarios
  - [ ] Config: 3-5 failure threshold, 5-min window, 5-min backoff
- [ ] Critical distinction:
  - [ ] Trip on infrastructure failures (5xx, timeouts) only
  - [ ] Do NOT trip on business errors (400, 401)
- [ ] Explain resilience patterns:
  - [ ] Exponential backoff with jitter, honor Retry-After
  - [ ] Bulkhead: semaphore per service/tenant
  - [ ] Degraded modes: Essential/Minimal/Emergency
- [ ] State resilience hierarchy:
  - [ ] Error classification → Retries → Circuit breakers → Bulkheads → Fallbacks → Queue buffering → Human escalation
- [ ] Explain timeout hierarchy:
  - [ ] Network connect (5-10s), TTFB (30s), inter-token gap (10-15s), total (120-300s), agent E2E (600s)
- [ ] Key stat: multi-agent systems fail at 41-86.7% without fault tolerance

## Phase 5: Structured Output & Token Management (3-4 min)
- [ ] Compare structured output across providers:
  - [ ] OpenAI: response_format + strict:true, CFG decoding, no oneOf
  - [ ] Anthropic: tool-use workaround, most permissive, silently corrupts deep nesting >3 levels
  - [ ] Gemini: response_json_schema, rejects oneOf/type-arrays, good deep nesting
- [ ] State defensive patterns:
  - [ ] Always validate independently (ajv, hyperjump)
  - [ ] Treat parse error = schema violation = refusal as equal failures
  - [ ] Flatten deep schemas for Anthropic
- [ ] Explain token counting differences:
  - [ ] OpenAI: tiktoken (cl100k_base, o200k_base)
  - [ ] Anthropic: custom (not public)
  - [ ] Google: SentencePiece-based
  - [ ] Estimation: ~4 chars/token English, ~2 chars/token CJK
  - [ ] Same prompt → different token counts, different context limits, different costs
- [ ] Explain rate limit management:
  - [ ] RPM, TPM (input/output separate), daily quotas
  - [ ] Token-aware (token bucket), not request counting
  - [ ] Backoff with jitter for 429s
  - [ ] Token budget management: daily/hourly caps, prompt compression (20-30%)

## Phase 6: Cost, Security & Complexity Routing (3-4 min)
- [ ] Explain cost tracking:
  - [ ] Tag every request: team, feature, environment, model
  - [ ] Gateway as single capture point for cost/latency/tokens
- [ ] Explain optimization strategies:
  - [ ] Model tier routing (80% savings), prompt caching (20-40%), semantic caching, batch API (50%)
  - [ ] Common traps: QA silent killer, retry storms, runaway agent loops
- [ ] Cover security considerations:
  - [ ] PII redaction before external providers (HIPAA/PCI-DSS/GDPR)
  - [ ] Centralized credential management in gateway
  - [ ] Data sovereignty: self-hosted, edge routing, hybrid
  - [ ] Supply chain: pin model versions, verify checksums
  - [ ] Audit trail: who called, which model, cost, latency
- [ ] Explain query complexity routing:
  - [ ] Rule-based, semantic, signal-driven, ML-based, cascade approaches
  - [ ] Simple classification → fast-tier; standard reasoning → standard-tier; frontier → frontier-tier

## Phase 7: System Design Bridge (2-3 min)
- [ ] Connect to LLM in Production:
  - [ ] Gateway is the operational backbone of model portfolio management
  - [ ] Gateway enables the observability patterns (tracing, cost tracking)
- [ ] Connect to Security:
  - [ ] PII redaction and credential management enforced at gateway layer
- [ ] Connect to RAG System:
  - [ ] Gateway routes RAG-augmented prompts to appropriate model tier
  - [ ] Retrieval results affect token count → routing decision
- [ ] Connect to Senior AI Engineer:
  - [ ] Retry logic, error handling, and API integration patterns live in the gateway
- [ ] Connect to SLO & Error Budgets:
  - [ ] Gateway latency overhead must fit within latency budget (justify 50ms)
  - [ ] Provider error rate allocated from error budget
- [ ] Connect to CS Fundamentals:
  - [ ] Circuit breakers, exponential backoff, token bucket — all classic distributed systems patterns

## Phase 8: Practice Questions (verbal drill)
- [ ] Q1: "How would you design a multi-model LLM gateway?" — Walk through centralized architecture, routing, fallbacks, monitoring
- [ ] Q2: "How do you handle provider outages?" — Circuit breaker → fallback chain → degraded mode
- [ ] Q3: "How do structured outputs differ?" — OpenAI strict vs Anthropic permissive vs Gemini middle ground, always validate independently
- [ ] Q4: "Reduce LLM costs by 50%?" — Tier routing, caching, prompt compression, batch API, A/B test cheaper models
- [ ] Q5: "Handle LLM rate limits?" — Token-aware rate limiting, backoff with jitter, budget management, queue buffering
- [ ] Q6: "Different tokenizers?" — tiktoken vs custom, estimation rules, impact on context limits and cost
- [ ] Q7: "Fallback chain for agent with 3 providers + output format changes?" — Composite fallback + schema validation + canonical normalization
- [ ] Q8: "Cost-per-feature attribution?" — Request tagging at gateway, centralized logging, per-team reporting
- [ ] Q9: "Justify 50ms gateway latency?" — Unified API, automatic failover, cost tracking, security, observability — ROI far exceeds 50ms
- [ ] Q10: "Claude and GPT-4 produce semantically different responses?" — Evaluation framework, canonical schema, model-specific tuning, A/B quality metrics

## Phase 9: Wrap-Up (1-2 min)
- [ ] Summarize the ten core competencies covered
- [ ] Emphasize: multi-model gateway is a distributed systems problem, not a prompt engineering problem
- [ ] Key takeaway: gateway is the single point where routing, resilience, cost, security, and observability converge
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
