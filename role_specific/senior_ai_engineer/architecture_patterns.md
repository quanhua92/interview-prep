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
