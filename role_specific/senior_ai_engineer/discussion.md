# Senior AI Engineer

Designing, building, evaluating, and operating production-grade GenAI systems end-to-end — from RAG architecture and agentic workflows through deployment, observability, and team leadership.

> **Scope note**: This role builds on the foundations in [ML/AI Engineer](../ml_ai_engineer/). That section covers ML fundamentals, model training, and broad GenAI concepts. This section focuses exclusively on **production GenAI engineering** — the system design, evaluation, deployment, and operational discipline that senior interviews test hardest.

## Interview Structure

Senior AI Engineer interviews are increasingly structured around end-to-end system ownership rather than isolated model knowledge. A typical 3-round process:

| Round | Focus | Duration |
|-------|-------|----------|
| **Round 1: RAG & Agentic AI** | Retrieval architecture, agent design, evaluation metrics | 45-60 min |
| **Round 2: Hands-on & System Design** | API design, error handling, deployment, observability | 45-60 min |
| **Round 3: Leadership / Managerial** | Project deep dives, production strategy, evaluation frameworks | 45-60 min |

**Key takeaway**: Senior AI interviews test end-to-end AI system design, evaluation, deployment, and observability — not just prompting or model APIs.

---

## Round 1: RAG & Agentic AI

### Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Production RAG Architecture | End-to-end pipeline: ingestion, chunking, embedding, indexing, retrieval, reranking, generation, evaluation. Financial/regulated-domain constraints (audit trails, PII handling, access control) | Design a complete RAG system from scratch for a regulated domain; justify every component choice with latency, cost, and accuracy constraints |
| Multi-Hop & Cross-Document Retrieval | Query decomposition, iterative retrieval, evidence fusion across documents, RAPTOR hierarchical indexing, long-context vs RAG trade-offs | Architect retrieval for questions that require synthesizing information from 3+ documents; design the retrieval-evidence-feedback loop |
| Table Extraction & Graph RAG | Structured data extraction from tables (PDF, HTML), knowledge graph construction, graph-augmented retrieval, hybrid vector + graph queries | Design a RAG system that handles unstructured text, tables, and relationships; explain when Graph RAG outperforms flat vector retrieval |
| Adaptive Retrieval Strategies | Query routing (keyword vs semantic vs hybrid), query expansion (HyDE, multi-query), adaptive chunk size, retrieval result caching, retrieval quality scoring | Design a retrieval system that adapts strategy by query type; explain why one-size-fits-all retrieval fails in production |
| Agent Design & Orchestration | ReAct pattern, tool design and error contracts, multi-agent orchestration (e.g., Swarm vs Orchestrator-Worker), LangGraph state machines, Semantic Kernel agent framework (Azure AI Foundry), HITL approval gates, managing long-term vs short-term memory across agentic turns, checkpointing and pause/resume | Design a production agent with tool contracts, loop guards, and human approval points; architect multi-agent workflows with typed shared state while preventing deadlocks and isolating failure points |
| Azure AI Foundry & Azure AI Search | Azure AI Foundry as unified AI platform (1800+ model catalog, agent orchestration, evaluations, tracing, A/B testing), Azure AI Search as RAG retrieval engine (vector + keyword hybrid search, semantic ranking, document-level RBAC, vectorized indexes), Prompt Flow for low-code prompt orchestration, agentic retrieval (parallel subqueries, structured grounding data), index design and field configuration, semantic reranking | Design an end-to-end RAG pipeline on Azure AI Search + Azure AI Foundry; explain hybrid search with reciprocal rank fusion, configure RBAC at the index level, and set up agentic retrieval for multi-hop questions |
| Vector Database Internals | ANN indexing (HNSW, IVF, PQ), hybrid search (BM25 + dense vector), metadata filtering vs post-filtering, vector quantization (PQ/BQ for compression), index sizing, scaling patterns (Pinecone serverless per-RU vs Qdrant/Weaviate/vCore allocation vs self-hosted), pgvector for small-scale | Choose the right vector DB by workload (scale, query volume, cost model, latency); design index schema with metadata fields for pre-filtering; estimate storage and query costs; explain why Azure AI Search, Pinecone, or Qdrant fits a specific use case |
| Redshift as RAG Data Source | Amazon Redshift data warehouse as structured data source for RAG (SQL-to-text pipeline, Redshift ML for in-warehouse embeddings, Spectrum for S3-based unstructured data, federated queries to external sources), Redshift as the operational layer beneath an AI agent | Design a RAG system where the AI agent queries Redshift for structured data and a vector DB for unstructured data; explain how to bridge Redshift tables into the LLM context (NL2SQL, text-to-SQL, structured data grounding) |
| Unstructured Data Pipelines | PDF parsing (layout detection, table extraction, OCR for scanned docs), document classification, chunking strategies for heterogeneous content (text + tables + images + specs), metadata enrichment, data quality validation, ingestion pipeline design for factory/specs/engineering documents | Design an ingestion pipeline that processes PDF specs, factory manuals, and engineering documents into searchable chunks; handle tables, images, and formatting artifacts; validate extracted data quality before indexing |
| Microsoft Copilot Integration | Copilot Studio as frontend/orchestration layer, Copilot Studio + Azure AI Foundry integration (HTTP request, MCP connector, Foundry models as primary model), topic-based workflows vs developer-controlled flows, progressive maturity model (start Copilot Studio → scale to Foundry), cost model (pay-per-message vs Azure consumption), MCP (Model Context Protocol) as open standard for tool integration | Explain when to use Copilot Studio alone vs with Azure AI Foundry; design an architecture where Copilot Studio handles the conversational UI and Azure AI Foundry handles multi-agent orchestration and RAG retrieval; articulate the MCP integration pattern |
| Async Programming for AI Systems | Python asyncio, concurrent LLM calls, streaming responses, backpressure management, async tool execution, FastAPI async endpoints, connection pooling for AI services | Write production async code for parallel LLM calls and tool execution; explain when async helps vs hurts in AI pipelines |
| Retrieval & Generation Evaluation | RAGAS (faithfulness, context precision/recall, answer relevance), custom evaluation harnesses, golden sets, LLM-as-judge with debiasing, offline-to-online eval bridge | Design a complete evaluation pipeline for a RAG system; implement golden-set CI that gates deployments; explain why offline scores don't predict online behavior |

### Common Interview Topics — Round 1

- Design a RAG system for a financial services firm that handles 10-K reports, earnings call transcripts, and regulatory filings. Walk through chunking, retrieval, reranking, and evaluation.
- Your RAG system retrieves relevant chunks but the LLM still hallucinates facts not in the context. How do you diagnose and fix this?
- Design a multi-hop retrieval system that answers "How does Company X's revenue growth compare to Company Y's, and what drove the difference?" — a question requiring retrieval from multiple documents.
- When would you use Graph RAG instead of standard vector-based RAG? What types of questions does each handle better?
- Your financial RAG system needs to extract data from tables in PDF reports. Walk through your extraction pipeline and how you handle malformed tables.
- Design an adaptive retrieval system that routes queries to the best strategy (BM25, dense, hybrid, SQL lookup) based on query characteristics.
- Walk through your approach to evaluating a production RAG system end-to-end. What metrics do you track and how do you set up regression testing?
- Design a human-in-the-loop agent for a compliance review workflow. When does the agent act autonomously vs escalate to a human?
- Explain how you would build a multi-agent system using LangGraph with typed state, checkpointing, and conditional routing.
- Your retrieval system has 95% Recall@10 on your golden set but users report frequent hallucination. Where is the gap?
- Explain how you would decouple data extraction from text generation in a high-stakes RAG pipeline to mitigate hallucination.
- When would you choose a Multi-Agent Swarm over a single LLM with multiple tools? What are the trade-offs regarding context dilution and the Principle of Least Privilege?
- How do you manage long-term vs. short-term memory across multiple agentic turns?
- How do you handle async concurrent LLM calls in a production system? What happens when one call in a batch fails?
- Compare streaming vs batch response patterns for LLM applications. When does each make sense?
- Design a RAG pipeline on Azure AI Foundry + Azure AI Search for a manufacturing company with factory specs, PDF manuals, and engineering documents. Walk through ingestion, indexing, retrieval, and generation.
- Explain Azure AI Search hybrid search: how does it combine BM25 keyword search with vector similarity search? What is reciprocal rank fusion (RRF)?
- Compare Pinecone, Qdrant, Weaviate, and Azure AI Search as vector databases. When would you choose each?
- How would you design a RAG system where the AI agent needs to query both a Redshift data warehouse (structured data) and a vector database (unstructured documents)? Walk through the NL2SQL and retrieval integration.
- Design an ingestion pipeline for unstructured PDF documents containing tables, diagrams, and technical specs from a factory. How do you handle table extraction, OCR, and chunking?
- How would you integrate Microsoft Copilot with an Azure AI Foundry agent? Explain the HTTP Request and MCP Connector integration patterns.
- When would you use Copilot Studio alone vs Copilot Studio + Azure AI Foundry? What is the progressive maturity model?
- Your Azure AI Search index has 50M vectors and queries are taking 800ms. How do you optimize — index structure, quantization, caching, or architecture change?
- Design the evaluation harness for a RAG system that must gate production deployments. What goes into CI vs what requires human review?

---

## Round 2: Hands-on & System Design

### Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| FastAPI & Pydantic | Async endpoints, request/response validation, dependency injection, middleware, structured error responses, Pydantic models for LLM I/O contracts | Design a production FastAPI service wrapping LLM calls with proper validation, error handling, and streaming support |
| Retry Logic, Timeouts & Error Handling | Exponential backoff with jitter, circuit breakers, timeout budgets, idempotency, structured error contracts for LLM API calls, graceful degradation | Implement robust error handling for LLM API calls that handles rate limits, timeouts, malformed responses, and partial failures |
| MLflow for Experiment Tracking | Experiment and run management, parameter/metric logging, model registry, prompt versioning, evaluation tracking, artifact storage | Design an experiment tracking workflow for prompt engineering, RAG configuration, and model comparison; integrate MLflow into a CI/CD pipeline |
| Serverless vs Kubernetes Deployments | Cold starts, scaling characteristics, cost models, GPU provisioning, model serving patterns (vLLM, Triton), container orchestration, inference optimization | Choose and justify deployment strategy by workload pattern (bursty vs steady, latency requirements, cost constraints); size GPU clusters |
| LangGraph Concepts | ReAct pattern, reducers and state aggregation, state machines with TypedDict, conditional edges, checkpointing, streaming, human-in-the-loop integration, subgraphs | Design a LangGraph workflow for a production multi-step agent; implement reducers for state aggregation; architect pause/resume with checkpoints |
| Guardrails & Safety | Multi-layered content filtering, input filtering (prompt injection detection), output moderation, deterministic rule-based checks | Design a safety layer for production AI systems that guarantees deterministic compliance while minimizing latency overhead |
| Observability & Tracing | OpenTelemetry + OpenInference, span kinds (LLM, RETRIEVER, TOOL, GUARDRAIL), trace waterfalls, cost/token attribution, latency SLOs (TTFT, ITL), alerting, agentic metrics (success rate, tool usage distribution, step-by-step latency) | Design a complete observability stack for an LLM application; implement distributed tracing across retrieval, generation, and tool execution; build agentic observability |
| Azure AI Foundry Deployment | Foundry project structure, model catalog (1800+ models including GPT, Claude, DeepSeek, Llama), Prompt Flow (low-code prompt orchestration with DAGs), Azure AI Search index creation and management, Foundry SDK/REST API for custom RAG apps, agent deployment with Semantic Kernel, AI Red Teaming for safety evaluation, A/B testing and evaluations in Foundry | Deploy a complete RAG application on Azure AI Foundry; configure Prompt Flow for prompt orchestration; set up Azure AI Search as the retrieval engine with hybrid search; deploy and evaluate an agent |
| Redshift + AI Integration | Redshift as the structured data backbone for AI systems, NL2SQL pipelines (text-to-SQL with LLM), Redshift ML for in-warehouse model inference, Spectrum for querying S3-based unstructured data, federated queries to join Redshift tables with external vector stores, Redshift as operational layer for AI agent tool calls | Design a system where an AI agent queries Redshift via NL2SQL for structured data and Azure AI Search for unstructured data; explain the dual-retrieval pattern |
| Copilot Studio + Azure AI Foundry Integration | MCP (Model Context Protocol) as open standard for LLM-tool connectivity, Copilot Studio HTTP Request integration with Foundry agents, Foundry models as primary model for Copilot Studio, progressive maturity model (Copilot Studio → Foundry), cost model comparison (pay-per-message vs Azure consumption), topic-based workflows vs pro-code orchestration | Architect an enterprise AI solution using Copilot Studio as the conversational frontend with Azure AI Foundry as the backend for RAG retrieval and multi-agent orchestration |

### Common Interview Topics — Round 2

- Design a FastAPI service that wraps multiple LLM providers with fallback logic, streaming support, and request validation via Pydantic.
- Walk through your error handling strategy for a production LLM API wrapper. How do you handle rate limits, timeouts, malformed JSON, and provider outages?
- How would you use MLflow to track prompt experiments, RAG configurations, and model performance across iterations?
- Compare serverless (AWS Lambda, Cloud Run) vs Kubernetes for deploying an LLM application. What are the trade-offs for each?
- Design a LangGraph workflow for a document processing agent that extracts structured data, validates it, and escalates edge cases to humans.
- Explain LangGraph reducers. How do you aggregate state from multiple parallel tool calls in a single graph node?
- Design the observability stack for a production RAG system serving 10K daily users. What traces, metrics, and alerts do you need?
- Walk through implementing distributed tracing for an LLM chain that calls a retriever, reranker, LLM, and tool executor. What span attributes matter?
- How do you size a GPU cluster for serving a 70B model at 100 QPS? Walk through the math for weights, KV cache, and concurrent requests.
- Your p99 latency doubled after a deploy but HTTP error rate is 0%. Walk through debugging using traces.
- Design a canary deployment strategy for a prompt template change. What gates must pass before full rollout?
- How do you track cost per tenant in a multi-tenant LLM platform? Handle reasoning tokens that are billed but hidden?
- Explain the prefill/decode distinction and why continuous batching is critical for production LLM serving.
- How do you implement multi-layered content filtering (input filtering, output moderation, deterministic rule-based checks) to ensure production safety?
- What metrics do you track for an agentic system (e.g., success rate, tool usage distribution, step-by-step latency) to monitor reliability?
- Design a Prompt Flow in Azure AI Foundry that orchestrates a RAG pipeline with parallel retrieval and conditional branching. What does the DAG look like?
- Your RAG system uses Azure AI Search with 10M vectors. Queries are returning irrelevant results for technical spec queries but work well for general questions. How do you diagnose — is it chunking, embedding, or search configuration?
- Design an NL2SQL pipeline that translates a natural language question into a Redshift query, executes it, and feeds results into an LLM for synthesis. How do you handle SQL injection, complex joins, and ambiguous column names?
- How would you set up Azure AI Foundry evaluations for a production RAG agent? What automated checks gate a deployment?
- Walk through the architecture for a Copilot Studio + Azure AI Foundry integration where Copilot Studio handles the conversational UI and Azure AI Foundry provides RAG retrieval and multi-agent orchestration via MCP.
- Your AI agent needs to query Redshift (production metrics), Azure AI Search (factory spec documents), and a REST API (weather data). Design the tool orchestration and query routing.

---

## Round 3: Leadership / Managerial

### Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Project Deep Dives | Articulating technical decisions and trade-offs (e.g., latency vs. accuracy), quantifying impact (latency, cost, accuracy), explaining what went wrong and what you learned, handling nuances and acknowledging imperfections, cross-functional collaboration stories | Present 2-3 projects end-to-end with clear problem statement, architecture decisions, metrics, and lessons learned; handle deep follow-up questions on any component |
| Infrastructure over Models | Designing for production reliability, governability, and system maintainability rather than just using the newest foundational model, mitigating regressions in agentic workflows | Advocate for investing in reliable infrastructure and guardrails; demonstrate how a solid system design outlasts specific LLM versions |
| Production Deployment Strategy | Shadow deployments, canary rollouts, A/B testing for ML/LLM, model versioning, prompt versioning, rollback mechanisms, deployment automation, SLO design | Design a full deployment lifecycle (shadow -> canary -> A/B -> rollout) for an LLM application; implement automated rollback on SLO violation |
| Evaluation Frameworks | Golden sets and regression CI, offline vs online evaluation, LLM-as-judge protocols with debiasing, human evaluation pipelines, cost-quality trade-off curves, evaluation-first development | Design an evaluation framework that gates all production changes; argue for evaluation as a first-class engineering concern, not an afterthought |
| Monitoring & Observability Strategy | Metric hierarchy (infra -> data -> model -> product), SLO design and error budgets, alerting strategy (page vs dashboard), anomaly detection for LLM outputs, drift detection, incident response playbooks | Design a monitoring strategy that covers the full LLM application stack; distinguish what to page on vs dashboard; architect drift detection for RAG systems |
| Technical Leadership & Mentoring | Code review standards for AI/ML code, establishing evaluation culture, documentation practices, on-call design for AI systems, cross-team collaboration (platform, product, data), hiring and interviewing | Describe how you would establish AI engineering standards on a team; design on-call rotations for LLM applications; explain how you mentor junior AI engineers |
| Stakeholder Communication | Translating model performance to business metrics, managing expectations on LLM capabilities and limitations, cost-benefit analysis of AI investments, risk communication (hallucination, bias, security) | Present a technical AI decision to a non-technical audience; justify infrastructure investment with cost-per-request math; communicate model limitations honestly |

### Common Interview Topics — Round 3

- Walk me through the most complex AI system you have built end-to-end. What were the hardest technical decisions?
- Tell me about a time an AI system you deployed failed in production. What happened, how did you respond, and what did you change?
- How do you decide when to use an LLM vs a traditional ML model vs a rules-based approach for a new feature?
- Describe your evaluation framework for a production LLM application. How do you ensure quality doesn't regress?
- How would you design the deployment pipeline for a new RAG system going to production for the first time?
- Your team wants to upgrade from GPT-4 to a new model. How do you evaluate and safely roll out the change?
- How do you handle the cost-quality trade-off when serving LLM applications at scale? Walk through your decision framework.
- Describe how you would set up monitoring and alerting for a production AI system. What metrics do you track and what triggers a page?
- How do you communicate model limitations and risks to product managers and executives?
- Tell me about a time you had to push back on a stakeholder request that was technically unsound.
- How do you mentor junior engineers on AI system design? What are the most common mistakes you see?
- Design an on-call rotation for a team that owns 3 production LLM applications. What runbooks do you need?
- Your LLM application's cost doubled this month. Walk through your investigation and optimization approach.
- How do you balance shipping fast with maintaining evaluation rigor?
- How do you advocate for investing in reliable infrastructure and guardrails when stakeholders just want to "use the newest LLM"?
- Tell me about a time you had to debug and fix an infinite loop or deadlock in a multi-agent workflow in production.

---

## Key Terminology

### RAG & Retrieval

- **Graph RAG** -- Retrieval-augmented generation enhanced with knowledge graph traversal; entities and relationships extracted from documents form a graph, enabling multi-hop reasoning across connected concepts that flat vector retrieval cannot capture
- **Adaptive Retrieval** -- Query routing system that selects retrieval strategy (BM25, dense, hybrid, SQL, graph) based on query classification; avoids one-size-fits-all retrieval that underperforms on specialized query types
- **Multi-Hop Retrieval** -- Iterative retrieval where the answer to one retrieval informs the next query; required when no single document contains the complete answer and evidence must be synthesized across sources
- **Cross-Document Retrieval** -- Retrieval and fusion of evidence from multiple documents to answer comparative or analytical questions; requires evidence tracking, deduplication, and conflict resolution
- **Table Extraction Pipeline** -- OCR + layout detection + cell parsing + header inference for extracting structured data from tables in PDFs and images; significantly harder than text extraction due to merged cells, spanning headers, and implicit relationships
- **RAPTOR** -- Recursive Abstractive Processing for Tree-Organized Retrieval; builds a tree of summaries over a corpus enabling retrieval at multiple abstraction levels, critical for broad thematic questions
- **HyDE (Hypothetical Document Embeddings)** -- Query expansion technique where an LLM generates a hypothetical answer, which is then embedded for retrieval; closes the query-document vocabulary gap but can hurt when the LLM's hypothesis is misleading
- **Query Decomposition** -- Breaking complex multi-hop questions into sub-queries, retrieving for each independently, then synthesizing; required for analytical questions spanning multiple documents
- **Context Window Strategy** -- Decision matrix between long-context models (stuff all docs, simple but expensive), RAG (retrieve relevant chunks, cheaper but requires pipeline), and hybrid (RAG + long context for top chunks)
- **Position-Aware Context Assembly** -- Ordering retrieved chunks to mitigate lost-in-the-middle effect; most-relevant chunks at the end (recency bias), system prompt at beginning, supporting context in the middle
- **RAGAS** -- Retrieval Augmented Generation Assessment: faithfulness (claims supported by context), context precision/recall, answer relevance; default evaluation framework for RAG systems
- **Golden Set CI** -- Fixed list of non-negotiable test cases with frozen prompts and expected outputs checked into git; the actual ship gate for production deployments, not public benchmarks
- **Offline-to-Online Eval Gap** -- Offline evaluation scores (RAGAS, LLM-as-judge) do not reliably predict production user satisfaction; bridge with shadow traffic evaluation and online A/B testing

### Agent & Agentic Systems

- **ReAct Pattern** -- Reason+Act+Observe loop: LLM reasons about state, selects tool with structured arguments, executes tool, observes result, repeats. Catches wrong assumptions early rather than executing stale plans
- **Human-in-the-Loop (HITL)** -- Agent architecture where certain actions require human approval before execution; implemented via checkpointing (pause workflow, await human input, resume). Required for actions with irreversible side effects
- **LangGraph State Machine** -- Production framework modeling agent workflows as directed graphs with typed TypedDict state; advantages: explicit inspectable state, cycles for iterative loops, built-in checkpointing, streaming intermediate steps
- **LangGraph Reducers** -- Functions that define how state updates are aggregated; e.g., `Annotated[list, add]` appends to list instead of replacing. Critical for parallel tool calls that each contribute partial state
- **Orchestrator-Worker Pattern** -- One coordinator LLM decomposes tasks into sub-tasks, routes to specialist workers, synthesizes results. Orchestrator uses best model; workers can be cheaper. Workers return structured outputs and are stateless
- **Tool Error Contract** -- Structured error from tools: error_code (machine-readable), error_message (human-readable), recoverable (boolean), retry_after_sec. Three error classes: transient (retry), correctable (let model repair), terminal (escalate)
- **Agent Loop Detection** -- Hash (tool, normalized_args) at each step; if same failing call repeats 3+ times, abort with diagnostic. Cap retries at 3 to prevent runaway cost
- **Checkpointing** -- Persisting agent state at each graph node execution enables pause/resume workflows; required for HITL patterns where workflow waits for human input
- **PEARL Framework** -- Decision framework for agent architecture: Problem (dynamic actions, side effects, latency), Engineering (chain vs ReAct vs graph), Accuracy (task + trajectory), Reliability (loops, auth, injection), Latency/Cost (turns, fan-out)

### Production Engineering

- **FastAPI Async Endpoints** -- `async def` endpoints that don't block the event loop during I/O-bound LLM calls; critical for high-concurrency LLM serving where each request involves network calls to model APIs
- **Pydantic Validation for LLM I/O** -- Typed models that validate LLM inputs/outputs at the API boundary; catches malformed prompts and responses before they propagate through the system. Combined with structured output enforcement
- **Exponential Backoff with Jitter** -- Retry strategy for LLM API rate limits: wait time = base * 2^attempt + random_jitter. Jitter prevents thundering herd when many clients retry simultaneously after a rate limit reset
- **Circuit Breaker** -- Failure detection pattern that stops calling a degraded LLM provider after N consecutive failures; trips open (fail fast), half-open (probe with one request), closed (normal). Prevents cascading latency
- **Timeout Budgets** -- Decomposing end-to-end latency SLA into per-component budgets: retrieval < 200ms, reranking < 100ms, LLM generation < 2s, tool execution < 5s. If any component exceeds budget, skip or fallback
- **MLflow Experiment Tracking** -- Logging prompt versions, model configurations, retrieval parameters, and evaluation metrics as experiments; enables reproducible comparison across prompt iterations and RAG configurations
- **Model Registry** -- Centralized versioning of fine-tuned models, embedding models, and rerankers; tracks which model version is deployed to which environment. Critical for rollback
- **vLLM PagedAttention** -- Treats KV cache like virtual memory pages, allocated on demand, eliminating GPU memory fragmentation. Increases concurrent request capacity from ~5 to ~100 on same hardware
- **Continuous Batching** -- Iteration-level scheduling: replace finished sequences with waiting requests after each decode step. 5-10x throughput improvement over static batching at variable request lengths
- **Serverless Cold Starts** -- Model loading latency (seconds to minutes for large models) when serverless containers scale from zero; mitigated by provisioned concurrency, model caching, or keeping warm instances
- **GPU Sizing Math** -- Model weights (params x bytes_per_param) + KV cache (2 x layers x kv_heads x d_k x seq_len x 2) + overhead. Llama-3-70B in BF16: 140GB weights + ~2.5GB KV per 8K request. A100-80G fits model + ~10 concurrent requests
- **TTFT (Time to First Token)** -- Latency from request to first generated token; dominated by prefill (processing all input tokens). Target: < 1s for interactive chat. Critical SLO for user experience
- **ITL (Inter-Token Latency)** -- Time between generated tokens after the first; dominated by decode memory bandwidth. Target: < 50ms. Formula: model_size / memory_bandwidth

### Observability

- **OpenInference Span Kinds** -- LLM-specific extension of OpenTelemetry: LLM, EMBEDDING, RETRIEVER, RERANKER, TOOL, AGENT, GUARDRAIL, EVALUATOR. Required attributes: llm.system, llm.model_name, llm.token_count.prompt/completion
- **Trace Waterfall** -- Visual representation of a multi-step LLM chain showing timing for each span (retrieval -> reranking -> generation -> tool execution); reveals where latency accumulates
- **Cost Attribution** -- Propagating tenant_id and user_id as trace-level attributes; query sum by tenant of llm_cost_usd for billing dashboards. Four-tier budgets: API key, team, customer, provider
- **Burn Rate Alerts** -- SLO burn rate measures how fast error budget is consumed; page on JSON parse failure burn rate > 14.4x in 1h, TTFT p99 > 2x baseline for 30min
- **Judge Drift** -- LLM-as-judge scores drift over time as judge model updates or prompt changes shift scoring; fix by anchoring to frozen reference set and tracking delta from baseline
- **Prompt Versioning** -- Treating prompt templates as code: version in git, CI checks on changes, canary deployments for prompt updates. Anti-pattern: editing prompts in-place in production
- **Shadow Deployment** -- Running new model/prompt on real traffic without serving results to users; compare outputs against production version. Zero user impact, catches distribution shifts before canary
- **Canary Deployment** -- Routing 1-5% of traffic to new model/prompt with automated rollback on error rate > 1% or latency > 2x baseline. First real-user validation after shadow passes
- **SLO Error Budget** -- Allowed failures per time window (e.g., 99.9% availability = 43.2 min/month downtime). Burns down with each incident; when exhausted, freeze deploys and focus on reliability

### Async Programming

- **asyncio Event Loop** -- Single-threaded cooperative multitasking; ideal for I/O-bound AI workloads (LLM API calls, DB queries, file I/O) where tasks spend most time waiting. NOT for CPU-bound work (use ProcessPoolExecutor)
- **Concurrent LLM Calls** -- `asyncio.gather(*[call_llm(prompt) for prompt in prompts])` for parallel requests; critical for batch evaluation, multi-query retrieval, and parallel tool execution. Handle partial failures with `return_exceptions=True`
- **Streaming Responses** -- Server-Sent Events (SSE) or WebSocket streaming of LLM tokens; reduces perceived latency from "wait for full response" to "see first token in ~100ms". Requires async generators
- **Backpressure** -- Flow control when downstream (LLM API) is slower than upstream (user requests); implement via semaphores (limit concurrent in-flight requests) and queue depth monitoring
- **Connection Pooling for AI Services** -- Reusing HTTP connections to LLM provider APIs (aiohttp ClientSession); avoids TCP handshake overhead per request. Pool size should match concurrency limits

### Azure AI Foundry & Ecosystem

- **Azure AI Foundry** -- Unified Azure platform for building AI apps and agents: 1800+ model catalog (GPT, Claude, DeepSeek, Llama, etc.), Prompt Flow (low-code prompt orchestration), agent framework (Semantic Kernel), evaluations, tracing, A/B testing. No platform charge; consumption-based billing for model usage. Replaced Azure OpenAI Service as the primary developer surface.
- **Azure AI Search** -- Microsoft's managed search service with vector + keyword hybrid search, semantic ranking, document-level RBAC, and vectorized indexes. Recommended retrieval engine for RAG on Azure. Supports RRF (Reciprocal Rank Fusion) for combining BM25 and vector scores. Index fields: vector fields (embeddings), searchable text fields, filterable metadata fields, retrievable content fields.
- **Prompt Flow** -- Azure AI Foundry's low-code tool for building LLM workflows as DAGs (directed acyclic graphs). Nodes represent steps (prompt templates, Python code, LLM calls, tool invocations); edges represent data flow. Enables rapid prompt engineering iteration with versioning and evaluation.
- **Agentic Retrieval** -- Azure AI Foundry's evolution of RAG: the model breaks complex queries into parallel subqueries, executes them simultaneously against Azure AI Search, and returns structured grounding data with citations. Context-aware query planning leverages conversation history. Built-in semantic ranking ensures relevance.
- **MCP (Model Context Protocol)** -- Open standard for LLM-tool connectivity. Provides model-agnostic interface for reading files, executing functions, and handling contextual prompts. Both Copilot Studio (MCP Connector tool) and Azure AI Foundry (via Agent Service, SDK, REST API) support MCP. Enables standardized integration with enterprise systems.
- **Copilot Studio + Foundry Integration** -- Three integration patterns: (1) HTTP Request: Copilot Studio triggers Foundry agents via HTTP, (2) MCP Connector: standardized tool integration, (3) Foundry Models as Primary Model: Copilot Studio agents use any Foundry catalog or custom fine-tuned model as their LLM. Progressive maturity: start Copilot Studio, scale to Foundry.
- **Semantic Kernel** -- Open-source toolkit (Microsoft) for building AI agents. Azure AI Foundry's agent framework extends Semantic Kernel for multi-agent orchestration. Agents coordinate with reduced boilerplate; supports typed plugins, planning, and memory. Used by KPMG, Fujitsu for enterprise agent orchestration.
- **AI Red Teaming Agent** -- Azure AI Foundry's automated safety testing agent (public preview). Systematically probes AI models using Microsoft Security's PyRIT framework. Generates comprehensive safety reports, tracks improvements over time. Addresses the gap where 50%+ of businesses still manually evaluate AI (per MIT Technology Review).
- **Reciprocal Rank Fusion (RRF)** -- Algorithm for combining ranked result lists from different retrieval strategies (BM25 + vector). Formula: score(d) = sum over queries of 1/(k + rank_i(d)), where k=60 typically. RRF is query-agnostic (no score normalization needed) and handles heterogeneous scoring scales.

### Vector Database Architecture

- **HNSW (Hierarchical Navigable Small World)** -- Graph-based ANN algorithm. Builds a multi-layer navigable graph; search starts at the top layer and greedily descends. High recall (95%+ @ top-10), fast queries, but high memory usage (~2x raw vectors). Used by Qdrant, Weaviate, Azure AI Search, pgvector.
- **IVF (Inverted File Index)** -- Clusters vectors into Voronoi cells via k-means. Search probes N closest clusters then scans within. Lower memory than HNSW, tunable recall via nprobe. Used by FAISS, Milvus.
- **PQ (Product Quantization)** -- Compresses vectors by decomposing into sub-vectors and quantizing each to a codebook. 8-32x compression with 2-5% recall loss. Always recovered via re-scoring against full vectors. Essential for cost control at scale.
- **BQ (Binary Quantization)** -- Converts each float dimension to a single bit (0 or 1). 32x compression, 2-5% recall loss. Fastest distance computation (Hamming distance via XOR + popcount). Available in Weaviate and Qdrant.
- **Hybrid Search Architecture** -- Runs BM25 (keyword) and vector search in parallel, merges with RRF. Requires an index that stores both text and vector fields. Azure AI Search, Pinecone, and Weaviate all support this natively. Key advantage: captures exact-match queries that pure vector search misses.
- **Metadata Pre-filtering** -- Applying hard filters (tenant_id, role, date) BEFORE vector search. Critical for RBAC: never retrieve then filter. Azure AI Search supports filterable fields natively. Post-filtering wastes compute on irrelevant vectors.
- **pgvector** -- PostgreSQL extension adding vector similarity search (HNSW, IVF). Best for <5M vectors when you already run Postgres. Zero incremental cost. Supports hybrid search via Postgres full-text search + vector queries in SQL.

### Redshift & Structured Data for AI

- **NL2SQL (Natural Language to SQL)** -- Pipeline: user question → LLM generates SQL → execute on Redshift → feed results into LLM for synthesis. Requires schema-aware prompting (table/column descriptions), SQL validation (syntax + safety), and result formatting. Handles structured data queries that RAG cannot.
- **Redshift Spectrum** -- Query data in S3 (including unstructured/text files) directly from Redshift SQL without loading into tables. Enables joining warehouse data with S3-based documents/samples. Useful for bridging structured and semi-structured data.
- **Redshift ML** -- Run ML models (including embeddings) directly in Redshift using SQL. CREATE MODEL statements train in-warehouse; PREDICT functions score. Avoids data movement for embedding generation on structured text columns.
- **Dual Retrieval Pattern** -- AI agent routes queries to two backends: (1) Azure AI Search / Vector DB for unstructured documents (PDFs, specs, manuals), (2) Redshift via NL2SQL for structured metrics (KPIs, production data, financials). LLM synthesizes both result sets. Requires query classifier to determine which backend(s) to query.
- **Federated Query** -- Redshift can query external sources (Postgres, MySQL, S3 via Spectrum). In AI context, enables joining Redshift operational data with vector similarity results from external stores without materializing vectors in Redshift.

### Unstructured Data Processing

- **Layout Detection** -- Identifying document structure elements (paragraphs, headings, tables, images, footers) before extraction. Critical for factory/engineering specs where layout conveys meaning (e.g., spec tables, assembly diagrams). Tools: Azure Document Intelligence, unstructured.io, Tesseract + custom parsers.
- **Table Extraction Pipeline** -- OCR + layout detection + cell parsing + header inference for extracting structured data from tables in PDFs. Challenging for merged cells, spanning headers, and implicit relationships. Extracted tables can be stored in Redshift for SQL querying or embedded as structured chunks for vector retrieval.
- **Semantic Chunking** -- Splitting documents at natural boundaries (sections, paragraphs, table boundaries) rather than fixed token windows. Produces more coherent chunks for retrieval. Requires document structure understanding (headings, lists, table captions) rather than naive sliding window.
- **Data Quality Validation** -- Validating extracted content before indexing: completeness checks (are all tables extracted?), format checks (is the chunk well-formed?), PII detection, language detection, encoding normalization. Bad chunks in = bad retrieval out — garbage in, garbage out applies to RAG.

---

## Cross-References

### Prerequisite Knowledge

- **ML/AI Engineer**: [Core competencies](../ml_ai_engineer/) — ML fundamentals, LLM architecture, fine-tuning, embeddings, tokenization. This section assumes fluency with these concepts.

### System Design

- **System Design**: [Distributed Cache](../../system_design/distributed_cache/) — caching strategies for RAG retrieval results and embedding caches
- **System Design**: [Rate Limiter](../../system_design/rate_limiter/) — protecting LLM API endpoints and managing provider rate limits
- **System Design**: [News Feed](../../system_design/news_feed/) — ranking pipelines relevant to recommendation and retrieval systems
- **System Design**: [Notification Service](../../system_design/notification_service/) — event-driven architecture patterns applicable to async AI pipelines

### CS Fundamentals

- **CS Fundamentals**: Networking (HTTP/2 for streaming, SSE, WebSocket) and Operating Systems (async I/O, event loops, process vs thread concurrency models)

### Production Engineering

- **Production Engineering**: Deployment strategies, monitoring, incident response, SLO design — directly applicable to LLM application operations

### AI-Assisted Interview Scenarios

- **AI Assisted**: [Scenarios](../../ai_assisted/) — practical exercises that combine system design with AI tooling

### Platform-Specific Knowledge

- **Azure AI Foundry**: Azure AI Search (hybrid search, vector indexes, semantic ranking), Prompt Flow (DAG-based prompt orchestration), Semantic Kernel (agent framework), Copilot Studio (conversational AI frontend), MCP (Model Context Protocol for tool integration). Primary enterprise AI platform for Microsoft-ecosystem clients (Singapore financial/enterprise sector).
- **AWS Alternatives**: Amazon Bedrock (model catalog), Redshift (structured data warehouse), OpenSearch (vector search), SageMaker (model training). Equivalent alternatives when not on Azure.
- **Vector DB Landscape**: Pinecone (serverless, per-RU billing), Qdrant (self-hosted or cloud), Weaviate (cloud or self-hosted), pgvector (Postgres extension), ChromaDB (local/embedded). Choice depends on scale, cost model, latency requirements, and existing infrastructure.
