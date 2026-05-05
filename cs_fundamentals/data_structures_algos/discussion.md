# Data Structures & Algorithms

Core data structures, traversal algorithms, complexity analysis, and a big-O reference table for SWE interviews.

## Key Concepts

- **Arrays**: Contiguous memory storage with O(1) access by index and O(n) insertion/deletion (shifting required). Static arrays have fixed size; dynamic arrays (ArrayList, vector) amortize resize operations to achieve O(1) average append. Cache-friendly due to memory locality.
- **Linked Lists**: Nodes connected by pointers with O(1) insertion/deletion at known positions but O(n) access by index. Singly linked lists have one direction; doubly linked lists support bidirectional traversal. No cache locality due to non-contiguous memory.
- **Hash Tables**: Store key-value pairs with O(1) average-case lookup, insertion, and deletion. Use a hash function to map keys to bucket indices. Collision resolution strategies include chaining (linked lists at each bucket) and open addressing (probing for the next open slot). Worst case is O(n) when many collisions occur.
- **Binary Search Trees (BST)**: Ordered tree structure with O(log n) average search, insert, and delete. Left subtree contains smaller values; right subtree contains larger values. Degenerates to O(n) when unbalanced (e.g., inserting sorted data). Balanced variants (AVL, red-black) guarantee O(log n) worst case.
- **Heaps**: A complete binary tree that maintains the heap property -- max-heap parents are greater than children, min-heap parents are smaller. O(1) access to the min/max element, O(log n) insert and extract. Implemented as an array for cache efficiency. Used in priority queues and heap sort.

## Common Questions with Brief Answer Outlines

**Q: When would you use a hash table versus a BST?**
- Use a hash table when you need O(1) average-case lookups and the order of elements does not matter.
- Use a BST when you need elements in sorted order or need range queries (find all keys between X and Y).
- Hash tables do not support efficient range queries; BSTs do via in-order traversal in O(n) for all, O(log n) per element.
- BSTs provide guaranteed O(log n) worst-case performance when balanced; hash tables can degrade to O(n) under worst-case collisions.
- Hash tables have higher constant factors due to hashing overhead and memory for buckets.

**Q: Explain BFS and DFS, and when to use each.**
- BFS (Breadth-First Search) explores level by level using a queue. Finds the shortest path in an unweighted graph. Uses O(V + E) time and O(V) space (queue can hold up to V/2 nodes at the widest level).
- DFS (Depth-First Search) explores as deep as possible before backtracking, using a stack (or recursion). Uses O(V + E) time and O(V) space (recursion depth or stack).
- Use BFS for shortest path in unweighted graphs, level-order traversal, and finding all nodes at distance k.
- Use DFS for cycle detection, topological sorting, connected components, maze solving, and when memory is constrained (DFS typically uses less space than BFS in wide graphs).

**Q: What is the difference between AVL trees and red-black trees?**
- Both are self-balancing BSTs guaranteeing O(log n) operations.
- AVL trees maintain a stricter balance factor (left and right subtree heights differ by at most 1), providing faster lookups.
- Red-black trees allow a looser balance constraint, requiring fewer rotations on insert and delete, providing faster writes.
- AVL trees are preferred in read-heavy workloads (databases, dictionaries); red-black trees in write-heavy workloads.
- Java's TreeMap and C++ std::map use red-black trees; databases often use AVL or B+ trees.

**Q: How does quicksort compare to mergesort?**
- Quicksort: average O(n log n), worst O(n^2) with poor pivot choice; in-place with O(log n) stack space; cache-friendly due to sequential access patterns.
- Mergesort: guaranteed O(n log n); requires O(n) additional space; stable sort (preserves relative order of equal elements); preferred for linked lists.
- Quicksort is generally faster in practice due to better cache locality and lower constant factors.
- Hybrid approaches (e.g., Timsort in Python/Java) combine insertion sort for small arrays with mergesort for larger ones.

**Q: What are time and space complexity trade-offs in common operations?**
- Precomputation (e.g., hash tables, prefix sums) trades space for faster query time.
- Memoization/caching stores computed results to avoid redundant work, using O(n) space to reduce exponential time to polynomial.
- In-place algorithms modify the input directly to save space but may be harder to understand or parallelize.
- Amortized analysis: a sequence of expensive operations averages out to low cost per operation (e.g., dynamic array resizing doubles capacity, giving O(1) amortized append).

**Q: How would you solve the "two sum" problem?**
- Problem: given an array of integers and a target sum, return the indices of two numbers that add up to the target.
- Brute force: check every pair -- O(n^2) time, O(1) space.
- Hash table approach: iterate through the array, storing each number in a hash table; for each element, check if (target - element) exists in the table -- O(n) time, O(n) space. This is the classic example of trading space for time.
- Sorting approach: sort the array, then use two pointers from both ends -- O(n log n) time, O(1) space (or O(n) if sorting is not in-place). Does not return original indices unless stored separately.

**Q: What is the difference between stable and unstable sorting?**
- A stable sort preserves the relative order of elements with equal keys; an unstable sort does not guarantee this.
- For example, if you sort a list of employees by department and then by name with a stable sort, employees with the same name will remain grouped by department. With an unstable sort, the department ordering among equal-name employees may be lost.
- Stable sorts: mergesort, Timsort (Python/Java default), insertion sort, bubble sort.
- Unstable sorts: quicksort (standard implementations), heapsort, shell sort.
- Stability matters when sorting on multiple keys or when equal elements carry additional associated data that should not be reordered.

## Quick Reference Table: Big-O Complexity

| Data Structure | Access | Search | Insert | Delete |
|---|---|---|---|---|
| Array | O(1) | O(n) | O(n) | O(n) |
| Linked List | O(n) | O(n) | O(1)* | O(1)* |
| Hash Table | O(1) avg | O(1) avg | O(1) avg | O(1) avg |
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(log n) |
| Heap | O(1) for min/max | O(n) | O(log n) | O(log n) |
| Trie | O(L) | O(L) | O(L) | O(L) |

*O(1) only if node pointer is known; O(n) if traversal is needed. L = length of key.
