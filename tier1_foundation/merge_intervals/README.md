# Merge Intervals

## Core Idea

Sort intervals by their start time, then iterate through them linearly.
When the current interval overlaps with the last merged interval, merge them
by extending the end time. Otherwise, start a new group. This is also known
as the "line sweep" or "interval sweep" technique.

## When to Recognize

Look for these keywords in the problem statement:

- "Intervals", "ranges", "time slots"
- "Meetings", "schedule", "calendar"
- "Overlapping", "merge", "conflict"
- "Free time", "available slots", "minimum meeting rooms"

## Complexity

| Variant | Time | Space |
|---------|------|-------|
| Merge overlapping intervals | O(n log n) | O(n) |
| Insert interval into sorted list | O(n) | O(n) |
| Minimum meeting rooms (sweep line) | O(n log n) | O(n) |

## Key Insight

After sorting by start time, you only need to compare each interval with the
last merged interval -- you never need to look back further. This is because
if interval A does not overlap with interval B, and B does not overlap with
interval C, then A cannot overlap with C (given sorted start times).

## Problems in This Pattern

| Problem | Difficulty | Variant |
|---------|-----------|---------|
| P056 Merge Intervals | Medium | Merge overlapping intervals |
| P253 Meeting Rooms II | Medium | Minimum meeting rooms (sweep line) |
| P057 Insert Interval | Medium | Insert + merge into sorted intervals |
| P495 Teemo Attacking | Easy | Overlap of time ranges |

## Template Variants

1. **Merge overlapping intervals** -- classic sort and merge
2. **Insert interval into sorted list** -- merge with early termination
3. **Minimum meeting rooms** -- sort starts and ends separately (sweep line)

See `template.py` for annotated skeleton code for each variant.
