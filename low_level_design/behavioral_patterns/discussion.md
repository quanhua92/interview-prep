# Behavioral Patterns: Observer, Command, Strategy, Template Method & Chain of Responsibility

Source: [Behavioral Patterns (CalibreOS)](https://www.calibreos.com/learn/lld-behavioral-patterns)

## One-Liner
Behavioral design patterns define how objects communicate and delegate work through five core patterns: Observer (event notification), Command (encapsulate requests), Strategy (interchangeable algorithms), Template Method (algorithm skeleton with extension points), and Chain of Responsibility (pipeline processing).

## Behavioral Patterns: How Objects Communicate
Behavioral patterns address how objects interact and distribute responsibilities. While structural patterns focus on what objects are made of, behavioral patterns focus on how they talk to each other. The recurring challenge they solve is: **how do you decouple the sender of a request from the receiver, so either side can change without affecting the other?**

The key insight shared across behavioral patterns is **delegation**: the caller doesn't know the specific handler, just an interface. This enables runtime flexibility (swap strategies, add observers, change the processing chain) without modifying the caller's code.

## What Earns Each Level

**6/10:** Names patterns. Provides textbook definitions. Implements a working but rigid example.

**8/10:** Selects the right pattern based on the problem description. Implements cleanly with correct abstraction level. Explains what the pattern decouples. Knows when NOT to use the pattern.

**10/10:** Chains patterns together (Command + Observer for a UI event system). Connects to real frameworks: Observer = Spring ApplicationEvent / RxJava Observable / GUI listeners; Strategy = Java Comparator; Template Method = Spring's JdbcTemplate; Chain of Responsibility = HTTP middleware, Java servlet filters. Identifies when adding a behavioral pattern increases complexity more than it reduces coupling.

## The Five Core Behavioral Patterns

### 01 — Observer: Notify multiple dependents of state changes
- When one object changes state, all dependent objects are notified automatically.
- Subject maintains a list of Observers and calls update() on each when it changes.
- Observer registers/unregisters with the Subject.
- Decouples Subject from its dependents; Subject doesn't know how many or what type of Observers exist.
- Signal: "When X changes, multiple independent components should react." Examples: event system, stock ticker, UI data binding, notification service.
- Java: EventListener, RxJava Observable, Spring ApplicationEvent.

### 02 — Command: Encapsulate a request as an object
- Package a request (method call + parameters) into an object with an execute() method.
- Benefits: decouple sender from receiver, queue/log/retry commands, support undo (store a reverse command).
- Signal: "We need to queue operations, support undo, or log all actions." Examples: undo/redo in a text editor, task queue, remote procedure, macro recording.
- The Command object knows the receiver; the invoker knows only the Command interface.

### 03 — Strategy: Make algorithms interchangeable
- Define a family of algorithms, encapsulate each, and make them interchangeable.
- Client selects the strategy at runtime or construction time.
- Eliminates large conditional logic (switch on sort type -> inject the right sorter).
- Signal: "There are multiple ways to do X, and we want to switch between them." Examples: sorting algorithms, payment methods, routing algorithms, pricing strategies, compression methods.
- Java: Comparator is the canonical Strategy example.

### 04 — Template Method: Define the algorithm skeleton, let subclasses fill in steps
- Abstract class defines the steps of an algorithm.
- Some steps have default implementations; others are abstract (left to subclasses).
- The overall structure (the template method) is fixed; specific steps vary.
- Provides the "Hollywood Principle": don't call us, we'll call you — the base class calls the subclass's overridden steps.
- Signal: "All variants of this process share the same overall steps, but differ in specific sub-steps." Examples: data parsers (read -> parse -> validate -> save), Spring's JdbcTemplate, test setUp/tearDown.

### 05 — Chain of Responsibility: Pass request through a chain of handlers
- Each handler decides whether to process the request or pass it to the next handler in the chain.
- Decouples sender from concrete handler; handlers can be reordered, added, or removed at runtime.
- Signal: "Multiple objects may handle a request; we want to avoid hard-coding which one." Examples: HTTP middleware (auth -> rate-limit -> log -> handle), exception handling (try-catch chain), customer support escalation (L1 -> L2 -> L3).
- Each handler has a reference to the next handler.

## Core Components

### Observer Template — Event Bus
```java
interface Observer { void update(Event event); }

class EventBus {
    private final Map<String, List<Observer>> listeners = new HashMap<>();

    public void subscribe(String event, Observer observer) {
        listeners.computeIfAbsent(event, k -> new ArrayList<>()).add(observer);
    }

    public void publish(String event, Event data) {
        listeners.getOrDefault(event, List.of()).forEach(o -> o.update(data));
    }
}
// Usage: eventBus.publish("ORDER_PLACED", orderEvent);
```

### Strategy Template — Payment Processing
```java
interface PaymentStrategy { void pay(double amount); }

class CreditCardPayment implements PaymentStrategy {
    public void pay(double amount) { /* charge credit card */ }
}
class CryptoPayment implements PaymentStrategy {
    public void pay(double amount) { /* broadcast transaction */ }
}

class Checkout {
    private PaymentStrategy strategy;
    public void setStrategy(PaymentStrategy s) { this.strategy = s; }
    public void checkout(double total) { strategy.pay(total); }
}
```

### Command Template — Undoable Operations
```java
interface Command { void execute(); void undo(); }

class InsertTextCommand implements Command {
    private final Document doc;
    private final String text;
    private final int position;

    public void execute() { doc.insert(position, text); }
    public void undo()    { doc.delete(position, text.length()); }
}

class CommandHistory {
    private final Deque<Command> history = new ArrayDeque<>();
    public void execute(Command cmd) { cmd.execute(); history.push(cmd); }
    public void undo() { if (!history.isEmpty()) history.pop().undo(); }
}
```

### Chain Template — HTTP Middleware
```java
abstract class Middleware {
    private Middleware next;
    public Middleware setNext(Middleware next) { this.next = next; return next; }
    public abstract boolean handle(HttpRequest req, HttpResponse resp);

    protected boolean passToNext(HttpRequest req, HttpResponse resp) {
        if (next == null) return true;
        return next.handle(req, resp);
    }
}

class AuthMiddleware extends Middleware {
    public boolean handle(HttpRequest req, HttpResponse resp) {
        if (!req.hasValidToken()) { resp.setStatus(401); return false; }
        return passToNext(req, resp);
    }
}

class RateLimitMiddleware extends Middleware {
    public boolean handle(HttpRequest req, HttpResponse resp) {
        if (isRateLimited(req.getIp())) { resp.setStatus(429); return false; }
        return passToNext(req, resp);
    }
}
```

### Template Method Template — Data Parser
```java
abstract class DataParser {
    public final void parse(String source) {
        String raw = read(source);
        Object data = parse(raw);
        validate(data);
        save(data);
    }

    protected abstract String read(String source);
    protected abstract Object parse(String raw);
    protected void validate(Object data) {}
    private void save(Object data) { db.save(data); }
}

class JsonParser extends DataParser {
    protected String read(String source) { return Files.readString(Path.of(source)); }
    protected Object parse(String raw) { return JSON.parse(raw); }
}
```

## Key Design Decisions

### Pattern Selection Guide

| Problem signal | Pattern | What it decouples |
|---|---|---|
| "Multiple components need to react when X changes" | Observer | Subject from its dependents |
| "Need to queue, undo, or log operations" | Command | Sender from receiver; request from execution |
| "Multiple algorithms for the same task; want to switch at runtime" | Strategy | Algorithm from the context that uses it |
| "Same overall process, different specific steps" | Template Method | Algorithm skeleton from step implementations |
| "Multiple handlers may process a request; want to add/remove handlers" | Chain of Responsibility | Sender from concrete handler; handlers from each other |
| "Need to notify exactly one subscriber (not all)" | Observer variant or direct callback | Observer notifies ALL subscribers; for one-to-one, use a callback/handler directly |

### Strategy vs Template Method
- **Strategy** uses composition (inject the algorithm). Prefer for runtime flexibility.
- **Template Method** uses inheritance (override the step). Use when the skeleton is fixed and variations are in specific named steps.
- Rule: "Template Method when the skeleton is stable; Strategy when the algorithm as a whole may swap."

### Command with Undo Stack + Strategy Runtime Swap
```java
// Command: encapsulate operations as objects, enables undo/redo
interface Command { void execute(); void undo(); }

class InsertTextCommand implements Command {
    private final Document doc;
    private final String text;
    private final int position;
    InsertTextCommand(Document doc, String text, int position) {
        this.doc = doc; this.text = text; this.position = position;
    }
    public void execute() { doc.insert(position, text); }
    public void undo()    { doc.delete(position, text.length()); }
}

class CommandHistory {
    private final Deque<Command> history = new ArrayDeque<>();
    public void execute(Command cmd) { cmd.execute(); history.push(cmd); }
    public void undo() { if (!history.isEmpty()) history.pop().undo(); }
}

// Strategy: swap algorithm at runtime without if-else chains
interface SortStrategy { void sort(List<Integer> data); }

class QuickSort implements SortStrategy {
    public void sort(List<Integer> data) { /* O(n log n) avg */ }
}
class TimSort implements SortStrategy {
    public void sort(List<Integer> data) { /* stable, O(n log n) worst */ }
}

class DataProcessor {
    private SortStrategy strategy = new TimSort();  // default
    public void setStrategy(SortStrategy s) { this.strategy = s; }
    public void process(List<Integer> data) {
        strategy.sort(data);  // no instanceof, no switch, open/closed
    }
}
```

### Command with Undo and Idempotent Replay Guard
```typescript
interface Command {
  id: string;
  execute(): void;
  undo(): void;
}

class TextBuffer {
  constructor(public value: string = "") {}
}

class InsertText implements Command {
  constructor(
    public readonly id: string,
    private readonly buffer: TextBuffer,
    private readonly index: number,
    private readonly text: string
  ) {}

  execute(): void {
    this.buffer.value =
      this.buffer.value.slice(0, this.index) +
      this.text +
      this.buffer.value.slice(this.index);
  }

  undo(): void {
    this.buffer.value =
      this.buffer.value.slice(0, this.index) +
      this.buffer.value.slice(this.index + this.text.length);
  }
}

class CommandHistory {
  private readonly applied = new Set<string>();
  private readonly undoStack: Command[] = [];

  apply(command: Command): void {
    if (this.applied.has(command.id)) return;
    command.execute();
    this.applied.add(command.id);
    this.undoStack.push(command);
  }

  undoLast(): void {
    const command = this.undoStack.pop();
    if (command) command.undo();
  }
}
```

## Common Pitfalls

**Observer — memory leaks.** If an Observer registers with a Subject but forgets to unsubscribe, the Subject holds a reference to the Observer forever, preventing garbage collection. In Java: use WeakReference for Observer storage, or ensure unsubscribe() is called in cleanup/destructor. This is a classic Android memory leak.

**Observer — notification order.** Don't assume Observers are notified in registration order. If order matters, it's not Observer — use a sorted list or explicit sequencing.

**Strategy — state in strategy.** If a Strategy object holds mutable state, it can't be safely shared across contexts. Either make strategies stateless (can be singletons/shared), or create a new instance per context.

**Template Method — inflexible hierarchy.** Template Method uses inheritance. If the algorithm skeleton needs to change, the base class changes, affecting all subclasses. Prefer Strategy (composition) when the skeleton itself may vary. Rule: "Template Method when the skeleton is stable; Strategy when the algorithm as a whole may swap."

**Command — CQRS confusion.** In CQRS (Command Query Responsibility Segregation), "Command" means a write operation. The Command design pattern means encapsulating a request. These are different uses of the word. Don't confuse them in an interview.

## Behavioral Patterns Make Control Flow Explicit
Behavioral patterns are about who decides what happens next. Strategy moves algorithm choice out of the caller. Command turns an action into data that can be queued, retried, logged, or undone. Observer moves reaction logic out of the subject. Chain of Responsibility moves request routing into a pipeline. Template Method keeps the algorithm skeleton in a base class while allowing specific steps to vary.

The main tradeoff is **visibility**. A direct method call is easy to trace. Observer and Chain introduce indirect control flow: a publish call may trigger five handlers; a request may be rejected by middleware before reaching the controller. That is good when the sender should not know the receivers, but dangerous when ordering, error handling, or transaction boundaries matter.

In interviews, tie the pattern to a failure mode. Observer without failure isolation can let one broken listener prevent analytics, email, and inventory updates. Command without idempotency can replay side effects twice. Chain without a clear terminal handler can silently drop requests. Strategy with mutable shared state can leak data between users. The pattern is not complete until those operational rules are stated.

## When NOT to Use Behavioral Patterns
Do not use Observer when delivery must be durable, ordered, or retried after process crash; use an outbox and queue. Do not use Command for simple synchronous calls that will never be queued, logged, retried, or undone. Do not use Chain of Responsibility when exactly one known handler always owns the request. Do not use Template Method if teams need to swap the entire algorithm at runtime; Strategy is cleaner. Do not use Strategy when the only variation is one `if` that is stable and local.

## State and Event Boundaries in Behavioral Designs
Behavioral patterns often sit on a state boundary. In an order system, `OrderService.placeOrder()` may publish an `OrderPlaced` event, but inventory reservation and payment capture are separate reactions with their own failure modes. If those reactions must commit atomically with order creation, Observer is the wrong shape; use a transaction plus explicit collaborators. If eventual consistency is acceptable, use Observer or an outbox.

State pattern is the opposite side of the same idea. The object delegates behavior to its current state object, and transitions are explicit: `PendingOrder.pay()` moves to `PaidOrder`; `ShippedOrder.cancel()` rejects. Use it when operations behave differently by state, not just because a status enum exists. If every state has the same methods and only valid transitions differ, a transition table is simpler and easier to audit.

The senior distinction is whether you need **polymorphic behavior** or **validated transitions**. Polymorphic behavior points to State. Validated transitions point to a table or state machine service. Mixing the two without naming the boundary produces code where rules are scattered across listeners, commands, and state objects.

## Interview Delivery Summary

- **Observer** pattern signal: "When X changes, multiple things happen." Chain of Responsibility signal: "A request passes through a pipeline of handlers, each can handle or pass it on."
- **Command** is the gateway to undo/redo, command queuing, and audit logging. Always mention all three benefits when you propose Command — interviewers want to know you're not just implementing execute(), but thinking about undo(), logging, and queue.
- Real-world links earn points: Observer = Java's EventListener / RxJava / React's useEffect dependency tracking. Strategy = Java's Comparator. Chain of Responsibility = Express.js middleware / Servlet filters.

## Follow-Up Variations
- Design an event notification system for an e-commerce platform where placing an order triggers email confirmation, inventory deduction, and fraud analysis.
- Design a payment system that supports multiple payment methods (Credit Card, PayPal, Crypto) and makes it easy to add new ones.
- Design an HTTP middleware pipeline with authentication, rate limiting, and logging. Handlers should be composable and reorderable.
- How would you handle Observer notification failure for one listener without blocking others?
- How would you implement a macro recording system using Command pattern?
