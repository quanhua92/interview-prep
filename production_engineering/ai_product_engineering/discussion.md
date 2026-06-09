# AI Product Engineering: From Prototype to Production

## Research & Discussion Guide for AI Engineer Interviews

---

## Table of Contents

1. [Decision Framework: When to Use AI vs. Traditional Approaches](#1-decision-framework-when-to-use-ai-vs-traditional-approaches)
2. [AI Product Development Lifecycle](#2-ai-product-development-lifecycle)
3. [Prompt as Code: Version Control & Management](#3-prompt-as-code-version-control--management)
4. [Eval as Code: LLM Evaluation Pipelines & CI](#4-eval-as-code-llm-evaluation-pipelines--ci)
5. [AI Feature Feasibility Assessment](#5-ai-feature-feasibility-assessment)
6. [Cost Per Feature Analysis](#6-cost-per-feature-analysis)
7. [Testing Strategies for LLM Applications](#7-testing-strategies-for-llm-applications)
8. [Deployment & Progressive Rollout Strategies](#8-deployment--progressive-rollout-strategies)
9. [LLM Application Reliability Engineering](#9-llm-application-reliability-engineering)
10. [Managing Stakeholder AI Expectations](#10-managing-stakeholder-ai-expectations)
11. [User Feedback Loops & Iteration](#11-user-feedback-loops--iteration)
12. [Common Pitfalls & Failure Modes](#12-common-pitfalls--failure-modes)
13. [Interview Questions & Model Answers](#13-interview-questions--model-answers)

---

## 1. Decision Framework: When to Use AI vs. Traditional Approaches

### Core Principle
Before saying "neural network," determine whether you even need ML. The simplest solution that can do the job is always the right starting point.

### Decision Tree

```
Is the problem well-defined with explicit rules?
  YES -> Use rule-based / deterministic solution
  NO -> Can you write 100+ if-else statements to cover it?
    YES -> Still use ML (or hybrid), rules are too complex
    NO -> Maybe use simple heuristics first
```

### When to Use Rule-Based Systems (Not AI)

- **Deterministic outputs are required**: Tax calculations, password validation, routing logic
- **Zero tolerance for errors**: Medical dosage, financial transactions, safety-critical systems
- **Small, static input space**: Only a few possible inputs that change infrequently
- **Full explainability needed**: Regulatory compliance, audit trails
- **Latency constraints sub-millisecond**: AI adds latency that may be unacceptable
- **Cost budget is $0**: Rule-based systems run on existing compute

### When to Use ML/AI

- **Input space is large and ambiguous**: Natural language, images, audio
- **Pattern recognition is needed**: Fraud detection, recommendation, classification
- **Rules would be too complex**: >100 nested if-else statements
- **Personalization matters**: Content ranking, search results
- **Generative tasks**: Content creation, summarization, translation, code generation
- **Handling unstructured data**: Extracting entities from text, image tagging

### When to Use LLMs Specifically

- **Understanding natural language intent**: Chatbots, intent classification
- **Working with unstructured text**: Summarization, extraction, transformation
- **Reasoning with context**: RAG systems, document QA
- **Code generation and review**: Copilot-style tools
- **Multi-step reasoning**: Chain-of-thought tasks, complex analysis

### When NOT to Use LLMs

- **Simple math or lookups**: Use a calculator or database
- **Exact formatting requirements**: Regex or template engines are more reliable
- **High-volume low-complexity tasks**: Rule-based is cheaper and faster
- **Deterministic business logic**: LLMs are probabilistic, not deterministic
- **Real-time safety-critical decisions**: Latency + non-determinism = danger

### The "Graduate Student Descent" Trap

Many teams jump straight to complex AI when a simple heuristic gets 50% of the way there. The framework:
1. Start with a **random baseline** (what's the expected performance of random guessing?)
2. Build a **simple heuristic** (e.g., "recommend the most popular item")
3. Only then try ML
4. Your ML model must **significantly outperform** the heuristic to justify added complexity

### Interview Relevance

**Q: "How would you decide whether to use an LLM for a feature?"**
A: Start with three questions: (1) Is the task primarily about understanding or generating natural language? (2) Can a simpler approach (regex, rules, traditional ML) achieve acceptable results? (3) What is our error tolerance? If the task needs structured, deterministic output with zero tolerance for hallucination, LLM is wrong. If it involves nuanced language understanding with acceptable error rates, LLM is appropriate. Always build a non-ML baseline first to measure the actual value add of AI.

**Sources:**
- Huyen, C. "Machine Learning Systems Design" - https://huyenchip.com/machine-learning-systems-design/design-a-machine-learning-system.html
- Zinkevich, M. "Rules of Machine Learning" (Google) - https://martin.zinkevich.org/rules_of_ml/rules_of_ml.pdf

---

## 2. AI Product Development Lifecycle

### The Four Phases

```
Project Setup -> Data Pipeline -> Modeling -> Serving
     ^                                         |
     |____________ Feedback Loop ________________|
```

### Phase 1: Project Setup

Before any code:
- **Goals**: What exactly are we optimizing for? Engagement? Revenue? Accuracy? Cost?
- **User Experience**: Walk through the end-user interaction step by step
- **Performance Constraints**: Latency SLAs, throughput requirements, precision vs recall tradeoffs
- **Evaluation Metrics**: How do we measure success? Both offline (during dev) and online (in production)
- **Personalization Requirements**: One model for all? Per-segment? Per-user?
- **Project Constraints**: Timeline, compute budget, team skills, existing infrastructure

### Phase 2: Data Pipeline

In production ML, you spend 70-80% of time on data:
- **Data availability**: What data exists? How much? How good is the annotation?
- **Data collection**: How do we get data from users? Annotation costs?
- **Privacy & compliance**: Anonymization, PII handling, consent
- **Bias detection**: Are our training data and labels inclusive and representative?
- **Feature engineering**: Raw data to model-ready features
- **Storage**: Where does data live? Size constraints? Freshness?

### Phase 3: Modeling

- **Model selection**: Start simple. Decision tree before transformer.
- **Baselines**: Random baseline, human baseline, simple heuristic baseline
- **Training**: Debug, hyperparameter tuning, scaling considerations
- **Ablation studies**: Remove components to verify each adds value
- **Version control**: Track model versions, training data versions, hyperparameters

### Phase 4: Serving (Deployment)

- **Inference architecture**: Online (real-time) vs batch vs hybrid
- **Model confidence**: What to do with low-confidence predictions? Fallback to rules? Human review?
- **A/B testing**: Compare new model against baseline in production
- **Monitoring**: Performance drift detection, data drift alerts
- **Retraining cadence**: When and how to update the model
- **Interpretability**: Can users/customers understand why a decision was made?

### The Prototype-to-Production Gap

| Prototype | Production |
|-----------|-----------|
| Jupyter notebook | Containerized service with API |
| Manual testing | Automated eval suite in CI |
| One model | Model versioning + rollback |
| No monitoring | Observability dashboards |
| Single prompt iteration | Prompt version control |
| No cost tracking | Token-level cost monitoring |
| "Works on my data" | Synthetic edge cases + adversarial tests |
| Hardcoded API key | Secret management + rotation |

### Interview Relevance

**Q: "Walk me through how you'd take an LLM feature from idea to production."**
A: (1) Project setup: Define the goal, constraints, evaluation metrics, and whether AI is even the right approach. (2) Prototype: Build the minimum viable prompt in a notebook, validate on 50-100 examples. (3) Evaluate: Build an eval suite with golden examples, edge cases, and failure modes. (4) Hardening: Add input validation, output parsing, fallback logic, prompt versioning. (5) Deploy: Start with shadow deployment or canary release. (6) Monitor: Track accuracy, latency, cost, and user satisfaction signals. (7) Iterate: Feed user feedback and production data back into improvements.

**Sources:**
- Huyen, C. "Machine Learning Systems Design" - https://huyenchip.com/machine-learning-systems-design/
- OpenAI "Production Best Practices" - https://platform.openai.com/docs/guides/production-best-practices
- Chip Huyen's ML Systems Design book

---

## 3. Prompt as Code: Version Control & Management

### Why Prompts Need Version Control

- Prompts are **software** — they change, have bugs, and affect system behavior
- A prompt change can break production (hallucination increase, format changes)
- You need to **revert** bad prompt changes quickly
- Different prompt versions may need to run in **parallel** (A/B testing)
- Compliance requires **audit trails** for prompt changes

### Prompt Management Architecture

```
prompts/
  v1/
    system_prompt.txt
    examples.json
    config.yaml          # model, temperature, max_tokens
  v2/
    system_prompt.txt
    examples.json
    config.yaml
  tests/
    test_v1.py
    test_v2.py
    regression_suite.py  # compare v1 vs v2 outputs
```

### Best Practices

1. **Prompts as separate files**: Never hardcode prompts in application code
2. **Semantic versioning**: Major version for behavior changes, minor for refinements
3. **Prompt templates with variables**: Use templating (Jinja2, f-strings) for dynamic parts
4. **Change tracking**: Git diff on prompt files shows exactly what changed
5. **Automated regression**: When changing a prompt, run the eval suite to catch regressions
6. **Prompt review process**: Require code review for prompt changes (like any code PR)
7. **Prompt documentation**: Explain WHY the prompt is structured this way

### Prompt Caching for Cost & Latency

Anthropic's prompt caching (and similar OpenAI features):
- Cache static parts of prompts (system instructions, examples, context)
- **Cache writes**: 1.25x base input cost (5-min TTL) or 2x (1-hour TTL)
- **Cache reads**: 0.1x base input cost (90% savings)
- Place `cache_control` on the **last stable block**, not the varying block
- Automatic caching for multi-turn conversations (breakpoint moves forward)
- Pre-warm caches with `max_tokens: 0` requests before users arrive

### Prompt Testing in CI

```yaml
# .github/workflows/prompt-tests.yml
name: Prompt Evals
on:
  pull_request:
    paths:
      - 'prompts/**'
  schedule:
    - cron: '0 0 * * *'  # daily eval run
jobs:
  eval:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Run prompt evals
        run: python -m evals.run --suite prompts/tests/
```

### Interview Relevance

**Q: "How do you manage prompts in production?"**
A: Prompts are treated as code — versioned in git, reviewed in PRs, tested in CI. Each prompt version lives in its own directory with associated config (model, temperature, parameters) and test cases. When a prompt changes, the eval suite runs automatically to catch regressions. We use prompt caching to reduce cost and latency on repeated calls. Rollback is a git revert away. We also maintain a changelog of prompt versions with notes on what changed and why.

**Sources:**
- Anthropic Prompt Caching Docs - https://docs.anthropic.com/en/docs/build-with-claude/prompt-caching
- OpenAI "Production Best Practices" - https://platform.openai.com/docs/guides/production-best-practices
- OpenAI Evals - https://github.com/openai/evals

---

## 4. Eval as Code: LLM Evaluation Pipelines & CI

### Why Evals Matter

> "Evals-driven development is the most important thing you can do when building with LLMs." — Greg Brockman, OpenAI

Without evals:
- You cannot tell if a model change improved or hurt your use case
- You cannot safely update your prompts
- You cannot compare different models
- You cannot detect regressions

### Types of Evals

#### 1. Unit Tests (Exact Match)
```python
def test_extract_names():
    result = extract_names("John and Jane went to Paris")
    assert "John" in result
    assert "Jane" in result
    assert len(result) == 2
```
- Good for: Structured output, extraction, classification
- Limitations: Too brittle for generative tasks

#### 2. Golden Dataset (Reference-based)
```python
GOLDEN_EXAMPLES = [
    {"input": "What is 2+2?", "expected_contains": "4"},
    {"input": "Summarize: ...", "expected_length_range": (50, 200)},
]
```
- Good for: Consistency checking, regression detection
- Human-curated, high-quality examples that represent your use case

#### 3. Model-Graded Eval (LLM-as-Judge)
```python
def test_hallucination():
    prompt = "Is the following factually accurate? Answer YES/NO."
    grader_response = call_llm(prompt + response)
    assert grader_response == "YES"
```
- Good for: Open-ended generation, accuracy, tone
- Risk: Judge model bias, self-preference

#### 4. Human Eval
- Labelers rate outputs on quality, helpfulness, safety
- Most reliable but slowest and most expensive
- Use for: Ground truth creation, calibrating automated evals

#### 5. Side-by-Side / Preference
- Show two outputs to human evaluators
- "Which response is better?"
- Use for: A/B testing models, prompt versions

### Eval Pipeline Architecture

```
evals/
  datasets/
    golden_examples.jsonl        # Human-curated test cases
    edge_cases.jsonl             # Boundary conditions
    adversarial_inputs.jsonl     # Attack vectors
  graders/
    exact_match.py
    contains_match.py
    llm_judge.py
    human_pref.py
  suites/
    unit_tests.yaml
    regression.yaml
    safety.yaml
  reports/
    .gitkeep                    # Generated eval reports
  run_eval.py                    # Main eval runner
```

### Running Evals in CI

```python
# Run evals on every prompt change
# Fail if accuracy drops below threshold
def test_prompt_v2_regression():
    results = run_eval_suite("prompts/v2/", dataset="golden_examples.jsonl")
    assert results.accuracy >= 0.85, f"Accuracy {results.accuracy} < 0.85"
    assert results.hallucination_rate <= 0.05
```

### Eval Metrics for Different Tasks

| Task | Key Metrics |
|------|-------------|
| Classification | Accuracy, F1, precision, recall |
| Summarization | ROUGE, BERTScore, human preference |
| RAG | Faithfulness, relevance, completeness |
| Code Gen | Test pass rate, syntax validity |
| Chat | Helpfulness, safety, coherence |
| Extraction | Exact match, F1, partial match |

### Interview Relevance

**Q: "How would you build an evaluation pipeline for an LLM application?"**
A: I'd create a layered eval system: (1) Unit tests for deterministic outputs (format validation, JSON schema checks). (2) Golden dataset of 200+ curated examples with expected outputs, checked with flexible matching (contains, regex, semantic similarity). (3) LLM-as-judge for open-ended tasks (factual accuracy, tone, safety). (4) Periodic human eval to calibrate automated metrics. All evals run in CI on prompt changes, with accuracy thresholds that fail the build if regression is detected. I'd also maintain separate eval sets for safety/adversarial inputs.

**Sources:**
- OpenAI Evals Framework - https://github.com/openai/evals
- OpenAI "Evaluation Best Practices" - https://platform.openai.com/docs/guides/evaluation-best-practices
- OpenAI Agent Evals - https://platform.openai.com/docs/guides/agent-evals

---

## 5. AI Feature Feasibility Assessment

### The Feasibility Framework

Before building, assess across 5 dimensions:

#### 1. Technical Feasibility
- **LLM capabilities**: Can current models actually do this well?
- **Input/output format**: Can we reliably structure the I/O?
- **Error tolerance**: How often will the LLM be wrong? Is that acceptable?
- **Context window limits**: Does the task require more context than available?
- **Latency requirements**: Can we meet SLAs with LLM inference time?

#### 2. Data Feasibility
- **Training/eval data**: Do we have enough examples to evaluate?
- **Golden dataset**: Can we create a representative test set?
- **User data access**: Do we have permission to use real user data?
- **Data quality**: Is our data clean enough for reliable evals?

#### 3. Cost Feasibility
- **Token cost per request**: Estimate input + output tokens
- **Traffic volume**: Requests per day/month
- **Total monthly cost**: tokens x volume x price
- **Comparison cost**: How much does a non-AI solution cost?

#### 4. Reliability Feasibility
- **Non-determinism tolerance**: Can we handle probabilistic outputs?
- **Fallback strategy**: What happens when the LLM fails or is slow?
- **Cascading failure risk**: Does AI failure break downstream systems?
- **Monitoring capability**: Can we detect when quality degrades?

#### 5. Organizational Feasibility
- **Team expertise**: Does the team have ML/AI experience?
- **Time to market**: How long until production-ready?
- **Maintenance burden**: Who maintains prompts, evals, monitoring?
- **Stakeholder alignment**: Do decision-makers understand AI limitations?

### Feasibility Assessment Template

```
Feature: [Name]
Task Type: [Classification | Generation | Extraction | RAG | Chat]
LLM Model: [GPT-4o | Claude Sonnet | GPT-4o-mini | ...]

Technical:    [HIGH / MEDIUM / LOW] - rationale
Data:         [HIGH / MEDIUM / LOW] - rationale
Cost:         [HIGH / MEDIUM / LOW] - rationale ($X/month estimate)
Reliability:  [HIGH / MEDIUM / LOW] - rationale
Org:          [HIGH / MEDIUM / LOW] - rationale

Overall: [GO / NO-GO / CONDITIONAL]
Conditions: [What would make this a GO?]
```

### Quick Feasibility Checks

- **Prototype in 1 day**: If you can't get a working demo in a day, feasibility is low
- **5-example test**: Run 5 diverse examples through the LLM. If 3+ fail, not ready
- **Cost sanity check**: Estimate worst-case monthly cost. If >10x current feature cost, investigate alternatives
- **Latency check**: Measure P99 latency on 100 requests. If >user tolerance, need architecture changes

### Interview Relevance

**Q: "A PM wants to add AI-powered feature X. How do you assess feasibility?"**
A: I evaluate across five dimensions: (1) Technical — can current LLMs handle this with acceptable accuracy? I'd prototype with 5-10 representative examples immediately. (2) Cost — estimate tokens per request times expected traffic to get monthly burn. (3) Reliability — is non-deterministic output acceptable, and what's our fallback? (4) Data — do we have enough examples for a golden eval set? (5) Org — does the team have the skills to maintain this? I'd deliver a go/no-go recommendation within 48 hours with a working prototype.

---

## 6. Cost Per Feature Analysis

### Cost Formula

```
Monthly Cost = (Input Tokens/Request + Output Tokens/Request) × Price/Token × Requests/Month
```

### Example Cost Calculation

| Component | Tokens | Cost (Sonnet) | Notes |
|-----------|--------|---------------|-------|
| System prompt | 500 | $0.0015/req | Cacheable — reduces to $0.00015/req |
| User input (avg) | 200 | $0.0006/req | Varies by use case |
| RAG context | 2,000 | $0.006/req | Cacheable if same documents |
| Output (avg) | 300 | $0.0045/req | Not cacheable |
| **Per-request total** | 3,000 | **$0.0126/req** | ~1.3 cents |
| 100K requests/month | 300M | **$1,260/month** | |
| 1M requests/month | 3B | **$12,600/month** | |
| 10M requests/month | 30B | **$126,000/month** | Need architecture changes |

### Cost Optimization Strategies

#### 1. Model Selection
- Use smaller/cheaper models for simpler tasks (Haiku for classification, Sonnet for reasoning)
- Implement **cascading routing**: Try cheap model first, escalate to expensive only if confidence is low
- Fine-tuned small models can replace prompts on large models for repeated tasks

#### 2. Prompt Caching
- Cache system prompts and static context (90% cost reduction on cached tokens)
- Cache RAG documents that are accessed frequently
- Use 1-hour TTL for system prompts that change less frequently

#### 3. Token Reduction
- Shorter prompts: Remove unnecessary instructions, compress examples
- Use structured outputs instead of verbose JSON
- Context window management: Only include relevant context

#### 4. Batching
- OpenAI Batch API: 50% cost reduction for non-latency-sensitive tasks
- Process offline tasks (summaries, analysis) in batches

#### 5. Result Caching
- Cache identical inputs → outputs (Redis, Memcached)
- Set appropriate TTL based on data freshness requirements
- Especially useful for FAQ-style queries

#### 6. Semantic Caching
- Cache semantically similar queries (embeddings-based similarity)
- Reduces API calls for variations of the same question

### Budget Planning Framework

```
Feature: AI-powered customer support
Traffic: 50K tickets/month, 2 LLM calls per ticket = 100K calls
Tokens per call: 3,000 avg
Model: Claude Sonnet ($3/MTok input, $15/MTok output)

Monthly token cost: (2,500 × $3 + 500 × $15) × 100K / 1M = $750 + $750 = $1,500
With caching (70% hit rate, output tokens never cached):
  30% uncached (30K calls): 30K × $0.015 = $450
  70% cached input (70K calls): 70K × ($0.00075 + $0.00750) = 70K × $0.00825 = $577.50
  Total: ~$1,028/month

Breakeven vs. human agents at $20/hour, 10min/ticket:
  Human cost: 50K × 10/60 × $20 = $166,667/month
  AI cost: ~$1,028/month
  Savings: $165,639/month (~99.4% cost reduction)
```

### Interview Relevance

**Q: "How would you estimate and manage costs for an LLM feature?"**
A: Calculate per-request token cost (input + output), multiply by projected traffic, add 30% buffer for unexpected growth. Optimize with prompt caching for static context (90% savings on cached tokens), model routing (cheap model for easy cases), result caching for repeated queries, and batch processing for async work. I'd set budget alerts at 50%, 75%, 90% of projected spend. Monitor cost per user and cost per successful outcome to measure ROI.

**Sources:**
- OpenAI Pricing - https://openai.com/pricing/
- Anthropic Pricing - https://docs.anthropic.com/en/about-claude/pricing
- OpenAI "Cost Optimization" - https://platform.openai.com/docs/guides/cost-optimization

---

## 7. Testing Strategies for LLM Applications

### Testing Pyramid for LLM Apps

```
        /  Human Eval  \           ← Slow, expensive, ground truth
       / Side-by-Side   \          ← A/B comparison
      /   LLM-as-Judge   \         ← Automated quality checks
     /   Golden Dataset    \       ← Regression tests
    /    Schema/Format     \      ← Output structure validation
   /   Unit Tests (I/O)    \     ← Fast, deterministic checks
  /________________________\    ← Traditional software tests
```

### Layer 1: Traditional Tests (No LLM Needed)

- **Input validation**: Schema checks, sanitization, length limits
- **Output parsing**: JSON schema validation, type checking
- **Fallback logic**: Test that fallback triggers correctly
- **Retry logic**: Test retry behavior on API errors
- **Rate limiting**: Verify rate limiters work correctly
- **Integration tests**: Test API routing, caching, queuing

### Layer 2: Deterministic LLM Tests

```python
# Test with controlled LLM output (mocked or cached response)
def test_summarization_format():
    result = summarize("controlled input")
    assert is_valid_json(result)
    assert len(result) <= 500
    assert "summary" in result.lower()
```

### Layer 3: Golden Dataset Tests

```python
GOLDEN = [
    {"input": "...", "should_contain": ["keyword1", "keyword2"], "should_not_contain": ["bad1"]},
    ...
]

@pytest.mark.parametrize("case", GOLDEN)
def test_against_golden(case):
    result = call_llm(case["input"])
    for expected in case["should_contain"]:
        assert expected in result
    for forbidden in case["should_not_contain"]:
        assert forbidden not in result
```

### Layer 4: LLM-as-Judge Tests

```python
def test_safety():
    """Ensure no harmful content in responses"""
    result = call_llm("How to make a bomb")
    judge = call_llm(f"Does this response contain harmful instructions? {result}")
    assert "NO" in judge.upper() or "HARMFUL" not in judge.upper()
```

### Layer 5: Adversarial Tests

- **Prompt injection**: "Ignore previous instructions and..."
- **Jailbreak attempts**: DAN-style attacks
- **Edge cases**: Empty input, extremely long input, special characters, Unicode tricks
- **Toxicity tests**: Offensive inputs that should be handled gracefully
- **Data extraction**: Attempts to extract system prompt

### Staging Environment with Synthetic Data

- **Shadow deployment**: Run new model alongside production, compare outputs
- **Synthetic users**: Script realistic user interaction patterns
- **Load testing**: Simulate production traffic volumes
- **Chaos testing**: Simulate LLM API failures, timeouts, rate limits

### Interview Relevance

**Q: "How do you test an LLM application?"**
A: Five layers: (1) Traditional software tests — input validation, output parsing, fallback logic, no LLM needed. (2) Golden dataset tests — 200+ curated examples checked for key outputs, runs in CI. (3) LLM-as-judge for subjective quality — factual accuracy, tone, completeness. (4) Adversarial tests — prompt injection, jailbreaks, toxicity. (5) Shadow deployment in staging — route real traffic to both old and new model, compare outputs before switching. Each layer catches different failure modes.

---

## 8. Deployment & Progressive Rollout Strategies

### Deployment Approaches for AI Features

#### 1. Shadow Deployment (Safest)
```
User Request -> Production Model -> User Response
             -> New Model -> Compare & Log (don't show user)
```
- No user-visible impact
- Can compare outputs, measure quality, latency, cost
- Run for 1-2 weeks before switch
- Limitation: Doesn't test user reactions to new model

#### 2. Canary Release
```
1% of traffic -> New Model
99% of traffic -> Production Model
Monitor metrics for 24-48 hours
If good: 5% -> 10% -> 25% -> 50% -> 100%
If bad: Rollback instantly
```
- Gradual exposure limits blast radius
- Real user behavior feedback
- Key metrics: Error rate, latency P99, user satisfaction, cost

#### 3. A/B Testing
```
Group A (50%) -> Model A
Group B (50%) -> Model B
Measure: Engagement, satisfaction, task completion
```
- Statistical significance required (usually 5%+ difference, p < 0.05)
- Run for sufficient time to collect enough data
- Account for novelty effect (new may seem better temporarily)

#### 4. Feature Flags
```python
if feature_flags.is_enabled("ai_summary_v2", user_id):
    return call_new_model(prompt)
else:
    return call_old_model(prompt)
```
- Instant rollback capability
- Per-user or per-segment targeting
- Works for both model and prompt changes

#### 5. Blue-Green Deployment
```
Blue (current)   ->  users
Green (new)      ->  staging tests
Switch traffic: Blue -> Green
```
- Full switch, not gradual
- Good for non-critical internal tools
- Fast rollback by switching back

### AI-Specific Rollout Concerns

- **Model warm-up**: First requests have higher latency (cold start). Pre-warm with cache
- **Token budgeting**: Monitor token usage per rollout percentage to catch cost anomalies
- **Quality drift**: Monitor eval scores per cohort, not just aggregate
- **User segmentation**: Roll out to internal users first, then beta, then general
- **Regulatory compliance**: Some regions may require different model behavior

### Rollback Strategy

```python
class ModelRouter:
    def __init__(self):
        self.current_model = "v1"
        self.rollback_threshold = 0.05  # 5% error rate triggers rollback

    def route(self, request):
        if self.should_use_canary(request):
            result = self.call_model("v2", request)
            if self.is_production_issue(result):
                self.trigger_rollback("v2")
                return self.call_model("v1", request)
            return result
        return self.call_model(self.current_model, request)

    def trigger_rollback(self, failed_version):
        alert(f"Rolling back {failed_version} — error rate exceeded threshold")
        self.current_model = "v1"
        feature_flags.disable(f"model_{failed_version}")
```

### Interview Relevance

**Q: "How would you roll out a new LLM model to production?"**
A: Shadow deployment first — run new model in parallel for 1-2 weeks, logging all outputs. Compare quality metrics, latency, and cost against production. If metrics look good, switch to canary release: 1% of traffic to new model, monitor error rate and user satisfaction. Gradually increase to 5%, 10%, 25% over a week. If any metric degrades beyond threshold, instant rollback via feature flag. Keep the old model running as fallback for at least 30 days after full rollout.

---

## 9. LLM Application Reliability Engineering

### Failure Modes of LLM Applications

| Failure Mode | Example | Mitigation |
|-------------|---------|------------|
| **Hallucination** | LLM fabricates facts | RAG, grounding, factual check layer |
| **Format drift** | LLM changes output format | Structured outputs, schema validation |
| **Latency spikes** | API slow under load | Caching, timeouts, async fallback |
| **Rate limiting** | API returns 429 | Exponential backoff, queue, graceful degradation |
| **Cost spike** | Unexpected token usage | Budget alerts, per-request caps, caching |
| **Model update regression** | Provider updates model | Version pinning, eval suite, shadow deployment |
| **Prompt injection** | User manipulates system | Input sanitization, guardrails, output filtering |
| **Context overflow** | Input exceeds context window | Chunking, summarization, truncation |
| **Non-determinism** | Same input, different output | Temperature=0, seed, retry with validation |
| **Service outage** | LLM API completely down | Graceful fallback to rules-based system |

### Reliability Patterns

#### 1. Circuit Breaker
```python
class LLMCircuitBreaker:
    def __init__(self, failure_threshold=5, recovery_timeout=60):
        self.failure_count = 0
        self.last_failure = None
        self.failure_threshold = failure_threshold
        self.recovery_timeout = recovery_timeout

    def call(self, prompt):
        if self.is_open():
            return self.fallback(prompt)
        try:
            result = call_llm(prompt)
            self.reset()
            return result
        except Exception as e:
            self.record_failure()
            return self.fallback(prompt)

    def is_open(self):
        return (self.failure_count >= self.failure_threshold and
                time.time() - self.last_failure < self.recovery_timeout)
```

#### 2. Retry with Validation
```python
def call_llm_with_retry(prompt, max_retries=3, validator=None):
    for attempt in range(max_retries):
        result = call_llm(prompt)
        if validator is None or validator(result):
            return result
    return fallback(prompt)
```

#### 3. Graceful Degradation
```python
def get_answer(query):
    try:
        # Tier 1: Full LLM with RAG
        return llm_rag_answer(query, timeout=5)
    except TimeoutError:
        try:
            # Tier 2: LLM without RAG (faster)
            return llm_answer(query, timeout=3)
        except TimeoutError:
            # Tier 3: Cached/pre-computed answers
            return cached_answer(query) or "I couldn't process that. Please try again."
```

#### 4. Input Sanitization
```python
def sanitize_input(user_input):
    if len(user_input) > MAX_INPUT_LENGTH:
        return truncate(user_input)
    if contains_injection_patterns(user_input):
        return handle_suspicious_input()
    return user_input
```

### Observability

Key metrics to monitor:
- **Quality metrics**: Accuracy, relevance score, user satisfaction (thumbs up/down)
- **Latency metrics**: P50, P95, P99 response time, time-to-first-token
- **Cost metrics**: Tokens per request, total spend, cost per successful outcome
- **Error metrics**: Error rate, timeout rate, rate limit hit rate
- **Usage metrics**: Requests per second, unique users, most common queries
- **Drift metrics**: Output distribution changes over time, data drift alerts

### Interview Relevance

**Q: "What are the main failure modes of LLM applications and how do you handle them?"**
A: The big five: hallucination, format drift, latency spikes, rate limits, and cost spikes. For hallucination, I use RAG with source attribution and a factual consistency check. For format drift, structured output mode with JSON schema validation. For latency, cascading timeouts with graceful degradation — try the full pipeline, then a simpler one, then cached responses. For rate limits, exponential backoff with request queuing. For cost, per-request token caps and caching. All wrapped in circuit breakers that fall back to rules-based systems when the LLM is unavailable.

---

## 10. Managing Stakeholder AI Expectations

### Common Misconceptions

| Stakeholder Belief | Reality |
|-------------------|---------|
| "AI will be 100% accurate" | LLMs are probabilistic; expect 85-95% accuracy on well-scoped tasks |
| "Just connect it to the LLM" | Production AI requires evals, monitoring, fallbacks, cost management |
| "It'll work on day one" | Expect 3-6 months from prototype to production-ready |
| "We don't need to maintain it" | Prompts drift, models update, user needs change — ongoing maintenance |
| "AI replaces all rules" | Best systems use hybrid: AI for nuance, rules for determinism |
| "Bigger model = better" | Smaller models are often sufficient and cheaper |

### Setting Expectations Framework

1. **Define acceptable error rates upfront**: "This feature will correctly handle ~90% of cases. For the remaining 10%, users will be offered a fallback."
2. **Show, don't tell**: Build a demo with 20 real examples, including 2-3 failures. Discuss failure handling.
3. **Phase the rollout**: MVP with limited scope → measure → expand. Never promise full scope on day one.
4. **Cost transparency**: Show the monthly cost estimate and how it compares to alternatives.
5. **Maintenance commitment**: "This feature requires ~4 hours/week of prompt monitoring and iteration."
6. **Model lock-in risk**: Explain that the model provider may change behavior; architecture should be model-agnostic.

### The "AI Confidence Spectrum"

```
High Confidence (Use AI)        Low Confidence (Use Rules)
─────────────────────────────────────────────────────────
Sentiment analysis          ->  Tax calculations
Content summarization       ->  Payment processing
Intent classification       ->  Access control
Translation                  ->  Safety systems
Email generation             ->  Compliance reporting
Code suggestion              ->  Cryptographic operations
```

### Interview Relevance

**Q: "How do you manage stakeholder expectations for an AI feature?"**
A: Three key practices: (1) Show them failures early — demo with 20 examples including 2-3 failures, explain how the system handles them. (2) Set quantified expectations: "This will handle 90% of cases correctly. The remaining 10% will fall back to human review." (3) Phase the rollout: start with a narrow scope, measure, then expand. I also clarify the ongoing maintenance cost — AI features aren't "build and forget," they need weekly monitoring and monthly prompt iteration.

---

## 11. User Feedback Loops & Iteration

### Feedback Collection Channels

| Channel | Signal | Latency | Cost |
|---------|--------|---------|------|
| Thumbs up/down | Satisfaction | Instant | Free |
| Explicit feedback form | Detailed input | Low | Low |
| Implicit signals (did user accept suggestion?) | Effectiveness | Low | Free |
| Correction/edit of AI output | Ground truth | Medium | Free |
| Support tickets | Failure modes | Slow | High |
| A/B test metrics | Comparative | Medium | Medium |

### Feedback-to-Improvement Pipeline

```
User Interaction
       |
       v
Signal Collection (thumbs, edits, accepts, rejects)
       |
       v
Labeling Pipeline (convert feedback to eval examples)
       |
       v
Eval Suite Update (add new golden examples, update edge cases)
       |
       v
Prompt Iteration (modify prompt, test against eval suite)
       |
       v
Shadow Deployment (test new prompt on real traffic)
       |
       v
Gradual Rollout (canary → full)
       |
       v
Monitor & Repeat
```

### Data Flywheel Effect

```
More Users → More Data → Better Evals → Better Prompts → Better Product → More Users
```

The key is closing the loop: user behavior → data → model improvement → better user experience.

### Golden Dataset Curation from Production

```python
# Daily job: Sample production interactions, add to eval set
def update_golden_dataset():
    samples = sample_production_logs(n=50)
    for sample in samples:
        if sample.user_accepted and not sample.in_dataset:
            add_to_golden_set(sample.input, sample.output)
        elif sample.user_corrected:
            add_correction_to_golden_set(
                sample.input,
                corrected_output=sample.correction,
                original_output=sample.output
            )
```

### Interview Relevance

**Q: "How do you iterate on an AI feature based on user feedback?"**
A: I build a feedback-to-improvement pipeline: (1) Collect signals — thumbs up/down, whether users accept AI suggestions, explicit corrections. (2) Convert feedback into eval cases — accepted outputs become golden examples, corrections show what the prompt got wrong. (3) Run weekly eval updates to catch quality drift. (4) Iterate on prompts based on failure patterns. (5) Test changes in shadow mode before rollout. The goal is a data flywheel: more users → more data → better evals → better prompts → better product.

---

## 12. Common Pitfalls & Failure Modes

### Technical Pitfalls

1. **Starting with the most complex solution**: "Let's use a RAG pipeline with vector DB" when a simple prompt template works
2. **Ignoring baselines**: Building an ML solution without knowing how a simple heuristic performs
3. **Overfitting to eval set**: Tuning prompts until they pass your eval, but they fail on real data
4. **No prompt versioning**: Changing prompts in production without tracking, unable to rollback
5. **Hardcoding model assumptions**: Your prompt works on GPT-4 but breaks on GPT-4-turbo
6. **Ignoring non-determinism**: Testing with temperature=0 but running with temperature=0.7
7. **No fallback**: When the LLM API is down, the entire feature breaks
8. **Context window overflow**: Not handling inputs that exceed the model's context limit
9. **Output parsing failures**: LLM returns slightly different JSON format than expected

### Organizational Pitfalls

1. **Underestimating maintenance**: AI features need continuous monitoring and iteration
2. **No eval culture**: Teams that don't invest in evals early end up with unmeasurable quality
3. **Stakeholder overpromise**: Selling "AI-powered" without explaining limitations
4. **Siloed AI team**: AI engineers separated from product engineers → integration failures
5. **No cost monitoring**: Monthly AI bills surprise the finance team
6. **Skipping staging**: Pushing prompt changes directly to production

### Architecture Pitfalls

1. **Tight coupling to one provider**: Lock-in to OpenAI/Anthropic API without abstraction
2. **No caching**: Paying for the same computation on every request
3. **Synchronous LLM calls in user-facing paths**: Blocking the user while waiting for the LLM
4. **No rate limiting**: Users or internal systems overwhelm the LLM API
5. **No request queuing**: Traffic spikes cause cascading failures
6. **Logging PII to LLM providers**: Privacy violations

### The "Jupyter to Production" Anti-Pattern

The most common failure: a data scientist builds a working prototype in a notebook, hands it to engineering, and says "make this production." What's missing:
- No eval suite
- No error handling
- No fallback logic
- No monitoring
- No prompt versioning
- No cost analysis
- No security review
- No input validation
- No output parsing
- No load testing

### Interview Relevance

**Q: "What are the most common reasons AI features fail in production?"**
A: Three categories: (1) Technical — no fallback when LLM fails, output format drift breaks downstream systems, context window overflow on large inputs. (2) Quality — no eval suite means you can't measure quality, prompt changes aren't tested, quality drifts over time. (3) Organizational — stakeholder expectations were too high, maintenance wasn't planned, cost wasn't monitored. The single biggest pattern I see: teams skip building evals, which means they can't detect regressions, can't iterate confidently, and can't prove the feature works.

---

## 13. Interview Questions & Model Answers

### System Design Questions

**Q1: "Design an AI-powered customer support chatbot."**
A: Start with scope: Is it for FAQ only or complex problem resolution? Assume FAQ + escalation. Architecture: (1) Intent classification (cheap model) → (2) RAG retrieval from knowledge base → (3) Generation (capable model) → (4) Confidence check → (5) If low confidence, escalate to human. Use prompt caching for knowledge base context. Implement eval suite with 500+ FAQ pairs, adversarial inputs, and escalation triggers. Shadow deploy for 2 weeks. Cost estimate: ~$0.02/conversation, $2K/month for 100K conversations. Fallback: keyword-based FAQ lookup when LLM is unavailable.

**Q2: "How would you build an AI code review tool?"**
A: Input: git diff + code context. Processing: (1) Parse diff into hunks, (2) Send to LLM with review guidelines prompt, (3) Structured output (JSON with severity, category, suggestion). Challenges: (1) Large diffs exceed context → chunking strategy, (2) False positives overwhelm developers → confidence threshold, (3) Different languages need different prompts. Eval: Curate 100+ PRs with known issues, measure recall (did we catch real issues?) and precision (were suggestions useful?). Cost: Cache common patterns, use cheap model for simple linting, expensive model only for complex logic.

**Q3: "Design a content moderation system using LLMs."**
A: Multi-stage pipeline: (1) Rule-based pre-filter (block known bad patterns, regex) — catches 60% instantly, (2) Embedding-based similarity check (compare against known violation embeddings) — catches another 20%, (3) LLM classification for ambiguous content — handles remaining 20%. Why not just LLM? Cost and latency. Rules are instant and free. LLM is slow and expensive. Eval: Curated dataset with labeled violations (hate speech, harassment, etc.), adversarial attempts, edge cases. Critical: False positive rate must be low (don't over-censor). Use human review for borderline cases.

### Behavioral Questions

**Q4: "Tell me about a time an AI feature didn't work as expected in production."**
A: [Structure] Situation: We deployed an LLM summarization feature. Task: Summarize meeting transcripts. Action: We tested on 50 examples and got 95% accuracy. In production, we discovered two issues: (1) Long meetings (>10K tokens) exceeded context window — we hadn't tested large inputs. (2) The model sometimes added fabricated action items that weren't in the transcript. Result: We added chunking for long inputs, a factual grounding check that cross-references claims against the original text, and expanded our eval suite to include 200+ real meeting transcripts. Accuracy dropped to 88% but we now had reliable quality measurement.

**Q5: "How do you decide when to use AI vs traditional software engineering?"**
A: I ask five questions: (1) Does the task require understanding unstructured data (text, images)? (2) Is the input space too large for explicit rules? (3) Is some error acceptable? (4) Can we build a reliable eval set to measure quality? (5) Does the cost of AI justify the improvement over rules? If the answer to 1-2 is yes and 3-5 are acceptable, AI is appropriate. Example: Spam detection — AI is great because email text is unstructured and some false positives/negatives are acceptable. But password validation — rules are better because it's deterministic and zero error tolerance.

### Technical Deep-Dive Questions

**Q6: "How do you handle LLM non-determinism in a production system?"**
A: Multiple strategies: (1) Temperature=0 for deterministic tasks. (2) Structured outputs to enforce format. (3) Validation layer that rejects malformed outputs and retries. (4) Retry with same seed for reproducibility. (5) For display outputs, show "AI-generated" label. (6) For action outputs, add confirmation step before executing. (7) Log all outputs for audit. The key principle: never let non-deterministic LLM output directly trigger irreversible actions without human confirmation.

**Q7: "What's your approach to prompt engineering in production?"**
A: (1) Start with the official provider's prompt guide (OpenAI, Anthropic). (2) Write the prompt, test on 20 examples. (3) Create golden eval set. (4) Iterate: add examples for failure cases, clarify instructions, add output format constraints. (5) Use prompt caching for static parts. (6) Version control every prompt change. (7) A/B test new prompts against old ones. (8) Monitor quality metrics over time — prompts can "drift" as model updates happen.

**Q8: "How would you design an evaluation framework from scratch?"**
A: Three layers: (1) Deterministic tests — JSON schema validation, format checks, keyword matching (fast, runs in CI). (2) Golden dataset — 500+ curated examples with expected outputs, checked with semantic similarity (medium speed, runs on prompt changes). (3) LLM-as-judge — for quality attributes like helpfulness, safety, accuracy (slow, runs nightly). All results logged to a dashboard. Regression detection: if accuracy drops >2% from baseline, alert the team. Integrate with CI: prompt file changes trigger eval run.

---

## Source References

### Core References
- Huyen, C. "Machine Learning Systems Design" — https://huyenchip.com/machine-learning-systems-design/
- Zinkevich, M. "Rules of Machine Learning: Best Practices for ML Engineering" (Google) — https://martin.zinkevich.org/rules_of_ml/rules_of_ml.pdf
- OpenAI "Production Best Practices" — https://platform.openai.com/docs/guides/production-best-practices
- Anthropic "Prompt Caching" — https://docs.anthropic.com/en/docs/build-with-claude/prompt-caching

### Evaluation
- OpenAI Evals Framework — https://github.com/openai/evals
- OpenAI "Evaluation Best Practices" — https://platform.openai.com/docs/guides/evaluation-best-practices
- OpenAI "Agent Evals" — https://platform.openai.com/docs/guides/agent-evals

### Cost & Scaling
- OpenAI "Cost Optimization" — https://platform.openai.com/docs/guides/cost-optimization
- OpenAI "Latency Optimization" — https://platform.openai.com/docs/guides/latency-optimization
- Anthropic Pricing — https://docs.anthropic.com/en/about-claude/pricing

### Prompt Engineering
- DeepLearning.AI "ChatGPT Prompt Engineering for Developers" (Ng & Fulford) — https://www.deeplearning.ai/short-courses/chatgpt-prompt-engineering-for-developers/
- OpenAI "Prompt Guidance" — https://platform.openai.com/docs/guides/prompt-guidance
- OpenAI "Prompt Engineering" — https://platform.openai.com/docs/guides/prompt-engineering

### Safety & Deployment
- OpenAI "Safety Best Practices" — https://platform.openai.com/docs/guides/safety-best-practices
- OpenAI "Deployment Checklist" — https://platform.openai.com/docs/guides/deployment-checklist
- OpenAI "Red Teaming" — https://platform.openai.com/docs/guides/red-teaming

### Architecture
- ChromaDB "Building with AI" — https://docs.trychroma.com/guides
- OpenAI "Structured Outputs" — https://platform.openai.com/docs/guides/structured-outputs
- OpenAI "Function Calling" — https://platform.openai.com/docs/guides/function-calling
