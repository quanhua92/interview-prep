# AI CI/CD: Pipelines for LLM Applications — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Framing (2-3 min)
- [ ] State the core tension: LLM outputs are non-deterministic, so traditional pass/fail tests don't work — evals replace unit tests as the primary quality gate
- [ ] Cite key statistics to establish scope:
  - [ ] 69% of LLM input tokens are system prompts (prompt changes = cost changes)
  - [ ] 5% of LLM calls error in production; 60% from rate limits
  - [ ] Provider-side model updates happen silently — pinning is essential
  - [ ] 22K+ GitHub stars for Promptfoo eval-as-code toolkit
- [ ] Frame the difference: traditional CI/CD = deterministic tests; AI CI/CD = statistical evals + quality gates

## Phase 2: Prompt-as-Code (2-3 min)
- [ ] Explain why prompts need version control:
  - [ ] Prompts are software — they change, have bugs, affect behavior
  - [ ] A prompt change can break production format, increase hallucination, shift tone, spike cost
  - [ ] Rollback must be instant (git revert)
- [ ] Walk through the prompt management architecture:
  - [ ] Versioned prompt directories (v1/, v2/) with system_prompt.txt, examples.json, config.yaml
  - [ ] Config includes model pin (e.g., `gpt-4o-2024-08-06`, not `gpt-4o`)
  - [ ] Linked test suite and regression comparison
  - [ ] CHANGELOG.md tracking what changed and why
- [ ] Explain prompt diffing: run old vs new prompt on golden dataset, compare with semantic similarity
- [ ] Mention prompt caching: 90% cost reduction on cached tokens for static system prompts

## Phase 3: Eval-as-Code (3-4 min)
- [ ] Explain the 5 types of evals:
  - [ ] Unit tests (exact match, schema validation) — fast, no LLM needed
  - [ ] Golden dataset (reference-based, semantic similarity) — medium, core regression tool
  - [ ] LLM-as-judge (quality: accuracy, tone, hallucination) — slow, 2x LLM calls
  - [ ] Adversarial (safety: injection, jailbreaks, toxicity) — medium, security gate
  - [ ] Integration (E2E pipeline: routing, fallback, caching) — slow, system-level
- [ ] Explain golden dataset composition:
  - [ ] 60% common scenarios, 20% edge cases, 20% adversarial inputs
  - [ ] Target: 200-500 cases minimum
  - [ ] Must grow over time from production failures and user corrections
- [ ] Walk through eval triggers:
  - [ ] PR: lint + unit tests + golden subset (100 cases) — <10 min
  - [ ] Deploy gate: full golden + safety eval + cost check — <20 min
  - [ ] Nightly: full suite + LLM-as-judge + adversarial — <60 min
- [ ] Demonstrate CI quality gate: fail build if accuracy drops below threshold

## Phase 4: Model Versioning & Registry (2-3 min)
- [ ] Explain why model pinning matters:
  - [ ] Providers update models silently; unpinned models break without code changes
  - [ ] Always use dated pins: `gpt-4o-2024-08-06` not `gpt-4o`
- [ ] Walk through model card contents:
  - [ ] Model ID and pin, cost profile, performance benchmarks
  - [ ] Known limitations, safety profile, context window
  - [ ] Compliance (data residency), retirement date
- [ ] Explain compatibility testing: when swapping models, new model must maintain >=95% of old model's accuracy
- [ ] Mention MLflow for fine-tuned model tracking (training data hash, hyperparameters, eval scores)

## Phase 5: LLM-Specific CI Pipeline (3-4 min)
- [ ] Walk through the 7-stage pipeline:
  - [ ] Stage 1: Lint & Static (30 sec) — prompt format, config schema, cost estimation
  - [ ] Stage 2: Unit Tests (2 min) — input validation, output parsing, fallback logic
  - [ ] Stage 3: Golden Set Eval (5-10 min) — accuracy threshold, regression check
  - [ ] Stage 4: LLM-as-Judge (5-15 min, nightly) — factual accuracy, tone, hallucination
  - [ ] Stage 5: Safety Eval (5-10 min, nightly) — adversarial inputs, PII, toxicity
  - [ ] Stage 6: Cost Check (30 sec) — token estimate, monthly projection
  - [ ] Stage 7: Deploy Gate — all green, model pinned, rollback plan documented
- [ ] Explain the tiered runtime budget:
  - [ ] PR fast gate: <10 min (stages 1-3 subset)
  - [ ] Deploy gate: <20 min (stages 1-3 full + 5-6)
  - [ ] Nightly: <60 min (all stages)
- [ ] Mention cost optimization: caching eval results, using cheap model for judges, subsetting golden dataset on PRs

## Phase 6: Prompt Regression Testing (2-3 min)
- [ ] Explain the core problem: how to detect quality changes when outputs are non-deterministic
- [ ] Walk through 3 regression detection methods:
  - [ ] Semantic similarity (embeddings, cosine similarity, threshold 0.85)
  - [ ] Side-by-side comparison (old vs new prompt on same golden dataset, diff view)
  - [ ] Distribution drift (aggregate metrics over time: accuracy, hallucination, length, sentiment)
- [ ] Give regression thresholds:
  - [ ] Accuracy drop >3% from baseline → fail build
  - [ ] Semantic similarity <0.85 from reference → flag for review
  - [ ] Hallucination increase >1% from baseline → fail build
- [ ] Explain silent regressions: quality degrades gradually without triggering error alerts, only detectable through eval tracking

## Phase 7: Deployment Pipeline for AI (3-4 min)
- [ ] Walk through progressive rollout:
  - [ ] Shadow (0%, 24-72h) → Canary (1-5%, 24-48h) → A/B (50/50, 7-14d) → Full (100%)
  - [ ] Shadow: no user impact, compare quality/latency/cost
  - [ ] Canary: monitor error rate, eval scores on live data
  - [ ] Full: keep old version as fallback for 30 days
- [ ] Present automated rollback triggers:
  - [ ] Error rate >5% above baseline → instant rollback
  - [ ] Latency P99 >2x baseline → instant rollback
  - [ ] Eval score >3% below baseline → alert + rollback
  - [ ] Any safety violation → instant rollback
- [ ] Explain feature flags for prompts:
  - [ ] All prompt versions deployed simultaneously, routing by flag
  - [ ] Instant rollback (toggle off), A/B testing without deploys
  - [ ] Per-user or per-segment targeting

## Phase 8: Eval Suite Architecture (2-3 min)
- [ ] Present the 5-layer eval stack:
  - [ ] Traditional tests (no LLM) → Unit tests (exact match) → Golden dataset → LLM-as-judge → Adversarial
  - [ ] Each layer catches different failure modes
- [ ] Walk through eval metrics by task type:
  - [ ] Classification: Accuracy, F1, precision, recall
  - [ ] Summarization: ROUGE, BERTScore, semantic similarity
  - [ ] RAG: Faithfulness, context precision, context recall (Ragas)
  - [ ] Chat: Helpfulness, safety, coherence
- [ ] Explain LLM-as-judge risks and mitigations:
  - [ ] Use different model as judge than model being evaluated
  - [ ] Calibrate against human labels periodically
  - [ ] Use multiple judges and aggregate

## Phase 9: Monitoring Post-Deploy (2-3 min)
- [ ] Explain what to monitor:
  - [ ] Quality: eval score on sampled outputs (5-10% of traffic), user satisfaction
  - [ ] Latency: P50, P95, P99, time-to-first-token
  - [ ] Cost: tokens per request, total spend, cost per successful outcome
  - [ ] Errors: error rate, timeout rate, rate limit hit rate
  - [ ] Drift: output distribution, response length, sentiment (KS-test)
  - [ ] Safety: toxicity, PII leakage, prompt injection attempts
- [ ] Present the monitoring architecture:
  - [ ] LLM Gateway (LiteLLM, OpenRouter) → Sampling (5-10%) → Eval Runner → Dashboard
  - [ ] Nightly eval runs catch provider-side model drift
  - [ ] Dashboard tracks trends over time (Langfuse or custom Grafana)
- [ ] Alert thresholds:
  - [ ] Quality metric >3% drop → alert
  - [ ] Error rate >5% → instant rollback
  - [ ] Any safety violation → instant rollback

## Phase 10: Tools & Frameworks (3-4 min)
- [ ] Walk through the tool categories and decision framework:
  - [ ] Testing: Promptfoo (red teaming, CI gates, $0), DeepEval (50+ metrics, pytest), Ragas (RAG)
  - [ ] Observability: Langfuse (self-hostable, open-source), LangSmith (LangChain-native), Arize Phoenix (OTel)
  - [ ] All-in-one: Braintrust (eval + tracing + experiments, $249/mo), Confident AI (DeepEval cloud)
  - [ ] Model registry: MLflow (fine-tuned models)
- [ ] Give the decision path:
  - [ ] $0 budget → Promptfoo + Arize Phoenix (testing + observability)
  - [ ] Max metrics → DeepEval + Langfuse (testing + observability)
  - [ ] RAG focus → Ragas + Langfuse
  - [ ] LangChain team → LangSmith
  - [ ] All-in-one budget → Braintrust
- [ ] Cite key facts:
  - [ ] Promptfoo: MIT license, 300K+ devs, 50+ vulnerability types, OpenAI acquired (March 2026, core stays MIT)
  - [ ] DeepEval: 50+ built-in metrics, pytest-native, agent evaluation, dashboards behind paid tier
  - [ ] Langfuse: self-hostable, 50K free observations/mo, vendor-agnostic

## Practice Questions

1. Why is AI CI/CD fundamentally different from traditional CI/CD? What breaks when you apply traditional testing to LLM applications?
2. Design a prompt management system with version control, review process, and automated regression testing.
3. Build an eval suite from scratch for a customer support chatbot. What's in your golden dataset? What metrics do you track?
4. Why is model version pinning essential? What happens when a provider updates a model silently?
5. Design a full AI CI pipeline with all 7 stages. Which stages run on PR vs nightly? What's your runtime budget?
6. How do you detect silent quality regressions when changing prompts? Walk through 3 detection methods.
7. Design a deployment pipeline with shadow → canary → A/B → rollout. What triggers automated rollback?
8. Compare Promptfoo, DeepEval, and Langfuse. When would you use each? What's your recommended combo for a $0 budget?
9. How do you run evals in CI without spending a fortune on LLM API calls? What cost optimizations do you apply?
10. Design a monitoring system that catches quality degradation after deployment. What metrics do you track and what triggers alerts?
11. Your golden dataset shows 95% accuracy in CI but users report poor quality in production. What went wrong and how do you fix it?
12. How do you test a multi-step AI agent that calls tools? What additional eval stages do you need vs a single LLM call?
13. Design eval-as-code for a RAG application. What RAG-specific metrics and stages do you add?
14. Two eval tools give contradictory results on the same test case. How do you resolve this?
15. Your LLM provider updates their model and eval scores drop 5%. Walk through your immediate and long-term response.

## Phase 11: System Design Bridge (2-3 min)
- [ ] Connect AI CI/CD to related topics:
  - [ ] cicd_pipelines: AI CI/CD extends traditional CI/CD with eval gates, model pinning, non-deterministic testing
  - [ ] ai_product_engineering: Prompt-as-code and eval-as-code lifecycle (prototype → eval → harden → deploy → monitor)
  - [ ] ai_safety_compliance: Red teaming in CI (Promptfoo), guardrails pipeline, OWASP Top 10
  - [ ] llm_in_production: Model portfolio management, LLM gateways (LiteLLM, OpenRouter) for routing/fallback
  - [ ] llm_cost_engineering: Token-level cost optimization, prompt caching, model routing economics
  - [ ] feature_flags: Feature flag architecture for prompt-level rollout and instant rollback
  - [ ] multi_model_gateway: LLM gateway design, model routing, fallback chains
  - [ ] rag_system: RAG-specific eval metrics (Ragas: faithfulness, context precision/recall)
  - [ ] postmortem: AI-specific incident analysis (model drift, prompt regression, provider outages)
- [ ] Emphasize the production reality: evals are non-negotiable, model pinning prevents silent breakage, and defense in depth requires testing + runtime guardrails + monitoring

## Phase 12: Wrap-Up & Synthesis (2-3 min)
- [ ] Summarize the 10 topic areas covered
- [ ] Reiterate the core insight: evals are the unit tests of AI; without eval-as-code, you're flying blind
- [ ] Highlight the most important practices:
  - [ ] Model version pinning (prevents silent breakage)
  - [ ] Golden dataset curation (foundation of eval-as-code)
  - [ ] Tiered CI pipeline (fast feedback on PRs, comprehensive validation before deploy)
  - [ ] Progressive deployment (shadow → canary → full with automated rollback)
  - [ ] Post-deploy monitoring (catch silent regressions)
- [ ] Connect to the 2026 landscape: OpenAI acquired Promptfoo (March 2026), eval tools maturing rapidly, provider-side model drift remains the #1 operational risk
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
