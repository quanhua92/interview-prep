# LLM in Production: Operating AI Systems at Scale — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Framing (2-3 min)
- [ ] State the problem: teams are moving LLM apps from demos to production but face reliability, cost, and observability challenges
- [ ] Cite key statistics to establish scope:
  - [ ] 70%+ orgs use 3+ models; 69% of tokens are system prompts
  - [ ] 60% of LLM errors from rate limits; 59% of agents are monolithic
  - [ ] Only 28% use prompt caching; token usage doubled YoY
- [ ] Frame the shift: AI engineering = distributed systems problem, not prompt engineering

## Phase 2: Model Portfolio Management (3-4 min)
- [ ] Explain why multiple models are necessary:
  - [ ] Different workloads need different models (lightweight for extraction, frontier for synthesis)
  - [ ] Cost, latency, quality, and risk vary per model
- [ ] Discuss risks of multi-model strategy:
  - [ ] Multiple SDKs, retry logic, provider-specific edge cases
  - [ ] Slow iteration speed, increased operational overhead
  - [ ] LLM tech debt: teams adopt new models but don't retire old ones
- [ ] Present solution: LLM Gateways
  - [ ] Unified API across providers
  - [ ] Automatic fallbacks and smart routing
  - [ ] Caching (40-60% cost reduction)
  - [ ] Rate limit management at platform layer
  - [ ] Tools: LiteLLM, OpenRouter, Portkey
- [ ] Mention best practices:
  - [ ] Treat inference like a pipeline with staged model selection
  - [ ] Maintain operationalized evaluation framework (especially online evals)
  - [ ] Proactively deprecate old models

## Phase 3: LLM Observability & Telemetry (3-4 min)
- [ ] Explain why traditional APM is insufficient:
  - [ ] LLM control flow is model-driven, not code-driven
  - [ ] Frameworks (LangChain, LangGraph, Vercel AI SDK) add hidden complexity
  - [ ] Agentic framework adoption doubled (9% → 18%)
- [ ] List signals to track:
  - [ ] Token usage and cost per request
  - [ ] Latency across agent steps
  - [ ] Prompt and response traces
  - [ ] Tool call success/failure rates
  - [ ] Hallucination/quality degradation patterns
  - [ ] Model routing and fallback behavior
  - [ ] Cache-hit rate and cached-token share
- [ ] Name observability tools:
  - [ ] LangSmith (deep tracing for LangChain/LangGraph)
  - [ ] Langfuse (open-source LLM observability)
  - [ ] Helicone (lightweight latency/cost)
  - [ ] Datadog LLM Observability (production monitoring)
  - [ ] OpenTelemetry (standard for AI instrumentation)

## Phase 4: Prompt Efficiency & Caching (3-4 min)
- [ ] Explain the system prompt tax:
  - [ ] 69% of input tokens are system prompts, not user input
  - [ ] Same instructions repeated across every request
- [ ] Discuss prompt caching underutilization:
  - [ ] Only 28% of LLM calls show cached-read input tokens
  - [ ] Common cause: poor prompt layout (dynamic content too early, stable blocks reordered)
- [ ] Optimization strategies:
  - [ ] Keep stable scaffolding at the beginning of the prompt
  - [ ] Inject dynamic content later for prefix reuse
  - [ ] Shorten system prompts, modularize reusable components
  - [ ] Monitor cache-hit rate as an operational metric
- [ ] Address monolithic prompt architecture:
  - [ ] 59% of agents still use a single service call
  - [ ] One prompt handles planning, reasoning, tool use, memory, response
  - [ ] Direction: modular/multi-agent architecture
  - [ ] New requirements: orchestration, shared memory, smart routing, cost/latency controls

## Phase 5: Context Engineering (3-4 min)
- [ ] Describe the context window explosion:
  - [ ] 128K → 2M tokens in two years
  - [ ] Avg tokens 2x median, 4x p90 YoY
  - [ ] Teams stuffing more state into prompts
- [ ] State the core insight:
  - [ ] Context quality, not quantity, is the new bottleneck
  - [ ] Large prompts add noise, redundancy, buried critical details
- [ ] Present context engineering practices:
  - [ ] Selective retrieval instead of dumping everything
  - [ ] Dynamic context injection based on user intent
  - [ ] Smarter memory management (summarization, prioritization, eviction)
  - [ ] Prompt compression and deduplication
  - [ ] Clear information hierarchy (most decision-relevant content first)

## Phase 6: Reliability Engineering for LLMs (4-5 min)
- [ ] State the rate limit problem:
  - [ ] 5% of LLM calls errored (Feb); 60% from rate limits
  - [ ] ~8.4M rate limit errors in March 2026
  - [ ] Reliability tied to provider capacity limits
- [ ] Discuss control of agent behavior:
  - [ ] Long agent loops multiply API calls
  - [ ] Aggressive tool fan-out triggers traffic spikes
  - [ ] Recursive planning creates runaway execution
  - [ ] Design bounded execution patterns
- [ ] Present traditional distributed systems patterns:
  - [ ] Queues to smooth traffic spikes
  - [ ] Exponential backoff and retries
  - [ ] Fallback models/providers
  - [ ] Circuit breakers
  - [ ] Rate limiting and concurrency controls
- [ ] Explain agent budgets:
  - [ ] Max model calls per run
  - [ ] Token budgets per execution
  - [ ] Execution timeouts
  - [ ] Tool invocation caps
- [ ] Address monolith → distributed evolution:
  - [ ] 59% of agents are still monolithic
  - [ ] Only 18% make 3+ service calls
  - [ ] Shift toward dedicated agent services and multi-agent architectures
  - [ ] Needs: cross-service tracing, tool service maps, orchestration, shared memory

## Phase 7: Wrap-Up & Synthesis (2-3 min)
- [ ] Summarize the five pillars:
  - [ ] Model portfolio management with gateways
  - [ ] LLM observability and agent telemetry
  - [ ] Prompt efficiency and caching
  - [ ] Context engineering (quality over quantity)
  - [ ] Reliability patterns (rate limits, budgets, distributed systems patterns)
- [ ] Emphasize that AI engineering = distributed systems engineering
- [ ] Connect operational excellence fundamentals (queues, backoff, fallbacks, circuit breakers) to LLM systems
- [ ] Highlight that the next advantage belongs to teams that make agents observable, governable, resilient, and cost-aware
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
