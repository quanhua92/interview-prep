# LLM Cost Engineering — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Framing (2-3 min)
- [ ] State the problem: LLM costs scale linearly with tokens and traffic — without engineering discipline, costs spiral unpredictably
- [ ] Frame the scope: token economics, caching (prompt + semantic), compression, model routing, batch processing, self-hosted economics, budget enforcement
- [ ] Cite key 2026 numbers:
  - [ ] Only 28% of LLM calls use prompt caching despite support
  - [ ] 69% of input tokens are system prompts (not user input)
  - [ ] GPT-4 ($30/MTok in 2024) → GPT-4.1-nano ($0.10/MTok in 2026) — 300x price drop for equivalent tasks
  - [ ] Frontier output is 5-8x input cost (was 2-3x in 2024)
- [ ] State the value: with disciplined cost engineering, 85-95% savings achievable without quality loss

## Phase 2: Token Economics (3-4 min)
- [ ] Explain per-token pricing model:
  - [ ] Input vs output tokens, output 4-8x more expensive
  - [ ] Pricing per million tokens (MTok)
- [ ] Walk through OpenAI 2026 pricing tiers:
  - [ ] Nano tier: GPT-5-nano ($0.05 in), GPT-4.1-nano ($0.10 in) — for classification, extraction
  - [ ] Mini tier: GPT-5-mini ($0.25 in), GPT-4.1-mini ($0.40 in) — standard tasks
  - [ ] Standard: GPT-5.1 ($1.25 in), GPT-4.1 ($2.00 in) — reasoning, code
  - [ ] Frontier: GPT-5.2 ($1.75 in), o3-pro ($20.00 in) — complex reasoning
  - [ ] Cached input = 90% discount ($1.75 → $0.175)
- [ ] Walk through Anthropic Claude 2026 pricing:
  - [ ] Haiku 4.5 ($1/$5), Sonnet 4.6 ($3/$15), Opus 4.8 ($5/$25)
  - [ ] Cache read at 0.1x (90% savings), write at 1.25x (5m) or 2x (1h)
- [ ] Mention open-source alternatives:
  - [ ] Llama, Qwen, Mixtral on A100/H100 — $0.10-0.80/MTok effective
- [ ] Explain pricing trends:
  - [ ] 80-95% price drop for equivalent capability (2024 → 2026)
  - [ ] New nano tier emerged
  - [ ] Context windows expanded (128K → 2M) but cost per token didn't decrease proportionally

## Phase 3: Cost Per Request Math (3-4 min)
- [ ] State the universal formula:
  - [ ] Cost/Request = (Input Tokens × Input Price) + (Output Tokens × Output Price)
  - [ ] Monthly Cost = Cost/Request × Requests/Month
- [ ] Walk through a calculation example:
  - [ ] System prompt (500 tok, cached), user input (200 tok), RAG context (3K tok, cached), output (400 tok)
  - [ ] Model: GPT-4.1-mini ($0.40/$1.60) → ~$0.001/request
  - [ ] At 100K requests/month → $107/month
  - [ ] At 1M requests/month → $1,070/month
- [ ] Show a larger example:
  - [ ] Enterprise RAG with Claude Sonnet 4.6 ($3/$15)
  - [ ] 11K tokens/request → ~$0.021/request → $1,072/month at 50K requests
  - [ ] At 500K requests → $10,725/month — optimization needed
- [ ] Emphasize: at scale, every 10% token reduction = thousands/month saved

## Phase 4: Prompt Caching (4-5 min)
- [ ] Explain what prompt caching is:
  - [ ] Reuses KV-cache from prior requests with same prompt prefix
  - [ ] Avoids redundant computation → lower latency + lower cost
- [ ] OpenAI caching:
  - [ ] Automatic, no code changes, 1024+ token minimum
  - [ ] 90% discount on cached input, no charge for cache writes
  - [ ] 5-10 min inactivity retention, up to 24h (extended) on GPT-5.x/GPT-4.1
  - [ ] Exact prefix match required — static content must be at start
  - [ ] ~15 req/min per prefix before overflow
  - [ ] `prompt_cache_key` to influence routing
- [ ] Anthropic caching:
  - [ ] Explicit breakpoints (`cache_control` on blocks) or automatic
  - [ ] Up to 4 breakpoints per request
  - [ ] 5-min (1.25x write) or 1-hour (2x write) TTL; reads at 0.1x
  - [ ] 20-block lookback window
  - [ ] Minimum cacheable length varies by model (1K-4K tokens)
  - [ ] Pre-warming with `max_tokens: 0`
- [ ] Cache invalidation rules:
  - [ ] Changing tool definitions → entire cache invalidated
  - [ ] Changing system prompt → system + messages invalidated
  - [ ] Adding images → messages cache invalidated
- [ ] Prefix layout best practice:
  - [ ] Static content (system, tools, examples) at start
  - [ ] Cache breakpoint after last static block
  - [ ] Dynamic content (user message, timestamps) after breakpoint
- [ ] Explain why 72% of teams don't benefit:
  - [ ] Dynamic content injected too early
  - [ ] Below minimum token threshold
  - [ ] Not monitoring `cached_tokens` in response

## Phase 5: Semantic Caching & Prompt Compression (3-4 min)
- [ ] Explain semantic caching:
  - [ ] Embed query → search vector store for similar queries → return cached if match
  - [ ] Tools: GPTCache, custom Redis + embeddings, LangChain cache, Portkey
  - [ ] Similarity threshold: cosine > 0.85 (start strict, tune down)
  - [ ] 30-50% savings on repetitive queries
- [ ] When semantic caching helps:
  - [ ] FAQ, knowledge base, documentation, customer support, code patterns
- [ ] When it hurts:
  - [ ] Personalized queries, time-sensitive, creative generation, high-cardinality
- [ ] Explain prompt compression techniques:
  - [ ] LLMLingua-2: trained classifier removes unimportant tokens (2-4x compression)
  - [ ] Selective Context: perplexity-based removal (2-3x compression)
  - [ ] Instruction pruning: manual removal of redundant instructions (20-40%)
  - [ ] Example culling: remove low-value few-shot examples (20-60%)
  - [ ] Context chunking: only include relevant RAG chunks (30-70%)
- [ ] Compression playbook order:
  - [ ] Start with instruction pruning (lowest risk)
  - [ ] Then example culling (eval-driven)
  - [ ] Then context optimization (reranking)
  - [ ] Then automated compression (LLMLingua-2, with eval)

## Phase 6: Model Tier Routing & Batch Processing (4-5 min)
- [ ] Explain cascade architecture:
  - [ ] Step 1: Cheap classifier (GPT-5-nano) → categorize query complexity
  - [ ] Step 2: 50-60% simple → fast model (GPT-5-mini, Haiku 4.5)
  - [ ] Step 3: 25-35% standard → mid-tier (GPT-4.1-mini, Sonnet 4.6)
  - [ ] Step 4: 10-15% complex → frontier (GPT-5.1, Opus 4.5)
  - [ ] Result: 70-83% savings vs all-traffic-to-frontier
- [ ] Routing approaches:
  - [ ] Rule-based (fastest, simple), classifier-based (accurate, +50ms)
  - [ ] Cascade/escalation (efficient, latency on 10-15% escalation)
  - [ ] ML-based (most accurate, needs training data)
- [ ] Failure modes of cascade:
  - [ ] Misclassification → overpay or quality loss
  - [ ] Cascade latency → double LLM call on escalation
  - [ ] Classifier drift → periodic retraining needed
  - [ ] Confidence miscalibration → tune thresholds on eval data
- [ ] Explain Batch API:
  - [ ] OpenAI: 50% discount, async, results within 24h
  - [ ] Anthropic: 50% on message batches
  - [ ] OpenAI Flex Processing: lower cost for non-production workloads
  - [ ] Good for: content moderation, embeddings, evals, data enrichment
  - [ ] Not for: user-facing chat, real-time features
- [ ] Batch architecture:
  - [ ] Queue → batch collector → batch file → API submission → poll → store results

## Phase 7: Self-Hosted vs Hosted & Budget Enforcement (4-5 min)
- [ ] GPU rental math:
  - [ ] A100 80GB: ~$1.50/hr spot, ~$3/hr on-demand, ~2K tok/s (70B model)
  - [ ] H100 80GB: ~$2.50/hr spot, ~$4/hr on-demand, ~4K tok/s
  - [ ] 8x A100 (p4d): ~$12/hr spot, ~32/hr on-demand, ~16K tok/s
- [ ] Break-even examples:
  - [ ] GPT-4.1-mini vs 1x A100: ~800K req/month break-even
  - [ ] Claude Sonnet 4.6 vs 2x H100: ~80K req/month break-even
- [ ] Self-hosted TCO includes:
  - [ ] GPU rental + monitoring + redundancy + engineering maintenance
  - [ ] Total: $7K-20K/month including FTE time
- [ ] When to self-host vs hosted:
  - [ ] Self-host: high volume, data privacy, custom models, latency control
  - [ ] Hosted: low volume, bursty traffic, multi-model, rapid iteration
- [ ] Serving frameworks: vLLM, TGI, TensorRT-LLM, llama.cpp, SGLang
- [ ] Explain budget enforcement architecture:
  - [ ] Budget hierarchy: org → team → feature → per-request → per-component
  - [ ] Components: cost tracker, alert engine, enforcement (hard caps)
  - [ ] Gateway as enforcement point (pre-counts tokens, checks budget)
  - [ ] Alert thresholds: 50%, 75%, 90%, hard cap at 100%
  - [ ] Multi-tenant quotas: free vs pro vs enterprise tiers
  - [ ] Downgrade strategy: when budget exceeded, fall back to cheaper model

## Phase 8: Cost Optimization Playbook & Debugging (3-4 min)
- [ ] Tier 1 quick wins (Day 1):
  - [ ] Enable prompt caching (20-40%)
  - [ ] Route classification to nano models (60-80%)
  - [ ] Set output token limits (10-30%)
  - [ ] Track cost per request
- [ ] Tier 2 medium effort (Week 1-2):
  - [ ] Model tier routing cascade (70-80%)
  - [ ] Manual prompt compression (20-40%)
  - [ ] Batch API for async work (50%)
  - [ ] Semantic caching (30-50%)
  - [ ] A/B test cheaper models (variable)
- [ ] Tier 3 complex (Week 2-4):
  - [ ] Self-hosting at scale (80-95%)
  - [ ] Fine-tuned small models (90%+)
  - [ ] Budget enforcement architecture
  - [ ] Custom semantic caching pipeline
- [ ] Combined savings: Tier 1 = 40-60%, Tier 1+2 = 70-85%, Tier 1+2+3 = 85-95%
- [ ] Cost debugging process for cost spike:
  - [ ] Check attribution (which feature/team/tenant?)
  - [ ] Check per-request token distribution
  - [ ] Check volume vs cost-per-request
  - [ ] Check model routing (cascade broken?)
  - [ ] Check cache hit rate
  - [ ] Check for retry storms

## Phase 9: Practice Questions (verbal drill)
- [ ] Q1: "Calculate monthly cost for 200K conversations on Claude Sonnet 4.6" — Walk through input/output token math with and without caching
- [ ] Q2: "Reduce LLM costs by 80%" — Model tier routing + caching + batch + compression + semantic cache = 85-95% combined
- [ ] Q3: "Why isn't your team benefiting from prompt caching?" — Dynamic content too early, below minimum, not monitoring
- [ ] Q4: "Self-hosting vs hosted — walk through the math" — GPU rental cost, break-even volume, TCO including engineering
- [ ] Q5: "Design budget enforcement for multi-tenant platform" — Budget hierarchy, gateway enforcement, alerts, quotas, downgrade
- [ ] Q6: "Semantic caching vs prompt caching" — Same vs similar queries, embedding similarity vs prefix match, different use cases
- [ ] Q7: "Costs tripled in a month — debug it" — Attribution → per-request tokens → volume → routing → cache → retries
- [ ] Q8: "Compare cost optimization across OpenAI, Anthropic, Google" — Caching differences, batch API, model tiers, pricing
- [ ] Q9: "Cascade architecture failure modes" — Misclassification, cascade latency, classifier drift, confidence calibration
- [ ] Q10: "Prevent cost spiral when PM wants AI everywhere" — Cost-per-feature estimation, budget caps, phased rollout, continuous review

## Phase 10: Cross-References & Synthesis (2-3 min)
- [ ] Connect to Multi-Model Gateway:
  - [ ] Gateway executes the cost engineering strategies (routing, caching, tracking)
  - [ ] Cost engineering defines the policies; gateway enforces them
- [ ] Connect to AI Product Engineering:
  - [ ] Cost per feature analysis is the PM-facing output of cost engineering
  - [ ] Feasibility assessment includes cost calculation
- [ ] Connect to LLM in Production:
  - [ ] 69% system prompt tokens = biggest optimization target
  - [ ] 28% cache adoption = massive untapped savings
  - [ ] Context engineering = selective inclusion to reduce token cost
- [ ] Connect to RAG System:
  - [ ] RAG context is largest token consumer — chunking and reranking affect cost
  - [ ] Retrieved docs are cacheable
- [ ] Connect to Cloud Cost and Capacity Planning:
  - [ ] Self-hosted GPU costs are cloud infrastructure costs
  - [ ] LLM traffic growth affects both API spend and GPU provisioning
- [ ] Summarize key takeaway: LLM cost engineering is a distributed systems discipline — token math, caching architecture, routing logic, budget enforcement — not just "use a cheaper model"

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
