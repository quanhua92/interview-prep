# Interview Prep

A pattern-based coding interview preparation toolkit. Master 20 coding patterns across 4 difficulty tiers, each with template code, key LeetCode problems, and automated tests.

## Quick Start

```bash
# Install dependencies (requires Python >= 3.13)
pip install -e ".[dev]"

# Run the progress dashboard
python main.py status

# Run all tests
pytest

# Run tests for a specific pattern
pytest tests/test_sliding_window.py -v

# Run a single problem file directly
python tier1_foundation/sliding_window/p003_longest_substring.py
```

## Patterns

### Tier 1: Foundation (Must Master)

| Pattern | Key Problems |
|---------|-------------|
| Sliding Window | P003 Longest Substring, P438 Find All Anagrams |
| Two Pointers | P167 Two Sum II, P011 Container With Most Water |
| Fast & Slow Pointers | P141 Linked List Cycle, P202 Happy Number |
| Merge Intervals | P056 Merge Intervals, P253 Meeting Rooms II |
| BFS | P102 Binary Tree Level Order, P994 Rotting Oranges |

### Tier 2: Intermediate (Very Common)

| Pattern | Key Problems |
|---------|-------------|
| DFS | P200 Number of Islands, P695 Max Area of Island |
| Two Heaps | P295 Median Finder |
| Top K Elements | P215 Kth Largest Element, P347 Top K Frequent Elements |
| Binary Search | P704 Binary Search, P153 Find Minimum in Rotated Sorted Array |
| Dynamic Programming | P070 Climbing Stairs, P322 Coin Change |

### Tier 3: Advanced (Important for Top Companies)

| Pattern | Key Problems |
|---------|-------------|
| Backtracking | P078 Subsets, P039 Combination Sum |
| Modified Binary Search | P033 Search in Rotated Sorted Array, P875 Koko Eating Bananas |
| Cyclic Sort | P442 Find All Duplicates, P268 Missing Number |
| Subsets | P046 Permutations, P090 Subsets II |
| Trie | P208 Implement Trie, P212 Word Search II |

### Tier 4: Expert (Differentiators)

| Pattern | Key Problems |
|---------|-------------|
| Union Find | P323 Connected Components, P684 Redundant Connection |
| Monotonic Stack | P739 Daily Temperatures, P084 Largest Rectangle in Histogram |
| Greedy | P055 Jump Game, P455 Assign Cookies |
| Matrix Traversal | P054 Spiral Matrix, P048 Rotate Image |
| Graph | P207 Course Schedule, P210 Course Schedule II |

## How to Use

### Standalone Run

Each problem file is self-contained and can be run directly:

```bash
python tier1_foundation/sliding_window/p003_longest_substring.py
```

### Pytest

Tests live in the `tests/` directory and mirror the pattern names:

```bash
# Run all tests
pytest

# Run a specific pattern's tests
pytest tests/test_sliding_window.py -v

# Run with coverage
pytest --cov=. --cov-report=term-missing
```

### CLI Dashboard

Track your progress across all 20 patterns:

```bash
# View progress for all patterns
python main.py status

# Mark a pattern as in progress
python main.py update sliding_window in_progress

# Mark a pattern as completed
python main.py update sliding_window completed

# Reset a pattern to not started
python main.py update sliding_window not_started

# Run tests for a specific pattern via the CLI
python main.py test sliding_window

# Run all tests via the CLI
python main.py test
```

Progress is persisted in `progress/tracker.json`.

## Project Structure

```
interview-prep/
├── main.py                        # CLI dashboard for progress tracking
├── pyproject.toml                 # Project config and dependencies
├── progress/
│   └── tracker.json               # Persisted progress data
├── src/
│   └── utils/                     # Shared utilities
├── tests/                         # Test files (one per pattern)
├── tier1_foundation/
│   ├── sliding_window/
│   │   ├── __init__.py
│   │   ├── README.md
│   │   ├── template.py
│   │   ├── p003_longest_substring.py
│   │   └── p438_find_anagrams.py
│   ├── two_pointers/
│   ├── fast_slow_pointers/
│   ├── merge_intervals/
│   └── bfs/
├── tier2_intermediate/
│   ├── dfs/
│   ├── two_heaps/
│   ├── top_k_elements/
│   ├── binary_search/
│   └── dynamic_programming/
├── tier3_advanced/
│   ├── backtracking/
│   ├── modified_binary_search/
│   ├── cyclic_sort/
│   ├── subsets/
│   └── trie/
└── tier4_expert/
    ├── union_find/
    ├── monotonic_stack/
    ├── greedy/
    ├── matrix_traversal/
    └── graph/
```

Each pattern directory contains:
- `template.py` -- Reusable template code for the pattern
- `pXXX_problem_name.py` -- Individual problem implementations with examples
- `README.md` -- Pattern explanation, approach, and complexity analysis
