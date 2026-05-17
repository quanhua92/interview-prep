# Behavioral Patterns — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Does the problem involve notifying multiple listeners when state changes (Observer)?
  - [ ] Do we need to queue, undo, log, or replay operations (Command)?
  - [ ] Are there multiple algorithms for the same task that should be swappable at runtime (Strategy)?
  - [ ] Is there a fixed algorithm skeleton where specific steps vary (Template Method)?
  - [ ] Does a request need to pass through a pipeline of handlers (Chain of Responsibility)?
- [ ] Identify which behavioral pattern(s) apply:
  - [ ] "When X changes, multiple independent components should react" -> Observer
  - [ ] "Need to queue operations, support undo, or log all actions" -> Command
  - [ ] "Multiple ways to do X, want to switch between them at runtime" -> Strategy
  - [ ] "Same overall process, different specific steps" -> Template Method
  - [ ] "Multiple handlers may process a request; want to add/remove handlers" -> Chain of Responsibility
- [ ] List non-functional concerns:
  - [ ] Does delivery need to be durable, ordered, or retried? (If yes, Observer alone is wrong — consider outbox + queue)
  - [ ] Do reactions need to be atomic with the triggering operation? (If yes, Observer is wrong — use transaction + collaborators)
  - [ ] Is the algorithm skeleton stable, or could it change at runtime? (Stable -> Template Method; variable -> Strategy)
- [ ] State your abstraction boundaries:
  - [ ] What does the pattern decouple? (Subject from dependents / sender from receiver / algorithm from context)
  - [ ] What are the failure modes if the pattern is misapplied?

## Phase 2: High-Level Design (3-5 min)
- [ ] Identify the key interfaces and their roles:
  - [ ] Observer: `Observer` (update), `Subject` (subscribe, unsubscribe, notify)
  - [ ] Command: `Command` (execute, undo), `Invoker` (trigger), `Receiver` (actual work)
  - [ ] Strategy: `Strategy` (algorithm interface), `Context` (delegates to strategy)
  - [ ] Template Method: `AbstractClass` (template method + hook methods), `ConcreteClass` (overrides hooks)
  - [ ] Chain of Responsibility: `Handler` (handle, setNext), concrete handlers in a linked chain
- [ ] Draw a simple diagram showing the interaction flow:
  - [ ] Observer: Subject -> notify -> [Observer A, Observer B, Observer C]
  - [ ] Command: Client -> Invoker -> Command -> Receiver
  - [ ] Strategy: Context -> Strategy (concrete impl)
  - [ ] Chain: Client -> Handler1 -> Handler2 -> Handler3
  - [ ] Template Method: Client calls templateMethod() which calls step1(), step2(), step3()
- [ ] Note the read:write ratio and where the pattern helps:
  - [ ] Observer: one event -> multiple reactions (fan-out)
  - [ ] Command: queue/stack for write operations (undo stack, task queue)
  - [ ] Strategy: eliminate switch/if-else chains for algorithm selection
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Implement the core interface(s) with correct abstraction:
  - [ ] Observer: `interface Observer { void update(Event event); }` + Subject with subscribe/unsubscribe/publish
  - [ ] Command: `interface Command { void execute(); void undo(); }` + CommandHistory with undo stack
  - [ ] Strategy: `interface Strategy { void doWork(Data data); }` + Context with setStrategy()
  - [ ] Chain: `abstract class Handler { private Handler next; setNext(); abstract handle(); }` with passToNext()
  - [ ] Template Method: `abstract class Abstract { public final void templateMethod() { step1(); step2(); step3(); } }` with abstract hooks
- [ ] Walk through the main flow end-to-end:
  - [ ] Observer: event published -> all subscribers notified -> each handles independently
  - [ ] Command: user action -> Command created -> Invoker executes -> pushes to history -> undo pops and calls undo()
  - [ ] Strategy: client sets strategy -> Context delegates work -> strategy executes algorithm
  - [ ] Chain: request enters chain -> handler1 processes/passes -> handler2 processes/passes -> terminal handler
  - [ ] Template Method: client calls templateMethod() -> fixed steps execute -> subclass hooks called
- [ ] Discuss composition vs inheritance trade-offs:
  - [ ] Strategy (composition) vs Template Method (inheritance) — prefer composition for runtime flexibility
  - [ ] "Template Method when the skeleton is stable; Strategy when the algorithm as a whole may swap"
- [ ] Address error handling and failure modes:
  - [ ] Observer: one failing listener should not block others (try-catch per listener, or async dispatch)
  - [ ] Command: idempotency guard for replay (Set of applied command IDs)
  - [ ] Chain: terminal handler must handle unmatched requests, or return a clear error
  - [ ] Strategy: stateless strategies can be shared; stateful ones need per-context instances

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss memory management:
  - [ ] Observer: memory leaks from forgotten subscriptions -> use WeakReference or ensure unsubscribe in cleanup
  - [ ] Command: undo stack growth -> cap stack size, or persist to disk for long sessions
- [ ] Explain scaling considerations:
  - [ ] Observer: async dispatch via event bus or message queue for high-volume events
  - [ ] Command: command queue for distributed task processing, retry from queue on failure
  - [ ] Chain: handler ordering matters for correctness (auth before rate-limit before business logic)
- [ ] Connect to real-world frameworks:
  - [ ] Observer: Java EventListener, RxJava Observable, Spring ApplicationEvent, React useEffect
  - [ ] Strategy: Java Comparator, Spring's injected dependencies
  - [ ] Command: undo/redo in editors, CQRS command objects, macro recording
  - [ ] Template Method: Spring JdbcTemplate, test setUp/tearDown, Android Activity lifecycle
  - [ ] Chain: Express.js middleware, Java Servlet filters, Spring Security filter chain
- [ ] Address when NOT to use the pattern:
  - [ ] Observer: when delivery must be durable/ordered -> use outbox + queue instead
  - [ ] Command: for simple synchronous calls that will never be queued/undone -> direct call is simpler
  - [ ] Chain: when exactly one handler always owns the request -> direct dispatch
  - [ ] Template Method: when the algorithm skeleton itself may vary -> use Strategy
  - [ ] Strategy: when the only variation is one stable local `if` -> YAGNI
- [ ] Discuss pattern combinations:
  - [ ] Command + Observer: UI event system (Command for actions, Observer for event propagation)
  - [ ] Strategy + Factory: Factory creates the right Strategy based on config
  - [ ] Chain + Strategy: each handler in the chain can use Strategy to choose processing approach
  - [ ] Observer + Command: event-sourced systems (Commands generate Events, Observers react)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why (visibility vs decoupling, complexity vs flexibility)
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
