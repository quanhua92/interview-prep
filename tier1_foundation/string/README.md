# String Manipulation

## Core Idea

Solve problems by iterating through strings character by character, applying validation rules, transformations, or simple comparisons. These problems test basic string handling skills -- iteration, indexing, character classification, and string building.

## When to Recognize

Look for these keywords in the problem statement:

- "Valid", "detect", "check if" (string validation)
- "Format", "reformat", "rearrange" (string transformation)
- "Compare", "longest uncommon" (string comparison)
- "Segment", "split", "count words" (string parsing)

## Complexity

| Variant | Time | Space |
|---------|------|-------|
| Single pass validation | O(n) | O(1) or O(n) for output |
| String transformation | O(n) | O(n) for output |
| Comparison | O(n) | O(1) |

## Key Insight

String problems often have simpler solutions than they appear. Read carefully -- many "string" problems are actually one-liners disguised as complex challenges (e.g., P521 is just an equality check).

## Problems in This Pattern

| Problem | Difficulty | Variant |
|---------|-----------|---------|
| P520 Detect Capital | Easy | Case pattern validation |
| P521 Longest Uncommon Subsequence I | Easy | String equality comparison |
| P434 Number of Segments in a String | Easy | Space-to-non-space counting |
| P482 License Key Formatting | Easy | String reformat from right |

## Template Variants

1. **Validation** -- check if string matches a pattern (all caps, title case, etc.)
2. **Reformatting** -- transform string layout (insert dashes, uppercase, etc.)
3. **Comparison** -- compare strings directly or by character
