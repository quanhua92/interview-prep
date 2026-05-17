# Scenario Problem Bank Guide

Source: [Scenario Problem Bank Guide, How to Practice the 38 Problems (CalibreOS)](https://www.calibreos.com/learn/scenarios-problem-guide)

## One-Liner

Curriculum map for 38 scenario problems across 6 tracks (Analytics, ML System, Infrastructure, Behavioral, GenAI, Business Strategy) with company-specific playlists for Meta, Airbnb, Netflix, DoorDash, and Stripe interview loops.

## Requirements

### What the Bank Covers
- 38 scenario problems organized into 6 skill tracks
- Each problem has a prompt, rubric checklist, and sample answer
- Problems are classified by difficulty: Foundation, Intermediate, Advanced, Staff-level
- Company playlists map 8-12 problems to real interview formats

### Self-Assessment (5 Questions)
- Q1: DAU Drop -- scores metric triage and segmentation (Analytics track)
- Q2: Model Degraded -- scores ML system debugging (ML System track)
- Q3: P0 Incident / Silent Pipeline Failure -- scores infrastructure incident handling (Infra track)
- Q4: Disagree With Manager -- scores behavioral structuring (Behavioral track)
- Q5: LLM Hallucination / LLM Cost Explosion -- scores GenAI incident response (GenAI track)
- Score under 6 on any question = start with that track

### Scoring Method
- Answer aloud without looking at the sample answer
- Compare against the rubric checklist
- Count rubric points covered with comparable specificity
- Most candidates score 4-6 on first attempt at senior-level scenarios

## Key Concepts

### Six Tracks
| Track | Foundation Problem | Key Skill |
|-------|-------------------|-----------|
| Analytics / Product | DAU Drop | Metric triage, segmentation, experimentation |
| ML System | Model Degraded | ML debugging, feature drift, rollback decisions |
| Infrastructure / Pipeline | P0 Incident | Incident response, root cause analysis |
| Behavioral / Leadership | Most Proud Project | STAR structuring, stakeholder navigation |
| GenAI / LLM | LLM Cost Explosion | LLM serving, hallucination, prompt injection |
| Business / Strategy | Define Metrics | Metric design, tradeoff analysis, opportunity cost |

### Difficulty Ladder (per track)
- **Foundation**: Canonical first problem. Must score 7+ before moving on.
- **Intermediate**: Builds on foundation with additional complexity (novelty effects, explainability, cross-team coordination)
- **Advanced**: Multi-factor tradeoffs (conflicting metrics, fairness, offline-online gaps)
- **Staff-level**: Org-level reasoning (cold starts, postmortems, influence without authority)

### Key Framework: DIAGNOSE
- Recovery move for unfamiliar prompts
- Structured reasoning framework referenced across all problems
- Re-read the night before an interview

## Decisions

### How to Pick Your Practice Order
1. Take the 5-question self-assessment to find your weakest category
2. Pick the company playlist matching your target interview
3. Use the difficulty ladder to set pace (15-25 min per problem first pass)
4. Re-do problems scored under 7/10 after a week

### Practice Duration
- Single company playlist: 4-5 hours first pass, 8-10 hours with re-dos
- Full track: 2-4 hours first pass depending on track size
- Recommended calendar: 4-6 weeks at 3-5 hours per week
- Cramming all 38 problems in a weekend will not work

### Track Timings
| Track | Problems | First Pass | With Re-Dos | Calendar |
|-------|----------|------------|-------------|----------|
| Analytics / Product | 9 | ~4 hrs | ~7 hrs | 1.5 wks |
| ML System | 8 | ~4 hrs | ~7 hrs | 1.5 wks |
| Infrastructure / Pipeline | 5 | ~2 hrs | ~4 hrs | 1 wk |
| Behavioral / Leadership | 7 | ~3 hrs | ~5 hrs | 1 wk |
| GenAI / LLM | 7 | ~3 hrs | ~5 hrs | 1 wk |
| Business / Strategy | 5 | ~2.5 hrs | ~4 hrs | 1 wk |

## Deep Dives

### Company Playlist: Meta DSI
- 45-minute product analytics + experimentation deep dive, single ambiguous prompt
- Segmentation framework is mandatory; jumping to hypotheses without segmenting is the #1 rejection signal
- Practice order: DAU Drop, Novelty Effect, Offline-Online Gap, Conflicting Metrics, A/B Test Design, Define Metrics, Cold Start, Postmortem
- Rejection signals: skipping data quality check, single hypothesis, no ship/no-ship recommendation

### Company Playlist: Airbnb Data Loop
- Four interviews: live coding, product/A-B case, ML system design, core values
- Causal inference bias is strong; think in counterfactuals, not correlations
- Practice order: A/B Test Design, Novelty Effect, Conflicting Metrics, Offline-Online Gap, DAU Drop, Cold Start, Competitor Launched, Enterprise Churn, Disagree With Manager, Most Proud Project
- Rejection signals: weak causal vs correlational language, no quasi-experiment proposal, not connecting to host/guest LTV

### Company Playlist: Netflix Experimentation
- Less algorithmic than Meta; evaluates defensibility of conclusions and structured reasoning
- Culture fit weighted heavily; can they disagree with you productively?
- Practice order: Offline-Online Gap, A/B Test Design, Conflicting Metrics, Novelty Effect, Postmortem, Disagree With Manager, Staff Career, Should We Build This?
- Rejection signals: weak uncertainty quantification, opinions without counterarguments, no risk framing

### Company Playlist: DoorDash / Marketplace Analytics
- Ambiguous prompts and supply-demand marketplace scenarios; less A/B, more diagnose-this-metric
- Geography and time-segmentation are recurring themes
- Practice order: DAU Drop, Cold Start, Conflicting Metrics, P0 Incident, Competitor Launched, Checkout vs Benchmark, Cross-Team Dependency, Postmortem
- Rejection signals: no geo/time segmentation, treating supply-demand as single market, missing operational levers

### Company Playlist: Stripe Technical-Data Hybrid
- Blends technical investigation with data analysis; "payments failing in Germany" is canonical
- Less ML, more data + engineering reasoning; cross-region, cross-product root cause
- Practice order: P0 Incident, Silent Pipeline Failure, DAU Drop, Feature Store Latency, Cross-Team Dependency, Technical Debt, Postmortem, Enterprise Churn, Privacy Conflict
- Rejection signals: no country/payment-method segmentation, missing two-sided root cause (consumer vs bank), not understanding 3DS/SCA flow

## Follow-Ups

### Common Mistakes
- Reading sample answers without attempting first (overestimates readiness)
- Skipping rubric comparison (cannot diagnose gap without it)
- Practicing all 38 instead of the right 10-12 in your playlist
- Treating behavioral and business-strategy as filler (30-50% of staff-level loops)
- Not doing a full 45-minute timed mock

### Beyond the Bank (scoring 8+ on all playlist problems)
- Generate your own scenarios from engineering blog posts (Netflix, Stripe, Uber, DoorDash, Meta AI, Anthropic, Airbnb, Pinterest, Shopify, Notion)
- Identify the decision the team made, write a prompt, answer using DIAGNOSE, compare to actual outcome

### 90-Minute Pre-Interview Refresher
- Min 0-15: re-read company playlist
- Min 15-45: re-read rubric (not sample answer) for 3 most aligned problems; recall without looking
- Min 45-75: out-loud 30-minute mock on a problem not done in 2+ weeks, timed
- Min 75-90: re-read DIAGNOSE framework page

---

## The DIAGNOSE Framework (Detailed)

Source: [How to Approach Data & Product Scenario Questions (CalibreOS)](https://www.calibreos.com/learn/scenarios-how-to-approach)

The DIAGNOSE framework gives you a structured 5-step approach that transforms vague "what would you do?" prompts into clear, systematic answers. Unlike SQL or ML theory questions, scenario questions have no single correct answer -- the interviewer evaluates your reasoning process, not your conclusion.

### Step 1 & 2: Define the Signal, Check the Instrument

Before investigating causes, get precise about what changed.

**Define the signal (D):**
- What metric dropped/spiked? (DAU, revenue, conversion rate, model precision)
- By how much? Is 15% drop large or small for this metric's normal variance?
- When did it start? Gradually over days, or a step change at a specific time?
- Which segments are affected? All users or a subset? All platforms or one?
- What is the normal baseline? Is this a seasonal trough or a genuine drop?

**Check the instrument (I) -- always do this first:**
Approximately 30-40% of "metric drops" in production are actually data pipeline failures, not real product changes. Check this before investigating business causes.

Instrument check playbook:
1. Is the logging system healthy? Check event ingestion lag, error rates in the pipeline.
2. Compare across data sources: does BigQuery show the same drop as the Kafka consumer?
3. Check recent deployments to the logging/analytics layer specifically.
4. Look at upstream dependencies: did the app stop sending events or did events start failing?
5. Check if the issue is timezone-localized (common with UTC vs local time bugs).

If the instrument check passes (data is trustworthy), proceed. If it fails, the "incident" is a data pipeline bug -- escalate to data engineering and scope the data gap.

### Step 3 & 4: Assemble Hypotheses, Generate Queries

Form a complete hypothesis tree before writing a single query. This is the most differentiating step; it shows you think before you act.

**Standard hypothesis tree for a metric drop:**

Internal causes (things you control):
- Product changes: new feature, A/B test launched, UI change, paywall added
- Engineering changes: deployment, config change, feature flag flipped
- Data/instrumentation: logging bug, pipeline outage, schema change
- Algorithm changes: ranking model update, recommendation change

External causes (things outside your product):
- Seasonality: day of week, holiday, back-to-school, product cycle
- Competitor action: competitor launched a feature, had an outage (your users migrating back)
- Platform change: iOS/Android OS update, App Store policy, browser update
- Macroeconomic: news event, regulatory change, market disruption

**Prioritize hypotheses before querying:**
- "We deployed a new checkout flow 3 hours before the drop" -- investigate that first
- "It's a Sunday in Q4" -- check if this matches historical Sunday patterns first
- "The logging team had a config change yesterday" -- check instrument first

**Diagnostic segmentation strategies:**
- Segment by platform (iOS vs Android vs web) -- if drop is iOS-only, look at iOS deployment
- Segment by user type (new vs returning) -- if drop is new-user-only, look at acquisition funnel
- Segment by geography -- if drop is US-only, look for US-specific events
- Compare to same time last week/month -- is this seasonal?
- Funnel analysis: where in the conversion path are users dropping off?

### Step 5 & 6: Narrow to Root Cause, Own the Recommendation

Use process of elimination, not trial and error.

**Narrowing examples:**
- If segmentation shows: iOS drop = 40%, Android drop = 2%, Web drop = 1% -- this is iOS-specific. Investigate iOS deployment, iOS version update, App Store listing.
- If funnel analysis shows: signups unchanged, but checkout completions dropped 20% -- the drop is in the checkout step. Investigate checkout changes, payment provider.
- If cohort comparison shows: new users dropped, returning users unchanged -- the drop is in acquisition or first-session experience. Investigate ad campaigns, onboarding flow, landing pages.

**Quantify the impact:**
- How many users are affected? (X% of DAU x user base size)
- What is the revenue impact? ($Y per affected user x affected user count)
- Severity: P0 (system down), P1 (major regression), P2 (minor regression)

**Own a recommendation:**
- If it's a bug: "Roll back the deployment immediately. Estimated fix time is X hours. Estimated impact at current rate is $Y/hour of continued outage."
- If it's a feature regression: "Disable the feature flag. Scope the full user impact before re-enabling. Schedule post-mortem."
- If it's external/seasonal: "No action required. Set up an alert for the same pattern next season. Update the DAU forecast model."
- If it's still unclear: "I need 2 more days of data to confirm. In the meantime, I'd monitor hourly and escalate if the drop accelerates."

### Scenario Type to Tailored Approach

| Scenario Type | First Check | Key Hypotheses | Diagnostic Segmentation | Recommendation Type |
|---|---|---|---|---|
| DAU / engagement drop | Data pipeline integrity | Deploy, seasonality, competitor, logging bug | Platform, geo, user cohort, time of day | Rollback / investigate / monitor |
| Model performance drop | Score distribution shift (data drift) | Feature drift, label drift, upstream data change, model bug | Feature importance, slice analysis, recent data | Retrain / rollback / alert |
| Ship-or-not A/B test | Experiment validity (SRM, novelty effects) | Primary metric lift vs counter-metric drop, long-term effects | User segments, device types, exposure duration | Ship / iterate / don't ship + why |
| P0 incident | Service health (error rates, latency, on-call alerts) | Recent deploys, dependency failures, traffic spikes | Error codes, affected endpoints, dependency SLOs | Rollback / scale / escalate + timeline |
| Metric design | Existing metrics coverage and gaps | Leading vs lagging indicators, gaming risk, sensitivity | User journey stages, team ownership boundaries | Define guardrail + northstar + diagnostic metrics |

### 9/10 vs 6/10 Answer

- **6/10**: "I'd look at the data, check if there was a deployment, maybe look at the database logs, and then figure out what happened."
- **9/10**: "I'd start by confirming the signal is real, check the data pipeline and compare across time zones and platforms to rule out instrumentation issues. If real, I'd build a hypothesis tree: internal causes (deployment, feature flag, data bug) vs external causes (competitor launch, seasonality, platform event). I'd prioritize hypotheses by probability x impact, pull the most diagnostic query first, then narrow down. Once I have the root cause, I'd quantify the user impact and recommend a remediation path."

The difference: the 9/10 answer follows a structure, forms hypotheses before querying, eliminates data quality issues first, and connects findings to a business recommendation.

### Five Common Mistakes

1. **Queries before hypotheses**: Jumping to queries before forming hypotheses. "I'd query DAU by platform" is not structured -- it's a guess. Build a hypothesis first, then explain why that segmentation tests it.
2. **Skipping pipeline checks**: Not checking the data pipeline first. About 30-40% of apparent metric drops are instrumentation failures. Skipping this step makes you look like you've never dealt with production data.
3. **Root cause only**: Stopping at root cause without a recommendation. "...so I'd recommend rolling back the modal, validating address client-side instead, and re-running the A/B test with the fix."
4. **Single hypothesis**: Proposing only one hypothesis. Experienced analysts know there are always multiple potential causes. Listing 3-5 hypotheses before narrowing shows breadth.
5. **Ignoring uncertainty**: If you're not sure, say so: "I'd want to see another 24 hours of data before concluding this is a real drop vs. noise." Acknowledging uncertainty is a sign of statistical maturity, not weakness.

### Interview Template

**Opening (30 seconds):** Restate the problem in your own words. Clarify the magnitude and timeline. "So DAU dropped 15% starting yesterday at 5pm -- is that 15% relative to the prior day or the weekly average? And which platforms are we seeing this on?"

**Step through DIAGNOSE out loud:**
1. "First I'd verify the data is accurate, check the pipeline..."
2. "Assuming data is good, here's my hypothesis tree..."
3. "I'd start with the deployment hypothesis because it's highest probability. The query I'd run is..."
4. "Based on that, I'd narrow to... and my recommendation is..."
5. "Open questions I'd want to validate are..."

**Time management:** Spend ~30% on hypothesis formation, ~40% on investigation logic, ~30% on recommendation. Don't get so deep into one hypothesis that you never make a recommendation.

---

## Deep Dive: DAU Drop Scenario Walkthrough

Source: [Scenario Walkthrough: Why Is DAU Dropping? (CalibreOS)](https://www.calibreos.com/learn/scenarios-dau-drop)

### What Strong Answers Optimize For

DAU is a headline, not a mechanism. In production, it moves when any of these move: the count of new users, the probability a logged-in user returns, sessions per user, the probability any session includes a counted active event, or the definition of "active" (schema, identity merge, or client instrumentation). Make that explicit early; treating DAU as a single lever usually leads to ad hoc slicing.

Interviewers are grading:
- **Instrument discipline** before cause stories
- **Decomposition** so you do not "explain" a new-user problem with a ranking story
- **Localization** to a version/geo/tenure slice that narrows the hypothesis set
- **Decision quality**: rollback, holdout, comms, guard alerts, with impact sizing and a statement of what you still do not know

### DAU Decomposition (Accounting View)

Treat DAU as a small set of levers so your story cannot contradict arithmetic. A durable mental model: active users = new + returning (with overlap handled by your identity graph). Returning is driven by D1/D7-style habits; new is driven by acquisition and activation. Sessions per DAU and events per session capture "depth" when you suspect engagement moved but the user base did not.

If the business only surfaces DAU, triangulate with whatever exists on the same clock: app opens, `session_start` counts, WAU, signups, notification sends.

- If DAU is down but signups and activation are up while return visits fall -- the story is retention, not acquisition.
- If DAU is down and only the paid channel's new users are down -- the story may be spend or attribution, not a universal product regression.
- The interview win is **consistency** between decomposition and the hypothesis you bet on.

### What Interviewers Are Testing at Each Level

**E4 / Mid-level:** Identifies the problem domain (platform, pipeline, or product regression). Checklist approach: check instrumentation, segment by platform, look for DoW effects. Can read a dashboard and tell you "iOS is down, Android is flat." Misses: doesn't rank hypotheses by P(hypothesis) x falsification cost; overlooks bot/scraper traffic removal; doesn't flag that a pipeline change removing invalid traffic can cause a step-function DAU drop that is actually a data quality improvement, not a regression.

**E5 / Senior:** Systematic investigation with explicit hypothesis formation ordered by cheapest disproof first. Decomposes DAU into new vs. returning and sessions-per-user before naming a cause. Understands DoW normalization and won't call a DoW-aligned drop a crisis. Reasons about mix effects: global DAU flat while a high-value geo craters is a Simpson's paradox the aggregate hides. Proposes both immediate mitigation (rollback flag, kill switch) AND precursor monitoring (crash rate by build as an alert). Marks metric windows as invalid for exec readouts when instrumentation was broken.

**E6+ / Staff:** Asks the org-level question: why did a 14% DAU drop reach the CEO without a P0 declared by the on-call? Drives postmortem action items that change process: staged rollout with crash gates, ETL SLOs with alerting on pipeline delay, written metric contract (what "DAU" means, which source wins during incidents, who owns the definition). Can explain the incident to a VP in two sentences. Doesn't need to present every segmentation slice to prove rigor.

### Signal Ladder

- **Low signal**: "I'd segment by platform and check seasonality" without ordered checks; one causal story; ends without an action or with a vague "monitor."
- **Good signal**: Clear D -> I -> A -> N -> O; instrumentation first; 3+ hypotheses; segmentation to localize; at least one confounder (Simpson, mix, experiment exposure).
- **High signal**: Ties the localized slice to a binary world event (ship at T-0, outage window, ad pause), quantifies user/revenue order of magnitude, defines P0 response and invalid metric window for exec readouts, and states pre-registered falsifiers for the top hypothesis.

### Simpson's Paradox and Mix Effects

Simpson's paradox and mix effects are not stats trivia; they are how smart people ship wrong conclusions. Example: DAU is flat overall while new user DAU craters and returning DAU rises -- if acquisition mix shifts toward low-retention geos, the aggregate can hide a severe activation problem. Always ask: "If I only looked at the total, which story am I forbidden to tell?"

Experiments add another wrinkle: if 40% of users are in a holdout and a bad treatment hits only that arm, the global DAU can look mildly negative while the affected slice is very negative. The fix is to join to exposure tables and read intent-to-treat or treatment effects, not just a global DAU line.

### Worked Example: Step Change at 17:00 UTC

- **Signal**: DAU -14% DoW-adjusted vs 4-week baseline; starts at 17:05 UTC, flat before.
- **Instrument**: Event volume from iOS clients is down; warehouse agrees with stream; no ETL delay spike. Not a pure pipeline story.
- **Narrow**: iOS 18% down, Android +1%. Geo is global; new vs return both down within iOS, strongest on the newest app version.
- **Mechanism match**: A mobile release landed at 17:00 UTC for iOS; crash rate for that build jumps in the same five-minute bin.
- **Own/State**: Recommend rollback or feature-flag off the crashing path; comms: "product metrics unreliable for iOS until hotfix" with ETA; P0. Confirm crash-free DAU in 24h on rollback cohort vs holdout; postmortem on staged rollout and crash gates.

Time-aligned binary events plus a localized slice is how you get from DAU to an owner in one hour.

### Segment Drill-Down SQL Shape

```sql
-- Analytic *shape* only: in interview, narrate the intent per slice, not 15 queries.
WITH daily AS (
  SELECT
    dt,
    platform,
    app_version,
    country,
    user_tenure_bucket,  -- e.g. 0-1d, 2-7d, 8-30d, 30d+
    COUNT(DISTINCT user_id) AS dau
  FROM fct_client_events
  WHERE dt BETWEEN :start AND :end
    AND is_active_user_event = TRUE
  GROUP BY 1,2,3,4,5
)
SELECT
  *,
  dau - LAG(dau) OVER (PARTITION BY platform, app_version, country, user_tenure_bucket ORDER BY dt) AS dau_delta
FROM daily
ORDER BY ABS(dau_delta) DESC
LIMIT 200;

-- Pick platform first when the story is a client crash,
-- or country first when the story is regional outage/ads.
```

### Slice Diagnostic Table

| Slice pattern | Leading hypotheses | Fast falsification |
|---|---|---|
| iOS down, Android flat | Bad release, WebView, push token, ASO | Release timestamp vs crash; version histogram |
| Single country | Outage, regional campaign pause, data residency | Infra/ISP map; ad spend; CDN |
| New users only | Attribution, store, ASO, paid fraud, onboarding | Signups, CAC, creative change log |
| Returning only | Relevance, habit, notifs, paywall, competitor | Session depth, reactivation campaigns |
| Exposed-to-test only | Bad treatment | Bucket integrity, SRM, guard metrics |
| Flat DAU, down revenue | Mix, not this scenario's hero metric | Cross-check: ARPU, paid events |

### Executive Readout Non-Negotiables

Refuse to ship without:
- **Two-source truth** for DAU for the period in question, with a named owner if sources diverge.
- **Localized slice** or honest statement "still global" with top 2 unexcluded possibilities.
- **Impact order-of-magnitude**, not fake precision: % of user base, rough ARPU if revenue is on the line.
- **Action + rollback** with a next-check time (e.g. T+2h, T+24h) and guard metric for the precursor.
- **Invalid window** if pipeline was broken: explicit "do not use 6h after deploy X for iOS DAU" for downstream teams.

### Traps That Fail Senior Bar

- **Dawn-of-time SQL without a hypothesis**: infinite slices lead to noise mining and correlation theater.
- **Mistaking DoW noise for a break**: always anchor DoW or YoY for consumer apps.
- **Treating p-values on 20 metrics as independent**: multiple testing is how teams ship false fixes.
- **Forgetting identity**: MAU/DAU merge rules changes can move "users" without moving humans.

### When the Answer Is "We Do Not Know Yet"

Staff-level candidates earn trust by separating confidence from clarity. If instrument checks are still running, you do not invent a P0. Time-box: "By T+2h we will know if warehouse matches stream; if not, I recommend freezing iOS DAU in exec decks only for that window and using Android as a sanity shadow metric -- not as ground truth, but as a directional check on global hype."

That sentence shows you understand governance and externalities to other teams' decisions -- higher signal than a clever causal graph no one can verify in time.

### Close Strong (45-Second Version)

"I treat DAU as non-stationary and composite: I lock the definition, verify data, decompose levers, localize the break, and only then name a cause with a timestamped world event. My ask of leadership is: give me 90 minutes to rule out pipeline, then we either rollback with a cost estimate or we broaden the search with acquisition and market calendar on the same timeline."

---

## Deep Dive: Engagement vs Revenue, Guardrails & Horizon

Source: [Scenario Walkthrough: Engagement vs Revenue, Guardrails & Horizon (CalibreOS)](https://www.calibreos.com/learn/scenarios-engagement-revenue)

### Why This Is Not a "Balance the Two" Question

Engagement (time-on-site, sessions, DAU) is a manipulable input on short horizons. Revenue and profit are often lagging and carry variance that a 7-day A/B test is underpowered to pin down. A feed team can maximize watch-time in ways that destroy ad inventory quality, push down RPM, and increase refunds -- sometimes while raising a naive CTR.

High-signal analysis refuses a single-hero-metric story. Define an OEC (overall evaluation criterion) with explicit guardrails (max acceptable regression on ARPU, refund rate, trust-and-safety incidents, and latency), and state the horizon needed before harms should appear. "We will monitor revenue" without a stopping rule, a duration, and an owner is not an operating plan.

### What Interviewers Are Testing at Each Level

**E4 / Mid-level:** Recognizes that engagement and revenue can diverge and names both as important. Can identify that "we should watch ARPU" is the right instinct. Knows Goodhart's law at a surface level ("when a measure becomes a target, it ceases to be a good measure"). Misses: can't articulate why a 7-day A/B test is structurally underpowered to detect ARPU harm (thin event count, high variance), doesn't pre-register guardrail redlines before starting the test, and can't explain what "novelty effect" means for a 5% session-time lift -- that week-one UX changes attract inflated engagement that inverts after habituation.

**E5 / Senior:** Pre-registers the OEC with explicit guardrails and stopping rules before the test runs. Distinguishes between proxy metric divergence (engagement up, RPM down) and Goodhart gaming (the team optimized engagement because that's the bonus metric, not because it's the right objective). Understands multi-objective optimization at the experiment level: proposes a constrained ranker objective -- maximize session length subject to an RPM floor -- rather than running a follow-up test. Calls out that CUPED reduces variance but doesn't substitute for a pre-registered duration when ARPU events are thin. Identifies the specific failure mechanism when engagement and revenue diverge: usually composition (time shifted to low-yield inventory), not a universal engagement quality drop.

**E6+ / Staff:** Asks the org-level question: who owns ARPU in the OEC stack? If PMs are bonused on DAU and engineers are bonused on engagement, the org will systematically trade revenue for vanity metrics until the P&L suffers, and no amount of per-experiment guardrail-setting fixes that. Drives changes to how OKRs are structured, how cross-functional review works when a primary lifts but a guardrail moves, and what written governance exists when an exec wants to override a redline. Can explain the north star metric definition problem: engagement-as-proxy only works if the correlation between engagement and LTV is stable, and it breaks when you're optimizing against it. Surfaces ecosystem risk -- creator quality, ad market depth, buyer-seller trust -- that a single-surface engagement win can slowly destroy.

### Depth Ladder (Mid, Senior, Staff)

- **Mid:** Names primary and secondary metrics; "we should look at both engagement and money."
- **Senior:** Pre-registers guardrails; segment-level ARPU; discusses novelty and underpowered revenue; suggests CUPED or longer run for precision.
- **Staff:** Organizational incentives and cannibalization between surfaces; ecosystem (creator supply, ad market depth); defines governance -- how exec exceptions work when a primary lifts but a guardrail wiggles; ties to holdout and long-run LTO (learning-to-optimize) failure modes.

### Goodhart, Gaming, and the Metric Stack

Goodhart's law is not philosophy club -- it is a release-review reality. If PMs or ML teams are bonused on a single engagement scalar, the system (human + model) will find degenerate equilibria: endless notifications, low-quality recency bias, or dark-pattern friction removal that increases short clicks and refunds.

Production orgs answer with a stack: a primary (often a growth or experience objective), 2-4 guardrails with redlines ("do not launch if..."), and diagnostic metrics to explain mechanism (ad CTR, ad depth, time-to-first-ad, return rate, chargeback rate, CS contacts). The interview wants you to name a mechanism when engagement and money diverge -- composition (low-value time), auction pressure, or ad relevance -- not vibes.

### Cannibalization, Surfaces, and the Portfolio Problem

A single-surface win can be a portfolio loss: more time in one tab that steals from higher-RPM moments, a checkout experiment that steers toward bad-margin SKUs, or a ranking change that overweights cheap UGC and hollows the premium supply your ads target.

Staff candidates say "cannibalization" out loud and ask whether the A/B is isolated or portfolio-interfering. If the same user sees multiple experiments or multiple ranking objectives, the SUTVA (stable unit treatment value assumption) story breaks; you need stricter readouts, switchback-style or stratified designs for network-heavy products, and longer washout when treatment effects are sticky.

### Guardrail-First Readout (Steps You Can Narrate in 8 Minutes)

1. **Clarify the decision class:** Ship a new UX, reweight a ranker, change ad density, or reprice? Who is exposed -- all users, new only, a country?
2. **Pre-specify OEC + guardrails + duration:** One primary. Guardrails: ARPU or RPM, refund or chargeback, D7/D30 retention proxy, p95 latency. Pre-registration beats fishing in 20 metrics.
3. **Check experiment hygiene:** SRM on assignment, novelty/learning effects (early lift may invert), and whether revenue metrics have enough events in the test window. Mention CUPED for precision when the baseline is stable.
4. **Decompose divergence:** If engagement is up and ARPU is down, split by inventory type, geography, and tenure (whale vs long tail). A flat ARPU in aggregate can hide harm in whales -- often the revenue story finance cares about.
5. **Quantify the trade in business terms:** Convert to expected revenue range per 1000 users (not a fake point estimate) and compare to rollout cost and reversibility.
6. **Decision rule:** Default: no broad ship if a pre-registered guardrail crosses a redline. Escalation path for exec exception with written risk ownership. Follow-up: targeted redesign, constrained ranker, or longer test.
7. **If you launch under uncertainty:** Staged % rollout, kill criteria on guardrails, and a champion model that reverts automatically when thresholds trip.

### Worked Example: +5% Time on Site, -2% RPM, Both "Significant" at 7d

- **Hygiene first:** SRM clean; exposure balanced; the RPM drop is not a tiny-CID artifact only.
- **Mechanism check:** Not just "ads bad" -- split by ad depth, inventory mix, and sponsored vs organic engagement. A common story: the redesign increases time in low-yield inventory; RPM falls because impression quality drops even as raw time rises.
- **Duration honesty:** 7d may be enough to see the RPM direction; 28d may be required for refund and repeat purchase. Say: "We are confident in short-revenue harm direction; we are underpowered on 28d LTV. Default no broad ship unless an exec takes named risk and we have staged rollout with kill on RPM."
- **Prefer a constrained second experiment** that directly optimizes session revenue or ad relevance subject to a time-on-site floor, instead of rerunning the same UX variant.

### Primary Up / Guardrail Down: Mechanism Map

| Pattern | What Likely Broke (Mechanism) | Next Cuts for Evidence |
|---|---|---|
| Engagement up, RPM down | Lower-quality inventory time; ad relevance | Sponsored CTR, eCPM, ad depth by page |
| Faster checkout, more GMV, lower profit | Margin mix, promo abuse | SKU mix, return rate, fraud signals |
| Feed time up, D30 ARPU flat or down | Time shifted to non-monetizable content | Revenue per minute of attention by category |
| Push/notification lift, later unsub spike | Fatigue, permission churn | Opt-out curve, 28d message volume |
| Aggressive rec for watch time, creator exodus 90d out | Supply ecosystem harm | Creator revenue share, upload trend by cohort |
| Latency regresses, engagement still up on slow networks | Hidden user harm in p50 only | p95, region slices, guard on Core Web Vitals |

### CUPED, Power, and What You Can Honest-Claim in a Week

CUPED (Deng, Xu, et al. at Microsoft) reduces variance in A/B by using a pre-period covariate; it is standard vocabulary for senior DS. The interview point is not the formula -- it is: "We should not pretend a noisy 7d ARPU with wide CIs is a license to ship if the guardrail is a safety constraint."

What impresses: you separate statistical significance on a short window from business sufficiency. If ARPU is a hard guardrail, you either extend the test, raise power with CUPED/covariates, or reframe the launch as staged with automatic rollback. You do not hand-wave "we will watch monthly ARPU" without an owner and a trigger.

### No-Ship and Maybe-Ship Triggers

**Hard no-ship (typical):** Any pre-registered guardrail crosses a redline (ARPU, chargebacks, refund, latency SLO) with enough power to trust directionally -- not necessarily z=3 on 7d, but a consistent story + mechanism.

**Maybe-ship (with exec sign-off):** Primary strong, guardrail borderline noisy, staged launch to 5% for two weeks, champion path that auto-reverts, named business owner for downside.

**Iterate-first:** Primary up but mechanism shows toxic engagement; redesign a variant that preserves the engagement lift in high-RPM moments only.

**Portfolio conflict:** Another team's metric moves because of your test -- synchronize readouts, cluster or switchback for interference-heavy surfaces.

### Anti-Patterns in Real Readouts

- **P-hacking across 20 metrics** without FDR or pre-registration -- your "5% false positive" is a fiction.
- **Novelty lift in week one** treated as steady-state -- many UX wins invert when learning effects burn off.
- **"We will monitor"** without kill switch and SLO is how revenue harm lands in Q3.

### One Staff-Level Sentence

"I don't maximize engagement. I maximize a pre-registered business objective subject to explicit revenue, trust, and latency constraints, with a stated horizon for each, because the shortcut that wins the 7d chart is often the one that taxes LTV in week six."

---

## Deep Dive: The A/B Test Went Wrong -- SRM, Peeking, and Interference

Source: [Scenario Walkthrough: The A/B Test Went Wrong, SRM, Peeking, and Interference (CalibreOS)](https://www.calibreos.com/learn/scenarios-ab-test-wrong)

### The Question Under the Question

A broken test in interviews is usually one of a few **classes**:

- **Statistics**: Peeking, optional stopping, many metrics without multiplicity control, or reading a thin revenue line on a short window.
- **Engineering**: SRM from bad assignment, eligibility applied after the bucket, redirect drops, or treatment-induced dropout.
- **Product**: Novelty in week one that inverts later.
- **Interference**: Shared inventory, ad auctions, or feeds so user-level SUTVA fails.

Weak candidates treat a small p-value as a **ship** bit. Strong candidates **stop** when identification breaks, run the SRM check before hero metrics, and separate *monitoring* from a pre-registered launch readout. They price a re-run or redesign against a bad OKR that can live for quarters, not against *looking* busy in SQL.

### What Interviewers Are Testing at Each Level

**E4 / Mid-level:** Knows what SRM is and can say "the test is broken" when it's present. Has a checklist: check SRM first, then peeking, then novelty. Can read a chi-square result and declare the test invalid. Misses: doesn't independently derive *why* the chi-square is the right test for this (goodness-of-fit on assignment counts), can't explain the family-wise error mechanics behind peeking beyond "you're not supposed to peek," and doesn't connect SUTVA failure to the specific mechanism (shared inventory, auctions, social graph) in the scenario at hand.

**E5 / Senior:** Systematic hypothesis formation across all four failure classes (statistics, engineering, product, interference) with explicit falsification. Explains peeking as multiple-comparison-over-time, not a moral rule. Can distinguish between SRM from treatment-induced dropout (bias in treatment effect) versus SRM from assignment bugs (broken randomization), and names different fixes for each. Proposes both immediate mitigation (invalidate test, fix bucketing, re-run) AND redesign path (cluster, switchback, or geo experiment if SUTVA fails). Adds monitoring: A/A checks on the next experiment, cumulative SRM alerts rather than manual end-of-test checks. Knows the difference between CUPED reducing variance and alpha-spending solving peeking -- they are orthogonal.

**E6+ / Staff:** Asks why this happened from a process standpoint. Was there a culture of daily optional stopping that no one formalized into a stopping rule? Did the experiment platform lack automated SRM checks? Drives post-mortem action items: add SRM gating to the experimentation platform so a broken test can't proceed to a readout, formalize pre-registration with a product and stats owner sign-off before an experiment starts, educate PMs that a monitoring dashboard is not a hypothesis test. Can explain the business cost of false learning (a bad OKR that lives for quarters) versus the cost of a re-run. Presents the invalidation to a VP in two sentences without making the team feel incompetent.

### What 9/10 Sounds Like

You call **SRM** a **chi-square** goodness-of-fit on assignment counts with a *stricter* alpha than product metrics -- many teams use 0.001 because it is a data quality gate. You describe peeking as family-wise error inflation, not a moral lecture. You name interference when the treatment moves shared inventory, ad auctions, or feeds so user-level SUTVA fails. You separate unit of randomization from unit of analysis.

### SRM: When Groups Are Not Comparable

**SRM** means the observed number of *assigned* units per arm does not match the planned ratio beyond sampling noise. The textbook check is Pearson's chi-square goodness-of-fit; platforms automate it on cumulative assignments. A significant SRM is treated as a **red light** for causality, not a detail to *weight away* in a deck.

Common *engineering* causes: assignment bugs, redirect tests dropping users, race conditions, caching of a variant, eligibility filters that run *after* bucket draw, and treatment-induced dropout when one arm is slow or broken. The interview win is: **stop reading treatment effects, fix the bucket, re-run** -- not *we reweighted*.

### Debug Order for a Broken Experiment

1. **Confirm unit and exposure**: User versus session assignment; is analysis on **intent-to-treat** or only exposed? Filter-after-assignment is a classic SRM and bias source.
2. **Run SRM on cumulative assignments**: Chi-square against planned ratio; plot assignment over time to catch step changes after a deploy.
3. **If SRM, segment**: Mobile versus web, app version, locale. Treatment-specific dropout often localizes the bug.
4. **If no SRM, check peeking and duration**: Were metrics watched daily with optional stopping? For thin outcomes, 7d may be underpowered noise.
5. **Novelty and learning**: Early lifts on UX often invert; pre-register duration or use sequential methods if the org supports them.
6. **Interference and spillover**: Shared auctions, follow graphs, inventory. If SUTVA fails, user-level ATE is not what you think; use cluster or switchback.
7. **Decision**: Fix and rerun. Do not ship on broken identification. If the business must act, run a smaller honest pilot with clear limits.

### Common Failure Modes: Symptom and Fix

| Symptom | Likely Cause | What Strong Candidates Say |
|---|---|---|
| 50/50 configured, 60/40 observed | Assignment bug, eligibility filter, redirect drops | SRM invalidates; fix bucket code |
| Big lift in week 1, flat or negative in week 3 | Novelty, learning, or seasonality | Pre-registered min duration; curve inspection |
| Primary p small, SRM p tiny | Do not read primary | Stop; debug assignment first |
| Conversion up in test, not in control | Analysis on converters only, conditioning on post-treatment | ITT or pre-specified compliers |
| Lift only in low-value geos | Interference or market-specific bug | Geo-stratified design or holdout |

### Worked Example: p = 0.001 on Primary, p = 1e-8 on SRM

I do not present the primary metric as a win. The readout is one line: **allocation** failed; causal comparison of arms is not licensed. I ask for an engineering owner to debug bucketing, a re-run date, and I separate product monitoring from a formal ship decision. If the business must act before the fix, I scope a limited pilot with clean assignment, or a clearly labeled observational read with wide uncertainty -- not a cosmetic reweight of means.

### Peeking, Optional Stopping, and the Culture of Daily Checks

Peeking means watching a metric until it crosses a lucky threshold, then treating **that first crossing** as the final test. Even with good intentions, that optional stopping **searches** across many chances for noise, so nominal 5% thresholds no longer mean 5% false-positive risk. Fix it with a pre-registered horizon, or a proper sequential / group-sequential design your platform actually supports so Type I error stays honest under early stops.

Culture matters too: a standing meeting that keeps asking "is it green yet?" is an implicit stopping rule even if the charter never said so. You should still **monitor SRM, latency, and reliability** as safety guardrails, without treating every dashboard glance as a formal inference on the launch primary.

**CUPED** and related variance reducers **shrink noise**; they **do not** fix peeking. Those are orthogonal knobs: one attacks sampling variance, the other corrupts the decision rule if you stop opportunistically.

### Phrases to Avoid in a Triage Meeting

- "We reweighted" as a full substitute for understanding why SRM happened.
- "Directional" when the allocation bug is large and treatment arms are not exchangeable.
- Citing a power calculation from a design you did not actually follow because you stopped early the first time p crossed a line.

### Close (45-Second Version)

"If **exchangeability** is broken, plot polish does not fix the test. I run SRM first, I respect time horizons for thin events and lagging metrics, and I name interference when SUTVA is false. After that, the choice is re-run, redesign with cluster or switchback, or a transparent non-causal pilot with guardrails -- not a hero slide with a p-value."

---

## Deep Dive: System Outage -- Payment Service Returning 500s in Production

Source: [Scenario Walkthrough: Payment Service Returning 500s in Production (CalibreOS)](https://www.calibreos.com/learn/scenarios-system-outage)

### What This Outage Scenario Evaluates

This scenario evaluates incident command quality under uncertainty, not just technical troubleshooting. Interviewers want to see whether you can sequence actions correctly while customer harm is happening in real time.

The expected order is consistent: stabilize user impact, contain blast radius, isolate first failing dependency, choose reversible mitigation, and communicate status with disciplined cadence. Candidates who start with root-cause theorizing before containment usually score poorly.

Payment outages are especially sensitive because delay translates directly to revenue loss and trust damage. Strong answers explicitly prioritize critical transaction flows over secondary functionality and describe decision thresholds for rollback versus targeted mitigation.

Staff-level responses include governance behavior: timeline ownership, stakeholder coordination, and post-incident prevention actions with clear owners and deadlines.

### What Interviewers Are Testing at Each Level

**E4 / Mid-level:** Knows to check recent deploys, look at error logs, and restart services. Has a mental checklist: is it the DB, is it the network, is it a code change? Can read dashboards and identify what's wrong once pointed at the right graph. Misses: doesn't think about blast radius containment first (starts with root cause theorizing while users are down), doesn't understand gray failure modes (partial availability is often worse than total outage because it's harder to detect and cascading failures are more likely), restarts services without preserving evidence.

**E5 / Senior:** Sequences actions correctly under pressure: declare severity and assign roles first, then contain impact with reversible mitigations (fail closed, activate degraded mode, protect core payment path), then localize fault by traversing the dependency graph. Understands cascading failure patterns -- a payment timeout storm can saturate upstream connection pools and take down services that were healthy. Explicitly chooses rollback vs. targeted mitigation based on temporal correlation with recent changes and rollback safety, not gut feel. Proposes SLO-gated recovery validation before declaring the incident resolved.

**E6+ / Staff:** Thinks about incident command architecture: who owns mitigation vs. diagnosis vs. stakeholder communication, and ensures these run in parallel rather than sequentially. Anticipates second-order effects -- retry amplification, queue buildup, fallback path overload -- and applies circuit breakers before those effects dominate. Can explain the incident to a VP in two sentences with named cause, containment action, and time-to-stabilize from telemetry, not hand-waved heroics. Drives post-mortem action items that change the architecture: pre-defined rollback thresholds, chaos engineering to validate blast radius containment, and runbooks that eliminate the need for real-time debate about mitigation strategy.

### High-Signal Response Pattern

Declare severity, establish command roles, protect critical transactions, and avoid blind restarts that erase evidence.

### P0 Outage Response Loop

1. **Declare and align:** Set severity, assign incident commander and communication owner, and create one source of truth channel.
2. **Contain impact:** Fail closed for unsafe operations, activate degraded mode, and prioritize payment authorization over non-critical features.
3. **Localize fault:** Use dependency health and traces to isolate whether failure is app, DB, network, or upstream provider.
4. **Choose mitigation:** Rollback if deployment-correlated; otherwise reroute, circuit-break, or shed load based on failure class.
5. **Recover and learn:** Validate SLO recovery, communicate customer impact, and run a blameless postmortem with concrete actions.

### Decision Table During Payment Outage

| Condition | Primary Action | Why | Risk if Delayed |
|---|---|---|---|
| Deployment in last 30 minutes and aligned metric break | Immediate rollback | Highest-probability reversible fix | Prolonged failed transactions |
| Upstream provider timeout surge | Circuit break and fallback provider | Stops retry amplification | Cascading saturation |
| DB saturation with queue growth | Load shed non-critical writes | Protect payment core path | Full database collapse |
| Unknown cause but severe impact | Degraded mode with strict prioritization | Buys time for diagnosis | Unbounded customer harm |

### Rollback Safety Matrix During Active Outage

| Recent Change Type | Rollback Safety | Failure Mode if Rolled Back Blindly | Preferred Response |
|---|---|---|---|
| Stateless application code only | High | Low risk; mostly request-level behavior reverts | Immediate rollback if correlated with incident start |
| Backward-compatible schema migration + app deploy | Medium | Partial mismatch if some instances still expect new fields | Rollback app first, keep migration, verify read/write paths |
| Non-backward-compatible schema or data format change | Low | Rollback can break deserialization or writes, extending outage | Forward fix with feature-flag disable, DB-safe hot patch |
| Third-party config/credential rotation | Medium | Reverting can invalidate new auth path or rotate stale secrets back | Validate dependency health and rotate to known-good credential set |
| Multiple concurrent changes | Low until isolated | Wrong rollback adds noise and destroys signal | Bisect by change timeline, mitigate blast radius, then rollback targeted component |

### Common Interview Failures

- Spending ten minutes on root-cause theory before containment.
- Restarting all services without dependency evidence.
- Ignoring stakeholder and customer communication timelines.

### Close Strong (45-Second Version)

"My first goal is to stop user harm, my second is to restore safely, and my third is to ensure this class of outage is harder to repeat."
