# AI-Assisted Interview Preparation

Modern technical interviews at companies like Meta, LinkedIn, and Google have shifted from abstract algorithmic puzzles toward **project-based assessments** where you collaborate with an AI assistant to build, debug, or extend production-like systems.

This directory contains realistic interview scenarios to practice that format.

## Interview Formats You'll Encounter

| Format | Description |
|--------|-------------|
| **Feature Build-Out** | Extend a partially completed project using AI while matching existing codebase style and architecture. |
| **Debugging Large Codebases** | Given an extensive codebase with failing tests, use AI to map system structure and resolve bugs. |
| **System Design Prototyping** | Move from high-level design to a working proof-of-concept skeleton (e.g., an API layer). |
| **AI Code Review** | Critique AI-generated code for subtle performance regressions, security risks, or design flaws. |

## Evaluation Rubric ("Vibe Coding" Criteria)

Interviewers assess your **engineering rigor** through how you manage the AI, not just whether the code works.

1. **Decomposition** — Can you break a complex system into atomic prompts the AI can handle without context loss?
2. **Verification** — Can you spot hallucinations, off-by-one errors, or O(n^2) logic hiding in AI output?
3. **Prompt Refinement** — When the AI fails, can you steer it back with specific constraints instead of repeating the same prompt?
4. **Justification** — Can you explain the trade-offs of the AI's suggestions (why a certain database, algorithm, or pattern was chosen)?

## Prompting Strategy (Chain-of-Thought)

Prevent the AI from generating unmanageable blocks of code by following this tiered approach:

1. **Define interfaces and data models** first.
2. **Ask for a skeleton** of the service logic.
3. **Implement core functionality** module-by-module.
4. **Prompt for edge cases and unit tests** explicitly.

## Scenario Library

| # | Scenario | Difficulty | Key Skills |
|---|----------|-----------|------------|
| [URL Shortener](url_shortener/README.md) | Medium | Encoding, caching, database trade-offs |
| [Spreadsheet Application](spreadsheet/README.md) | Hard | Dependency graphs, cycle detection, concurrency |
| [Distributed Rate Limiter](rate_limiter/README.md) | Hard | Throttling algorithms, distributed state, resilience |
| [Maze Solver / Pathfinder](maze_solver/README.md) | Medium | Graph traversal, pathfinding, memory optimization |
| [Card Game Logic](card_game/README.md) | Medium | Game rules, extensibility, input validation |
| [Notification Service](notification_service/README.md) | Hard | Async processing, idempotency, priority queuing |

## How to Use This Guide

1. **Read the problem README** as if the interviewer just handed it to you.
2. **Set a timer** (45-60 minutes) to simulate real interview pressure.
3. **Use an AI assistant** (Claude, ChatGPT, Copilot) to help you build the solution.
4. **Practice steering the AI** — don't just accept its output; verify, refine, and justify.
5. **Progress through follow-ups** sequentially, as you would in a real interview.
6. **Review TIPS.md** after your attempt to identify gaps in your approach.
