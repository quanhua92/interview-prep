# Senior AI Engineer -- Prep Checklist

Use this checklist to track preparation for a Senior AI Engineer interview focused on production-grade GenAI systems. Assumes fluency with ML fundamentals and LLM basics (see [ML/AI Engineer](../ml_ai_engineer/)).

## Topic Prep Checklist per Competency

### Round 1: RAG & Agentic AI

- [ ] **Production RAG Architecture**: Design end-to-end RAG pipelines for regulated domains (financial, healthcare, legal). Practice chunking strategy selection, embedding model comparison, ANN index sizing, reranking pipeline design, and evaluation. Include hallucination mitigation by decoupling extraction from generation.
- [ ] **Multi-Hop & Cross-Document Retrieval**: Practice query decomposition, iterative retrieval, and evidence synthesis across multiple documents. Be ready to design systems for comparative and analytical questions.
- [ ] **Table Extraction & Graph RAG**: Review PDF table extraction pipelines (OCR, layout detection, cell parsing). Understand when knowledge graph construction adds value over flat vector retrieval. Practice designing hybrid vector + graph systems.
- [ ] **Adaptive Retrieval Strategies**: Design query routing systems that select between BM25, dense, hybrid, SQL, and graph retrieval. Practice HyDE, multi-query expansion, and adaptive chunk sizing. Know when each strategy wins.
- [ ] **Agent Design & Orchestration**: Design production agents with tool error contracts, loop detection, and HITL approval gates. Practice LangGraph state machines with typed state, reducers, and checkpointing. Prepare to discuss trade-offs between Multi-Agent Swarms vs. Single LLM with tools (e.g., context dilution, isolating failures).
- [ ] **State & Memory Management**: Design long-term vs short-term memory mechanisms across multiple agentic turns to prevent context overflow while maintaining conversational context.
- [ ] **Async Programming**: Review Python asyncio patterns for AI systems — concurrent LLM calls with `asyncio.gather`, streaming with async generators, backpressure via semaphores, connection pooling with aiohttp.
- [ ] **Retrieval & Generation Evaluation**: Design complete evaluation pipelines with RAGAS, golden sets, LLM-as-judge with debiasing, and offline-to-online evaluation bridges. Practice implementing golden-set CI.

### Round 2: Hands-on & System Design

- [ ] **FastAPI & Pydantic**: Build a FastAPI service wrapping LLM calls with async endpoints, Pydantic request/response validation, streaming support, and middleware for logging/tracing.
- [ ] **Guardrails & Safety**: Implement multi-layered content filtering (input filtering, output moderation, deterministic rule-based checks) to ensure production safety and mitigate prompt injection/jailbreaking.
- [ ] **Retry Logic & Error Handling**: Implement exponential backoff with jitter, circuit breakers, timeout budgets, and graceful degradation for LLM API calls. Know the three error classes: transient, correctable, terminal.
- [ ] **MLflow Experiment Tracking**: Design experiment tracking for prompt engineering, RAG configuration comparison, and model evaluation. Practice integrating MLflow into CI/CD for reproducible experiments.
- [ ] **Deployment Strategy**: Compare serverless vs Kubernetes for LLM serving by workload pattern. Practice GPU cluster sizing (weights + KV cache math). Know vLLM, continuous batching, and quantization trade-offs. Address system scalability and cost optimization (latency vs. API costs) in iterative agentic calls.
- [ ] **LangGraph**: Build LangGraph workflows with ReAct pattern, reducers for state aggregation, conditional edges, checkpointing, and HITL integration. Practice subgraph composition to prevent deadlocks in multi-agent workflows.
- [ ] **Observability & Tracing**: Design observability stacks with OpenTelemetry + OpenInference. Practice implementing distributed tracing across retrieval, generation, and tool execution. Track agentic-specific metrics like success rate, tool usage distribution, and step-by-step latency.

### Round 3: Leadership / Managerial

- [ ] **Project Deep Dives**: Prepare 2-3 detailed project "war stories" covering: problem statement, architecture decisions, trade-offs (e.g., latency vs. accuracy), metrics/impact, failures, and lessons learned. Practice explaining any component in depth and acknowledging nuances.
- [ ] **Infrastructure over Models**: Demonstrate a mindset that prioritizes the reliability, governability, and surrounding infrastructure of the AI system over just selecting the latest foundation model.
- [ ] **Production Deployment Strategy**: Design full deployment lifecycle (shadow -> canary -> A/B -> rollout) for LLM applications. Know prompt versioning, model versioning, and automated rollback on SLO violation. Be prepared to discuss handling regressions.
- [ ] **Evaluation Frameworks**: Design evaluation frameworks that gate all production changes. Practice arguing for evaluation-first development. Know cost-quality trade-off curves and when to invest in evaluation vs shipping.
- [ ] **Monitoring & Observability Strategy**: Design monitoring across the full LLM stack (infra -> data -> model -> product). Practice distinguishing page vs dashboard signals. Know drift detection for RAG systems, debugging agentic loops, and incident response playbooks.
- [ ] **Technical Leadership**: Prepare stories about code review standards, establishing evaluation culture, on-call design for AI systems, and cross-team collaboration. Know common failure patterns in AI engineering teams.
- [ ] **Stakeholder Communication**: Practice translating model performance to business metrics, managing expectations on LLM limitations, and presenting cost-benefit analyses for AI investments.

## Practice Questions

### Round 1 Questions

1. Design a RAG system for a hedge fund that needs to answer questions across 10-K filings, earnings transcripts, and SEC filings. Walk through chunking, embedding, retrieval, reranking, generation, and evaluation.
2. Your RAG system returns relevant chunks but the LLM still hallucinates. Walk through your diagnostic: is it a retrieval problem, context assembly problem, or generation problem? How do you isolate the failure?
3. Design a multi-hop retrieval system that answers "Compare the AI strategy of Microsoft and Google based on their latest earnings calls." What sub-queries do you decompose? How do you merge evidence?
4. When would you use Graph RAG over standard vector RAG? Give a concrete example where graph traversal is necessary.
5. Your financial RAG system needs to extract and query data from tables in PDF reports. Design the extraction pipeline and how extracted tables integrate into retrieval.
6. Design an adaptive retrieval router. What signals determine whether a query goes to BM25, dense search, SQL, or graph traversal? What classifier do you use?
7. Design a HITL agent for compliance document review. When does the agent act autonomously vs escalate? How do you implement the pause/resume workflow?
8. How do you evaluate a RAG system that handles both factual Q&A and analytical multi-hop questions? Design separate evaluation tracks.
9. Write pseudocode for concurrent LLM calls with partial failure handling. How do you handle rate limits across the batch?
10. Design the complete evaluation pipeline (offline + online) for a production RAG system. What gates a deployment?
11. Compare a Multi-Agent Swarm architecture to a single LLM with multiple tools. What are the key trade-offs in terms of context dilution and failure isolation?
12. How do you implement a "Human-in-the-Loop" (HITL) mechanism in a reasoning-planning-acting-observing loop without creating significant latency bottlenecks?

### Round 2 Questions

1. Design a FastAPI service that wraps OpenAI and Anthropic APIs with automatic fallback, streaming, retry logic, and request validation. Show the key classes and error handling flow.
2. Walk through implementing a circuit breaker for LLM API calls. What states exist? What triggers state transitions? How do you handle the half-open state?
3. How would you structure MLflow tracking for a team iterating on RAG configurations? What do you log as parameters vs metrics vs artifacts?
4. Compare deploying a RAG application on AWS Lambda vs EKS (Kubernetes). What are the cold start implications? When is each the right choice?
5. Design a LangGraph workflow for an agent that researches a company, extracts financial data, generates a report, and gets human approval before publishing. Show the state schema and edge conditions.
6. Explain LangGraph reducers with a concrete example. How do you aggregate results from 3 parallel tool calls into a single state field?
7. Design the tracing architecture for a multi-step LLM chain (retrieval -> reranking -> generation -> validation). What OpenInference spans do you create? What attributes on each?
8. Your LLM application's cost doubled this month. Walk through your investigation using observability data. What do you look for?
9. Size a vLLM cluster for serving Llama-3-70B at 50 QPS with 4K context. How many H100s? What is the cost per 1M tokens?
10. Design a canary deployment for a new prompt template. What automated checks gate the rollout?
11. How do you implement multi-layered content filtering (input filtering, output moderation, deterministic rules) to ensure production safety for an agentic system?
12. What specific metrics and observability patterns would you implement for an agentic workflow to monitor success rates, tool usage distribution, and step-by-step latency?

### Round 3 Questions

1. Tell me about the most complex AI system you have built. What was the hardest technical decision and what would you do differently?
2. Your team deployed a RAG system that worked in staging but hallucinates in production. Walk through your debugging and remediation process.
3. How do you decide between using an LLM, a fine-tuned model, or a traditional ML approach for a new feature? Walk through the decision framework.
4. Design the evaluation strategy for an LLM application from development through production. What evaluations run in CI vs pre-deploy vs continuously in production?
5. Your VP asks why the AI platform costs $50K/month. Walk through how you justify the investment with business metrics and cost-per-outcome analysis.
6. How do you mentor a junior engineer who is building their first production LLM application? What are the top 3 things you teach them?
7. Design the on-call setup for a team owning 3 production LLM applications. What runbooks do you write? What alerts page vs dashboard?
8. Tell me about a time you had to debug and fix an infinite loop or deadlock in a multi-agent workflow in production.
9. As a senior engineer, how do you advocate for investing in reliable infrastructure and guardrails when stakeholders just want to "use the newest LLM"?

## System Design Bridge Items

- [ ] Review [Distributed Cache](../../system_design/distributed_cache/) for caching RAG retrieval results, embedding caches, and LLM response caches.
- [ ] Study [Rate Limiter](../../system_design/rate_limiter/) for protecting LLM API endpoints and managing upstream provider rate limits.
- [ ] Review [News Feed](../../system_design/news_feed/) for ranking and retrieval pipeline patterns applicable to RAG systems.
- [ ] Study [Notification Service](../../system_design/notification_service/) for event-driven architecture and async pipeline patterns.
- [ ] Map RAG evaluation requirements to [production_engineering/](../../production_engineering/) monitoring and deployment practices.
- [ ] Connect LLM serving decisions to [cs_fundamentals/](../../cs_fundamentals/) for networking (HTTP/2, SSE), concurrency (async I/O), and OS concepts (memory management, GPU scheduling).

## Practice Log

- [ ] 2026-06-__: Completed RAG architecture and agentic AI review (Round 1 topics)
- [ ] 2026-06-__: Built FastAPI service with error handling and observability (Round 2 topics)
- [ ] 2026-06-__: Prepared project deep dive stories and leadership narratives (Round 3 topics)
- [ ] 2026-06-__: Mock interview covering all three rounds
