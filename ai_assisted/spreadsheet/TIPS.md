# Tips: Spreadsheet Application

## Key Concepts to Know

- **Dependency graph (DAG)** — Cells form a directed acyclic graph. An edge from A1→B1 means "B1 depends on A1."
- **Topological sort** — Determines the correct evaluation order so that dependencies are resolved before dependents.
- **Cycle detection** — DFS with a "visited" and "recursion stack" set detects cycles in O(V+E).
- **Expression parsing** — Use a recursive descent parser or the Shunting Yard algorithm to handle operator precedence.

## Common Mistakes

| Mistake | Why It's Wrong |
|---------|---------------|
| Evaluating cells in insertion order | Dependencies may not be resolved yet |
| Not parsing formulas — just using `eval()` | Security risk, no operator precedence control, no reference tracking |
| Rebuilding the entire dependency graph on every change | O(n) per update when only a subgraph needs recalculation |
| Ignoring empty cell references | `get_cell("Z99")` on an unset cell should return 0, not crash |
| Storing computed values without marking them dirty | Stale values after upstream changes |

## How to Prompt the AI Effectively

1. **Data model first:** "Design a Cell class that stores a raw formula string, a parsed AST, and a cached computed value."
2. **Parser separately:** "Implement a recursive descent parser for arithmetic expressions with cell references like A1, B2."
3. **Graph separately:** "Build a dependency graph class that tracks which cells depend on which, with topological sort and cycle detection."
4. **Verify the parser:** Ask the AI for test cases. Check that `=A1+B2*3` parses as `A1 + (B2*3)`, not `(A1+B2)*3`.

## Architecture Patterns

```
set_cell("B1", "=A1*2+C3")
       │
       ▼
  ┌──────────┐
  │  Parser   │  → AST: Add(Mul(Ref(A1), Lit(2)), Ref(C3))
  └──────────┘
       │
       ▼
  ┌──────────────┐
  │ Dependency    │  → B1 depends on [A1, C3]
  │ Graph (DAG)   │
  └──────────────┘
       │
       ▼
  ┌──────────────┐
  │ Evaluator     │  → Topological order: resolve A1, C3, then B1
  │ (recalc)      │
  └──────────────┘
```

## What Interviewers Look For

- Understanding of DAGs and topological ordering for dependency resolution.
- Ability to implement a basic expression parser (not just `eval()`).
- Cycle detection as a first-class concern, not an afterthought.
- Extensibility design — can new formula functions be added cleanly?
- Practical reasoning about performance at scale (dirty-bit tracking, partial recalculation).
