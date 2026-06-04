# Behavioral & War Stories Framework

Use the STAR format (Situation, Task, Action, Result) but focus heavily on trade-offs, failures, and cross-team impact.

## Story 1: The Architecture Trade-off
**Prompt:** "Tell me about a time you had to choose between two competing AI architectures."
- **Example Focus:** Choosing a single Orchestrator LLM vs. a Swarm, or choosing RAG vs. Long-Context windows.
- **Key Elements to Hit:**
  - Latency vs. Accuracy vs. Cost analysis.
  - How you validated the decision (e.g., A/B test, shadow deploy).
  - Acknowledging the nuances (e.g., "Long-context was easier to build, but RAG was necessary for cost-control at scale").

## Story 2: The Production Failure (and Fix)
**Prompt:** "Tell me about a time an AI system you deployed failed or hallucinated in production."
- **Example Focus:** A multi-agent deadlock, a prompt injection attack, or a silent RAG retrieval failure.
- **Key Elements to Hit:**
  - How you detected it (Observability, OpenTelemetry).
  - The root cause analysis (e.g., "The vector DB was returning chunks out of order").
  - The systemic fix (e.g., decoupling extraction from generation, implementing a loop guard).

## Story 3: Infrastructure over Models
**Prompt:** "Tell me about a time you had to push back on stakeholders who just wanted to 'use the newest LLM'."
- **Example Focus:** Investing in guardrails, evaluation pipelines, or reliable LLMOps instead of chasing the latest model hype.
- **Key Elements to Hit:**
  - Demonstrating that a solid system design outlasts specific LLM versions.
  - How you translated technical debt (lack of evals) into business risk (hallucinations hurting brand trust).
