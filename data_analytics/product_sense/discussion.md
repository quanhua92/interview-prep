# Product Sense Interviews

Source: [Product Sense Interviews: Structured Frameworks for Improving Products with Data (CalibreOS)](https://www.calibreos.com/learn/analytics-product-sense)

## One-Liner
Use a problem-first, solution-second, metrics-third framework to answer "improve Product X" questions by clarifying scope, segmenting users, mapping journeys, and defining measurable success.

## Requirements

### What the Interview Is Testing
- Ability to reason from **user problems** to **product solutions** (not from ideas to post-hoc justifications)
- Discipline of structured thinking: problem first, solution second, metrics third -- in that order, every time

### Functional Requirements
- Clarify the problem scope with targeted questions before proposing anything
- Segment users into meaningful groups (primary, secondary, power users)
- Map the user journey and identify specific drop-off points with data signals
- Generate breadth-first solutions tied to distinct root causes
- Prioritize using Impact x Feasibility matrix
- Define success with a primary metric, guardrail metric, and counter-metric

### Non-Functional Requirements
- Complete the answer in 20-25 minutes with clear structure
- Demonstrate production-grade thinking (risks, tradeoffs, what you are NOT building)
- Communicate your framework aloud at each step

## Key Concepts

### The 8-Step Framework
1. **Clarify scope** (2 min): segment, platform, goal (growth/retention/monetization), constraints. Ask at most 3-4 questions.
2. **Define user segments** (3 min): 2-3 segments (e.g., casual viewers, active creators, passive scrollers). Identify which is underserved.
3. **Map the user journey** (3 min): Awareness -> Acquisition -> Activation -> Engagement -> Retention. Estimate drop-off at each stage.
4. **Identify pain points** (3 min): Name pain points with data signals (NPS, session recordings, support tickets, churn rates).
5. **Generate solutions breadth-first** (5 min): 3-5 solutions across the problem space, each mapped to a specific pain point.
6. **Prioritize** (3 min): Impact x Feasibility x Risk. Pick the best intersection; explain what you deprioritize and why.
7. **Define success metrics** (2 min): Primary metric + guardrail + counter-metric.
8. **Tradeoffs and risks** (2 min): Name one thing that could go wrong and how you would catch it early.

### The Suppression Trap
- In ad-supported products (Meta, Snap, X), a feature that improves engagement quality can **reduce ad impressions** by making sessions shorter and more intentional
- Canonical example: Instagram's chronological-to-algorithmic feed switch -- higher relevance but fewer ad impressions per session
- Always ask: "Does this feature change ad impression volume or CTR?" If yes, include revenue/ARPU as a guardrail
- Run experiments for at least 14 days to catch downstream revenue suppression (7-day tests can show engagement lift but miss the revenue drop)

### Funnel Drop-Off Analysis
- Build the funnel with concrete step-by-step conversion rates
- The step with the largest drop-off is where to focus investment
- Each drop-off point maps to a different root cause requiring a different solution

## Decisions

### 9/10 vs 6/10 Answer
| Aspect | 6/10 (passes) | 9/10 (impresses) |
|--------|---------------|-------------------|
| Opening | States segment, generates 3 ideas | Asks clarifying questions first, maps journey with data signals |
| Pain points | General/intuitive | Backed by named data signals (NPS, session recordings, support tickets) |
| Solutions | All in one area | Each addresses a different root cause |
| Metrics | Single metric ("we'd measure DAU") | Primary + guardrail + counter-metric; names the suppression trap unprompted |
| Risks | Not addressed | Names what could go wrong and early warning signals |

### Prioritization Matrix
- Evaluate each solution on: Impact (users affected x behavior change), Feasibility (eng complexity + timeline), Risk (what could go wrong)
- Pick the best impact x feasibility x low-risk intersection
- Explicitly state what you deprioritize and why ("deprioritizing X because it addresses a smaller segment with higher implementation risk")

## Deep Dives

### Model Answer: Facebook Engagement Declining in 18-24
1. **Clarify**: Define "engagement" (DAU? time-in-app? content interactions?). Recent or long-term trend? Isolated or cross-demographic? Platform?
2. **Diagnose by segment**: If isolated to 18-24 on mobile, likely causes: competitive displacement (TikTok), social graph aging (friends are parents/grandparents), content format mismatch (prefer ephemeral over permanent)
3. **Solutions by cause**: Short-form video (Reels) for competitive, Groups for social graph aging, Stories/Reels prominence for format mismatch. Pick the cause with strongest evidence.
4. **Metrics**: Primary = 18-24 DAU/MAU ratio. Guardrail = overall DAU. Counter = reported satisfaction scores.

### Model Answer: LinkedIn Job Application Completion
- Key insight: this is an **activation funnel problem**, not a feature design problem
- Common drop-offs: cover letter requirement (friction), incomplete employer profiles (can't evaluate company), Easy Apply fields that don't autofill (re-entering existing data)
- Each requires a different feature -- identifying the drop-off location IS the product sense

### The Five Interview Traps
1. **Jumping to solutions without user research**: Proposing features before identifying the problem
2. **Building for the "average user"**: There is no average user; always segment
3. **Proposing a single metric as success**: Any metric can be gamed; name the counter-metric
4. **Forgetting feasibility**: A brilliant 18-month ML infrastructure project is not a good interview answer
5. **Not stating what you're NOT building**: Deprioritization demonstrates real tradeoff thinking

## Follow-Ups
- How would you design an A/B test for a feature that might have suppression effects on revenue?
- What if the primary metric improves but the guardrail regresses -- how do you decide whether to ship?
- How do you evaluate a feature's worth before you can run an A/B test?
- How would you handle a situation where different user segments respond oppositely to the same feature?
- What leading indicators would you watch in the first 48 hours of a rollout?
