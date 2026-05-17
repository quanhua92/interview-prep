# North Star Metric Interview — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] Restate the product and its core user value in your own words
- [ ] Ask clarifying questions:
  - [ ] Is this a daily-habit product or infrequently-used product? (determines cadence)
  - [ ] Is this a one-sided or two-sided marketplace?
  - [ ] What is the primary user action that delivers value?
- [ ] Identify what the product does for users (3-5 items):
  - [ ] What core problem does the product solve?
  - [ ] What is the primary user action that delivers value?
  - [ ] What does a successful session look like?
  - [ ] What is the usage cadence (daily, weekly, monthly, event-driven)?
- [ ] State why revenue is NOT the NSM:
  - [ ] Revenue is a lagging indicator, not a user-value signal
  - [ ] Revenue can rise (price hikes, ad load) while user value declines
  - [ ] The NSM should be decoupled from monetization efficiency

## Phase 2: Key Concepts (3-5 min)
- [ ] Name the NSM and explain the leading-indicator mechanism:
  - [ ] State the metric clearly (e.g., "Nights booked per week")
  - [ ] Explain WHY it predicts long-term retention
  - [ ] Reference the 5-criterion rubric (user value, leading, actionable, decomposable, resistant to gaming)
- [ ] Justify your choice over alternatives:
  - [ ] Why not revenue? (lagging, doesn't capture user value)
  - [ ] Why not DAU? (counts presence, not value delivery; wrong for infrequent products)
  - [ ] Why not vanity metrics? (downloads, registrations count events, not value)
- [ ] Name the counter-metric:
  - [ ] Identify a metric that should NOT move if the NSM gain is genuine
  - [ ] Explain what "cheating" looks like and how the counter-metric catches it
- [ ] Cite a real-world NSM example to show domain knowledge (Airbnb, Slack, Spotify, Uber)

## Phase 3: Decomposition (5-8 min)
- [ ] Build the metric tree (NSM / L1 / L2):
  - [ ] NSM (company level): the single metric, reported weekly or monthly
  - [ ] L1 metrics (product area): 2-4 leading indicators owned by PMs
  - [ ] L2 metrics (feature level): specific feature behaviors owned by engineering teams
- [ ] Express the NSM as a product or sum of input metrics:
  - [ ] E.g., Nights Booked = Search Traffic x CTR x Booking Rate x Avg Stay Length
  - [ ] Each component is owned by a distinct team
- [ ] Walk through the chain for a hypothetical feature:
  - [ ] "Feature F will move L2 metric M2 by X%, which moves L1 metric M1 by Y%, contributing to NSM movement of Z%"

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss Goodhart's Law by name:
  - [ ] "When a measure becomes a target, it ceases to be a good measure"
  - [ ] Give a concrete example of gaming (Airbnb cancellations, Slack bots, Facebook dark patterns)
  - [ ] Explain how counter-metrics catch gaming
- [ ] Address the 5 NSM anti-patterns:
  - [ ] Revenue as NSM (lagging output, not user value)
  - [ ] Vanity metrics (downloads, registrations, page views)
  - [ ] Metric no team owns ("customer happiness" is not actionable)
  - [ ] No counter-metric (proposing NSM without a guardrail)
  - [ ] DAU for infrequently-used products (wrong cadence)
- [ ] Discuss when to change the NSM:
  - [ ] When it no longer predicts retention (validate with cohort analysis)
  - [ ] When the product model shifts
  - [ ] When gaming overwhelms counter-metric guardrails
- [ ] Handle the "DAU trap" question:
  - [ ] DAU counts presence, not value delivery
  - [ ] A user who opens the app to dismiss a notification counts the same as a power user
  - [ ] DAU is a component or guardrail, not the NSM itself (except daily-habit products)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize in the 4-part structure (under 90 seconds):
  - [ ] State the user value the product delivers
  - [ ] Name the NSM and explain the leading-indicator mechanism
  - [ ] Decompose it into the input-metric tree
  - [ ] Name the counter-metric and what cheating looks like
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
