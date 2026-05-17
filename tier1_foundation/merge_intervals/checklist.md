# Merge Intervals Pattern — Working Checklist

Source: [Interval Patterns: Merge Intervals, Meeting Rooms & Sweep Line (CalibreOS)](https://www.calibreos.com/learn/dsa-intervals)

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Identify the Problem Type (1-2 min)
- [ ] Recognize keywords: "intervals", "overlapping", "meeting rooms", "schedule", "merge", "free slots", "minimum resources"
- [ ] Determine which variant:
  - [ ] Merge overlapping intervals (sort + scan with running merge)
  - [ ] Minimum meeting rooms / resources (sweep line or heap)
  - [ ] Insert interval into sorted list (3-phase scan)
  - [ ] Find free time slots (merge then find gaps)
  - [ ] Maximum overlap count (sweep line, track peak)
  - [ ] Interval scheduling maximization (sort by end time, greedy pick)
  - [ ] Minimum removals to make non-overlapping (same as scheduling max)
- [ ] Clarify boundary convention: are intervals closed [s,e] or half-open [s,e)?
  - [ ] Closed: `next.start <= current.end` means overlap
  - [ ] Half-open: `next.start < current.end` means overlap

## Phase 2: Brute Force (1 min)
- [ ] State the naive approach: compare all pairs, O(n^2) time
- [ ] Identify why it's suboptimal: sorting eliminates the need for pairwise checks

## Phase 3: Optimal Approach (2-3 min)
- [ ] State the sorting step: "Sort intervals by start time" (or end time for scheduling maximization)
- [ ] Explain why sorting enables greedy scan: transitivity of non-overlap
- [ ] Describe the scan logic:
  - [ ] Type 1 (Merge): maintain running merged interval, extend end on overlap, push and start new on gap
  - [ ] Type 2 (Sweep Line): convert each [s,e] to events (+1, -1), sort events, track running count, peak is answer
- [ ] State complexity: O(n log n) time from sort, O(n) space for output/events

## Phase 4: Code the Solution (5-8 min)
- [ ] Sort intervals (defensively, even if input looks sorted)
- [ ] Initialize result list or running variables
- [ ] Iterate through intervals/events with correct overlap check
- [ ] Handle the merge/extend logic: use `max(current.end, next.end)` for merging
- [ ] For sweep line: handle tie-breaking at same timestamp (end events before start events for open intervals)
- [ ] Return result

## Phase 5: Edge Cases (2-3 min)
- [ ] Empty input → `[]`
- [ ] Single interval → unchanged
- [ ] All intervals identical → one merged interval
- [ ] Completely non-overlapping → unchanged list
- [ ] Fully nested interval (e.g., [1,10] contains [2,5]) → `max()` handles it
- [ ] Touching intervals at boundary: does [1,2] and [2,3] overlap? (depends on open/closed)

## Phase 6: Communicate (ongoing)
- [ ] State the sort step explicitly at the beginning
- [ ] Draw a timeline for the interviewer to visualize the sweep
- [ ] Explain the sweep line intuition: "convert intervals to +1/-1 events, sort, track peak"
- [ ] Mention alternative approaches (heap for meeting rooms, 3-phase scan for insert)

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
