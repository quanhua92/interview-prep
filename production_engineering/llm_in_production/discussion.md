# LLM in Production: Operating AI Systems at Scale

Sources:
- [Datadog State of AI Engineering Report 2026](https://lp.datadoghq.com/rs/875-UVY-685/images/ResearchReport-2026StateofAIEngineering.pdf)
- [Datadog's AI Report: 5 Things Senior Engineers Can't Ignore (Aayush Ostwal)](https://aayushostwal2.substack.com/p/datadogs-ai-report-5-things-senior)

## One-Liner
Operating LLM-powered systems in production requires distributed systems engineering discipline — model portfolio management, observability, context engineering, and reliability patterns — not just prompt engineering.

## Key Statistics
- **70%+** organizations use 3+ models; **63%** OpenAI, Gemini & Claude gaining 20pp+ YoY
- **69%** of input tokens are system prompts (not user input)
- Only **28%** of LLM calls use prompt caching despite support
- **5%** of LLM calls errored (Feb 2026); **60%** of errors from rate limits
- **59%** of agentic apps use a single service call (monolithic)
- Agent framework adoption doubled: **9% → 18%** (2025→2026)
- Avg tokens per request **2x** for median, **4x** for p90 YoY
- Models with **2M token** context windows now available

## 1. Model Portfolio Management & LLM Gateways

### Why Multiple Models?
- Different models excel at different workloads: reasoning, coding, summarization, classification, extraction
- **Model portfolio** approach: pick the right model per task based on latency, cost, operational risk, and quality requirements
- OpenAI still dominates (63%) but Google Gemini and Anthropic Claude are gaining rapidly
- Number of organizations using 6+ models nearly doubled YoY

### Risks of Multi-Model Strategy
- Juggling multiple SDKs, APIs, retry logic, provider-specific edge cases
- Fallback mechanisms when a provider fails
- Slower iteration speed due to integration complexity
- **LLM tech debt**: teams adopt new models quickly but are slow to retire old ones → operational overhead compounds
- Each additional model introduces its own quality, latency, and cost profile
- Old models (GPT-4o, Sonnet 4.5) persist at high adoption rates even after newer releases

### Solution: LLM Gateways
Abstraction layer between your app and model providers:
- **Unified API**: single interface for 100+ LLM providers
- **Automatic fallbacks**: route to backup model when primary fails
- **Smart routing**: direct requests to optimal model based on task type, cost, latency targets
- **Caching**: cache repeated prompts → 40-60% cost reduction
- **Rate limit management** at the platform layer
- Tools: **LiteLLM**, **OpenRouter**, **Portkey**

### Best Practices
- Treat inference like a pipeline: lightweight models for extraction/tagging, frontier models for synthesis
- Maintain an operationalized evaluation framework (especially online evals)
- Continuously benchmark and swap models as costs fall and performance evolves
- Proactively deprecate older models before providers sunset them

## 2. LLM Observability & Agent Telemetry

### Why It Matters
- Agentic frameworks (LangChain, LangGraph, Pydantic AI, Vercel AI SDK) adoption doubled
- Frameworks add abstraction layers that hide execution complexity
- Tool fan-out, retries, branching are "one import away" → cost/latency drifts, failures hard to reproduce
- Modern AI systems are no longer simple API calls — they involve prompts, tool calls, retrieval pipelines, memory, multi-step reasoning, fallbacks
- Traditional APM is insufficient to debug LLM workflows

### Signals to Track
- Token usage and cost per request
- Latency across agent steps
- Prompt and response traces
- Tool call success/failure rates
- Hallucination or quality degradation patterns
- Model routing and fallback behavior
- User feedback and agent success metrics
- Cache-hit rate and cached-token share

### Tools
- **LangSmith**: deep tracing for LangChain/LangGraph workflows
- **Langfuse**: open-source LLM observability (tracing, prompt management, evals, cost tracking)
- **Helicone**: lightweight latency/cost/caching observability
- **Datadog LLM Observability**: production monitoring alongside infrastructure telemetry
- **OpenTelemetry (OTEL)**: increasingly the standard for instrumenting AI apps across services, agents, model calls

### Key Insight
The next wave of agent failures won't be about what agents can't do — it'll be about what teams can't observe. Unlike traditional software, agent control flow is driven by the LLM itself, making observability essential.

## 3. Prompt Efficiency & Caching

### The System Prompt Tax
- **69% of input tokens** are system prompts — internal instructions, policy definitions, tool guidance
- Most organizations repeatedly send the same instructions, context, and formatting rules with every request
- This is a major optimization opportunity: prompt caching can reuse previously computed prompt states

### Prompt Caching: Underutilized
- Even among models that support prompt caching, **only 28% of LLM call spans** show any cached-read input tokens
- Common culprit: prompt layout is inefficient
  - Dynamic content injected too early in the prompt
  - Stable blocks get reordered or rewritten between requests
  - Breaks the prefix reuse that enables caching

### Optimization Strategies
- Keep stable scaffolding (system instructions, policies, tool schemas) at the beginning of the prompt
- Inject dynamic content later to maximize prefix reuse
- Shorten system prompts where possible
- Modularize reusable components for caching
- Monitor cache-hit rate and cached-token share as operational metrics

### Monolithic Prompts → Modular Architecture
- **59%** of agentic apps still make a single service call (monolithic prompt)
- One large prompt handles planning, reasoning, tool use, memory, and response generation
- This approach is hard to scale, debug, and optimize
- Direction: dedicated agent services, multi-agent architectures
  - One agent for retrieval, another for reasoning, another for execution/validation
  - Requires: orchestration, observability, shared memory, smart routing, cost/latency controls

## 4. Context Engineering

### The Shift
- Context windows have exploded: 128K → 2M tokens in two years
- Average tokens per request doubled (median), quadrupled (p90) YoY
- Teams are stuffing more state: conversation history, retrieved documents, tool outputs, policy guardrails
- **Context window size is no longer the bottleneck. Context quality is.**

### The New Challenge
- Not "How do I fit everything into the context window?" but rather "What is the minimum high-quality context the model actually needs?"
- Large prompts introduce noise, redundancy, and conflicting information
- Critical details get buried deep in long inputs
- Latency and cost increase with prompt size

### Context Engineering Practices
- **Selective retrieval** instead of dumping everything
- **Dynamic context injection** based on user intent
- **Smarter memory management** (summarization, prioritization, eviction)
- **Prompt compression** and deduplication
- **Clear information hierarchy** — most decision-relevant content first
- Remove noisy or redundant context aggressively
- Systems to reliably select, compress, and structure decision-relevant information

## 5. Reliability Engineering for LLMs

### The Rate Limit Problem
- **5%** of all LLM call spans reported an error (Feb 2026)
- **60%** of those errors caused by exceeded rate limits
- In March 2026: 2% error rate, rate limits almost a third (~8.4M rate limit errors)
- Reliability of AI applications is tied to model providers' capacity limits
- Building AI systems = distributed systems problem

### Engineering Solutions

**LLM Gateways** (as covered in section 1):
- Automatic failover to backup providers/models
- Load balancing across providers
- Retry handling and intelligent routing
- Rate limit management at the platform layer

**Control Agent Behavior**:
- Long agent loops multiply API calls unexpectedly
- Aggressive tool fan-out triggers sudden traffic spikes
- Recursive planning creates runaway execution paths
- Design **bounded execution patterns**: max model calls, token budgets, execution timeouts, tool invocation caps

**Traditional Distributed Systems Patterns** (reintroduced):
- **Queues** to smooth traffic spikes
- **Exponential backoff and retries** for transient failures
- **Fallback models/providers** when capacity is constrained
- **Circuit breakers** to prevent cascading failures
- **Rate limiting and concurrency controls**

**Agent Budgets**:
- Maximum number of model calls per agent run
- Token budgets per execution
- Execution timeouts
- Tool invocation caps
- Prevents runaway loops from exhausting provider capacity and impacting downstream services

### Monolith to Distributed Evolution
- Most agents are still monolithic (59% single service call)
- Only 18% make 3+ service calls
- Shift toward dedicated agent services and multi-agent architectures
- New platform requirements:
  - Context/trace propagation across service boundaries
  - Service maps that include tools
  - Orchestration between agents
  - Shared memory and context management
  - Stronger cost and latency controls

## Cross-Cutting: LLM Tech Debt
- Debt from model/agent complexity compounds faster than traditional code debt
- Sources: slow model retirement, monolithic prompts, scattered integrations, unobserved agents
- Prevention: continuous evaluation, governance, efficient routing via gateways, telemetry-driven optimization

## Evaluation Framework for Production AI Systems
| Dimension | Key Metrics | Good Signal | Red Flag |
|-----------|-------------|-------------|----------|
| Cost | $/request, token usage, cache-hit rate | Cache-hit >50%, cost decreasing per request | Zero cache hits, cost growing linearly with usage |
| Reliability | Error rate, rate-limit errors, P50/P95 latency | <1% error rate, stable latency | >5% error rate, rate limits >30% of errors |
| Quality | Evals score, user feedback, hallucination rate | Improving eval scores, positive user feedback | Increasing hallucination rate, declining user satisfaction |
| Observability | Trace coverage, agent success metrics | Full trace coverage, all agent steps visible | Blind spots in agent execution, no tool call tracking |
| Architecture | Service calls per request, model count, prompt size | Trend toward modular, intelligently routed | Monolithic prompts growing unbounded, model sprawl |
