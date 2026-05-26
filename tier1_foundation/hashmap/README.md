# HashMap / HashSet

## Core Idea

Use hash-based data structures (dict/set in Python, HashMap/HashSet in Java, unordered_map in C++) for O(1) average-time lookups, insertions, and deletions. This eliminates nested loops by enabling instant "have I seen this?" checks.

## When to Recognize

Look for these keywords in the problem statement:

- "Count frequency", "number of occurrences", "distinct"
- "Find if exists", "contains", "lookup"
- "Group by", "categorize", "classify"
- "Encode/decode", "map one value to another"
- "Random access by value" (not index)

## Complexity

| Variant | Time | Space |
|---------|------|-------|
| Frequency counting | O(n) | O(k) where k = unique elements |
| Lookup/contains check | O(1) avg | O(n) |
| Group by key | O(n) | O(k) |

## Key Insight

HashMap trades O(n) space for O(1) lookups. When a problem asks "does X exist?" or "how many times does X appear?", a hash map is almost always the answer. The alternative (sorting + two pointers) achieves O(1) space but O(n log n) time.

## Problems in This Pattern

| Problem | Difficulty | Variant |
|---------|-----------|---------|
| P380 Insert Delete GetRandom O(1) | Medium | HashMap + array design |
| P398 Random Pick Index | Medium | HashMap value -> indices |
| P447 Number of Boomerangs | Medium | HashMap distance counting |
| P500 Keyboard Row | Easy | HashSet row membership |
| P535 Encode and Decode TinyURL | Medium | HashMap encode/decode |
| P575 Distribute Candies | Easy | HashSet unique counting |
| P382 Linked List Random Node | Medium | Array indexing / reservoir sampling |
| P391 Perfect Rectangle | Hard | HashSet corner parity + area verification |

## Template Variants

1. **Frequency counting** -- count occurrences with Counter/dict
2. **Lookup table** -- map keys to values for O(1) retrieval
3. **Set membership** -- use HashSet for existence checks
