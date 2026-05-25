/**
 * P912: Sort an Array (Medium)
 * https://leetcode.com/problems/sort-an-array/
 * Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Merge Sort, Bucket Sort, Radix Sort, Counting Sort
 * 
 * Given an array of integers nums, sort the array in ascending order and return it.
 * You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.
 * 
 * Example 1:
 *     Input: nums = [5,2,3,1]
 *     Output: [1,2,3,5]
 *     Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).
 * 
 * Example 2:
 *     Input: nums = [5,1,1,2,0,0]
 *     Output: [0,0,1,1,2,5]
 *     Explanation: Note that the values of nums are not necessarily unique.
 * 
 * Constraints:
 *     - 1 <= nums.length <= 5 * 104
 *     - -5 * 104 <= nums[i] <= 5 * 104
 * 
 * Template (python3):
 *     class Solution:
 *         def sortArray(self, nums: List[int]) -> List[int]:
 * 
 * Hint: Implement merge sort — divide array in half, sort recursively, merge.
 */
function mergeSort(nums)
  if (nums.length <= 1) return [...nums];

  const mid = Math.floor(nums.length / 2);
  const left = mergeSort(nums.slice(0, mid));
  const right = mergeSort(nums.slice(mid));

  const result = [];
  let i = 0, j = 0;
  while (i < left.length && j < right.length)
    if (left[i] <= right[j])
      result.push(left[i]);
      i++;
    } else
      result.push(right[j]);
      j++;
    }
  }
  while (i < left.length)
    result.push(left[i]);
    i++;
  }
  while (j < right.length)
    result.push(right[j]);
    j++;
  }
  return result; {
    throw new Error("NotImplementedError");
}

function solve(nums)
  return mergeSort(nums); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [5, 2, 3, 1], expected: [1, 2, 3, 5] },
  { label: "duplicates", input: [5, 1, 1, 2, 0, 0], expected: [0, 0, 1, 1, 2, 5] },
  { label: "single element", input: [1], expected: [1] },
  { label: "empty array", input: [], expected: [] },
  { label: "already sorted", input: [1, 2, 3, 4, 5], expected: [1, 2, 3, 4, 5] },
  { label: "reverse sorted", input: [5, 4, 3, 2, 1], expected: [1, 2, 3, 4, 5] },
  { label: "all same elements", input: [7, 7, 7, 7], expected: [7, 7, 7, 7] },
  { label: "negative numbers", input: [-5, -3, -8, -1], expected: [-8, -5, -3, -1] },
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
