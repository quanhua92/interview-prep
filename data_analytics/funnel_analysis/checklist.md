# Funnel Analysis Interview Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] Restate the problem: what funnel are we analyzing and what is the business goal?
- [ ] Ask clarifying questions:
  - [ ] Is this a user-level or session-level funnel?
  - [ ] What is the conversion window (7, 14, or 30 days)?
  - [ ] What events define each funnel step?
  - [ ] Is the funnel linear or does it have branching paths (e.g., guest vs registered checkout)?
- [ ] Define the funnel steps explicitly with concrete event names:
  - [ ] Step 1: entry event (e.g., product_view)
  - [ ] Step 2: engagement event (e.g., add_to_cart)
  - [ ] Step 3: commitment event (e.g., checkout_start)
  - [ ] Step 4: conversion event (e.g., order_confirmed)
- [ ] State what you will measure:
  - [ ] Step-over-step conversion rates
  - [ ] Overall conversion rate
  - [ ] Absolute user counts at each step
  - [ ] Time-to-convert (P50, P90)

## Phase 2: Funnel Construction (3-5 min)
- [ ] Choose user-level vs session-level and justify:
  - [ ] User-level for multi-session journeys (B2B, high-consideration purchases)
  - [ ] Session-level for single-session flows (impulse e-commerce, signup)
- [ ] Set the conversion window if user-level (7/14/30 days)
- [ ] Sketch the SQL approach:
  - [ ] CTE with MIN(CASE WHEN event_type = '...' THEN occurred_at END) per step
  - [ ] Enforce sequential ordering: step2_at > step1_at
  - [ ] Enforce conversion window: step2_at <= step1_at + INTERVAL '14 days'
  - [ ] Count distinct users at each step, compute step-over-step and overall rates
- [ ] State the key SQL patterns you would use:
  - [ ] GROUP BY user_id to pivot events into columns
  - [ ] CASE WHEN for step completion flags
  - [ ] NULLIF to avoid division by zero
  - [ ] Window functions for session-level funnels (BOOL_OR, ROW_NUMBER)

## Phase 3: Diagnosis and Segmentation (5-8 min)
- [ ] Confirm the drop is real before diagnosing:
  - [ ] Check for instrumentation gaps and logging bugs
  - [ ] Compare to same period last week/month to rule out seasonality
  - [ ] Cross-check across data sources
- [ ] Segment the funnel by key dimensions:
  - [ ] Device: mobile vs desktop (mobile friction is the #1 conversion killer)
  - [ ] User type: new vs returning (separates onboarding from core product issues)
  - [ ] Acquisition channel: paid search vs organic vs email vs social (traffic quality differs)
  - [ ] Geography: country/region (payment methods, localization, seasonality)
- [ ] Use the hypothesis lookup table to match drop location to likely cause:
  - [ ] Landing -> Signup: poor value prop, slow load, irrelevant traffic
  - [ ] Signup -> Email verify: deliverability, verification friction
  - [ ] Cart -> Checkout: shipping cost shock, trust concerns
  - [ ] Checkout -> Payment: form friction, missing payment methods
  - [ ] Payment -> Confirm: payment gateway failures, timeouts
- [ ] Correlate with product changes (deployment log, UI changes, pricing changes)
- [ ] Watch for Simpson's Paradox: aggregate improvement can hide segment-level degradation

## Phase 4: Prioritization and Recommendation (5-10 min)
- [ ] Compute absolute impact at each step:
  - [ ] Impact = (users entering step N) x (drop rate) x (expected improvement)
  - [ ] Prioritize by absolute users recovered, not worst conversion percentage
- [ ] Propose a specific, testable intervention (not "improve UX"):
  - [ ] Reduce friction: fewer form fields, faster load, remove unnecessary steps
  - [ ] Increase motivation: better copy, social proof, urgency signals
  - [ ] Build trust: security badges, transparent pricing, return policies
- [ ] Quantify expected impact with benchmarks:
  - [ ] "Reducing form fields from 12 to 6 should lift conversion ~10%, recovering ~15K users/month"
- [ ] Recommend A/B test before full rollout
- [ ] If attribution comes up, explain trade-offs between models:
  - [ ] Last-touch is default but undervalues top-of-funnel
  - [ ] Time-decay is best general-purpose model
  - [ ] Data-driven (Shapley/Markov) requires high conversion volume

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize your analysis in 2-3 sentences
- [ ] State the single highest-impact recommendation
- [ ] Mention what you would investigate further with more time
- [ ] Ask the interviewer if they have follow-up questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
