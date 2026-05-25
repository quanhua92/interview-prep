/**
 * P295: Find Median from Data Stream (Hard)
 * https://leetcode.com/problems/find-median-from-data-stream/
 * Topics: Two Pointers, Design, Sorting, Heap (Priority Queue), Data Stream
 * 
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
 * Implement the MedianFinder class:
 * 
 * Example 1:
 *     Input
 *     ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
 *     [[], [1], [2], [], [3], []]
 *     Output
 *     [null, null, null, 1.5, null, 2.0]
 * 
 *     Explanation
 *     MedianFinder medianFinder = new MedianFinder();
 *     medianFinder.addNum(1);    // arr = [1]
 *     medianFinder.addNum(2);    // arr = [1, 2]
 *     medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
 *     medianFinder.addNum(3);    // arr[1, 2, 3]
 *     medianFinder.findMedian(); // return 2.0
 * 
 * Constraints:
 *     - -105 <= num <= 105
 *     - There will be at least one element in the data structure before calling findMedian.
 *     - At most 5 * 104 calls will be made to addNum and findMedian.
 * 
 * Template (python3):
 *     class MedianFinder:
 * 
 *         def __init__(self):
 * 
 * 
 *         def addNum(self, num: int) -> None:
 * 
 * 
 *         def findMedian(self) -> float:
 * 
 * 
 * 
 *     # Your MedianFinder object will be instantiated and called as such:
 *     # obj = MedianFinder()
 *     # obj.addNum(num)
 *     # param_2 = obj.findMedian()
 * 
 * Hint: Use a max-heap for the lower half and a min-heap for the upper half.
 */
class MinHeap
  constructor()
    this.heap = [];
  }
  push(val)
    this.heap.push(val);
    this._bubbleUp(this.heap.length - 1);
  }
  pop()
    const top = this.heap[0];
    const last = this.heap.pop();
    if (this.heap.length > 0)
      this.heap[0] = last;
      this._sinkDown(0);
    }
    return top;
  }
  get size()
    return this.heap.length;
  }
  peek()
    return this.heap[0];
  }
  _bubbleUp(i)
    while (i > 0)
      const parent = (i - 1) >> 1;
      if (this.heap[i] < this.heap[parent])
        [this.heap[i], this.heap[parent]] = [this.heap[parent], this.heap[i]];
        i = parent;
      } else break;
    }
  }
  _sinkDown(i)
    const n = this.heap.length;
    while (true)
      let smallest = i;
      const left = 2 * i + 1;
      const right = 2 * i + 2;
      if (left < n && this.heap[left] < this.heap[smallest]) smallest = left;
      if (right < n && this.heap[right] < this.heap[smallest]) smallest = right;
      if (smallest !== i)
        [this.heap[i], this.heap[smallest]] = [this.heap[smallest], this.heap[i]];
        i = smallest;
      } else break;
    }
  } {
    throw new Error("NotImplementedError");
}

function solve(stream, _unused)
  const small = new MinHeap();
  const large = new MinHeap();
  const medians = [];

  for (const num of stream)
    small.push(-num);
    large.push(-small.pop());
    if (large.size > small.size)
      small.push(-large.pop());
    }

    if (small.size > large.size)
      medians.push(-small.peek());
    } else if (large.size > small.size)
      medians.push(large.peek());
    } else
      medians.push((-small.peek() + large.peek()) / 2);
    }
  }
  return medians; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "stream median", input: [[5, 15, 1, 3], "median"], expected: [5.0, 10.0, 5.0, 4.0] },
  { label: "two elements", input: [[1, 2], "median"], expected: [1.0, 1.5] },
  { label: "single element", input: [[42], "median"], expected: [42.0] },
  { label: "all same", input: [[3, 3, 3, 3], "median"], expected: [3.0, 3.0, 3.0, 3.0] },
  { label: "negative numbers", input: [[-5, -3, -1, 0], "median"], expected: [-5.0, -4.0, -3.0, -2.0] },
  { label: "alternating high low", input: [[100, 0, 100, 0, 100, 0], "median"], expected: [100.0, 50.0, 100.0, 50.0, 100.0, 50.0] },
  { label: "descending order", input: [[10, 9, 8, 7, 6, 5], "median"], expected: [10.0, 9.5, 9.0, 8.5, 8.0, 7.5] },
  { label: "extreme values", input: [[-100000, 100000], "median"], expected: [-100000.0, 0.0] },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(...t.input);
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
