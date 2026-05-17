# Divide and Conquer — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

Source: [Divide and Conquer: Master Theorem, Merge Sort, Quick Select, and Closest Pair (CalibreOS)](https://www.calibreos.com/learn/dsa-divide-conquer)

## Phase 1: Pattern Recognition (1-2 min)
- [ ] Identify that the problem can be split into **independent** subproblems
- [ ] Confirm subproblems do NOT overlap (if they do, consider DP instead)
- [ ] Estimate that the naive solution is O(n^2) or worse
- [ ] Verify the combine step can be done in O(n) or O(n log n)
- [ ] State the three D&C steps: Divide, Conquer, Combine

## Phase 2: Recurrence Analysis (2-3 min)
- [ ] Write the recurrence: T(n) = aT(n/b) + f(n)
- [ ] Identify a (number of subproblems), b (size reduction factor), f(n) (combine cost)
- [ ] Compute the critical exponent log_b(a)
- [ ] Apply the correct Master Theorem case:
  - [ ] Case 1: f(n) polynomially smaller than n^(log_b a) -> T(n) = Theta(n^(log_b a))
  - [ ] Case 2: f(n) = Theta(n^(log_b a)) -> T(n) = Theta(n^(log_b a) * log n)
  - [ ] Case 3: f(n) polynomially larger -> T(n) = Theta(f(n))
- [ ] State the final time complexity
- [ ] State space complexity (auxiliary array + recursion stack)

## Phase 3: Core Algorithm Design (5-8 min)
- [ ] Define the base case correctly (length 0 or 1 for sort, n <= 3 for closest pair)
- [ ] Define the divide step (split by index, by coordinate, by partition position)
- [ ] Define the combine/merge step (two-pointer merge, strip check, partition)
- [ ] Handle edge cases:
  - [ ] Empty input or single element
  - [ ] Two elements
  - [ ] All elements equal (stability matters for merge sort)
  - [ ] Already sorted / reverse sorted input
- [ ] Write clean recursive or iterative implementation
- [ ] Use indices instead of slicing where possible (avoids O(n) copy overhead)

## Phase 4: Algorithm-Specific Deep Dive (5-8 min, interviewer-directed)

### If Merge Sort / Inversion Count:
- [ ] Explain why merge sort is preferred over quicksort for linked lists
- [ ] Show how the merge step works (two-pointer, place smaller element)
- [ ] Explain stability (use `<=` not `<` in comparison)
- [ ] Demonstrate inversion counting during merge (add `len(left) - i` when placing right element)

### If Quick Select:
- [ ] Explain single-partition recursion (vs quicksort's both sides)
- [ ] Choose Lomuto partition for clear pivot final position
- [ ] Use random pivot to avoid O(n^2) worst case
- [ ] State the median-of-medians guarantee (O(n) worst case, high constant)
- [ ] Compare with heap approach: quick select O(n) vs heap O(n log k)

### If Closest Pair:
- [ ] Explain the divide by x-coordinate midpoint
- [ ] Describe the strip construction (points within d of dividing line)
- [ ] Prove at most 7 comparisons per strip point (d x d square argument)
- [ ] Note: presorting by y eliminates the extra log factor

### If Median of Two Sorted Arrays:
- [ ] Binary search on partition of the **smaller** array
- [ ] Maintain `|left_A| + |left_B| = (m+n+1)/2`
- [ ] Valid partition: `max(left_A) <= min(right_B)` AND `max(left_B) <= min(right_A)`
- [ ] Handle edge sentinel values (-inf / +inf) for boundary partitions

## Phase 5: Complexity Justification (2-3 min)
- [ ] State time complexity with the Master Theorem case that justifies it
- [ ] State space complexity (auxiliary arrays, recursion depth)
- [ ] Compare with alternative approaches:
  - [ ] D&C vs DP (independent vs overlapping subproblems)
  - [ ] Quick select O(n) vs Heap O(n log k) vs Sort O(n log n)
  - [ ] Merge sort O(n log n) guaranteed vs Quicksort O(n log n) average
- [ ] Discuss best/worst/average case if relevant

## Phase 6: Wrap-Up (1-2 min)
- [ ] Summarize the approach in 2-3 sentences
- [ ] State trade-offs made and why
- [ ] Mention what you would optimize with more time
- [ ] Ask the interviewer if they have follow-up questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
