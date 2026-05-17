# Scenario Problem Bank Guide — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the scenario type back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What is the core metric or incident in question?
  - [ ] Is this a root-cause diagnosis, a ship/no-ship decision, or a design problem?
  - [ ] What is the scope (single feature, full product, cross-team, cross-region)?
- [ ] List what you know (3-5 items):
  - [ ] The metric change or incident description
  - [ ] The timeframe and affected segments
  - [ ] Any recent changes (feature launches, model deploys, infra changes)
  - [ ] Available data sources and dashboards
  - [ ] Stakeholders involved
- [ ] List constraints and non-functional considerations:
  - [ ] Time pressure (is this P0 / blocking launch / post-mortem?)
  - [ ] Data quality and availability
  - [ ] Blast radius and severity
- [ ] State your approach framework:
  - [ ] DIAGNOSE or equivalent structured reasoning framework
  - [ ] Segmentation dimensions (geo, platform, user cohort, time)

## Phase 2: High-Level Diagnosis (3-5 min)
- [ ] Clarify the metric and its components:
  - [ ] Define the metric precisely (DAU = users with 1+ action in 24h, not just opens)
  - [ ] Decompose into sub-metrics (e.g., DAU = new + retained + resurrected)
  - [ ] Check for data quality issues before analyzing (logging changes, pipeline delays)
- [ ] Segment the problem systematically:
  - [ ] By platform (iOS, Android, Web)
  - [ ] By geography (country, region)
  - [ ] By user cohort (new vs returning, power vs casual)
  - [ ] By time (hour-of-day, day-of-week, seasonality)
  - [ ] By feature area (which surface is affected)
- [ ] Form a hypothesis tree (not a single hypothesis):
  - [ ] External causes (seasonality, competitor, holiday, regulation)
  - [ ] Internal product changes (new feature, UI change, ranking change)
  - [ ] Internal technical changes (model deploy, infra change, config change)
  - [ ] Data issues (logging bug, pipeline failure, definition change)
- [ ] Present your top 2-3 hypotheses with supporting evidence and get alignment

## Phase 3: Deep Analysis (5-8 min)
- [ ] Design the investigation for your top hypothesis:
  - [ ] What data would confirm or rule out this hypothesis?
  - [ ] What query or analysis would you run?
  - [ ] What segment comparison would isolate the cause?
- [ ] Address experimentation considerations if relevant:
  - [ ] Is an A/B test appropriate here, or is it observational?
  - [ ] Guardrail metrics and OEC (Overall Evaluation Criterion)
  - [ ] Power analysis and sample size
  - [ ] Novelty effect and long-term vs short-term effects
  - [ ] SRM (Sample Ratio Mismatch) check
- [ ] If ML-related, discuss model-specific angles:
  - [ ] Feature drift, data drift, concept drift
  - [ ] Training-serving skew
  - [ ] Offline vs online metric gap
  - [ ] Rollback vs mitigation tradeoffs
- [ ] Walk through the resolution end-to-end:
  - [ ] Immediate mitigation (what do you do right now?)
  - [ ] Root cause fix (what is the permanent solution?)
  - [ ] Monitoring and alerting (how do you prevent recurrence?)

## Phase 4: Communication & Tradeoffs (5-10 min, interviewer-directed)
- [ ] Make a concrete recommendation:
  - [ ] Ship / no-ship / investigate further -- state it clearly
  - [ ] Quantify the expected impact if possible
  - [ ] Acknowledge uncertainty and state assumptions
- [ ] Address conflicting metrics:
  - [ ] Identify the tradeoff (engagement vs revenue, short-term vs long-term)
  - [ ] Propose guardrails or thresholds for the secondary metric
  - [ ] Frame as a decision under risk, not certainty
- [ ] Discuss stakeholder communication:
  - [ ] How would you present findings to PM / engineering leadership?
  - [ ] What is the narrative arc of your recommendation?
- [ ] Address behavioral / leadership dimensions if prompted:
  - [ ] Disagreement scenarios: state the other side's likely reasoning first
  - [ ] Cross-team coordination: identify shared incentives and blocking dependencies
  - [ ] Escalation: when and how to escalate, what you would communicate

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize your diagnosis and recommendation in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would investigate with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
