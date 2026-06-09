# Multi-Model API Gateway & Provider Integration

## One-Liner
A multi-model LLM gateway is the distributed systems layer between application code and model providers — handling routing, fallbacks, rate limits, cost attribution, and output normalization so that app teams interact with a single unified API regardless of which model serves the request.

## Core Competencies Table

| Competency | Why It Matters | Interview Trigger |
|------------|---------------|-------------------|
| Gateway Architecture | Choose deployment model (sidecar, centralized, edge) based on team size, latency, and compliance needs | "Design a multi-model LLM gateway" |
| Routing Strategies | Route requests by cost, capability, latency, or A/B test to maximize ROI | "How would you reduce LLM costs by 50%?" |
| Fallback Chains | Maintain availability across provider outages and model failures | "How do you handle provider outages?" |
| Error Handling & Resilience | Apply circuit breakers, bulkheads, and degraded modes to LLM-specific failure modes | "Your gateway adds 50ms latency — justify it" |
| Structured Output Normalization | Handle provider-specific JSON schema differences and validation | "How do structured outputs differ across providers?" |
| Rate Limit Management | Token-aware rate limiting, backoff with jitter, budget enforcement | "How do you handle LLM rate limits?" |
| Cost Tracking & Optimization | Per-feature cost attribution, caching strategies, common cost traps | "Implement cost-per-feature attribution" |
| Security | PII redaction, credential management, data sovereignty, audit trails | "Security considerations for external model providers" |
| Query Complexity Routing | Match model tier to task difficulty for optimal cost/quality | "When do you use Haiku vs Opus?" |
| Token Counting | Understand tokenizer differences and their impact on context limits and cost | "How do you handle different tokenizers?" |

## Common Interview Topics

### 1. Gateway Architecture & Design Patterns

#### What an LLM Gateway Does
- Sits between application code and model providers (OpenAI, Anthropic, Google, Cohere, local models)
- Presents a unified API — app code calls one endpoint, gateway routes to the appropriate provider/model
- Handles: routing, retries, fallbacks, rate limiting, token counting, cost tracking, logging, caching

#### Key Difference from Generic API Gateways
- **Streaming responses**: LLM calls return tokens incrementally over 30+ seconds, not a single JSON response
- **Token billing**: Cost is per-token, not per-request — requires upstream token counting before routing decisions
- **Provider-specific errors**: Each provider has different error codes, rate limit headers, and failure modes
- **Long-running calls**: Requests can take 30-300 seconds vs typical API calls under 1 second
- **Structured output normalization**: Same schema must work across providers with different JSON generation behavior

#### Three Deployment Patterns

| Pattern | Description | Pros | Cons | When to Use |
|---------|-------------|------|------|-------------|
| Sidecar Proxy | Gateway runs alongside each service (same process or pod) | Minimal added latency (~1-5ms), no network hop, per-service config | Duplication across services, no cross-service visibility, harder to update consistently | Latency-critical services, small number of services |
| Centralized Gateway | Dedicated service that all app services call | Cross-service visibility, unified config, single audit point, easier to add new providers | Extra network hop (5-50ms), single point of failure (mitigated by redundancy), scaling bottleneck at high traffic | 3+ services, multi-provider strategy, org-wide policies |
| Edge Routing | Gateway at CDN/edge (Cloudflare Workers, AWS Lambda@Edge) | Data residency enforcement, low latency globally, DDoS protection | Limited compute at edge, complex deployment, higher cost | Multi-region deployments, compliance requirements |

#### When You Need One
- **<3 services, <$3K/month**: No gateway — direct SDK calls are fine, overhead not justified
- **3+ services or multi-provider**: Centralized gateway recommended
- **Multi-provider + cost optimization + compliance**: Full routing gateway with caching, guardrails, audit

#### Build vs Adopt
- **Start with LiteLLM in proxy mode** — OpenAI-compatible API, YAML config, built-in cost tracking, 40K+ GitHub stars
- Custom gateway rarely justified unless: extreme latency requirements (<1ms), proprietary routing logic, or regulatory isolation
- If building custom: start in Go or Rust (TensorZero-level overhead), not Python

### 2. Open-Source Gateway Implementations

| Gateway | Language | Overhead | Throughput | License | Strengths |
|---------|----------|----------|------------|---------|-----------|
| **LiteLLM** | Python | ~50ms | Varies | MIT | Easiest to adopt, OpenAI-compatible API, YAML config, built-in cost tracking, 40K+ stars |
| **TensorZero** | Rust | <1ms | 10K+ QPS | Open-source | ML-based routing, highest throughput, low overhead |
| **Portkey** | TypeScript | Moderate | High | MIT | Best for production guardrails, semantic caching, TypeScript ecosystem |
| **OpenRouter** | SaaS | N/A | N/A | SaaS | 300+ models, managed, 5.5% fee, no infra to manage |
| **Kong AI Gateway** | Lua/Go | Low | High | Open-source | Enterprise features, plugin ecosystem, existing Kong users |
| **Cloudflare AI Gateway** | Edge | Low | High | Managed | Edge deployment, analytics, built-in caching, Workers ecosystem |

#### Selection Framework
- **Prototype/startup**: LiteLLM proxy mode (fastest to adopt)
- **Latency-critical production**: TensorZero
- **Guardrails + caching**: Portkey
- **No infra management**: OpenRouter
- **Enterprise/Kong ecosystem**: Kong AI Gateway

### 3. Routing Strategies & Fallback Chains

#### Cost-Based Routing
Route to the cheapest model that meets quality requirements:
- Classification/tagging → Haiku ($0.25/MTok) — 90% cost reduction vs frontier
- Standard generation → Sonnet ($3/MTok) — good balance
- Complex reasoning → Opus ($15/MTok) — only when needed
- **Typical savings: 70-80%** by routing classification work to lightweight models

#### Capability-Based Routing
Route based on task requirements:
- Vision tasks → GPT-4o or Gemini Pro Vision
- Long-context (>128K tokens) → Gemini 1.5 Pro or Claude 3.5 Sonnet
- Structured output required → OpenAI with `strict:true` or Anthropic via tool-use
- Code generation → Claude or GPT-4o

#### Latency-Based Routing
- Streaming chat (user waiting) → fastest available model
- Batch processing (no user waiting) → cheapest model, possibly batch API
- Background tasks → queue-based routing to underutilized providers

#### A/B Testing Routing
- Split N% of traffic to new model candidate
- Compare quality metrics, latency, and cost
- Gradual rollout: 1% → 5% → 25% → 100%

#### Fallback Chains

**Model-level fallbacks** (same provider, different model):
```
claude-opus → claude-sonnet → claude-haiku → cached response → error
```

**Provider-level fallbacks** (different provider, similar capability):
```
anthropic/claude-sonnet → openai/gpt-4o → cohere/command-r-plus → local/llama-3
```

**Composite fallback** (cascading across both):
```
anthropic/claude-opus → openai/gpt-4o → anthropic/claude-sonnet → openai/gpt-4o-mini → cached → error
```

#### The Output Format Challenge
- Different models produce different JSON structures even with the same schema
- GPT-4 might include extra fields, Claude might reorder properties, Gemini might change types
- Downstream parsers break silently on format differences
- Solution: strict schema validation at gateway level (ajv/hyperjump) before forwarding to app
- Alternatively: normalize output at gateway into canonical format

### 4. Error Handling & Resilience Patterns

#### Circuit Breaker State Machine
```
CLOSED (normal) --[failures >= threshold]--> OPEN (rejecting)
OPEN (rejecting) --[timeout expires]--> HALF-OPEN (testing)
HALF-OPEN (testing) --[success]--> CLOSED (normal)
HALF-OPEN (testing) --[failure]--> OPEN (rejecting)
```

Extended states for flapping:
```
OPEN --[repeated failure recovery then fail]--> OPEN_EXTENDED (longer cooldown)
```

#### Circuit Breaker Configuration
| Parameter | Recommended Value |
|-----------|------------------|
| Failure threshold | 3-5 failures |
| Detection window | 5 minutes |
| Initial backoff | 5 minutes |
| Max backoff | 10-30 minutes |
| Half-open test requests | 1-3 |

**Critical: Only trip on infrastructure failures** (5xx, timeouts, connection refused). Do NOT trip on business errors (400 bad request, 401 unauthorized) — those indicate app-level problems, not provider health.

#### Exponential Backoff with Jitter
```python
delay = min(base * 2^attempt + random_jitter, max_delay)
```
- Honor `Retry-After` headers from providers when present
- Different backoff for rate limits (429) vs server errors (5xx)

#### Bulkhead Pattern
- Separate semaphore/concurrency limits per service type, per provider, per model
- Prevents one noisy service from consuming all gateway capacity
- Example: service-A gets 100 concurrent Anthropic calls, service-B gets 50

#### Degraded Modes
| Level | Behavior |
|-------|----------|
| **Full** | All providers/models available, all features enabled |
| **Essential** | Primary provider down, fallback active; caching aggressive; non-critical features disabled |
| **Minimal** | Only cheapest/slowest models available; queuing enabled; user-facing latency increase |
| **Emergency** | Cached responses only or graceful error message |

#### Resilience Hierarchy (bottom to top)
1. **Error classification**: distinguish infrastructure (retry) vs business (no retry) errors
2. **Retries**: exponential backoff with jitter, respect Retry-After
3. **Circuit breakers**: stop sending traffic to unhealthy providers
4. **Bulkheads**: isolate failures per service/tenant
5. **Fallbacks**: route to alternate provider/model
6. **Queue buffering**: async requests during partial outage
7. **Human escalation**: alerting and manual intervention

#### Timeout Hierarchy
| Timeout | Recommended | Notes |
|---------|-------------|-------|
| Network connect | 5-10s | TCP + TLS handshake |
| Time to first byte (TTFB) | 30s | Model start-up + first token |
| Inter-token gap | 10-15s | Detect stalled streaming |
| Total request | 120-300s | Full response generation |
| End-to-end agent | 600s | Multi-step agent with tool calls |

#### Key Statistic
- Multi-agent systems are significantly more failure-prone than single-model systems due to compounding error modes

### 5. Structured Output Differences Across Providers

| Provider | Mechanism | Strictness | Deep Nesting | oneOf/anyOf | Notes |
|----------|-----------|------------|--------------|-------------|-------|
| **OpenAI** | `response_format` + `strict:true` | Strictest | Handles well | **Not supported** with strict | Schema validation at submission time + strict token-level enforcement (implementation detail not publicly documented), requires `additionalProperties:false` |
| **Anthropic** | Tool-use API workaround | Most permissive | **Silently corrupts** >3 levels | Supported | Most schemas pass but silent failures on deep nesting are dangerous |
| **Gemini** | `response_json_schema` | Middle ground | Handles well | **Rejects** oneOf/type-arrays | Good validation, rejects unsupported features clearly |

#### Benchmark Results
- **Anthropic**: 7/8 schemas at 100% compliance — most permissive, but silent corruption on deep schemas
- **OpenAI**: Strictest validation — fails loudly on unsupported features (safer, more predictable)
- **Gemini**: Middle ground — good deep nesting support, but rejects oneOf/type-arrays

#### Defensive Patterns
1. **Always validate independently** (ajv, hyperjump) — never trust provider JSON schema enforcement
2. **Treat all failures equally**: parse error = schema violation = refusal = model fallback trigger
3. **Flatten deep schemas** for Anthropic (>3 levels nesting is unsafe)
4. **Use lowest common denominator schema**: avoid oneOf/anyOf when multi-provider
5. **Add version field** to output schema for forward compatibility

### 6. Rate Limit Management

#### Rate Limit Types
| Type | Unit | Notes |
|------|------|-------|
| RPM | Requests per minute | Per model, per tier |
| TPM (Input) | Input tokens per minute | Often separate from output |
| TPM (Output) | Output tokens per minute | Generation speed matters |
| Daily quotas | Tokens/day | Hard cap, resets at midnight UTC |

#### Token-Aware Rate Limiting
- Use **token bucket** algorithm, not simple request counting
- A single 100K-token request costs more headroom than ten 1K-token requests
- Pre-count tokens (tiktoken for OpenAI, estimation for others) before sending
- Reserve capacity for critical requests

#### Backoff Strategy for 429s
- Exponential backoff with jitter: `delay = base * 2^attempt + random(0, base)`
- Honor `Retry-After` header if present
- Implement **rate limit budget**: don't retry if budget exhausted, queue instead

#### Token Budget Management
- Daily/hourly caps per team, per feature, per environment
- **Prompt compression**: 20-30% token savings with minimal quality loss
- **Reasoning token budgets**: define "quick" (low reasoning tokens) vs "thorough" (high reasoning tokens) profiles
- Monitor and alert on budget burn rate

### 7. Cost Tracking & Optimization

#### Cost Attribution
- Tag every request: team, feature, environment, model, user-segment
- Gateway is the single point to capture: model, tokens_in, tokens_out, latency, cost, cache_hit
- Enable per-feature cost reporting: "feature X costs $2.3K/month across 3 models"

#### Optimization Strategies

| Strategy | Savings | Effort | Notes |
|----------|---------|--------|-------|
| Model tier routing | 70-80% | Medium | Classification → Haiku, reasoning → Sonnet |
| Prompt caching | 20-40% | Low | Reuse system prompt prefix |
| Semantic caching | 30-50% | High | Cache similar (not identical) prompts |
| Context optimization | 10-30% | Medium | Remove noise, compress context |
| Batch API | 50% | Low | Async non-streaming requests |
| A/B cheaper models | Variable | Medium | Test if cheaper model is "good enough" |

#### Common Cost Traps
1. **QA environment silent killer**: QA uses production-tier models without monitoring → untracked costs
2. **Retry storms**: cascading retries during partial outage multiply costs 5-10x
3. **Runaway agent loops**: agents calling LLM in loops without budgets → $100+ per run
4. **Context window bloat**: 2M token windows make it easy to send 100K+ tokens per request

### 8. Security Considerations

#### PII Redaction
- Redact PII before sending prompts to external providers (HIPAA, PCI-DSS, GDPR)
- Gateway is the natural enforcement point — all traffic flows through it
- Regex-based + NER-based redaction, with allowlists for safe fields
- Log redacted prompts for audit, not originals

#### Credential Management
- Centralize API keys in the gateway — app services never touch provider credentials
- Key rotation without app deployments
- Per-team/per-feature key quotas
- Monitor for leaked credentials in code/repos

#### Data Sovereignty
- Some regulations require data stays in specific geographies
- Options: self-hosted gateway + local models, edge routing, hybrid (sensitive → local, general → cloud)
- Gateway routing decisions can enforce geo-policies transparently

#### Supply Chain Security
- Pin model versions (`gpt-4o-2024-08-06`, not `gpt-4o`)
- Verify model checksums for self-hosted models
- Monitor for model behavior changes after updates

#### Audit Trail
- Log: who called, which model, prompt hash (not full prompt), response hash, cost, latency, tokens
- Retention policy aligned with compliance requirements
- Alert on anomalous patterns (sudden cost spike, unusual model access)

### 9. Model Routing by Query Complexity

#### Routing Approaches

| Approach | How It Works | Pros | Cons |
|----------|-------------|------|------|
| Rule-based | Hardcoded rules: if task=classification → fast-tier | Simple, predictable | Doesn't adapt, requires maintenance |
| Semantic | Embed query → compare to task clusters | Flexible, adaptive | Needs embedding infrastructure |
| Signal-driven | Use metadata (token count, user tier, feature flags) | Lightweight, fast | Limited to available signals |
| ML-based | Train classifier on query → model tier mapping | Most accurate | Complex, needs training data |
| Cascade | Try fast model first, escalate if confidence low | Efficient, simple | Added latency on escalation |

#### Decision Framework
| Query Complexity | Model Tier | Examples |
|-----------------|-----------|----------|
| Simple classification | Fast-tier (Haiku, GPT-4o-mini, Gemini Flash) | Sentiment, intent detection, entity extraction |
| Standard reasoning | Standard-tier (Sonnet, GPT-4o, Gemini Pro) | Summarization, Q&A, code generation |
| Complex reasoning | Frontier-tier (Opus, o1, Gemini Ultra) | Multi-step reasoning, complex analysis, creative tasks |

### 10. Token Counting Across Tokenizers

#### Tokenizer Differences

| Provider | Tokenizer | Notes |
|----------|----------|-------|
| OpenAI | tiktoken (cl100k_base for GPT-4, o200k_base for GPT-4o) | Public, well-documented |
| Anthropic | Custom (not publicly available) | Must estimate or use API response headers |
| Google | SentencePiece-based | Varies by model |

#### Estimation Rules
- English: ~4 characters per token
- CJK (Chinese, Japanese, Korean): ~2 characters per token
- Code: ~3-4 characters per token (varies by language)
- Always estimate high for budgeting purposes

#### Practical Impact
- **Same prompt, different token count**: "Hello world" might be 2 tokens for OpenAI, 3 for Anthropic
- **Different context limits**: GPT-4o (128K), Claude (200K), Gemini (2M) — same prompt hits different limits
- **Different costs**: Same prompt costs different amounts across providers
- **Gateway responsibility**: Pre-count tokens to select correct model tier and enforce budget limits

## Interview Questions

1. **How would you design a multi-model LLM gateway?** — Architecture, deployment model, routing, fallbacks, monitoring
2. **How do you handle provider outages?** — Circuit breakers, fallback chains, degraded modes, alerting
3. **How do structured outputs differ across providers?** — OpenAI strict mode, Anthropic tool-use workaround, Gemini response_json_schema, validation strategies
4. **How would you reduce LLM costs by 50%?** — Model tier routing, caching, prompt compression, batch API, A/B testing cheaper models
5. **How do you handle LLM rate limits in production?** — Token-aware rate limiting, backoff with jitter, budget management, queue buffering
6. **How do you handle different tokenizers across providers?** — tiktoken vs custom, estimation rules, context limit implications, cost differences
7. **Design a fallback chain for an agent that uses 3 LLM providers. What happens when output format changes between providers?** — Composite fallback chain, output validation, schema normalization, graceful degradation
8. **How would you implement cost-per-feature attribution for a multi-tenant AI platform?** — Request tagging, centralized logging, per-team reporting, budget enforcement
9. **Your LLM gateway adds 50ms latency. How do you justify this overhead?** — Unified API, automatic failover, cost tracking, rate limiting, security enforcement, observability
10. **How do you handle a situation where Claude and GPT-4 produce valid but semantically different responses to the same prompt?** — Output validation, canonical schema, evaluation framework, model-specific tuning, A/B testing

## Key Terminology

| Term | Definition |
|------|-----------|
| LLM Gateway | Proxy service between app code and model providers offering unified API, routing, and resilience |
| Token Bucket | Rate limiting algorithm that allows bursty traffic up to a capacity, then refills at a steady rate |
| Circuit Breaker | Pattern that stops sending traffic to a failing service after threshold failures |
| Bulkhead | Pattern that isolates failures to prevent cascading across services/tenants |
| Sidecar Proxy | Gateway deployed alongside each application service for minimal latency |
| Centralized Gateway | Single shared gateway service used by multiple application services |
| Model Tier Routing | Routing strategy that selects model based on task complexity/cost/latency requirements |
| Prompt Caching | Reusing previously computed KV-cache for repeated prompt prefixes |
| Semantic Caching | Caching responses for semantically similar (not just identical) prompts |
| Token Budget | Maximum tokens allowed per request/team/environment within a time window |
| Structured Output | Forcing LLM to return JSON conforming to a specific schema |
| TTFB | Time to First Byte — latency until the first token is generated |
| Degraded Mode | Operating with reduced functionality (fallback models, cached responses, disabled features) |
| Rate Limit Header | HTTP header (e.g., `Retry-After`) indicating when a client may resume requests |

## Cross-References

| Topic | Connection |
|-------|-----------|
| [LLM in Production](../llm_in_production/discussion.md) | Model portfolio management, gateway role in multi-model strategy, LLM observability, reliability patterns |
| [Security](../security/discussion.md) | PII redaction, credential management, data sovereignty, audit trails |
| [RAG System](../../system_design/rag_system/discussion.md) | RAG pipeline integration through gateway, retrieval-augmented routing decisions |
| [Senior AI Engineer](../../role_specific/senior_ai_engineer/discussion.md) | API integration patterns, retry logic, error handling in AI services |
| [SLO & Error Budgets](../slo_error_budgets/discussion.md) | Latency budgets for gateway overhead, error budget allocation for LLM providers |
| [CS Fundamentals](../../cs_fundamentals/discussion.md) | Networking (TCP/TLS timeouts), distributed systems (circuit breakers, backoff, queuing) |
