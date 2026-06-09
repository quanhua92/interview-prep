# AI Product Engineering: From Prototype to Production

## Interview Preparation Checklist

---

### Decision Framework: AI vs Traditional
- [ ] Can articulate the decision tree for when to use AI vs rules
- [ ] Know 3+ examples where rule-based beats AI (deterministic tasks, zero-error tolerance, sub-ms latency)
- [ ] Can explain the "simple heuristic baseline" principle
- [ ] Understand the "Graduate Student Descent" anti-pattern
- [ ] Can name 5 tasks where LLMs are appropriate and 5 where they're not

### Development Lifecycle
- [ ] Can walk through all 4 phases: Setup → Data → Modeling → Serving
- [ ] Know what questions to ask during project setup (goals, constraints, metrics)
- [ ] Understand the prototype-to-production gap (10 key differences)
- [ ] Can explain the feedback loop between serving and earlier phases
- [ ] Know the difference between research ML and production ML (SOTA obsession vs user value)

### Prompt as Code
- [ ] Understand why prompts need version control
- [ ] Can describe a prompt directory structure with versioning
- [ ] Know prompt caching mechanics (cache writes vs reads, TTL, invalidation)
- [ ] Can explain automatic vs explicit cache breakpoints
- [ ] Understand prompt pre-warming for latency optimization
- [ ] Know how to test prompts in CI (trigger on file change, eval suite)

### Eval as Code
- [ ] Can name 5 types of evals (unit, golden, LLM-judge, human, side-by-side)
- [ ] Know when to use each eval type
- [ ] Can design a golden dataset curation strategy
- [ ] Understand eval metrics for different tasks (classification, generation, RAG, code)
- [ ] Know the OpenAI Evals framework structure
- [ ] Can explain "evals-driven development"
- [ ] Know how to set regression thresholds and fail CI

### Feasibility Assessment
- [ ] Can articulate the 5-dimension feasibility framework (Technical, Data, Cost, Reliability, Org)
- [ ] Know quick feasibility checks (1-day prototype, 5-example test, cost sanity check)
- [ ] Can create a feasibility assessment template
- [ ] Understand context window limits and their implications

### Cost Analysis
- [ ] Can calculate monthly cost from tokens/request × traffic × price
- [ ] Know 6 cost optimization strategies (model selection, caching, token reduction, batching, result caching, semantic caching)
- [ ] Understand cascading model routing (cheap first, escalate if low confidence)
- [ ] Know prompt caching pricing mechanics (1.25x write, 0.1x read)
- [ ] Can estimate cost savings from caching with hit rate math
- [ ] Understand the OpenAI Batch API (50% cost reduction)

### Testing Strategies
- [ ] Can describe the LLM testing pyramid (6 layers)
- [ ] Know Layer 1: Traditional tests that don't need LLM
- [ ] Know Layer 2-3: Golden dataset and LLM-as-judge
- [ ] Know Layer 4: Adversarial tests (prompt injection, jailbreak, toxicity)
- [ ] Understand shadow deployment in staging
- [ ] Know how to use synthetic data for pre-production testing

### Deployment & Rollout
- [ ] Can compare shadow deployment, canary, A/B, blue-green, feature flags
- [ ] Know the canary rollout progression (1% → 5% → 10% → 25% → 50% → 100%)
- [ ] Understand when to use each deployment strategy
- [ ] Know AI-specific rollout concerns (model warm-up, token budgeting, quality drift)
- [ ] Can implement a rollback strategy with feature flags

### Reliability Engineering
- [ ] Can name 10+ failure modes of LLM applications
- [ ] Know the circuit breaker pattern for LLM calls
- [ ] Understand retry with validation pattern
- [ ] Can design graceful degradation tiers (full LLM → simple LLM → cached → error message)
- [ ] Know key observability metrics (quality, latency, cost, error, usage, drift)
- [ ] Understand input sanitization for prompt injection defense

### Stakeholder Management
- [ ] Can name 6 common stakeholder misconceptions about AI
- [ ] Know the expectation-setting framework (quantify error rates, show failures, phase rollout)
- [ ] Understand the "AI Confidence Spectrum" (high confidence vs low confidence tasks)
- [ ] Can explain maintenance burden honestly

### User Feedback Loops
- [ ] Can name 5+ feedback collection channels with their tradeoffs
- [ ] Understand the feedback-to-improvement pipeline (collect → label → eval → iterate → deploy)
- [ ] Know the data flywheel effect
- [ ] Can design a golden dataset curation process from production data

### Common Pitfalls
- [ ] Know 9+ technical pitfalls (starting complex, ignoring baselines, overfitting eval, no versioning, etc.)
- [ ] Know 6+ organizational pitfalls (underestimating maintenance, no eval culture, stakeholder overpromise)
- [ ] Know 6+ architecture pitfalls (provider lock-in, no caching, synchronous calls, no rate limiting)
- [ ] Can describe the "Jupyter to Production" anti-pattern and what's missing

### System Design Practice
- [ ] Can design: AI customer support chatbot
- [ ] Can design: AI code review tool
- [ ] Can design: Content moderation system with LLM
- [ ] Can design: RAG-based document Q&A system
- [ ] Can design: AI-powered search ranking
