# Binary Search -- Discussion & Deep Dive

## One-Liner
Master binary search by internalizing three templates (exact match, predicate search, neighbor-compare) and the bisect-on-answer generalization, not by improvising loop conditions on the fly.

## Why Binary Search Trips Up Strong Candidates
Binary search is the most misimplemented algorithm in FAANG interviews. Candidates who can recite "eliminate half the search space" still fumble LC 33, 34, or 162 because they improvise the loop condition and boundary updates instead of applying a fixed template.

The core principle: binary search works whenever you have a **monotonic property** -- a boolean predicate that is `False` for a prefix of the search space and `True` for the suffix (or vice versa). You don't need a sorted array. You need a sorted *predicate*. This reframing unlocks a huge class of problems where binary search is non-obvious: "minimum capacity to ship packages", "find peak element in unsorted array", "median of two sorted arrays".

## What Interviewers Are Testing
1. Can you identify that binary search applies to a non-obvious problem?
2. Do you get the loop condition and boundary updates right on the first attempt?
3. Can you extend it to bisect-on-answer?

A candidate who says "I'll binary search on the capacity" for a shipping problem, before any coding, signals strong problem-solving instincts.

## The Three Templates

### Template 1: Exact Target Exists
- Use when you KNOW the target is in the array and you want its index.
- Loop condition: `left <= right`.
- Update: `left = mid + 1` or `right = mid - 1`.
- Never exits with `left == right` without checking `mid`.
- Use for: LC 704 (basic search), finding any occurrence of a target.

```python
def search(nums, target):
    left, right = 0, len(nums) - 1
    while left <= right:
        mid = left + (right - left) // 2
        if nums[mid] == target:
            return mid
        elif nums[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1
```

### Template 2: First Index Satisfying a Predicate
- Use when searching for the leftmost position where a condition becomes true.
- Loop condition: `left < right`.
- Update: `right = mid` (never skip mid, it might be the answer) or `left = mid + 1`.
- After loop, `left == right` is your answer, no post-loop check needed.
- **This is the most general template for LC-style problems.**

```python
def find_first_true(nums, predicate):
    left, right = 0, len(nums) - 1
    while left < right:
        mid = left + (right - left) // 2
        if predicate(nums[mid]):
            right = mid      # mid might be the answer
        else:
            left = mid + 1   # mid is False, safe to skip
    return left if predicate(nums[left]) else -1
```

### Template 3: Peak/Boundary Needing mid-1 and mid+1
- Use only when you need to compare mid with its neighbors AND guarantee neither `mid-1` nor `mid+1` goes out of bounds.
- Loop condition: `left + 1 < right`.
- After loop, manually check `left`, `mid`, `right`.
- Rarely needed; prefer Template 2 when possible.

## Bisect-on-Answer: The Most Powerful Generalization

You can binary search on **any monotonic answer space**, even when there's no array at all.

The pattern: "What is the minimum X such that condition C(X) holds?" If C(X) is monotonic (once true for some X, it's true for all larger X), binary search on X directly.

**Identification checklist:**
1. The question asks for a minimum or maximum value
2. You can write a feasibility function `can_do(X)` that checks whether X works in O(n) or O(n log n)
3. If X works, then X+1 also works (monotonicity)

**Examples:**
- LC 1011: Minimum capacity to ship packages -- binary search capacity from `max(weights)` to `sum(weights)`
- LC 875: Koko eating bananas -- binary search eating speed
- LC 410: Split array largest sum -- binary search on the maximum subarray sum
- Template is always: `left = minimum_possible`, `right = maximum_possible`, Template 2 with predicate = `can_do(mid)`

## Canonical Problems (Deep Dives)

### Search in Rotated Sorted Array (LC 33)
Key insight: **one half is always sorted** after any rotation. Determine which half is sorted by comparing `arr[left]` and `arr[mid]`.

Decision rule: if `arr[left] <= arr[mid]`, left half `[left..mid]` is sorted. Otherwise, right half `[mid..right]` is sorted. Check if target falls within the sorted half's range.

For LC 81 (with duplicates): `arr[left] == arr[mid]` is ambiguous; handle with `left++, right--` which degrades worst case to O(n).

This is Template 1 applied to a non-standard structure. State the sorted-half insight explicitly before coding.

### Find First and Last Position (LC 34)
Template 2 applied twice: once for leftmost, once for rightmost.

**Leftmost:** When `nums[mid] == target`, don't return, set `right = mid`. Predicate: `nums[mid] >= target`.

**Rightmost:** Safer approach -- binary search for first index where `nums[mid] > target`, then subtract 1.

### Find Peak Element (LC 162)
Demonstrates binary search on **unsorted arrays**. Only requirement is a monotonic decision rule, not sorted order.

Key insight: if `nums[mid] < nums[mid+1]`, a peak exists to the right (either the array stops increasing, or we hit the boundary which is `-inf`). Template 2 with predicate `nums[mid] > nums[mid+1]`. Loop invariant: a peak always exists within `[left, right]`.

### Median of Two Sorted Arrays (LC 4)
Typically the hardest binary search problem; usually a "stretch" question at Staff level.

The idea: the median partitions the combined array into two equal halves. Binary search on the **partition point** of the smaller array. If partition after index `i` in A, then partition in B must be at `j = (m+n+1)/2 - i`. We need: `A[i-1] <= B[j]` and `B[j-1] <= A[i]`.

Binary search on the smaller array gives O(log(min(m,n))). Edge cases: use `-inf`/`+inf` for boundary partitions.

## 12-Problem Taxonomy

| LC# | Problem | Template | Key Predicate |
|-----|---------|----------|--------------|
| 704 | Binary Search | Template 1 | Exact target |
| 35 | Search Insert Position | Template 2 | `nums[mid] >= target` |
| 33 | Search in Rotated Array | Template 1 | One half always sorted |
| 34 | First and Last Position | Template 2 x2 | Two passes: leftmost + rightmost |
| 153 | Min in Rotated Array | Template 2 | `nums[mid] > nums[right]` |
| 162 | Find Peak Element | Template 2 | `nums[mid] < nums[mid+1]` |
| 875 | Koko Eating Bananas | Bisect-on-answer | `can_eat(speed): total_hours <= H` |
| 1011 | Ship Packages in D Days | Bisect-on-answer | `can_ship(cap): days_needed <= D` |
| 410 | Split Array Largest Sum | Bisect-on-answer | `can_split(max_sum): splits <= m` |
| 74 | Search 2D Matrix | Template 1 (2D->1D) | Flattened sorted array |
| 240 | Search 2D Matrix II | Elimination | Start top-right, move left/down |
| 4 | Median of Two Sorted Arrays | Template 1 on partition | `left_a <= right_b AND left_b <= right_a` |

## Common Mistakes That Cost Offers

1. **Wrong loop condition:** Using `left <= right` with `right = mid` creates infinite loop when `left == right`. Always pair `left < right` with `right = mid`.

2. **Integer overflow (non-Python):** Use `left + (right - left) / 2`, not `(left + right) / 2`.

3. **Off-by-one in predicate direction:** For Template 2, if `predicate(mid)` is True, set `right = mid` (not `mid-1`). Swapping produces wrong answers, not runtime errors -- the hardest class of bug.

4. **Wrong boundary for bisect-on-answer:** For minimum-capacity problems, `right = sum(weights)`, not `max(weights)`.

Source: [Binary Search Patterns: 3 Templates and Bisect-on-Answer (CalibreOS)](https://www.calibreos.com/learn/dsa-binary-search)
