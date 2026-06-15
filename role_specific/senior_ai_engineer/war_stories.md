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

## Story 4: The Azure Migration
**Prompt:** "Tell me about a time you migrated an AI system from a custom stack to Azure AI Foundry."
- **Example Focus:** Moving from LangChain + Pinecone to Azure AI Foundry + Azure AI Search. Or building a new system on Azure from scratch and choosing the stack.
- **Key Elements to Hit:**
  - Why Azure AI Foundry over alternatives (evaluation tooling, model catalog, enterprise support).
  - How Azure AI Search hybrid search improved retrieval over the previous vector-only setup.
  - Challenges: index migration, RBAC configuration, Copilot Studio integration, cost model differences.
  - The Copilot Studio frontend integration — how it simplified the conversational layer but required backend changes in the Foundry agent.

## Story 5: The Redshift NL2SQL Failure
**Prompt:** "Tell me about a time your AI system generated wrong SQL that caused a production issue."
- **Example Focus:** NL2SQL pipeline generating incorrect joins, missing WHERE clauses, or querying the wrong table.
- **Key Elements to Hit:**
  - How you detected the wrong SQL (result validation, user feedback, or monitoring).
  - Root cause: stale schema catalog, ambiguous column names, or insufficient schema context in the prompt.
  - The fix: SQL whitelist enforcement, schema refresh automation, query result validation, and LIMIT clauses.
  - How this experience shaped your approach to NL2SQL safety (whitelist, timeout, read-only, result bounds checking).

## Story 6: The Unstructured Data Quality Crisis
**Prompt:** "Tell me about a time poor document quality broke your RAG pipeline."
- **Example Focus:** Factory PDFs with scanned images, non-standard table layouts, or corrupted chunks entering the vector index.
- **Key Elements to Hit:**
  - How you detected it (low retrieval relevance, user complaints about missing answers, embedding quality metrics).
  - Root cause: OCR failures on scanned pages, table extraction parsing errors, naive fixed-size chunking splitting tables mid-row.
  - The fix: Azure Document Intelligence for better layout detection, semantic chunking at table boundaries, data quality validation before indexing.
  - The lesson: "Garbage in, garbage out" applies to RAG — invest in ingestion quality before worrying about retrieval algorithms.
