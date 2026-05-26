/**
 * P493: Reverse Pairs [PREMIUM] (Hard)
 * https://leetcode.com/problems/reverse-pairs/
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set
 * 
 * Given an integer array nums, return the number of reverse pairs in the array.
 * A reverse pair is a pair (i, j) where:
 * Example 1:
 *     Input: nums = [1,3,2,3,1]
 *     Output: 2
 *     Explanation: The reverse pairs are:
 *     (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
 *     (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
 * 
 * Example 2:
 *     Input: nums = [2,4,3,5,1]
 *     Output: 3
 *     Explanation: The reverse pairs are:
 *     (1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
 *     (2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
 *     (3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 5 * 104
 *     - -231 <= nums[i] <= 231 - 1
 * 
 * Hint: Use the merge-sort technique.
 * Hint: Divide the array into two parts and sort them.
 * Hint: For each integer in the first part, count the number of integers that satisfy the condition from the second part. Use the pointer to help you in the counting process.
 * 
 * Template (python3):
 *     class Solution:
 *         def reversePairs(self, nums: List[int]) -> int:
 */
function solve(nums)
  function mergeSort(arr)
    if (arr.length <= 1) return 0;
    const mid = Math.floor(arr.length / 2);
    const left = arr.slice(0, mid);
    const right = arr.slice(mid);
    let count = mergeSort(left) + mergeSort(right);

    let j = 0;
    for (const num of left)
      while (j < right.length && num > 2 * right[j])
        j++;
      }
      count += j;
    }

    const merged = [];
    let li = 0;
    let ri = 0;
    while (li < left.length && ri < right.length)
      if (left[li] <= right[ri])
        merged.push(left[li++]);
      } else
        merged.push(right[ri++]);
      }
    }
    while (li < left.length) merged.push(left[li++]);
    while (ri < right.length) merged.push(right[ri++]);

    for (let k = 0; k < arr.length; k++)
      arr[k] = merged[k];
    }
    return count;
  }

  return mergeSort([...nums]); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [1, 3, 2, 3, 1], expected: 2 },
  { label: "example 2", input: [2, 4, 3, 5, 1], expected: 3 },
  { label: "single element", input: [1], expected: 0 },
  { label: "all descending", input: [5, 4, 3, 2, 1], expected: 4 },
  { label: "sorted ascending", input: [1, 2, 3, 4, 5], expected: 0 },
  { label: "negative numbers", input: [2, 1, -1], expected: 2 },
  { label: "all equal", input: [1, 1, 1, 1], expected: 0 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
