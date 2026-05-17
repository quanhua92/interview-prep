# Writing the Blameless Postmortem

Source: [Writing the Blameless Postmortem: RCAs That Actually Drive Change (CalibreOS)](https://www.calibreos.com/learn/prod-postmortem-writing)

## One-Liner
Write postmortems that prevent recurrence by identifying systemic root causes, not by assigning blame to individuals.

## Functional Requirements
- Produce a structured postmortem document within 48 hours of incident resolution
- Include a verifiable timeline built from logs and dashboards, not memory
- Identify proximate cause, contributing factors, and systemic root cause
- Generate owned, time-bounded, tracked action items organized by tier
- Quantify business impact in concrete terms (users affected, revenue lost, SLO budget burned)

## Non-Functional Requirements
- Blameless culture: focus on system failures, not human mistakes
- Actionable: every action item must have an owner, deadline, ticket, and success criterion
- Concise: summary readable in 60 seconds by any engineer in the company
- Trackable: action item completion reviewed weekly until closed

## Key Scale Questions
- A postmortem is warranted for: any user-visible impact, significant SLO budget burn, or gaps in the threat model
- Routine P3 alerts resolved in <5 min without user impact need a runbook entry, not a postmortem
- Over-filing creates fatigue; under-filing lets systemic issues fester
- Meeting capped at 60 min and 8 attendees to avoid audience dynamics

## Core Components

### The 7-Section Postmortem Structure
1. **Summary** (3-5 sentences): What broke, who was affected, how long, impact, fix. Write last, place first.
2. **Timeline** (factual events only): Chronological UTC timestamps. Facts from logs, not interpretations.
3. **Root Cause and Contributing Factors**: Three layers -- proximate cause, contributing factors, systemic root cause.
4. **Impact**: Quantified business impact with methodology (e.g., error rates, estimated revenue loss, SLO minutes burned).
5. **Action Items**: Specific owner, due date, tracking ticket, success criterion. Organized by tier.
6. **What Went Well**: Defenses that worked; not positive spin, but identification of what to strengthen and replicate.
7. **Lessons Learned**: 2-4 system-level insights that are surprising, not platitudes.

## Key Design Decisions

### Causal Analysis: Three Layers
- **Proximate cause**: The immediate trigger (e.g., the config change that caused the OOM kill)
- **Contributing factors**: Conditions that made the trigger possible and consequences severe (e.g., no canary deploy, alert threshold too high, missing runbook)
- **Systemic root cause**: The process or environment that produced all contributing factors (e.g., deployment process has no automated validation gate for config changes)
- Most postmortems stop at the proximate cause; effective ones identify all three layers

### Action Item Tiers
| Tier | Question | Example |
|------|----------|---------|
| Prevent recurrence | What stops this exact failure? | Add config validation gate to CI pipeline |
| Detect earlier | What alerts the next incident in this class faster? | OOM alert fires at 70% memory, not at process kill |
| Reduce blast radius | What limits impact when this category recurs? | Implement canary deploy for all config changes |

### Postmortem Meeting Agenda (60 min max)
1. Timeline review (15 min): shared factual understanding
2. Causal analysis review (20 min): surface disagreement on contributing factors
3. Action item review (20 min): right intervention, right owner, realistic deadline
4. Decision (5 min): commit to action items with named owners and dates

## Common Failure Modes
- **"Human error" as root cause**: Always a symptom of a system that made the error easy. Ask why the system allowed it.
- **Action items owned by teams**: "The platform team will..." means no one owns it. Assign a named individual.
- **Timeline from memory**: Unreliable after 48 hours. Use logs, Slack channels, PagerDuty records.
- **Filing without tracking**: A postmortem without completed action items is just a document. Review weekly until closed.
- **Over-filing for every P3**: Reserve postmortems for meaningful incidents; use runbooks for routine alerts.

## Deep Dive Topics
- The 5 Whys failure mode: linear chain reasoning misses branching causal factors; prefer causal graphs
- Distinguishing "could have been prevented" (systems insight) from "should have known better" (blame in disguise)
- Detection lag: measuring how long between incident start and alert fire is as important as the incident itself
- Latent conditions: systemic issues that predated the incident and made it inevitable

## Follow-Up Variations
- How do you handle a postmortem where the root cause spans multiple teams?
- What if an action item keeps getting deprioritized -- how do you escalate?
- How do you measure whether your postmortem culture is improving over time (e.g., recurrence rates, action item completion rates)?
- How would you write a postmortem for an incident caused by a third-party dependency outage?
