# Product Sense Interview -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] Restate the problem in your own words
- [ ] Ask clarifying questions (max 3-4):
  - [ ] Which user segment?
  - [ ] Which platform (iOS/Android/web/all)?
  - [ ] What is the primary goal (growth, retention, monetization)?
  - [ ] New feature or improving an existing one?
  - [ ] Any constraints or off-limits areas?
- [ ] Summarize the scope after the interviewer answers
- [ ] State the key metric the business cares about for this problem

## Phase 2: User Segments & Journey (3-5 min)
- [ ] Identify 2-3 meaningful user segments:
  - [ ] Primary users (core use case)
  - [ ] Secondary users (adjacent use cases)
  - [ ] Power users (outsized value drivers)
- [ ] Identify which segment is underserved and why
- [ ] Map the user journey funnel:
  - [ ] Awareness -> Acquisition -> Activation -> Engagement -> Retention
  - [ ] Estimate drop-off at each step (ballpark is fine)
- [ ] Name data signals for each drop-off point:
  - [ ] NPS scores, session recordings, support tickets, churn rates
- [ ] State the specific pain point(s) backed by evidence

## Phase 3: Solutions & Prioritization (5-8 min)
- [ ] Generate 3-5 solutions breadth-first across the problem space:
  - [ ] Each solution maps to a specific pain point
  - [ ] Solutions address different root causes (not all in one area)
- [ ] Evaluate each solution:
  - [ ] Impact (users affected x behavior change)
  - [ ] Feasibility (engineering complexity + timeline)
  - [ ] Risk (what could go wrong)
- [ ] Pick the top solution and justify:
  - [ ] Best impact x feasibility x low-risk intersection
  - [ ] Explicitly state what you deprioritize and why

## Phase 4: Success Metrics & Risks (5-10 min, interviewer-directed)
- [ ] Define success metrics:
  - [ ] Primary metric (what moves if the solution works)
  - [ ] Guardrail metric (what must not regress)
  - [ ] Counter-metric (what moves if the primary is being gamed)
- [ ] Check for the suppression trap:
  - [ ] If ad-supported, does the feature change ad impression volume or CTR?
  - [ ] If yes, include revenue/ARPU as a guardrail
- [ ] Sketch the A/B test design:
  - [ ] Treatment vs control, randomization unit
  - [ ] Minimum experiment duration (14 days if touching feed/content surface)
  - [ ] Pre-registered analysis plan
- [ ] Name at least one risk and how you would catch it early:
  - [ ] What early warning signals would you watch?
  - [ ] What would make you roll back?

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize your answer in 2-3 sentences (problem -> solution -> metrics)
- [ ] State the tradeoffs you made and why
- [ ] Mention what you would improve or explore with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
