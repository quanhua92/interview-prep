# Code Review Excellence

Source: [Code Review Excellence: The Craft That Most Engineers Never Learn (CalibreOS)](https://www.calibreos.com/learn/prod-code-review)

## One-Liner
Apply a structured review hierarchy (correctness > design > tests > maintainability > style) to give actionable feedback that improves both code quality and team growth.

## Requirements

### What Code Review Must Deliver
- Catch correctness bugs and design flaws before they reach production
- Improve the author's engineering skills over time (mentorship, not gatekeeping)
- Keep the codebase maintainable for future engineers who were not part of the original change
- Avoid adversarial dynamics that slow velocity or suppress honest feedback

### Why Most Review Falls Short
- **LGTM culture**: rubber-stamping to avoid conflict; bugs and architectural debt accumulate silently
- **Nitpick spiral**: 80% of comments on formatting/naming while missing broken logic or bad design
- **Cargo-cult practices**: teams inherit review habits by osmosis without questioning effectiveness

## Key Concepts

### The Review Hierarchy (Strict Order)

| Priority | Layer | Blocking? | Focus |
|----------|-------|-----------|-------|
| 1 | Correctness | Always | Does the code do what the PR claims? Happy path, edge cases, error handling, failure modes |
| 2 | Design | Usually | Right abstraction? Code in the right place? Simpler alternative? Leaky abstractions? |
| 3 | Tests | For non-trivial logic | Would a bug in this path be caught? Tests assert behavior, not implementation details |
| 4 | Maintainability | Mostly non-blocking | Names encode intent, comments explain why, no magic numbers, duplication extracted |
| 5 | Style | Never (if linter exists) | Formatting, import order; automate with tooling, not reviews |

Key rule: do not proceed to the next layer until the current one is satisfied.

### Review Decision Framework
- **Approve**: No correctness or design issues; suggestions are truly optional
- **Approve with Comments**: Non-blocking suggestions worth noting; code can ship as-is
- **Block**: Correctness bug, design flaw, missing tests for business logic, or actively misleading naming

### Comment Labels (Make Intent Explicit)

| Label | Meaning |
|-------|---------|
| `[blocking]` | Must fix before merge |
| `[suggestion]` | Would improve code; author's call on timing |
| `[nit]` | Minor style/naming; explicitly non-blocking |
| `[question]` | Reviewer uncertain; asking for clarification |
| `[praise]` | Something done well; builds trust |
| `[future]` | Worth addressing later, not in this PR |

## Decisions

### Four-Part Comment Structure
1. **Observation**: What you see (not "this is wrong")
2. **Problem**: Why it matters (concrete consequence)
3. **Suggestion**: Specific alternative with example
4. **Label**: Signal blocking vs. non-blocking

This structure separates technical truth from interpersonal friction. The same insight written as "This is slow" creates defensiveness; written as observation + problem + suggestion it creates collaboration.

### Asking Questions vs. Making Statements
When uncertain, frame as a question first: "Is there a reason this doesn't use the connection pool?" The author may know something you do not. Invite explanation before requiring change.

### When to Take Discussion Outside the PR
Design disagreements that require more than 2-3 rounds of comments should move to a synchronous discussion or design doc. PR threads are a poor medium for architectural debates.

## Deep Dives

### Reviewing for the Future Maintainer
The most important reader is the engineer debugging this code at 2am six months from now, not the author. This changes what you look for:
- **Context-dependent names**: `tmp`, `data`, `result` only make sense to the author
- **Comments that explain why**: "Sort by creation date because the UI expects chronological order and the DB returns insertion order after backfills" vs. "Sort by creation date"
- **Magic numbers**: `count > 100` without explanation becomes a mystery; `MAX_BATCH_SIZE = 100` with a comment about the source
- **Implicit preconditions**: `process_payment(user_id, amount)` does not signal that `user_id` must be pre-validated

Test: "If I had never seen this codebase, what would I need to know that is not obvious from reading it?"

### PR Size and Review Effectiveness
- Empirical data (Microsoft Research, SmartBear): reviewers effectively review ~400 lines of diff; above that, defect detection drops sharply
- Target: one PR = one conceptual change, 200-400 lines (excluding generated code and tests)
- A 1,500-line PR should be sent back with a decomposition suggestion, not reviewed as-is

### Reviewer Turnaround Obligations
- First response within one business day (Google's internal standard)
- PRs waiting 3+ days kill momentum and cause merge conflicts
- If you cannot review promptly, acknowledge and state when you can
- Read the PR description before the diff; if there is no description, ask for one

### Anti-Patterns to Watch For
- **LGTM culture**: If you would not feel comfortable being on-call for this code at 2am, do not approve it
- **Nitpick spiral**: Count blocking vs. non-blocking comments; zero blocking findings on a non-trivial PR means you missed something
- **Ego-driven blocking**: "I wouldn't have done it this way" needs concrete evidence (fewer bugs, better perf, clearer maintainability)
- **Serial reviewing**: Ten comments, wait for fixes, ten more. Prefer one thorough pass
- **Reviewing without running the code**: UI, migrations, and concurrency bugs often surface only under execution

### Level Differentiation

| Level | Review Focus | Common Gap |
|-------|-------------|------------|
| L3/Junior | Style, obvious bugs | Design problems, edge cases, mentorship angle |
| L4/Mid | Correctness, tests; starting to see design | Systemic issues, own anti-patterns |
| L5/Senior | Full hierarchy in order; labeled comments | Team-level patterns, measuring effectiveness |
| Staff | Reviews design before code; uses review for mentorship and team norms | This is the target level |

## Follow-Ups
- How do you handle a PR from a senior engineer who resists feedback?
- How do you measure whether your team's code review process is actually working?
- What do you do when you inherit a codebase with deeply entrenched LGTM culture?
- How do you balance review thoroughness with shipping velocity during a deadline crunch?
- How would you onboard a new team member into your review culture?

## Interview Questions (from the article)
1. Walk me through how you approach reviewing a pull request
2. How do you give feedback on a PR that has a fundamental design problem, when the author has already written all the code?
3. How do you use code review as a mentorship tool?
