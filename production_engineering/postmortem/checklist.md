# Writing a Blameless Postmortem — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the incident scope in your own words: what broke, who was affected, for how long
- [ ] Ask clarifying questions:
  - [ ] Was there user-visible impact?
  - [ ] Did it burn significant SLO budget?
  - [ ] Did it reveal a gap in the system's threat model?
  - [ ] Is a postmortem warranted, or does this belong in a runbook?
- [ ] Identify the incident class (3-5 items):
  - [ ] Deployment failure, config error, or code regression
  - [ ] Infrastructure failure (hardware, network, dependency outage)
  - [ ] Performance degradation or capacity exhaustion
  - [ ] Security incident or data integrity issue
  - [ ] Cascading failure across multiple services
- [ ] List non-functional requirements for the postmortem:
  - [ ] Blameless: focus on system failures, not individual mistakes
  - [ ] Timely: document within 48 hours while evidence is fresh
  - [ ] Actionable: every action item has owner, deadline, ticket, success criterion
  - [ ] Quantified: business impact measured in concrete terms
- [ ] State the expected audience and scope:
  - [ ] On-call engineers who responded
  - [ ] One domain expert per affected system
  - [ ] One engineering leader (staff or manager)
  - [ ] Maximum 8 attendees at the review meeting

## Phase 2: High-Level Structure (3-5 min)
- [ ] List the 7 sections of the postmortem document in order:
  - [ ] Summary (3-5 sentences, written last)
  - [ ] Timeline (factual events with UTC timestamps)
  - [ ] Root Cause and Contributing Factors (three layers)
  - [ ] Impact (quantified business impact)
  - [ ] Action Items (owned, time-bounded, tiered)
  - [ ] What Went Well (defenses that worked)
  - [ ] Lessons Learned (2-4 surprising system-level insights)
- [ ] Note the key rules for each section:
  - [ ] Summary: readable in 60 seconds, no blame or speculation
  - [ ] Timeline: facts only, verifiable from logs/dashboards, no editorializing
  - [ ] Root Cause: proximate cause + contributing factors + systemic root cause
  - [ ] Impact: concrete numbers with methodology, not "users were affected"
  - [ ] Action Items: specific owner by name, due date, ticket link, success criterion
  - [ ] What Went Well: identify defenses to strengthen and replicate
  - [ ] Lessons Learned: surprising insights, not platitudes
- [ ] Present the structure and get alignment

## Phase 3: Core Analysis (5-8 min)
- [ ] Explain the three-layer causal analysis:
  - [ ] Proximate cause: the immediate trigger (what happened)
  - [ ] Contributing factors: conditions that made it possible and severe (why it spread)
  - [ ] Systemic root cause: the process or environment that produced the above (why the system allowed it)
- [ ] Apply the blameless reframe:
  - [ ] Wrong question: "Why did the engineer do that?"
  - [ ] Right question: "What was it about the system that made that action easy and its consequences hard to predict?"
- [ ] Walk through action item tiering:
  - [ ] Tier 1 -- Prevent: stops this exact failure from recurring
  - [ ] Tier 2 -- Detect: alerts on this class of failure earlier
  - [ ] Tier 3 -- Reduce blast radius: limits impact when similar failures recur
- [ ] Provide a concrete action item example:
  - [ ] Bad: "Improve monitoring"
  - [ ] Good: "Add alert: fire P2 when checkout error rate exceeds 1% for 5 consecutive minutes; owner: @alice; due: May 15; ticket: ENG-4821"
- [ ] Walk through the meeting agenda:
  - [ ] Timeline review (15 min): shared factual understanding
  - [ ] Causal analysis review (20 min): surface disagreement on contributing factors
  - [ ] Action item review (20 min): validate interventions, owners, deadlines
  - [ ] Decision (5 min): commit with named owners and dates

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss common failure modes:
  - [ ] "Human error" as root cause: always a symptom, not a cause
  - [ ] Action items owned by teams instead of named individuals
  - [ ] Timeline reconstructed from memory instead of logs
  - [ ] Filing without tracking action item completion
  - [ ] Over-filing postmortems for routine P3 alerts
- [ ] Address meeting anti-patterns:
  - [ ] Inviting too many people (creates audience, performance, blame)
  - [ ] Letting the timeline become narrative instead of facts
  - [ ] Confusing "could have been prevented" with "should have known better"
  - [ ] Closing without committed owners for every action item
- [ ] Explain level differentiation:
  - [ ] L3/Junior: proximate cause only, vague action items
  - [ ] L4/Mid: contributing factors identified, specific but unowned action items
  - [ ] L5/Senior: all three causal layers, tiered and owned action items
  - [ ] Staff/SRE Lead: causal graphs, cross-incident patterns, process-level changes
- [ ] Discuss measuring postmortem culture health:
  - [ ] Action item completion rate over time
  - [ ] Recurrence rate of similar incident classes
  - [ ] Time from incident to postmortem completion
  - [ ] Detection lag (time between incident start and alert fire)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the postmortem philosophy in 2-3 sentences
- [ ] State the key trade-offs (thoroughness vs. timeliness, depth vs. overhead)
- [ ] Mention what you would improve with more time (e.g., automated causal analysis tooling, cross-team postmortem review board)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
