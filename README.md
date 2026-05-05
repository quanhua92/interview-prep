# Interview Prep

A comprehensive interview preparation toolkit covering coding patterns, system design, and behavioral interviews. Track progress across all 40 topics with a unified CLI dashboard.

## Quick Start

```bash
# Install dependencies (requires Python >= 3.13)
uv venv && uv pip install -e ".[dev]"

# Run the progress dashboard
python main.py status

# Run all coding tests
pytest

# Run tests for a specific pattern
pytest tests/test_sliding_window.py -v

# Run a single problem file directly
python tier1_foundation/sliding_window/problems/p003_longest_substring.py
```

## Coding Patterns (20 patterns, 4 tiers)

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

Each pattern contains:
- `template.py` — Annotated skeleton with variants
- `problems/` — Practice stubs with test cases (implement `solve()`)
- `solutions/` — Answer keys
- `README.md` — Pattern explanation, when to recognize it, complexity table

## System Design (10 topics)

| Topic | Core Concepts |
|-------|--------------|
| [URL Shortener](system_design/url_shortener/) | ID generation, caching, base62, sharding |
| [Chat System](system_design/chat_system/) | WebSockets, message queues, presence |
| [Rate Limiter](system_design/rate_limiter/) | Token bucket, sliding window, Redis |
| [News Feed](system_design/news_feed/) | Fan-out on write/read, graph, ranking |
| [Notification Service](system_design/notification_service/) | Push/pull, reliability, dedup, priority |
| [Search Autocomplete](system_design/search_autocomplete/) | Trie, ranking, prefix search at scale |
| [Distributed Cache](system_design/distributed_cache/) | Consistent hashing, replication, eviction |
| [Key-Value Store](system_design/key_value_store/) | SSTables, LSM trees, Bloom filters |
| [Web Crawler](system_design/web_crawler/) | URL frontier, politeness, dedup, BFS |
| [Ticket Booking](system_design/ticket_booking/) | Concurrency, locks, idempotency, oversell |

Each topic contains:
- `discussion.md` — Concise reference (key concepts, trade-offs, vocabulary)
- `checklist.md` — Step-by-step working checklist with 5 phases + practice notes

## Behavioral (10 themes, STAR method)

| Theme | Competency |
|-------|-----------|
| [Teamwork Conflict](behavioral/teamwork_conflict/) | Collaboration, empathy |
| [Handling Failure](behavioral/handling_failure/) | Self-awareness, resilience |
| [Leadership Without Authority](behavioral/leadership_initiative/) | Influence, ownership |
| [Difficult Decision](behavioral/difficult_decision/) | Judgment, trade-off analysis |
| [Adapting to Change](behavioral/adapting_to_change/) | Flexibility, prioritization |
| [Working Under Pressure](behavioral/meeting_deadline_pressure/) | Time management, composure |
| [Receiving Feedback](behavioral/receiving_feedback/) | Humility, growth |
| [Mentoring a Teammate](behavioral/mentoring_other/) | Teaching, patience |
| [Owning a Mistake](behavioral/owning_mistake/) | Accountability, transparency |
| [Competing Priorities](behavioral/competing_priorities/) | Prioritization, stakeholder management |

Each theme contains:
- `discussion.md` — STAR framework guidance, what interviewers look for, story mining prompts
- `checklist.md` — Story workshop with drafting checkboxes, refinement checks, practice log

## CLI Dashboard

Track progress across all 40 topics (coding + system design + behavioral):

```bash
# View progress for all topics
python main.py status

# Mark any topic as in progress / completed / not started
python main.py update sliding_window in_progress
python main.py update url_shortener completed
python main.py update handling_failure in_progress

# Run coding tests (all or specific pattern)
python main.py test
python main.py test sliding_window
```

Progress is persisted in `progress/tracker.json`.

## Project Structure

```
interview-prep/
├── main.py                        # CLI dashboard
├── system_design/                 # 10 system design topics
│   └── <topic>/
│       ├── discussion.md
│       └── checklist.md
├── behavioral/                    # 10 behavioral themes
│   └── <theme>/
│       ├── discussion.md
│       └── checklist.md
├── tier{1-4}_*/                   # 20 coding patterns
│   └── <pattern>/
│       ├── template.py
│       ├── problems/              # Practice stubs
│       ├── solutions/             # Answer keys
│       └── README.md
├── tests/                         # pytest suite (108 tests)
├── src/utils/                     # Shared utilities
└── progress/tracker.json          # Progress data (gitignored)
```
