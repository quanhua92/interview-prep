# Design

## Core Idea

Design data structures that support specific operations with required time complexity constraints. Common patterns: HashMap + array for O(1) CRUD, HashMap + doubly-linked list for O(1) ordered operations, HashMap + frequency buckets for O(1) min/max.

## When to Recognize

- "Design", "implement a data structure"
- O(1) time constraints for insert, delete, get, getRandom, etc.
- LFU/LRU cache
- "Encode and decode" (if hash-based mapping)

## Complexity

| Variant | Time | Space |
|---------|------|-------|
| HashMap + array (random access) | O(1) amortized | O(n) |
| HashMap + DLL (ordered access) | O(1) amortized | O(n) |
| HashMap + freq buckets (min/max) | O(1) amortized | O(n) |

## Problems in This Pattern

| Problem | Difficulty | Variant |
|---------|-----------|---------|
| P460 LFU Cache | Hard | HashMap + freq-to-keys sets |
