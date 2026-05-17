# Funnel Analysis

Source: [Funnel Analysis: Conversion Optimization, Drop-off Attribution, and Funnel SQL (CalibreOS)](https://www.calibreos.com/learn/analytics-funnel-analysis)

## One-Liner
Measure how users progress through a sequence of steps toward a goal, identify where they drop off, diagnose why, and prioritize fixes by absolute impact.

## Requirements

### Functional
- Define funnel steps explicitly with concrete events (e.g., product_view -> add_to_cart -> checkout_start -> payment_entry -> order_confirmed)
- Track user-level funnels (multi-session, conversion window of 7/14/30 days) and session-level funnels (single visit)
- Report step-over-step conversion rates, overall conversion rate, and absolute user counts at each step
- Segment funnels by device, user type (new/returning), acquisition channel, and geography
- Support conditional paths (e.g., guest checkout skips account creation) and retry/recovery flows (payment failure -> retry -> success)

### Non-Functional
- Accurate sequential ordering (step N+1 must occur after step N in time)
- Conversion window enforcement to prevent inflating metrics with stale journeys
- Handle large event volumes efficiently in SQL (window functions, CTEs)
- Guard against instrumentation gaps and logging bugs that masquerade as funnel drops

## Key Concepts

### Funnel Types
- **User-level**: tracks whether a unique user eventually completed each step across multiple sessions. Best for B2B SaaS, high-consideration purchases. Requires a conversion window.
- **Session-level**: tracks whether a single session progressed through all steps. Best for impulse purchases, content signups.

### Core Metrics
- **Step-over-step conversion**: users completing step N / users completing step N-1. The primary diagnostic metric.
- **Overall conversion**: users completing the last step / users entering the first step. The headline metric.
- **Drop-off rate**: 1 - step-over-step conversion. Proportion of users lost at each step.
- **Time-to-convert**: P50 and P90 time from funnel entry to completion. Long P90 indicates friction.
- **Impact**: (users entering step) x (drop rate) x (improvement potential) = users recovered.

### Attribution Models
- **Last-touch**: 100% credit to the final interaction. Default in most tools, but undervalues top-of-funnel channels.
- **First-touch**: 100% credit to the first interaction. Measures acquisition quality.
- **Linear**: equal credit to all touchpoints. Treats an ad impression the same as "buy now" -- rarely appropriate.
- **Time-decay**: exponential decay from conversion time. Weight = e^(-lambda * (T - t)). Balances recency with full-journey credit.
- **Position-based (U-shaped)**: 40% first touch, 40% last touch, 20% middle. Balances acquisition and conversion measurement.
- **Data-driven (Shapley/Markov)**: computes incremental contribution from each touchpoint. Requires high conversion volume (10K+/month).

### Segmentation Dimensions
- Device (mobile vs desktop) -- reveals UX friction
- New vs returning users -- separates onboarding from core product issues
- Acquisition channel -- reveals traffic quality and intent differences
- Geography -- surfaces localization, payment, and regulatory issues
- Cart value -- identifies price sensitivity and shipping cost shock

### Simpson's Paradox
An aggregate trend can reverse when segmented. Example: overall conversion "improved" from 20% to 22%, but mobile actually dropped 15%->12% and desktop barely changed 28%->29%. The shift was caused by a traffic mix change (more desktop users), not product improvement. Always segment before concluding causality.

## Decisions

### User-Level vs Session-Level
- Use user-level for multi-session journeys (B2B, high-consideration purchases) with a 7-30 day conversion window.
- Use session-level for single-session flows (impulse e-commerce, content signup) where cross-session attribution does not make sense.
- Track both when the question spans product analytics (user-level) and UX analysis (session-level).

### Prioritization: Impact vs Worst Rate
- Prioritize by absolute users recovered, not by worst conversion percentage.
- A step with 80% drop but 5K users is less important than a step with 40% drop and 500K users.
- Impact formula: (users entering step N) x (current drop rate) x (expected improvement) = users recovered.

### Attribution Model Selection
- Last-touch is appropriate when the final touchpoint is the genuine decision driver (retargeting campaigns).
- Time-decay is the best general-purpose model when you believe recent interactions matter more but want to reward the full journey.
- Data-driven models (Shapley, Markov) require sufficient volume and are worth the complexity only at scale.

## Deep Dives

### Funnel SQL Patterns

**User-level funnel** uses CTEs with MIN(CASE WHEN ...) to find first occurrence of each step per user, then enforces sequential ordering (step2_at > step1_at) and a conversion window (step2_at <= step1_at + INTERVAL '14 days'). Counts users at each step and computes step-over-step and overall rates.

**Session-level funnel** uses BOOL_OR per session to check whether each event occurred within the session. Groups by session_id, filters to sessions that started the funnel.

**Segmented funnel** joins events with a users table to pull device_type, acquisition_channel, and user_type (new/returning based on first_seen_at). Groups by these dimensions to expose where drop-offs are concentrated.

**Time-decay attribution** assigns exponential weights using EXP(-lambda * seconds_before_conversion), then normalizes weights per user so total credit = 1 per conversion. Aggregates attributed conversions by channel.

**Conditional paths** use COALESCE to handle alternative routes (e.g., COALESCE(login_at, guest_at) for the checkout step), then GROUP BY checkout_type to compare registered vs guest conversion.

**Payment retry/recovery** tracks failure_count per session and computes recovery_rate by number of failures. Uses ROW_NUMBER to sequence attempts within a session.

### Drop-off Diagnosis Framework
1. **Confirm the drop is real** -- check for instrumentation failure, logging bugs, seasonality (weekday vs weekend), and compare across data sources.
2. **Segment to isolate** -- break down by platform, user type, device, geography, acquisition channel. A localized drop (iOS only, paid search only) points to a specific cause.
3. **Correlate with product changes** -- check deployment logs for UI changes, new form fields, pricing changes, payment method changes, or load-time regressions.
4. **Build a hypothesis and test it** -- e.g., "Mobile checkout dropped because the new address form added two required fields harder to fill on mobile." Run an A/B test or short experiment.

### Common Funnel Mistakes
1. Not enforcing time ordering (step2_at > step1_at) -- inflates conversion with out-of-order events.
2. No conversion window -- counts stale sessions as same journey.
3. Reporting only overall conversion -- step-over-step rates are where the diagnostic value lives.
4. Ignoring channel mix shifts -- lower-intent traffic from changed ad spend can look like a funnel degradation.
5. Not checking instrumentation gaps -- a missing event on a new screen looks like a massive drop.

### Conversion Optimization Levers
1. **Reduce friction**: fewer form fields (Expedia gained $12M/year removing one field), faster load time, remove unnecessary steps.
2. **Increase motivation**: stronger copy, social proof, urgency signals (Booking.com's "Only 2 rooms left!" lifted ~15%).
3. **Build trust**: security badges, return policies, transparent pricing (security logos add 5-12% conversion lift).

## Follow-Ups
- How would you handle a funnel with branching paths (e.g., users who choose different payment methods)?
- What if the same user enters the funnel multiple times -- how do you de-duplicate?
- How would you design an A/B test to validate a funnel optimization? What metric, what sample size, what guardrail metrics?
- How do you attribute conversion credit when users interact with multiple marketing channels across sessions?
- A funnel conversion improved overall but degraded for mobile users -- how do you diagnose and communicate this? (Simpson's Paradox)
- How would you build a real-time funnel monitoring system that alerts on unexpected drops?
