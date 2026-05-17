# Code Review Excellence — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State what code review must accomplish in your own words
- [ ] Ask clarifying questions:
  - [ ] Is the interviewer asking about giving reviews, receiving reviews, or building a review culture?
  - [ ] What level is the target audience (junior team, senior team, cross-functional)?
  - [ ] Is the context a specific PR scenario or a general process question?
- [ ] List the two main failure modes:
  - [ ] LGTM culture: rubber-stamping that lets bugs and debt accumulate
  - [ ] Nitpick spiral: focusing on style while missing correctness and design
- [ ] State the core mental model: code review is a teaching opportunity disguised as a quality gate
- [ ] Describe what interviewers look for at each level:
  - [ ] L4/Mid: knows what to look for, has opinions on PR size
  - [ ] L5/Senior: has a review hierarchy, gives actionable non-adversarial feedback
  - [ ] Staff: frames review as a system, measures effectiveness, uses review for mentorship

## Phase 2: High-Level Approach (3-5 min)
- [ ] Present the five-layer review hierarchy in strict order:
  - [ ] Layer 1: Correctness (always blocking)
  - [ ] Layer 2: Design (usually blocking, raised early)
  - [ ] Layer 3: Tests (blocking for non-trivial logic)
  - [ ] Layer 4: Maintainability and naming (mostly non-blocking)
  - [ ] Layer 5: Style (never blocking if linter exists)
- [ ] Explain the approve/block decision framework:
  - [ ] Approve: no correctness or design issues
  - [ ] Approve with Comments: non-blocking suggestions
  - [ ] Block: correctness bug, design flaw, missing tests, misleading naming
- [ ] State the key rule: do not proceed to the next layer until the current one is satisfied

## Phase 3: Core Technique Design (5-8 min)
- [ ] Explain the four-part comment structure:
  - [ ] Observation: what you see (not "this is wrong")
  - [ ] Problem: why it matters (concrete consequence)
  - [ ] Suggestion: specific alternative with example
  - [ ] Label: signal blocking vs. non-blocking intent
- [ ] Walk through the comment label system:
  - [ ] `[blocking]`: must fix before merge
  - [ ] `[suggestion]`: author's call on timing
  - [ ] `[nit]`: explicitly non-blocking style/naming
  - [ ] `[question]`: asking for clarification before deciding
  - [ ] `[praise]`: specific positive signal, builds trust
  - [ ] `[future]`: awareness of tech debt, not this PR
- [ ] Contrast bad vs. good feedback examples:
  - [ ] Bad: "This is slow" (observation only, no problem, no suggestion)
  - [ ] Good: "[blocking] This loop makes N sequential DB writes. At 50K records/day this takes ~25s and risks pool exhaustion. Use batch insert instead."
- [ ] Explain when to ask questions vs. make statements (uncertain = ask first)

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss reviewing for the future maintainer:
  - [ ] Context-dependent names (tmp, data, result) need replacement
  - [ ] Comments explain why, not what
  - [ ] Magic numbers become named constants with source documentation
  - [ ] Implicit preconditions need explicit documentation
  - [ ] Test: "What would someone who has never seen this code need to know?"
- [ ] Address PR size and review effectiveness:
  - [ ] Effective review drops above ~400 lines of diff (Microsoft Research data)
  - [ ] Target: one PR = one conceptual change, 200-400 lines
  - [ ] Large PRs should be decomposed, not reviewed as-is
- [ ] Discuss reviewer turnaround obligations:
  - [ ] First response within one business day (Google standard)
  - [ ] Read the PR description before the diff
  - [ ] No description = ask for one before reviewing
- [ ] Identify and explain anti-patterns:
  - [ ] LGTM culture: would you be on-call for this at 2am?
  - [ ] Nitpick spiral: count blocking vs. non-blocking; zero blocking on non-trivial PR = missed something
  - [ ] Ego-driven blocking: "I wouldn't do it this way" needs concrete evidence
  - [ ] Serial reviewing: prefer one thorough pass
  - [ ] Reviewing without running the code: pull the branch for non-trivial changes
- [ ] Explain level differentiation (L3 through Staff review behavior)
- [ ] Discuss when to move design debates out of the PR and into a design doc

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize your approach in 2-3 sentences
- [ ] State the key trade-offs (thoroughness vs. velocity, style vs. substance)
- [ ] Mention what you would improve with more time (metrics, team culture shifts)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
