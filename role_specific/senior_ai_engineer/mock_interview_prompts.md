# AI Interview Simulator Prompts

Copy and paste these prompts into ChatGPT, Claude, or Gemini to simulate a rigorous Senior AI Engineer interview.

## Prompt 1: System Design (RAG & Multi-Tenancy)
> "Act as a Principal Engineer at a top-tier tech company interviewing me for a Senior AI Engineer role. We are doing a 45-minute system design round. I need to design a production-grade RAG system for a financial firm that handles sensitive 10-K reports and user portfolios. The system requires strict Role-Based Access Control (RBAC) and must mitigate hallucinations. 
> Ask me one question at a time. Push back hard on my choices regarding vector database partitioning, where authorization happens (pre vs. post retrieval), and how I evaluate the system. Do not break character."

## Prompt 2: Agentic Architecture
> "Act as a Staff AI Engineer interviewing me. I need to design a multi-agent system that researches companies, writes summary reports, and requires human approval before publishing. 
> Ask me about the trade-offs between a single orchestrator vs. a multi-agent swarm. Push me on how I handle deadlocks, manage state across long-running turns, and implement the Human-in-the-Loop checkpointing without blocking server resources. Ask one question at a time."

## Prompt 3: LLMOps & Serving (Round 2)
> "Act as an ML Infrastructure Manager interviewing me. I am deploying a 70B parameter model serving 100 QPS. 
> Grill me on GPU sizing math (weights + KV cache). Ask me to explain continuous batching vs static batching. Push me on my deployment strategy (Shadow vs Canary) and how I trace requests using OpenTelemetry and OpenInference. Ask one question at a time."

## Prompt 4: Azure AI Foundry + Redshift (JD-Aligned)
> "Act as a Principal Engineer at a Singapore-based enterprise interviewing me for a Senior AI Engineer role (3-6 month contract). The project: build an AI Agent layer on top of Amazon Redshift, integrate Microsoft Copilot via Azure AI Foundry, and build a RAG pipeline for unstructured data (PDFs, engineering specs, factory documents).
> 
> Round 1: Ask me to design the complete architecture — ingestion pipeline for PDFs/specs, Azure AI Search index design (hybrid search, RBAC), NL2SQL pipeline for Redshift, Copilot Studio integration, and how the agent routes between structured and unstructured queries. Push me on: why Azure AI Search over Pinecone/Qdrant, how I handle table extraction from PDFs, how I validate NL2SQL outputs, and the Copilot Studio + Foundry integration pattern (HTTP vs MCP). Ask one question at a time.
> 
> Round 2: Grill me on operational concerns — Azure AI Foundry deployment lifecycle, Prompt Flow for prompt orchestration, monitoring (Azure Monitor + OpenTelemetry), Redshift query cost attribution, and handling failures when Copilot Studio can't reach the Foundry backend. Ask one question at a time.
> 
> Round 3: Ask me about production failures I've dealt with in RAG systems — hallucination despite grounding, wrong NL2SQL, poor document quality in ingestion. Push on lessons learned and how I prevent recurrence. Ask one question at a time."
