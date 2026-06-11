"""
P04: ReAct Agent Loop Simulation

Simulate a Reason+Act+Observe agent loop. The agent reasons about a task,
selects tools, executes them, and observes results.

Agent terminates when it produces a "FINAL_ANSWER" action.

Input: N (number of agent steps)
  For each step, a line with: THOUGHT|ACTION|OBSERVATION <content>
    - THOUGHT: agent's reasoning (ignored, just logged)
    - ACTION: tool name and arguments
    - OBSERVATION: tool result

Output: For each step, print the step classification.
  If ACTION is "FINAL_ANSWER <answer>", print "[OUT] FINAL <answer>" and stop.
  Otherwise print "[OUT] <type> <content>".

Skills: Agent architecture, ReAct pattern, tool calling, termination semantics
"""

from src.wasm_libs.py.io import read_int, read_line, write_string
import sys


def process_react_loop(steps):
    raise NotImplementedError


def main():
    n = read_int()
    steps = []
    for _ in range(n):
        steps.append(read_line())
    results = process_react_loop(steps)
    for r in results:
        write_string(r)
    sys.exit(0)


if __name__ == "__main__":
    main()
