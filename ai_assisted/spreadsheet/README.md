# Problem 02: Spreadsheet Application (Dependency Logic)

**Role:** Full-Stack Engineer
**Duration:** 45-60 minutes
**Difficulty:** Hard
**Format:** Feature Build-Out

---

## Background

We're building a lightweight spreadsheet engine (think a simplified Google Sheets). Cells can contain literal values or formulas that reference other cells. When a cell changes, all dependent cells must update automatically.

You're responsible for the core evaluation engine. Don't worry about the UI — focus on the data model and computation graph.

## Functional Requirements

1. A cell can hold a **numeric value** or a **formula** (e.g., `=A1+B2*3`).
2. Formulas support basic arithmetic: `+`, `-`, `*`, `/`.
3. Cell references use the format `COLUMN_ROW` (e.g., `A1`, `B3`, `Z99`).
4. When a cell value changes, all cells that depend on it must **recalculate automatically**.
5. Support a `get_cell(ref)` and `set_cell(ref, value_or_formula)` API.

## Non-Functional Requirements

- Formula evaluation should handle operator precedence correctly (`*` and `/` before `+` and `-`).
- Circular references must be detected and reported as an error.
- The system should gracefully handle references to empty cells (treat as 0).

## Constraints

- Grid size: 26 columns (A-Z) x 100 rows (1-100) = 2,600 cells.
- No external libraries for formula parsing — implement your own parser.
- Single-threaded execution for the initial implementation.

## Starter Interface

```python
class Spreadsheet:
    def set_cell(self, ref: str, raw_value: str) -> None:
        """Set a cell's value or formula (e.g., '=A1+B2*3' or '42')."""
        ...

    def get_cell(self, ref: str) -> float:
        """Return the computed value of a cell."""
        ...

    def get_raw(self, ref: str) -> str:
        """Return the raw input string (formula or literal)."""
        ...
```

---

## Follow-Up Questions

### Follow-Up 1: Circular Dependency Detection
> "What happens if a user sets A1 to `=B1` and B1 to `=A1`? How do you detect and prevent circular references?"

- Explain your approach (DFS cycle detection, topological sort, or timestamp tracking).
- Should the system reject the input immediately or mark cells as `#CIRC!`?
- What if the cycle is indirect (A→B→C→A)?

### Follow-Up 2: Formula Extensions
> "Now add support for built-in functions: SUM(A1:A5), AVG(B1:B10), MAX(C1:C3)."

- Design an extensible function registry so new functions can be added without modifying the parser.
- How do range references (A1:A5) expand into individual cell references?
- What's the impact on your dependency graph?

### Follow-Up 3: Multi-User Concurrency
> "Multiple users edit the same sheet simultaneously. How do you handle conflicts?"

- Discuss optimistic vs. pessimistic locking at the cell level.
- How would you implement Operational Transformation (OT) or CRDT for cell values?
- What's the recalculation strategy when concurrent edits create temporary inconsistencies?

### Follow-Up 4: Large-Scale Recalculation
> "A financial model has 10,000 formulas that all indirectly depend on cell A1. When A1 changes, recalculating everything is slow. How do you optimize?"

- Topological ordering of the dependency graph.
- Can you skip recalculation for cells whose inputs haven't actually changed? (Dirty-bit tracking)
- Parallel evaluation of independent subgraphs.
