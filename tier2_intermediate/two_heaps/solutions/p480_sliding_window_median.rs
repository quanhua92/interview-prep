/*
 * P480: Sliding Window Median (Hard)
 * https://leetcode.com/problems/sliding-window-median/
 * Topics: Array, Hash Table, Sliding Window, Heap (Priority Queue)
 *
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
 * You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
 * Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.
 *
 * Example 1:
 *     Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 *     Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
 *     Explanation:
 *     Window position                Median
 *     ---------------                -----
 *     [1  3  -1] -3  5  3  6  7        1
 *      1 [3  -1  -3] 5  3  6  7       -1
 *      1  3 [-1  -3  5] 3  6  7       -1
 *      1  3  -1 [-3  5  3] 6  7        3
 *      1  3  -1  -3 [5  3  6] 7        5
 *      1  3  -1  -3  5 [3  6  7]       6
 *
 * Example 2:
 *     Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
 *     Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
 *
 * Constraints:
 *     - 1 <= k <= nums.length <= 105
 *     - -231 <= nums[i] <= 231 - 1
 *
 * Hints:
 *     - The simplest of solutions comes from the basic idea of finding the median given a set of numbers. We know that by definition, a median is the center element (or an average of the two center elements). Given an unsorted list of numbers, how do we find the median element? If you know the answer to this question, can we extend this idea to every sliding window that we come across in the array?
 *     - Is there a better way to do what we are doing in the above hint? Don't you think there is duplication of calculation being done there? Is there some sort of optimization that we can do to achieve the same result? This approach is merely a modification of the basic approach except that it simply reduces duplication of calculations once done.
 *     - The third line of thought is also based on this same idea but achieving the result in a different way. We obviously need the window to be sorted for us to be able to find the median. Is there a data-structure out there that we can use (in one or more quantities) to obtain the median element extremely fast, say O(1) time while having the ability to perform the other operations fairly efficiently as well?
 *
 * Template (python3):
 *     class Solution:
 *         def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
 *
 * Hint: Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
 */


use std::collections::{BinaryHeap, HashMap};
use std::cmp::{Reverse, Ordering};

#[derive(Clone, Copy)]
struct Entry {
    val: i64,
    idx: usize,
}

impl PartialEq for Entry {
    fn eq(&self, other: &Self) -> bool { self.val == other.val }
}

impl Eq for Entry {}

impl PartialOrd for Entry {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> { Some(self.cmp(other)) }
}

impl Ord for Entry {
    fn cmp(&self, other: &Self) -> Ordering { self.val.cmp(&other.val) }
}

fn solve(nums: &[i32], k: usize) -> Vec<f64> {
    let mut small: BinaryHeap<Entry> = BinaryHeap::new();
    let mut large: BinaryHeap<Reverse<Entry>> = BinaryHeap::new();
    let mut delayed: HashMap<usize, i32> = HashMap::new();
    let mut in_small: HashMap<usize, bool> = HashMap::new();
    let mut small_sz: usize = 0;
    let mut large_sz: usize = 0;

    let prune_small = |small: &mut BinaryHeap<Entry>, delayed: &mut HashMap<usize, i32>| {
        while let Some(&top) = small.peek() {
            if let Some(&cnt) = delayed.get(&top.idx) {
                if cnt > 0 {
                    delayed.insert(top.idx, cnt - 1);
                    if cnt == 1 { delayed.remove(&top.idx); }
                    small.pop();
                } else { break; }
            } else { break; }
        }
    };

    let prune_large = |large: &mut BinaryHeap<Reverse<Entry>>, delayed: &mut HashMap<usize, i32>| {
        while let Some(&Reverse(ref top)) = large.peek() {
            if let Some(&cnt) = delayed.get(&top.idx) {
                if cnt > 0 {
                    delayed.insert(top.idx, cnt - 1);
                    if cnt == 1 { delayed.remove(&top.idx); }
                    large.pop();
                } else { break; }
            } else { break; }
        }
    };

    let make_balanced = |small: &mut BinaryHeap<Entry>, large: &mut BinaryHeap<Reverse<Entry>>,
                              delayed: &mut HashMap<usize, i32>, in_small: &mut HashMap<usize, bool>,
                              small_sz: &mut usize, large_sz: &mut usize| {
        while *small_sz > *large_sz + 1 {
            prune_small(small, delayed);
            if let Some(e) = small.pop() {
                in_small.insert(e.idx, false);
                *small_sz -= 1;
                *large_sz += 1;
                large.push(Reverse(Entry { val: e.val, idx: e.idx }));
                prune_small(small, delayed);
            } else { break; }
        }
        while *small_sz < *large_sz {
            prune_large(large, delayed);
            if let Some(Reverse(e)) = large.pop() {
                in_small.insert(e.idx, true);
                *large_sz -= 1;
                *small_sz += 1;
                small.push(Entry { val: e.val, idx: e.idx });
                prune_large(large, delayed);
            } else { break; }
        }
    };

    let mut res = Vec::new();
    let n = nums.len();

    for i in 0..n {
        prune_small(&mut small, &mut delayed);
        prune_large(&mut large, &mut delayed);

        let go_small = small.peek().map_or(true, |&Entry { val, .. }| nums[i] as i64 <= val);
        if go_small {
            small.push(Entry { val: nums[i] as i64, idx: i });
            in_small.insert(i, true);
            small_sz += 1;
        } else {
            large.push(Reverse(Entry { val: nums[i] as i64, idx: i }));
            in_small.insert(i, false);
            large_sz += 1;
        }

        make_balanced(&mut small, &mut large, &mut delayed, &mut in_small, &mut small_sz, &mut large_sz);

        if i >= k {
            let out_idx = i - k;
            *delayed.entry(out_idx).or_insert(0) += 1;
            if *in_small.get(&out_idx).unwrap_or(&true) {
                small_sz -= 1;
            } else {
                large_sz -= 1;
            }
            make_balanced(&mut small, &mut large, &mut delayed, &mut in_small, &mut small_sz, &mut large_sz);
        }

        if i >= k - 1 {
            prune_small(&mut small, &mut delayed);
            prune_large(&mut large, &mut delayed);
            if k % 2 == 1 {
                res.push(small.peek().unwrap().val as f64);
            } else {
                let s = small.peek().unwrap().val;
                let l = large.peek().unwrap().0.val;
                res.push((s + l) as f64 / 2.0);
            }
        }
    }
    res
}

fn feq(a: f64, b: f64) -> bool { (a - b).abs() < 1e-5 }

fn main() {
    struct Case<'a> { label: &'a str, input: &'a [i32], k: usize, expected: &'a [f64] }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[1, 3, -1, -3, 5, 3, 6, 7], k: 3, expected: &[1.0, -1.0, -1.0, 3.0, 5.0, 6.0] },
        Case { label: "window size 1", input: &[1, 2], k: 1, expected: &[1.0, 2.0] },
        Case { label: "example 2", input: &[1, 2, 3, 4, 2, 3, 1, 4, 2], k: 3, expected: &[2.0, 3.0, 3.0, 3.0, 2.0, 3.0, 2.0] },
        Case { label: "large int boundary", input: &[2147483647, -2147483648], k: 2, expected: &[-0.5] },
        Case { label: "all same values", input: &[1, 1, 1, 1], k: 2, expected: &[1.0, 1.0, 1.0] },
        Case { label: "window equals array", input: &[5, 5, 5, 5, 5], k: 5, expected: &[5.0] },
        Case { label: "all negative ascending", input: &[-5, -4, -3, -2, -1], k: 3, expected: &[-4.0, -3.0, -2.0] },
        Case { label: "descending order", input: &[10, 9, 8, 7, 6], k: 3, expected: &[9.0, 8.0, 7.0] },
    ];

    println!("\n============================================================");
    println!("  480. Sliding Window Median");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = solve(tc.input, tc.k);
        let ok = got.len() == tc.expected.len() && got.iter().zip(tc.expected.iter()).all(|(a, b)| feq(*a, *b));
        if ok {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}", tc.expected);
            println!("    Got:      {:?}", got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
