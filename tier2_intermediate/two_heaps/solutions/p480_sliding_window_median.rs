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
 *
 * Example 2:
 *     Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
 *     Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
 *
 * Constraints:
 *     - 1 <= k <= nums.length <= 10^5
 *     - -2^31 <= nums[i] <= 2^31 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
 *
 * Hint: Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
 */

use wasm_libs::*;
use std::collections::{BinaryHeap, HashMap};
use std::cmp::{Reverse, Ordering};
use std::io::{self, Write};

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

fn main() {
    let nums = read_ints();
    let kline = read_ints();
    let k = kline[0] as usize;

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

    let mut out = io::stdout().lock();
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
                writeln!(out, "{:.6}", small.peek().unwrap().val as f64).unwrap();
            } else {
                let s = small.peek().unwrap().val;
                let l = large.peek().unwrap().0.val;
                writeln!(out, "{:.6}", (s + l) as f64 / 2.0).unwrap();
            }
        }
    }

    std::process::exit(0);
}
