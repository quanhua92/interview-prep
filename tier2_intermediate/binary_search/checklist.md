# Binary Search -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Identify the Template (1-2 min)
- [ ] Read the problem: does it ask for an exact value, a boundary, or a min/max answer?
- [ ] Determine which template applies:
  - [ ] **Template 1** (`left <= right`): exact target in a known structure
  - [ ] **Template 2** (`left < right`): first/last position satisfying a predicate -- most common
  - [ ] **Template 3** (`left + 1 < right`): need both neighbors (peak, local min/max)
  - [ ] **Bisect-on-answer**: problem asks min/max X where `can_do(X)` is monotonic
- [ ] If bisect-on-answer, identify the search space bounds and write the feasibility function signature
- [ ] State the loop invariant out loud before writing any code

## Phase 2: Write the Core Loop (3-5 min)
- [ ] Initialize `left` and `right` with correct bounds:
  - [ ] Template 1: `left = 0, right = len(arr) - 1`
  - [ ] Template 2: `left = 0, right = len(arr) - 1` (or `len(arr)` for insert-at-end)
  - [ ] Bisect-on-answer: `left = min_possible, right = max_possible`
- [ ] Write the loop condition matching your template
- [ ] Compute `mid = left + (right - left) // 2`
- [ ] Write the predicate / comparison:
  - [ ] Template 1: check `==`, `<`, `>` with `left = mid + 1` / `right = mid - 1`
  - [ ] Template 2: if predicate True → `right = mid`, else → `left = mid + 1`
- [ ] Verify: does the loop converge? (no infinite loop when `left == right`)

## Phase 3: Handle the Variant (3-5 min)

### Rotated Sorted Array (LC 33, 153)
- [ ] State insight: "one half is always sorted after any rotation"
- [ ] Determine sorted half: `arr[left] <= arr[mid]` means left is sorted
- [ ] Check if target falls in the sorted half's range, then narrow accordingly
- [ ] For duplicates (LC 81): handle `arr[left] == arr[mid] == arr[right]` with `left++, right--`

### First/Last Position (LC 34)
- [ ] Plan: two separate binary searches, not one pass
- [ ] Leftmost: predicate `nums[mid] >= target`, when equal set `right = mid`
- [ ] Rightmost: predicate `nums[mid] > target`, answer is `right - 1`

### Peak Element (LC 162)
- [ ] State insight: "binary search works on unsorted arrays when the decision rule is monotonic"
- [ ] Predicate: `nums[mid] < nums[mid+1]` → peak is right
- [ ] Verify `mid+1` is safe: `left < right` guarantees `mid < right`

### Median of Two Sorted Arrays (LC 4)
- [ ] Binary search on partition index of the smaller array (O(log min(m,n)))
- [ ] Compute `j = half_len - i` for the partition in the second array
- [ ] Cross-condition: `A[i-1] <= B[j]` and `B[j-1] <= A[i]`
- [ ] Edge cases: use `-inf`/`+inf` for boundary indices

### Bisect-on-Answer (LC 875, 1011, 410)
- [ ] Define `can_do(X)` feasibility function
- [ ] Verify monotonicity: if X works, X+1 also works
- [ ] Set search bounds: lower = `max(weights)` or similar, upper = `sum(weights)` or similar
- [ ] Apply Template 2 with `predicate = can_do(mid)`

## Phase 4: Verify Edge Cases (2-3 min)
- [ ] Empty array / single element
- [ ] Target at boundaries (first/last index)
- [ ] All elements equal
- [ ] Target not present
- [ ] For bisect-on-answer: check that lower bound is achievable and upper bound is valid

## Phase 5: Common Pitfalls Self-Check
- [ ] Did I pair `left <= right` with `right = mid - 1` (Template 1 only)?
- [ ] Did I pair `left < right` with `right = mid` (Template 2)?
- [ ] Am I using `left + (right - left) // 2`, not `(left + right) // 2`?
- [ ] For bisect-on-answer, is my upper bound `sum(...)`, not `max(...)`?
- [ ] Does my predicate direction match the boundary update?

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:

Source: [Binary Search Patterns: 3 Templates and Bisect-on-Answer (CalibreOS)](https://www.calibreos.com/learn/dsa-binary-search)
