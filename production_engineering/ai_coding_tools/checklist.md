# AI-Assisted Development and Vibe Coding — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem in your own words: using AI coding tools in production without degrading system quality
- [ ] Identify the three loops to discuss:
  - [ ] Generation loop (how you produce drafts quickly)
  - [ ] Verification loop (how you prevent low-quality merges)
  - [ ] Learning loop (how prompts and guardrails improve over time)
- [ ] List the key non-negotiable controls:
  - [ ] Architecture constraints
  - [ ] Security guardrails
  - [ ] Human review accountability
  - [ ] Production verification gates
- [ ] Define measurable objectives:
  - [ ] Reduce cycle time by ~20% while holding change failure rate stable
  - [ ] No increase in escaped defects or rollback frequency
  - [ ] No prompt payload with secrets, credentials, or production customer data

## Phase 2: Core Workflow Design (3-5 min)
- [ ] Explain the PAIR loop workflow:
  - [ ] **P (Plan):** Define boundaries before prompting (touched modules, forbidden layers, performance budget, security requirements)
  - [ ] **A (Ask):** Generate in small, testable increments with explicit acceptance criteria
  - [ ] **I (Inspect):** Validate against codebase conventions, domain invariants, error-handling expectations
  - [ ] **R (Run):** Execute tests, lints, static analysis, security checks; feed failures back into prompt revisions
- [ ] Discuss vibe coding practices that scale vs. practices that fail:
  - [ ] Scale: prompt with boundaries, anchor to existing patterns, demand explainability, adversarial tests, human ownership
  - [ ] Fail: blind copy/paste, no architectural context, merging without test evidence, treating AI as authoritative in domain logic
- [ ] Present the task-type risk matrix:
  - [ ] Boilerplate scaffolding (High fit) -> provide reference file and naming constraints
  - [ ] Core domain logic (Medium fit) -> generate alternatives, validate with domain tests
  - [ ] Refactoring legacy code (Medium fit) -> require snapshot tests and incremental commits
  - [ ] Security-sensitive changes (Low-Medium fit) -> human-first design plus security checklist
  - [ ] Operational scripts/runbooks (High fit) -> ask for retry/timeouts and rollback notes

## Phase 3: Verification and Testing Strategy (5-8 min)
- [ ] Explain why AI-generated code needs more rigorous testing, not less:
  - [ ] Models optimize for local plausibility, not global correctness
  - [ ] Most common failure: tests assert implementation details rather than verify behavior
- [ ] Detail the five testing principles:
  - [ ] Behavior-focused tests (verify API contract, not internal states)
  - [ ] Property-based testing (Hypothesis, fast-check for systematic edge-case exploration)
  - [ ] Mutation testing (`mutmut`, `Stryker` to validate test effectiveness)
  - [ ] Manual adversarial cases (nulls, empty collections, timeouts, retries, race conditions, idempotency)
  - [ ] Coverage baselines pre/post generation (reject if AI drops coverage below baseline)
- [ ] Walk through the production-ready three-stage workflow:
  - [ ] Stage 1 (Constrained generation): scope boundaries, architectural constraints, performance requirements, security requirements, test expectations
  - [ ] Stage 2 (Deep verification): unit tests, integration tests, property-based tests, mutation testing, architecture linting, performance benchmarks, security scans, manual domain review
  - [ ] Stage 3 (Instrumented learning): pattern library, anti-pattern library, metrics dashboard, incident retrospectives

## Phase 4: Failure Modes and Debt Prevention (5-10 min, interviewer-directed)
- [ ] Describe the five production failure modes:
  - [ ] Architecture drift (bypasses established boundaries)
  - [ ] Test illusion (asserts implementation details, misses regressions)
  - [ ] Security leakage (sensitive values in prompts or weak auth defaults)
  - [ ] Context mismatch (generic patterns vs. your runtime constraints)
  - [ ] Accountability ambiguity ("AI wrote it")
- [ ] Explain the five technical debt patterns from AI generation:
  - [ ] Invisible duplication across modules
  - [ ] Architecture boundary violations
  - [ ] Weak error handling and operational blindness
  - [ ] Suboptimal algorithm selection
  - [ ] Test debt from coverage theater
- [ ] Discuss the compounding debt trap:
  - [ ] Generation velocity hides accumulation; 30 days of AI debt = 6 months of manual debt
  - [ ] Debt gates before merge: architecture linting, duplication detection, performance regression checks, mutation score thresholds
- [ ] Present prevention controls:
  - [ ] Architecture linting (pylint custom checkers, ESLint plugins)
  - [ ] Duplication detection (jscpd, PMD CPD, SonarQube)
  - [ ] Performance regression checks (pytest-benchmark, JMH, Criterion)
  - [ ] Mutation testing (mutmut, Stryker, PIT)
  - [ ] Dependency vulnerability scans (Dependabot, Snyk, OWASP Dependency-Check)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Frame AI tooling as a systems problem, not a tool preference
- [ ] Summarize the three loops: generation, verification, learning
- [ ] Emphasize guardrails (quality, security) before adoption velocity
- [ ] Connect tool usage to measurable outcomes: cycle time, change failure rate, rollback frequency
- [ ] Demonstrate awareness of failure modes: architecture drift, test illusion, context mismatch
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
