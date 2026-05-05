# Concurrency

Threads, synchronization primitives, race conditions, deadlocks, lock strategies, and concurrent data structures for SWE interviews.

## Key Concepts

- **Race Condition**: A bug where the output depends on the non-deterministic interleaving of concurrent operations. It occurs when two or more threads access shared data without proper synchronization, and at least one access is a write.
- **Mutex (Mutual Exclusion)**: A lock that ensures only one thread can access a critical section at a time. A thread must acquire the mutex before entering the section and release it afterward. If the mutex is already held, other threads block until it is released.
- **Semaphore**: A signaling mechanism that controls access to a shared resource through a counter. A counting semaphore allows N threads to access a resource simultaneously; a binary semaphore (value 0 or 1) functions similarly to a mutex but can be released by any thread.
- **Deadlock**: A state where two or more threads are each waiting for a lock held by another, creating a circular dependency. Deadlock prevention strategies include lock ordering (always acquire locks in a fixed order), lock timeouts, and using try-lock with backoff.
- **Optimistic vs Pessimistic Locking**: Pessimistic locking assumes conflicts are likely and locks data before reading/writing (e.g., database row locks with SELECT FOR UPDATE). Optimistic locking assumes conflicts are rare, reads without locking, and checks for conflicts at write time using version numbers or timestamps.

## Common Questions with Brief Answer Outlines

**Q: What is the difference between a mutex and a semaphore?**
- A mutex is a locking mechanism that provides mutual exclusion; only the owning thread can release it.
- A semaphore is a signaling mechanism with a counter; any thread can increment or decrement it.
- A mutex has ownership semantics; a semaphore does not.
- Binary semaphores can be used for mutex-like behavior but lack ownership guarantees, risking accidental release.
- Semaphores are better suited for resource pooling (e.g., limiting concurrent database connections).

**Q: How do you prevent deadlocks in concurrent programs?**
- Use a fixed lock ordering: always acquire locks in a consistent, predetermined order to break circular wait.
- Use lock timeouts: if a lock cannot be acquired within a timeout, release held locks and retry.
- Use try-lock patterns: attempt to acquire all locks non-blockingly, releasing and retrying on failure.
- Minimize lock scope: hold locks for the shortest possible duration to reduce contention.
- Use higher-level abstractions: thread pools, message queues, or lock-free data structures can eliminate the need for manual locking.

**Q: Explain optimistic locking with a version column.**
- Read the data along with a version number or timestamp.
- Perform computation on the local copy without holding a lock.
- On write, include a WHERE clause checking that the version has not changed (e.g., UPDATE ... WHERE version = N).
- If the update affects 0 rows, another thread modified the data; retry the read-modify-write cycle.
- This approach performs well when conflicts are rare but can lead to high retry rates under contention.

**Q: What are common concurrent data structures and when would you use them?**
- ConcurrentHashMap (Java) uses lock striping to allow concurrent reads and non-blocking writes across different segments.
- BlockingQueue provides thread-safe FIFO operations with put/take that block when the queue is empty or full.
- AtomicReference and AtomicInteger use CPU-level compare-and-swap (CAS) instructions for lock-free updates.
- ReadWriteLock allows multiple concurrent readers but only one writer, ideal for read-heavy workloads.
- Lock-free queues (e.g., MPMC queues) use CAS operations to avoid locking entirely at the cost of implementation complexity.

**Q: What is the difference between a condition variable and a mutex?**
- A mutex protects shared data; a condition variable allows threads to wait for a specific condition to become true.
- A thread waits on a condition variable by atomically releasing the associated mutex and blocking.
- When another thread signals the condition variable, a waiting thread wakes up and reacquires the mutex.
- Condition variables are used in the producer-consumer pattern: producers signal when items are added, consumers wait when the buffer is empty.
- Spurious wakeups are possible, so always check the condition in a loop after waking up.

**Q: What is the Python GIL and how does it affect multithreading?**
- The Global Interpreter Lock (GIL) is a mutex in CPython that allows only one thread to execute Python bytecode at a time.
- The GIL exists because CPython's memory management (reference counting) is not thread-safe by default.
- This means multithreading in Python cannot achieve true parallelism for CPU-bound tasks; two CPU-heavy threads will alternate rather than run simultaneously.
- Workarounds: use multiprocessing (separate processes, each with its own GIL), use C extensions that release the GIL (NumPy, I/O operations), or use async I/O for I/O-bound concurrency.
- For I/O-bound tasks (network calls, file reads), the GIL is released during I/O waits, so multithreading still provides concurrency benefits.

**Q: What is the difference between synchronous, asynchronous, and non-blocking I/O?**
- Synchronous (blocking) I/O: the calling thread waits until the operation completes before continuing. Simple to reason about but wastes CPU cycles while waiting.
- Asynchronous I/O: the operation is initiated and the thread continues executing; a callback, future, or event loop notifies the thread when the operation completes. Enables high concurrency with a single thread (e.g., Node.js, Python asyncio).
- Non-blocking I/O: the call returns immediately with whatever data is available (or an error indicating "would block"). The caller must poll or use an event notification mechanism (epoll, kqueue, select) to know when data is ready.
- async/await syntax (Python, JavaScript, C#) provides a synchronous-looking way to write asynchronous code; under the hood, the runtime uses an event loop and non-blocking I/O.

**Q: What is immutability and why is it important in concurrent programming?**
- An immutable object is one whose state cannot be modified after creation. All fields are final, and any mutable sub-objects are defensively copied.
- Immutable objects are inherently thread-safe because no thread can modify them, eliminating the need for locks or synchronization when sharing data between threads.
- Examples: strings in Java/Python, tuples in Python, frozen dataclasses, and records in Java.
- Trade-offs: immutability can increase memory usage due to copying on "modification" (creating new objects), and may produce more garbage for the collector. However, it simplifies reasoning about concurrent code and eliminates entire classes of bugs (race conditions on shared mutable state).

## Quick Reference Table

| Mechanism | Scope | Ownership | Blocking | Use Case |
|---|---|---|---|---|
| Mutex | Single resource | Owning thread only | Yes | Critical section protection |
| Semaphore (binary) | Single resource | No ownership | Yes | Signaling between threads |
| Semaphore (counting) | N resources | No ownership | Yes | Resource pooling |
| ReadWriteLock | Single resource | Reader or writer | Yes | Read-heavy workloads |
| Spinlock | Single resource | Owning thread only | Busy-wait | Short critical sections on multiprocessor |
| CAS / Atomic | Single variable | No lock needed | Non-blocking | Lock-free counters, references |
