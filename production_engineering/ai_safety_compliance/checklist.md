# AI Safety, Guardrails & Compliance — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Framing (2-3 min)
- [ ] State the core tension: models now take actions in the real world, making guardrails non-negotiable
- [ ] Cite key statistics to establish scope:
  - [ ] Prompt injection is OWASP LLM01 (#1 risk)
  - [ ] JBFuzz achieves ~99% ASR across 9 models
  - [ ] Cloud guardrails collapse to 0.19-0.61 F1 under adversarial pressure
  - [ ] EchoLeak CVSS 9.3, GitHub Copilot RCE CVSS 9.6 are real-world CVEs
- [ ] Frame the distinction: alignment makes models less likely to misbehave, guardrails make systems less able to act on misbehavior

## Phase 2: Prompt Injection Taxonomy & Defense (3-4 min)
- [ ] Explain why prompt injection is unsolvable architecturally:
  - [ ] LLMs cannot distinguish trusted instructions from untrusted data
  - [ ] All text in context window processed with equal weight
- [ ] Walk through the 6-category taxonomy:
  - [ ] Direct (attacker types malicious input)
  - [ ] Indirect (hidden in external data — emails, docs, web, RAG)
  - [ ] Multimodal/Visual (steganography, image scaling attacks)
  - [ ] RAG Poisoning (PoisonedRAG: 5 docs = 90% success)
  - [ ] Agentic/Cross-Plugin (Moltbook: 2.6% agent posts contain payloads)
  - [ ] Memory/Persistence (ZombieAgent: zero-click via connectors)
- [ ] Explain direct vs indirect distinction:
  - [ ] Direct: attacker interacts with LLM, defense = input validation
  - [ ] Indirect: attacker never interacts with LLM, defense = content sanitization + RAG integrity
- [ ] Walk through the promptware kill chain (7 stages):
  - [ ] Initial Access → Privilege Escalation → Reconnaissance → Persistence → C2 → Lateral Movement → Actions
  - [ ] Persistence in 12/21 attacks; lateral movement grew 0→8 (2023→2025)
- [ ] Present the 6-layer defense-in-depth:
  - [ ] Input validation, instruction hierarchy, least privilege, output validation, monitoring, red teaming
  - [ ] Emphasize: assume initial access will occur, defend every stage

## Phase 3: Jailbreak Defense (3-4 min)
- [ ] Distinguish from prompt injection:
  - [ ] Jailbreaking targets model safety alignment (what model refuses)
  - [ ] Prompt injection targets application layer (what model does)
- [ ] Walk through attack types:
  - [ ] Token-level (character substitution, Unicode homoglyphs)
  - [ ] Prompt-level (DAN role-play, educational framing, translation)
  - [ ] Multi-turn/Dialogue (Crescendo: gradual escalation)
  - [ ] Optimization-based (JBFuzz fuzzing, LRM-driven agents)
  - [ ] Many-shot (flood context with fake unsafe examples)
  - [ ] Policy file formatting (Policy Puppetry: XML/JSON bypasses)
- [ ] Cite key ASR benchmarks:
  - [ ] JBFuzz ~99% across 9 models, ~7 queries each
  - [ ] Hagendorff ~97% (LRMs autonomously plan jailbreaks)
  - [ ] Claude Opus 4.5: 63% at 100 attempts
- [ ] Present defense stack:
  - [ ] Model-level: RLHF, Constitutional AI, adversarial fine-tuning
  - [ ] System-prompt hardening: explicit refusal categories, no role-play overrides
  - [ ] Runtime: input filtering, output moderation, human escalation, rate limiting

## Phase 4: Guardrails Tools & Architecture (3-4 min)
- [ ] Explain the customizability problem:
  - [ ] Generic taxonomy: fast but limited
  - [ ] LLM-as-judge: flexible but slow (5-11s) and itself jailbreakable
  - [ ] Adversarially trained custom guard: fast (ms) and robust (requires training pipeline)
- [ ] Walk through tool comparison:
  - [ ] GA Guard: 0.983 F1, 29ms — strongest adversarial benchmark
  - [ ] Llama Guard 4: 0.961 F1 — free baseline
  - [ ] Google Vertex Model Armor: 0.945 F1, 873ms — slowest
  - [ ] NeMo Guardrails: 0.875 F1, <50ms — NVIDIA stack
  - [ ] Azure AI Content Safety: 0.193 F1 under adversarial — collapses
- [ ] State the critical finding: clean benchmarks are misleading; adversarial robustness gap is the single most important metric
- [ ] Present the guardrail pipeline architecture:
  - [ ] Input guardrail → LLM → Output guardrail → Policy enforcement → Delivery
  - [ ] Each layer independently logs for audit trail
- [ ] Give the latency budget: total guardrail overhead <60ms (parallel where possible)

## Phase 5: PII Detection & Regulated Industries (3-4 min)
- [ ] Explain the 3 PII threat vectors:
  - [ ] User inputs, training data memorization, model outputs
- [ ] Walk through Microsoft Presidio architecture:
  - [ ] Regex (95%+ structured), NER (85-90% unstructured), Custom recognizers, Context validation
- [ ] Present the production pipeline pattern:
  - [ ] Regex → NER → Context validator → PII tokenizer → LLM → Output scan → Re-identification (session-scoped)
- [ ] Explain NER limitations in LLM contexts:
  - [ ] Context-dependent, obfuscated, multi-hop, contextual PII
- [ ] Cover regulated industries:
  - [ ] Finance: SR 11-7 model validation, FINOS governance, off-policy advice risk
  - [ ] Healthcare: HIPAA access logs, FDA SaMD validation, PHI leakage risk
  - [ ] Cross-industry output filtering: schema → PII → toxicity → factuality → policy → human review

## Phase 6: EU AI Act & Compliance (2-3 min)
- [ ] Walk through 4-tier risk system:
  - [ ] Unacceptable (banned), High-Risk (heavily regulated), Limited (transparency), Minimal (unregulated)
- [ ] Explain high-risk Annex III use cases:
  - [ ] Biometrics, critical infrastructure, education, employment, essential services, law enforcement, migration, justice
- [ ] State GPAI systemic risk threshold: >10^25 FLOPs
- [ ] List 8 provider obligations:
  - [ ] Risk management, data governance, technical docs, record-keeping, instructions, human oversight, accuracy/robustness, quality management
- [ ] Cite penalties: up to €35M / 7% global turnover
- [ ] Give timelines: prohibited 6mo, GPAI 12mo, high-risk Annex III 24mo

## Phase 7: Red Teaming, Moderation & Audit Trails (3-4 min)
- [ ] Explain AI red teaming methodology:
  - [ ] Model vs system weaknesses (training issues vs infrastructure issues)
  - [ ] 5 risk categories: responsible AI, illegal activities, brand image, data privacy, unauthorized access
- [ ] Walk through the pipeline:
  - [ ] Generate → Enhance → Execute → Evaluate → Report
- [ ] Name tools: DeepTeam (50+ vulnerabilities), Promptfoo (OWASP framework), DeepEval, Azure AI Foundry
- [ ] Cite key metrics: ASR <1% known / <5% novel, coverage >95%, FPR <5%
- [ ] Explain content moderation 3-tier architecture:
  - [ ] Tier 1 automated (99%, <50ms), Tier 2 human (0.5-1%, minutes), Tier 3 expert (0.01-0.1%, hours)
  - [ ] Decision thresholds: auto-block >0.8, human review 0.5-0.8, auto-pass <0.5
  - [ ] Overturn rate target <5%
- [ ] Cover AI audit trails:
  - [ ] Log: timestamp, model_id, prompt, response, guardrails decisions, cost, tokens
  - [ ] LLM-specific: conversation history, prompt versions, RAG sources, hallucination evidence
  - [ ] Immutability: append-only, Ed25519 signing, tamper-evident
  - [ ] Notification deadlines: GDPR 72h, NIS2 24h/72h/1mo, HIPAA 60 days, EU AI Act without undue delay

## Phase 8: Bias, Fairness & OWASP Top 10 (3-4 min)
- [ ] Explain sources of bias:
  - [ ] Training data, alignment (RLHF annotator demographics), evaluation, deployment
- [ ] Walk through measurement techniques:
  - [ ] Demographic parity (equal positive rates), equalized odds (equal TPR/FPR)
  - [ ] Disparate impact (80% rule), counterfactual fairness
- [ ] Present mitigation strategies:
  - [ ] Pre-training: data curation; training: adversarial (KGAT)
  - [ ] Post-training: diverse RLHF annotators, DPO with fairness constraints
  - [ ] Runtime: output filtering; inference: hidden states modification
- [ ] Walk through OWASP Top 10 LLM risks:
  - [ ] LLM01 Prompt Injection → LLM10 Unbounded Consumption
  - [ ] For each: name, one-line description, key mitigation
- [ ] State MITRE ATLAS: LLM01 maps to AML.T0051, analogous to ATT&CK for ML/LLM

## Practice Questions

1. Explain the 6 categories of prompt injection. Which is hardest to defend against?
2. A user finds they can bypass your chatbot's safety filters using a multi-turn attack. Walk through your investigation and fix.
3. Compare NeMo Guardrails, Llama Guard 4, and cloud guardrails. When would you use each?
4. How would you detect and redact PII in LLM prompts before sending to an external provider?
5. Your company wants to deploy an LLM in the EU. What AI Act compliance requirements apply?
6. Design a content moderation pipeline for a production LLM application. What are the three tiers?
7. How would you design an audit trail for an LLM application in a regulated financial institution?
8. Walk through how you would red-team a production RAG system. What vectors do you test?
9. Your LLM outputs show gender bias in role recommendations. How do you measure and mitigate this?
10. How do you handle a situation where your guardrails produce false positives that frustrate users?
11. Design a safety layer for a multi-agent system where agents can call external tools. What boundaries do you enforce?
12. Pick 3 risks from the OWASP Top 10 LLM list and explain your defense strategy for each.

## Phase 9: System Design Bridge (2-3 min)
- [ ] Present the 5-layer production safety architecture:
  - [ ] Input Sanitization → System Prompt Hardening → LLM Processing → Output Filtering → Policy Enforcement
- [ ] Connect to related topics:
  - [ ] LLM gateways (llm_in_production): guardrail selection per model in portfolio
  - [ ] RAG poisoning defense (system_design/rag_system): retrieval integrity verification
  - [ ] Cryptography (cs_fundamentals): Ed25519 signing for audit trail immutability
  - [ ] Senior AI engineer role: ownership of guardrail selection and safety architecture
  - [ ] ML engineer role: bias measurement and fairness mitigation
- [ ] Emphasize the production reality: defense in depth, continuous red teaming, adversarial benchmarking over clean benchmarks

## Phase 10: Wrap-Up & Synthesis (2-3 min)
- [ ] Summarize the 11 topic areas covered
- [ ] Reiterate the core insight: alignment alone is insufficient; runtime guardrails + continuous red teaming + audit trails are production necessities
- [ ] Highlight the adversarial robustness gap as the single most important metric for guardrail evaluation
- [ ] Connect to regulatory pressure: EU AI Act mandates adversarial testing for high-risk and GPAI systems
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
