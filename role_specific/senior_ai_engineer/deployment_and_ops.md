# LLMOps & Deployment Playbook

## 1. GPU Sizing Math & Memory Bottlenecks

**Total VRAM = Model Weights + KV Cache**

**Model Weights (Fixed):**
- Formula: `Parameters (in billions) × Bytes per parameter`
- FP16/BF16: 2 bytes/param (70B model = 140 GB)
- INT8: 1 byte/param (70B model = 70 GB)
- INT4: 0.5 bytes/param (70B model = 35 GB)

**KV Cache (Dynamic):**
- The KV cache scales linearly with batch size and sequence length. For long-context workloads (e.g., 32k+ tokens), the KV cache can easily dwarf the model weights.
- **KV Cache Formula (bytes per token):** `2 (for K & V) × Number of Layers × Number of Attention Heads × Head Dimension × Bytes per parameter`
- Always budget for your *maximum* expected concurrent tokens across all active requests.
- **Overhead:** Always reserve a buffer (e.g., 2-4GB) for CUDA context and forward pass activations.

## 2. Inference Optimization

- **Continuous Batching:** Treats inference as an iterative process. As soon as one request finishes, the scheduler injects a new one into that slot. Increases throughput 2-4x over static batching.
- **PagedAttention (vLLM):** Manages KV cache memory like an OS manages RAM, reducing memory fragmentation from ~60-80% to <4%. Allows fitting much larger batches.

## 3. Deployment Strategies

- **Canary Deployments:** Route a small percentage (e.g., 5%) of production traffic to a new LLM version or prompt. Monitor token usage, latency, and error rates before full rollout.
- **Shadow Deployments:** Route a copy of production traffic to both the existing "stable" model and the "challenger" model. Only the stable model returns a response to the user. Compare outputs to validate the challenger safely.

## 4. Observability & Tracing

- **OpenTelemetry (OTel):** The universal standard for distributed tracing.
- **OpenInference:** Provides semantic conventions (standardized attributes) for AI-specific workloads on top of OTel.
  - Span kinds: `LLM`, `RETRIEVER`, `TOOL`, `GUARDRAIL`.
  - Captures token usage, model names, and retrieval similarity scores.
- **Data Governance:** Capturing full prompts helps debugging but creates PII risks. Implement redaction and sampling policies at the OTel Collector level.
- **Context Management:** Explicitly pass session-level context in agentic workflows so multi-turn conversations form a single logical trace.

## 5. Azure AI Foundry Deployment

### Project Structure & Setup

- **Foundry Project:** Logical container for models, connections, evaluations, and deployments. Created in Azure Portal or via Foundry SDK. Contains connections to: Azure AI Search (retrieval), Azure OpenAI (model inference), Azure Storage (artifacts), Key Vault (secrets).
- **Model Catalog:** 1800+ models available: GPT-4o, GPT-5, Claude, DeepSeek, Llama, Mistral, Phi, etc. Deploy as managed compute (pay-per-token) or provisioned throughput units (PTU — reserved capacity for predictable cost). Custom fine-tuned models can be registered and deployed the same way.
- **Connections:** Secure links to Azure resources. Use Managed Identity (not API keys) in production. Connections carry to Copilot Studio when integrating.

### Prompt Flow (Low-Code Orchestration)

- **DAG Structure:** Prompt Flows are directed acyclic graphs. Nodes: LLM calls, Python scripts, prompt templates, tool invocations, conditional branches. Edges: data flow between nodes.
- **Development Cycle:** Develop in VS Code (Prompt Flow extension) → test locally → evaluate in Foundry → deploy to Azure AI Foundry endpoint.
- **Versioning:** Each Flow run is versioned with parameters, inputs, and outputs logged. Enables reproducible evaluations and A/B testing between prompt variations.
- **Evaluation Integration:** Built-in eval runners: faithfulness, relevance, fluency, coherence. Connect to golden datasets for regression testing.

### Azure AI Search Index Operations

- **Index Creation:** Define schema via Azure Portal, REST API, or SDK. Key decisions: vector field dimensions, which fields are searchable/filterable/retrievable, similarity metric (cosine, dot-product, euclidean).
- **Ingestion:** Azure Document Intelligence extracts text/tables from PDFs → chunking → embedding generation (batch API for cost savings) → push to index. Supports incremental updates (partial document updates).
- **Hybrid Search Tuning:** `searchMode=hybrid` + `semanticConfiguration` for RRF merging. Tune `weight` parameter between BM25 and vector components (default 0.5/0.5). Enable semantic ranking only if it measurably improves relevance — it adds latency and cost.
- **RBAC Configuration:** Document-level access control via security filters (Entra ID group membership mapped to index metadata). Filter applied at query time BEFORE vector search.
- **Scaling:** Standard tier (1-3 replicas) for dev. Higher tiers for production with auto-scale. Monitor QPS, latency p99, and storage growth. vCore-based pricing for predictable cost; per-transaction pricing for variable workloads.

### Redshift Integration Patterns

- **Connection:** Boto3 / SQL Alchemy for Python. Use IAM authentication (not embedded credentials). Connection pooling via pg8000 or psycopg2.
- **NL2SQL Pipeline Deployment:**
  - Schema catalog: Stored in a JSON/YAML file, version-controlled in git, refreshed via cron
  - SQL validation: Parse generated SQL with sqlparse, check against whitelist of tables/columns, enforce LIMIT clauses, prevent DDL/DML mutations (SELECT only)
  - Timeout: Set query timeout to 5-10 seconds. Long-running queries → abort → return fallback message
  - Connection management: Pool of 5-10 connections; auto-reconnect on failure
- **Redshift Spectrum:** Configure external schema pointing to S3 buckets. Query PDF text or extracted tables stored as CSV/Parquet in S3 without loading into Redshift. Useful for joining structured warehouse data with semi-structured extraction results.
- **Cost Monitoring:** Track Redshift queries triggered by NL2SQL separately. Use Redshift query tags (SET QUERY_GROUP TO 'ai_agent') to attribute costs. Alert on query volume spikes (could indicate LLM generating expensive SQL).

### Copilot Studio Deployment

- **Agent Configuration:** Define topics (conversation flows), trigger phrases, and entity types in Copilot Studio. Connect to Azure AI Foundry agent via HTTP or MCP.
- **Testing:** Test in Copilot Studio canvas → validate in preview mode → publish to production channel (Teams, website, custom app).
- **Monitoring:** Copilot Studio analytics show session count, topic usage, escalation rate, and satisfaction scores. Use alongside Azure AI Foundry tracing for end-to-end observability.
- **Cost Model:** Pay-per-message (after 25,000 free messages/month for M365 Copilot license holders) or message pack subscription. Azure AI Foundry costs billed separately via Azure consumption.
- **Progressive Deployment:** Start with Copilot Studio for rapid prototyping → add Azure AI Foundry backend for complex RAG/multi-agent logic → use Foundry fine-tuned models via MCP for domain-specific accuracy.

### Production Checklist (Azure Stack)

- [ ] Managed Identity configured for all Azure connections (no API keys in code)
- [ ] Azure AI Search index schema validated: vector dimensions, filterable fields, retrievable fields
- [ ] Redshift NL2SQL pipeline has SQL whitelist, LIMIT enforcement, and timeout budgets
- [ ] Prompt Flow evaluation pipeline gates deployment in CI/CD
- [ ] Redshift query costs tracked separately from general warehouse queries
- [ ] Copilot Studio + Foundry integration tested end-to-end with fallback on HTTP failure
- [ ] AI Red Teaming scan run before production launch
- [ ] Azure Monitor alerts configured for: Azure AI Search latency p99 > 500ms, Redshift query timeouts > 5/min, Foundry model rate limits hit, Copilot Studio escalation rate > 10%
