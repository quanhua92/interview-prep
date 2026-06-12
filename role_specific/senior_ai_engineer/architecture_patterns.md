# Architecture Patterns: Senior AI Engineer

This document covers production-grade architectural patterns you should be prepared to design, whiteboard, and defend during system design interviews.

## 1. Enterprise RAG with RBAC & Multi-Tenancy

**The Challenge:** Designing a retrieval system for regulated domains (e.g., finance, healthcare) where users can only access specific documents.

**Key Principles:**
- **Authorization Before Retrieval:** Never rely on the LLM to filter unauthorized data. Enforce access control *before* the context is assembled.
- **Identity-Aware Pipelines:** Queries must carry `tenant_id` and `user_role` metadata.
- **Data Isolation:** Use namespace or metadata-based partitioning in the vector database.

**Architecture Flow:**
1. **Ingestion Layer:** Tag every document chunk with security attributes (`tenant_id`, `owner_id`, `allowed_roles`). Redact PII *before* embedding.
2. **Retrieval Layer (Filter-First & Rerank):** Apply hard metadata filters (e.g., `tenant_id == X AND role IN (Y, Z)`) before performing semantic vector search. Follow up with a Cross-Encoder (Reranker) to boost top-K relevance while minimizing context window size.
3. **Generation Layer:** The LLM receives only authorized, highly relevant chunks to synthesize the answer.

## 2. Agentic Workflows: Orchestrator-Worker vs. Swarm

**The Challenge:** Designing a multi-agent system to handle complex, multi-step tasks reliably.

**Pattern A: Orchestrator-Worker (Hierarchical)**
- **Design:** A single "Router" or "Orchestrator" LLM decomposes the task, delegates to specialist worker agents (which may be cheaper models), and synthesizes the results.
- **Pros:** Strong central control, easy to trace, predictable cost.
- **Cons:** Orchestrator becomes a bottleneck; context dilution if the orchestrator has to read all worker outputs.

**Pattern B: Multi-Agent Swarm (Decentralized)**
- **Design:** Agents communicate directly with each other, passing state.
- **Pros:** Highly scalable, follows the Principle of Least Privilege (agents only see what they need).
- **Cons:** Harder to debug (deadlocks, infinite loops).

**Handling Deadlocks & Loops:** Implement a "Loop Guard" (e.g., hashing tool arguments at each step and aborting if the same failing call repeats 3+ times).

## 3. Human-in-the-Loop (HITL) & Checkpointing

**The Challenge:** Pausing an autonomous agent to wait for human approval before executing a high-risk action (e.g., sending an email, dropping a table) without blocking server resources.

**Architecture Flow:**
- Use a state machine framework (e.g., LangGraph).
- **Checkpointing:** Serialize and save the agent's state (messages, variables) to a database (e.g., PostgreSQL).
- **Interrupt:** The agent suspends execution and yields an `interrupt` signal to the client.
- **Resume:** Once the human approves, the system deserializes the state and continues the workflow from the exact node it left off.

## 4. RAG Cost Estimation

**The Challenge:** Leadership asks for a monthly cost estimate for a production RAG system before building it. You need a defensible number with clear assumptions.

**Cost Layers (4 buckets):**

| Layer | Type | Key Drivers |
|-------|------|-------------|
| **Ingestion** | One-time or periodic | Document parsing, chunking, embedding generation, vector DB indexing |
| **Storage** | Recurring | Vector DB hosting, document storage, metadata indexes |
| **Retrieval** | Recurring | Vector search queries, reranking model calls, caching infrastructure |
| **Generation** | Recurring (dominant) | LLM inference tokens (prompt + context + output), model choice |

**Why Generation Dominates:** In production, every user query triggers an LLM call with retrieved context. Token usage scales linearly with query volume and directly drives cost. A poorly tuned RAG system that retrieves excessive context can multiply inference cost 5-10x without improving answer quality.

**Real Pricing Reference (verified 2025-2026):**

| Component | Option | Price | Notes |
|-----------|--------|-------|-------|
| **Embedding Models** | OpenAI text-embedding-3-small | $0.02/1M tokens | 1,536-dim, best value |
| | OpenAI text-embedding-3-large | $0.13/1M tokens | 3,072-dim, higher accuracy |
| **LLM Generation (per 1M tokens)** | GPT-4o | $4.00 in / $20.00 out | Flagship-grade |
| | GPT-4o-mini | $0.15 in / $0.60 out | Budget, 10x cheaper |
| | Claude Sonnet 4.6 | $3.00 in / $15.00 out | Mid-tier, strong reasoning |
| | Claude Haiku 4.5 | $1.00 in / $5.00 out | Fast, cost-efficient |
| | Claude Opus 4.8 | $5.00 in / $25.00 out | Anthropic flagship |
| | GPT-5 mini | $0.25 in / $2.00 out | Newer budget option |
| | GPT-5 nano | $0.05 in / $0.40 out | Cheapest OpenAI, classification tasks |
| | DeepSeek V3.2 | $0.28 in / $0.42 out | Ultra-low cost, 128K context |
| **Reranking** | Cohere Rerank v3 | $2.00/1M tokens | Cross-encoder, query+doc tokens |
| | Cohere Rerank 3.5 (via Pinecone) | $2.00/1K requests | Per-request pricing |
| **Vector Database** | Pinecone Serverless (Standard) | $16/M Read Units + $0.33/GB/mo storage | $50/mo minimum. Per-query billing. 1 RU per 1GB namespace scanned |
| | Pinecone Serverless (Enterprise) | $24/M Read Units | $500/mo minimum |
| | Qdrant Cloud | ~$96/mo (16GB node) | Zero per-query billing. RAM/vCPU allocation model |
| | Self-hosted Qdrant (DigitalOcean) | $20-96/mo (Droplet) | 16GB Droplet handles 10-20M vectors. Zero per-query cost |
| | Weaviate Cloud (Flex) | ~$0.095/M dimensions/mo | 10M × 1536-dim ≈ $1,459/mo. With PQ/BQ compression: $45-365/mo |
| | pgvector (Postgres) | $0 incremental | Add to existing DB. Best under 5M vectors |
| **Self-Hosted GPU (vLLM)** | AWS A100 40GB | ~$2.16/GPU-hr | After June 2025 price reduction |
| | AWS H100 SXM5 | ~$6.88/GPU-hr | After 44% reduction. Alternative providers: $1.50-4.00/hr |
| | Llama 3.3 70B (via OpenRouter) | ~$0.59-0.90/1M tokens | Hosted inference, no GPU ops |

**Cost Estimation Framework:**

1. **Estimate daily token budget:**
   - Daily queries × avg prompt tokens × avg retrieved context tokens × avg output tokens
   - Account for peak vs. average (production systems see 3-5x peak-to-average ratio)
   - Example: 5K queries/day × (500 prompt + 3,000 context + 500 output) = 20M tokens/day = 600M tokens/month

2. **Calculate LLM generation cost (the dominant line item):**
   - Using Claude Sonnet 4.6 at 600M tokens/month (70% input, 30% output): 420M × $3/1M + 180M × $15/1M = $1,260 + $2,700 = **$3,960/month**
   - Same workload on GPT-4o-mini: 420M × $0.15/1M + 180M × $0.60/1M = $63 + $108 = **$171/month**
   - Same workload on Claude Haiku 4.5: 420M × $1/1M + 180M × $5/1M = $420 + $900 = **$1,320/month**
   - **Model choice alone swings cost by 23x ($171 to $3,960) for identical workload.**

3. **Calculate embedding cost (one-time or periodic):**
   - 100K documents × avg 2,000 tokens each = 200M tokens to embed
   - Using text-embedding-3-small: 200M × $0.02/1M = **$4 one-time** (or on re-index)
   - Using text-embedding-3-large: 200M × $0.13/1M = **$26 one-time**

4. **Calculate vector DB cost:**
   - Pinecone Serverless for 5M vectors (~29GB with HNSW overhead): ~$29/mo storage + query costs
   - Self-hosted Qdrant on $96/mo Droplet: handles 10-20M vectors with zero per-query cost
   - Pinecone scaling risk: at 50K queries/day against a 50GB namespace, each query consumes 50 RUs → 2.5M RUs/day → $40/month in read costs alone

5. **Add reranking cost (if used):**
   - Cohere Rerank at $2/1M tokens: 5K queries/day × 5K tokens/query = 25M tokens/month → **$50/month**

**Worked Example: Medium Enterprise RAG (~$3-8K/month)**

| Line Item | Assumptions | Monthly Cost |
|-----------|-------------|-------------|
| LLM Generation | 5K queries/day, Claude Sonnet 4.6, 4K avg context | ~$3,960 |
| Embedding (initial) | 100K docs × 2K tokens, text-embedding-3-small | $4 (one-time) |
| Embedding (re-index, quarterly) | Same volume, 4x/year | ~$16/year |
| Vector DB | Pinecone Serverless, 5M vectors | ~$50-100 |
| Reranking | Cohere Rerank, 5K queries/day | ~$50 |
| Observability | OpenTelemetry + logging | ~$100-200 |
| API Gateway + caching | Cloud infra | ~$200-500 |
| **Total** | | **$4,400-4,800/month** |
| **With GPT-4o-mini instead** | Same workload | **$600-1,000/month** |

**Ballpark Estimates (mid-size enterprise):**

| Scale | Documents | Daily Queries | Model Tier | Monthly Cost Range |
|-------|-----------|---------------|------------|-------------------|
| Small | ~10K | ~500 | Budget (Haiku/mini) | $100 - $500 |
| Small | ~10K | ~500 | Flagship (Sonnet/GPT-4o) | $500 - $2K |
| Medium | ~100K | ~5K | Budget (Haiku/mini) | $600 - $1.5K |
| Medium | ~100K | ~5K | Flagship (Sonnet/GPT-4o) | $3K - $8K |
| Large | ~1M+ | ~50K | Budget (Haiku/mini) | $5K - $15K |
| Large | ~1M+ | ~50K | Flagship (Sonnet/GPT-4o) | $15K - $60K |

**Architecture Decisions That Affect Cost:**

| Decision | Cost Impact | Detail |
|----------|-------------|--------|
| Chunk size (512 vs 2048 tokens) | ±50% on generation cost | Larger chunks = more context tokens per query. Must balance recall vs. cost. |
| Reranking | Net reduction if tuned well | Adds $2/1M tokens but reduces context from 10 chunks to 3 → fewer tokens to LLM |
| Semantic caching | 15-30% generation cost cut | Cache hit = skip LLM call entirely. Requires similarity threshold tuning. |
| Query routing (model selection) | 30-60% generation cost cut | Route simple factual queries to Haiku ($1/$5), complex analysis to Sonnet ($3/$15) |
| Quantization (PQ/BQ on vector DB) | 4-32x vector DB storage reduction | Binary Quantization: 32x compression, 2-5% recall loss. Recoverable via re-scoring. |
| Prompt caching (Anthropic/OpenAI) | 90% input cost on cache hits | Anthropic: cache reads at 0.1x base rate. OpenAI: cached input at 0.5x. |
| Batch API processing | 50% discount | For non-real-time workloads (eval, indexing, batch QA). |
| Self-hosted vLLM vs. API | 80-90% reduction at high volume | AWS H100 at $6.88/hr ≈ $5K/month. At 10M tokens/day, API would cost $50-150K/month. |

**Common Mistakes:**
- Only estimating infrastructure (vector DB, hosting) and ignoring token economics — the dominant cost.
- Assuming uniform query complexity. Analytical multi-hop queries cost 3-5x more than simple factual lookups.
- Not accounting for retrieval quality impact on cost. Bad retrieval → more context sent → more tokens → higher cost. "The cheapest token is the one you never send to the model."
- Ignoring Pinecone's per-RU billing at scale: a query against a 50GB namespace consumes 50 RUs regardless of top_k=1 or top_k=100. At high query volumes, self-hosted Qdrant on a $96/mo Droplet eliminates per-query billing entirely.
- Not enabling prompt caching. Anthropic cache reads cost 0.1x base rate — a 90% discount on repeated system prompts and instructions.
- Not modeling peak-to-average ratios. Production sees 3-5x peak-to-average. Budget on peak, not average.

**Interview Approach:** Break the answer into layers, state assumptions explicitly (query volume, model choice, context size), and walk through the token math with real pricing. Stakeholders want to see you understand *what drives cost* and can make trade-off decisions — not just a single number. Show the model selection impact: "If we use Haiku instead of Sonnet, generation drops from $4K to $1.3K/month. For this use case, Haiku quality is sufficient, so I recommend starting there and upgrading only if evaluation shows quality gaps."
