# Python Async/Await & asyncio

Sources:
- [Python 3.13 asyncio Documentation — Coroutines and Tasks](https://docs.python.org/3/library/asyncio-task.html)
- [Python 3.13 asyncio Documentation — Event Loop](https://docs.python.org/3/library/asyncio-eventloop.html)
- [Python's asyncio: A Hands-On Walkthrough (Real Python)](https://realpython.com/async-io-python/)
- [PEP 492 — Coroutines with async and await syntax](https://peps.python.org/pep-0492/)
- [uvloop — Fast asyncio event loop](https://github.com/MagicStack/uvloop)
- [FastAPI Documentation — Async](https://fastapi.tiangolo.com/async/)
- [httpx — Async HTTP Client](https://www.python-httpx.org/async/)
- [aiohttp — Async HTTP Client/Server](https://docs.aiohttp.org/en/stable/)

## One-Liner

Python's asyncio provides single-threaded cooperative multitasking via coroutines and an event loop — the primary concurrency model for I/O-bound AI workloads including concurrent LLM API calls, streaming responses, and high-throughput web services.

## Core Competencies Table

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Event Loop Fundamentals | How the asyncio event loop schedules and runs coroutines, loop lifecycle, event loop policies, uvloop | Explain the event loop's internal scheduling mechanism; describe when and why to replace it with uvloop |
| Coroutines & async/await | Coroutine functions vs coroutine objects, await semantics, calling vs awaiting, async generators | Write correct async code; explain why `coro()` doesn't execute and why `await` is required |
| Task Management | `create_task`, `TaskGroup`, `gather`, `wait`, `as_completed`, ensuring task completion | Use TaskGroup for structured concurrency; handle partial failures in gather with return_exceptions |
| Concurrency Patterns for LLMs | Concurrent LLM API calls, aiohttp/httpx, connection pooling, streaming SSE responses | Implement concurrent LLM calls with proper error handling, rate limiting, and connection pooling |
| async for & Async Iterators | Async generators, async comprehensions, streaming LLM token-by-token | Write async generators for streaming data; consume streaming LLM responses |
| Synchronization Primitives | `asyncio.Lock`, `Semaphore`, `BoundedSemaphore`, `Event`, `Queue` | Apply semaphores for rate limiting; use Queue for producer-consumer async patterns |
| Timeout & Cancellation | `asyncio.timeout()`, `wait_for`, task cancellation, `shield()`, `CancelledError` | Implement timeouts correctly; explain the difference between shield and timeout |
| Thread Pool & Process Pool | `run_in_executor`, `asyncio.to_thread`, `ProcessPoolExecutor` for CPU work | Offload blocking I/O to threads and CPU work to processes from async code |
| Common Pitfalls | Blocking the event loop, deadlock with Lock, unawaited coroutines, exception handling in tasks | Diagnose and fix event loop blocking; explain why exceptions in unawaited tasks are silently lost |
| FastAPI Async Patterns | `async def` endpoints, `BackgroundTasks`, lifespan events, async middleware | Design a FastAPI service with proper async endpoints and background processing |
| Python 3.11+ Features | `TaskGroup`, `asyncio.timeout()`, `asyncio.to_thread`, `except*` syntax | Use modern asyncio APIs; explain the ExceptionGroup pattern in TaskGroup |
| Performance | uvloop, uvicorn workers, connection pooling sizing, benchmarking async code | Justify uvloop adoption; size connection pools for concurrent LLM API usage |

## 1. Event Loop Fundamentals

### What the Event Loop Does

The asyncio event loop is the central execution engine. It:

1. **Schedules and runs coroutines** — registers coroutines as tasks, executes them until they `await`, suspends them, and resumes when their awaited operation completes
2. **Manages I/O multiplexing** — uses OS-level mechanisms (`epoll` on Linux, `kqueue` on macOS, `IOCP` on Windows) to detect when file descriptors are ready for read/write
3. **Executes callbacks** — runs scheduled callbacks via `loop.call_soon()`, `loop.call_later()`, `loop.call_at()`
4. **Handles signals and futures** — resolves `Future` objects, handles `asyncio.Future` callbacks

### Event Loop Lifecycle

```python
import asyncio

async def main():
    pass

# asyncio.run() creates a new loop, runs main(), closes the loop
asyncio.run(main())
```

Under the hood, `asyncio.run()` does:
```python
loop = asyncio.new_event_loop()
asyncio.set_event_loop(loop)
try:
    loop.run_until_complete(main())
finally:
    loop.run_until_complete(loop.shutdown_asyncgens())
    loop.close()
```

### Getting the Loop

```python
import asyncio

async def demo():
    # Preferred: get the currently running loop
    loop = asyncio.get_running_loop()
    
    # Deprecated (3.10+): asyncio.get_event_loop()
    # Deprecated: loop = asyncio.get_event_loop()
```

### Event Loop Policies

The event loop is pluggable via `asyncio.AbstractEventLoopPolicy`. You can replace the default event loop:

```python
import asyncio
import uvloop

# Replace the default event loop policy with uvloop
asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())
```

**uvloop** is a Cython reimplementation of the asyncio event loop using `libuv` (the same library as Node.js). Benefits:
- 2-4x faster than the default `SelectorEventLoop` for I/O operations
- Drop-in replacement — no code changes needed beyond setting the policy
- Production standard for high-performance async Python services (used by Sanic, by default in gunicorn with uvicorn workers)

### Platform-Specific Loops

| Platform | Default Event Loop | Notes |
|----------|-------------------|-------|
| Linux | `SelectorEventLoop` (epoll) | Replace with uvloop for production |
| macOS | `SelectorEventLoop` (kqueue) | Replace with uvloop for production |
| Windows | `ProactorEventLoop` | Better subprocess support; uvloop not available on Windows |

## 2. Coroutines & async/await

### Coroutine Functions vs Coroutine Objects

```python
async def fetch_data():
    await asyncio.sleep(1)
    return 42

# fetch_data is a coroutine FUNCTION
# fetch_data() is a coroutine OBJECT — calling it does NOT execute it

coro = fetch_data()       # <coroutine object fetch_data at 0x...>
result = await coro       # Actually executes it, returns 42
```

**Key rules:**
- `async def` defines a coroutine function
- Calling a coroutine function returns a coroutine object — no execution happens
- A coroutine must be `await`ed or wrapped in a `Task` to execute
- `await` is only valid inside `async def` functions
- Using `await` outside `async def` raises `SyntaxError`

### Three Awaitable Types

| Type | Description | Usage |
|------|-------------|-------|
| **Coroutine** | Object returned by calling `async def` | `await coro()` |
| **Task** | Wrapper that schedules a coroutine on the event loop | `await asyncio.create_task(coro())` |
| **Future** | Low-level placeholder for an eventual result | Rarely created directly; returned by some APIs |

### async def Variants

```python
# Regular coroutine
async def regular():
    return await some_async_op()

# Async generator (uses yield)
async def generate_numbers():
    for i in range(10):
        await asyncio.sleep(0.1)
        yield i

# NOT valid: yield from in async def
async def invalid():
    yield from some_gen()  # SyntaxError
```

### Common Mistake: Unawaited Coroutine

```python
async def main():
    fetch_data()  # RuntimeWarning: coroutine 'fetch_data' was never awaited
                  # The coroutine never executes!
```

Fix: always `await` or wrap in a task:
```python
async def main():
    result = await fetch_data()           # Awaits directly
    # OR
    task = asyncio.create_task(fetch_data())  # Schedules for concurrent execution
    result = await task
```

## 3. Task Management

### asyncio.create_task

Wraps a coroutine in a `Task` and schedules it to run concurrently:

```python
async def main():
    task = asyncio.create_task(fetch_data())
    # Task is now running concurrently
    # Can do other work here...
    result = await task  # Wait for it to complete
```

**Critical**: save a reference to the task. The event loop only keeps weak references — a garbage-collected task silently disappears.

### TaskGroup (Python 3.11+) — Preferred for Structured Concurrency

```python
async def main():
    async with asyncio.TaskGroup() as tg:
        task1 = tg.create_task(fetch_user(1))
        task2 = tg.create_task(fetch_user(2))
        task3 = tg.create_task(fetch_user(3))
    # All tasks are guaranteed complete here
    # If any task raises, remaining tasks are cancelled
    # Exceptions are grouped into ExceptionGroup
```

**TaskGroup guarantees:**
1. All tasks are awaited when the context manager exits
2. If one task raises an exception, all remaining tasks are cancelled
3. Non-cancellation exceptions are combined in an `ExceptionGroup`
4. New tasks can be added dynamically during execution

### asyncio.gather

```python
async def main():
    # Run multiple coroutines concurrently
    results = await asyncio.gather(
        fetch_user(1),
        fetch_user(2),
        fetch_user(3),
    )
    # results = [user1, user2, user3] — order matches input order
```

With error handling:
```python
async def main():
    results = await asyncio.gather(
        fetch_user(1),
        fetch_user(2),  # This might fail
        fetch_user(3),
        return_exceptions=True,  # Exceptions become values in the result list
    )
    for result in results:
        if isinstance(result, Exception):
            print(f"Failed: {result}")
        else:
            print(f"Success: {result}")
```

**gather vs TaskGroup:**

| Aspect | `gather` | `TaskGroup` |
|--------|----------|-------------|
| On exception | Does NOT cancel remaining tasks (propagates first exception by default) | Cancels remaining tasks |
| Result | List of results in input order | Access via `task.result()` |
| Dynamic tasks | Fixed at call time | Can add tasks during execution |
| Python version | All asyncio versions | 3.11+ |
| Exception handling | Single exception or list with return_exceptions=True | ExceptionGroup with except* |

### asyncio.wait

```python
async def main():
    tasks = [asyncio.create_task(fetch_user(i)) for i in range(5)]
    
    # Wait for ALL to complete
    done, pending = await asyncio.wait(tasks)
    
    # Wait for FIRST to complete
    done, pending = await asyncio.wait(tasks, return_when=asyncio.FIRST_COMPLETED)
    
    # Wait for FIRST exception
    done, pending = await asyncio.wait(tasks, return_when=asyncio.FIRST_EXCEPTION)
    
    # With timeout (returns pending tasks)
    done, pending = await asyncio.wait(tasks, timeout=2.0)
```

### asyncio.as_completed

```python
async def main():
    tasks = [asyncio.create_task(fetch_user(i)) for i in range(5)]
    
    # Process results as they complete (not in input order)
    for coro in asyncio.as_completed(tasks):
        result = await coro
        print(f"Got result: {result}")
```

### Fire-and-Forget Pattern

```python
async def main():
    background_tasks = set()
    
    for i in range(10):
        task = asyncio.create_task(process_item(i))
        background_tasks.add(task)
        task.add_done_callback(background_tasks.discard)
    
    # Don't await — but keep references to prevent GC
```

## 4. Concurrency Patterns for LLMs

### Concurrent LLM API Calls

```python
import asyncio
import httpx

async def call_llm(client: httpx.AsyncClient, prompt: str) -> str:
    response = await client.post(
        "https://api.openai.com/v1/chat/completions",
        json={
            "model": "gpt-4",
            "messages": [{"role": "user", "content": prompt}],
            "temperature": 0.7,
        },
        headers={"Authorization": f"Bearer {API_KEY}"},
        timeout=30.0,
    )
    return response.json()["choices"][0]["message"]["content"]

async def process_prompts(prompts: list[str]) -> list[str | Exception]:
    async with httpx.AsyncClient() as client:
        results = await asyncio.gather(
            *[call_llm(client, p) for p in prompts],
            return_exceptions=True,
        )
    return results
```

### Connection Pooling with httpx

```python
# Single shared client = connection pooling (HTTP/2 multiplexing)
async def main():
    limits = httpx.Limits(max_connections=100, max_keepalive_connections=20)
    
    async with httpx.AsyncClient(
        limits=limits,
        timeout=httpx.Timeout(30.0, connect=10.0),
    ) as client:
        # All requests share the connection pool
        results = await asyncio.gather(
            *[call_llm(client, p) for p in prompts]
        )
```

**Pool sizing for LLM APIs:**
- `max_connections`: total concurrent connections (match your concurrency limit)
- `max_keepalive_connections`: idle connections kept alive (typically 10-20)
- Avoid creating new `AsyncClient` per request — this defeats pooling

### Rate Limiting with Semaphores

```python
async def process_prompts_rate_limited(prompts: list[str], rate: int = 10):
    semaphore = asyncio.Semaphore(rate)
    
    async def limited_call(client, prompt):
        async with semaphore:
            return await call_llm(client, prompt)
    
    async with httpx.AsyncClient() as client:
        results = await asyncio.gather(
            *[limited_call(client, p) for p in prompts],
            return_exceptions=True,
        )
    return results
```

### Streaming LLM Responses

```python
async def stream_llm_response(client: httpx.AsyncClient, prompt: str):
    async with client.stream(
        "POST",
        "https://api.openai.com/v1/chat/completions",
        json={
            "model": "gpt-4",
            "messages": [{"role": "user", "content": prompt}],
            "stream": True,
        },
        headers={"Authorization": f"Bearer {API_KEY}"},
    ) as response:
        async for line in response.aiter_lines():
            if line.startswith("data: ") and line != "data: [DONE]":
                chunk = json.loads(line[6:])
                if chunk["choices"][0].get("delta", {}).get("content"):
                    yield chunk["choices"][0]["delta"]["content"]

# Usage with async for
async for token in stream_llm_response(client, "Hello"):
    print(token, end="", flush=True)
```

## 5. async for & Async Iterators

### Async Iterators and Generators

An **async iterator** implements `__aiter__()` and `__anext__()`. An **async generator** uses `async def` with `yield`.

```python
# Async generator
async def count_up_to(n: int):
    for i in range(n):
        await asyncio.sleep(0.1)
        yield i

# Consuming with async for
async def main():
    async for value in count_up_to(5):
        print(value)

# Async comprehension
async def main():
    result = [i async for i in count_up_to(5) if i % 2 == 0]
    # result = [0, 2, 4]
```

### Streaming Pattern for LLM Responses

```python
async def stream_tokens(llm_stream):
    """Collect streamed tokens into a full response."""
    chunks = []
    async for chunk in llm_stream:
        chunks.append(chunk)
    return "".join(chunks)

async def fan_out_stream(client, prompts, max_concurrent=5):
    """Stream multiple LLM responses concurrently."""
    sem = asyncio.Semaphore(max_concurrent)

    async def process_one(prompt):
        async with sem:
            return await stream_tokens(
                stream_llm_response(client, prompt)
            )

    async with httpx.AsyncClient() as client:
        results = await asyncio.gather(
            *[process_one(p) for p in prompts],
            return_exceptions=True,
        )
    return results
```

### Async Context Managers

```python
class AsyncResource:
    async def __aenter__(self):
        await asyncio.sleep(0.1)  # async setup
        return self

    async def __aexit__(self, exc_type, exc_val, exc_tb):
        await asyncio.sleep(0.1)  # async teardown
        return False

async def main():
    async with AsyncResource() as resource:
        await resource.do_something()
```

Common usage: `aiohttp.ClientSession()`, database connections, file handles in async contexts.

## 6. Synchronization Primitives

All asyncio synchronization primitives are designed for cooperative multitasking within a single event loop (unlike `threading` primitives for OS threads).

### asyncio.Lock

```python
async def main():
    lock = asyncio.Lock()
    
    async def protected_section(id):
        async with lock:
            print(f"Task {id} in critical section")
            await asyncio.sleep(1)
            print(f"Task {id} done")

    await asyncio.gather(protected_section(1), protected_section(2))
    # Runs sequentially, not concurrently (locked)
```

### asyncio.Semaphore

Limits the number of coroutines that can access a resource simultaneously:

```python
async def main():
    sem = asyncio.Semaphore(3)  # Max 3 concurrent

    async def limited_task(id):
        async with sem:
            print(f"Task {id} started")
            await asyncio.sleep(2)
            print(f"Task {id} finished")

    # 10 tasks, but only 3 run at a time
    await asyncio.gather(*[limited_task(i) for i in range(10)])
```

### asyncio.BoundedSemaphore

Same as `Semaphore` but raises `ValueError` if `release()` is called more times than `acquire()` — catches programming errors.

### asyncio.Event

Allows one coroutine to signal other coroutines:

```python
async def main():
    event = asyncio.Event()

    async def waiter(name):
        print(f"{name} waiting...")
        await event.wait()
        print(f"{name} triggered!")

    async def setter():
        await asyncio.sleep(1)
        print("Setting event")
        event.set()

    await asyncio.gather(waiter("A"), waiter("B"), setter())
```

### asyncio.Queue

Thread-safe (for asyncio coroutines) FIFO queue for producer-consumer patterns:

```python
async def main():
    queue = asyncio.Queue(maxsize=10)

    async def producer():
        for i in range(5):
            await queue.put(i)
            print(f"Produced {i}")
        await queue.put(None)  # Sentinel

    async def consumer():
        while True:
            item = await queue.get()
            if item is None:
                queue.task_done()
                break
            print(f"Consumed {item}")
            await asyncio.sleep(0.5)
            queue.task_done()

    await asyncio.gather(producer(), consumer())
```

**Key Queue methods:**
- `await queue.put(item)` — add item (blocks if full)
- `await queue.get()` — remove item (blocks if empty)
- `queue.task_done()` — signal that processing is complete
- `await queue.join()` — block until all items are task_done()

### Synchronization Summary

| Primitive | Use Case | AI Engineer Example |
|-----------|----------|---------------------|
| `Lock` | Mutual exclusion for shared state | Protecting shared result cache writes |
| `Semaphore(n)` | Limit concurrent access | Rate limiting LLM API calls (n = max RPM) |
| `BoundedSemaphore` | Safer Semaphore with error detection | Same but catches release bugs |
| `Event` | One-to-many signaling | "Model loaded" event before processing requests |
| `Queue` | Producer-consumer decoupling | Task queue for async document processing |

## 7. Timeout & Cancellation

### asyncio.wait_for (Classic)

```python
async def main():
    try:
        result = await asyncio.wait_for(fetch_data(), timeout=5.0)
    except TimeoutError:
        print("Operation timed out")
```

Cancels the task on timeout, waits for cancellation to complete, then raises `TimeoutError`.

### asyncio.timeout (Python 3.11+) — Preferred

```python
async def main():
    try:
        async with asyncio.timeout(5.0):
            result = await fetch_data()
    except TimeoutError:
        print("Operation timed out")
```

**Advantages over `wait_for`:**
- Context manager syntax — clearer scoping
- Reschedulable via `cm.reschedule(new_deadline)`
- Inspectable via `cm.expired()`
- Safely nestable
- Internally converts `CancelledError` to `TimeoutError`

### Task Cancellation

```python
async def long_running():
    try:
        await asyncio.sleep(3600)
    except asyncio.CancelledError:
        print("Cleaning up...")
        await asyncio.sleep(0.5)  # Cleanup
        raise  # MUST re-raise unless you truly want to suppress
        # If suppressed, call task.uncancel() to clear cancellation state

async def main():
    task = asyncio.create_task(long_running())
    await asyncio.sleep(1)
    task.cancel()
    try:
        await task
    except asyncio.CancelledError:
        print("Task was cancelled")
```

**Rules:**
- `CancelledError` subclasses `BaseException` (not `Exception`) — most exception handlers won't catch it
- Always re-raise `CancelledError` unless you have a specific reason to suppress
- If suppressing, call `task.uncancel()` to clear the cancellation counter
- TaskGroup and `asyncio.timeout()` use cancellation internally — swallowing `CancelledError` breaks them

### asyncio.shield

Protects an awaitable from cancellation:

```python
async def main():
    task = asyncio.create_task(critical_operation())
    
    try:
        # If this coroutine is cancelled, critical_operation continues
        result = await asyncio.shield(task)
    except asyncio.CancelledError:
        print("We were cancelled, but the critical task still runs")
        # The shielded task is NOT cancelled
```

**Key difference**: `shield()` prevents the inner task from being cancelled when the outer coroutine is cancelled. The outer coroutine still gets `CancelledError`, but the shielded task keeps running.

**Important**: you must still save a reference to the shielded task and handle its result separately if needed.

## 8. Thread Pool vs Process Pool

### When to Use Each

| Executor | Use Case | Overhead | GIL Impact |
|----------|----------|----------|------------|
| `ThreadPoolExecutor` | Blocking I/O (sync file ops, sync HTTP, C extensions) | Low | Released during I/O waits |
| `ProcessPoolExecutor` | CPU-bound work (image processing, ML inference, data transforms) | High (new process) | Each process has own GIL |

### run_in_executor

```python
import asyncio
from concurrent.futures import ThreadPoolExecutor

async def main():
    loop = asyncio.get_running_loop()
    
    # Run blocking I/O in a thread (doesn't block event loop)
    result = await loop.run_in_executor(
        ThreadPoolExecutor(max_workers=4),
        blocking_read_file,
        "data.json",
    )
```

### asyncio.to_thread (Python 3.9+) — Preferred

```python
import asyncio

async def main():
    # Simpler API for running sync functions in threads
    result = await asyncio.to_thread(blocking_read_file, "data.json")
    
    # Run multiple blocking calls concurrently
    results = await asyncio.gather(
        asyncio.to_thread(read_file, "a.json"),
        asyncio.to_thread(read_file, "b.json"),
        asyncio.to_thread(read_file, "c.json"),
    )
```

**Note**: `to_thread` uses the default `ThreadPoolExecutor`. For CPU-bound work, use `ProcessPoolExecutor` explicitly:

```python
import asyncio
from concurrent.futures import ProcessPoolExecutor

async def main():
    loop = asyncio.get_running_loop()
    
    with ProcessPoolExecutor() as executor:
        results = await asyncio.gather(
            loop.run_in_executor(executor, cpu_heavy_transform, data1),
            loop.run_in_executor(executor, cpu_heavy_transform, data2),
        )
```

### AI Engineer Example: Hybrid Async + CPU Work

```python
async def process_documents(docs: list[str]):
    """Embed documents: CPU-bound embedding + I/O-bound LLM calls."""
    loop = asyncio.get_running_loop()
    
    # Step 1: CPU-bound embedding (parallel across processes)
    with ProcessPoolExecutor() as pool:
        embeddings = await asyncio.gather(
            *[loop.run_in_executor(pool, compute_embedding, doc)
              for doc in docs]
        )
    
    # Step 2: I/O-bound LLM summarization (async concurrent calls)
    async with httpx.AsyncClient() as client:
        summaries = await asyncio.gather(
            *[call_llm(client, f"Summarize: {doc[:500]}")
              for doc in docs],
            return_exceptions=True,
        )
    
    return list(zip(embeddings, summaries))
```

## 9. Common Pitfalls

### 1. Blocking the Event Loop

```python
async def main():
    # BAD: time.sleep blocks the entire event loop
    time.sleep(5)
    
    # GOOD: asyncio.sleep yields control
    await asyncio.sleep(5)
    
    # BAD: requests.get blocks
    response = requests.get("https://api.example.com")
    
    # GOOD: httpx async
    async with httpx.AsyncClient() as client:
        response = await client.get("https://api.example.com")
    
    # BAD: heavy CPU computation blocks
    result = sum(range(10**8))
    
    # GOOD: offload to process pool
    result = await asyncio.to_thread(sum, range(10**8))  # thread (GIL-limited)
    # Or for true parallelism:
    loop = asyncio.get_running_loop()
    result = await loop.run_in_executor(None, sum, range(10**8))
```

**Detection**: Enable debug mode to get warnings when tasks take too long:
```python
asyncio.run(main(), debug=True)
# Or set the environment variable:
# PYTHONASYNCIODEBUG=1
```

### 2. Deadlock with asyncio.Lock

```python
# BAD: acquiring lock without releasing (forgot async with)
async def bad():
    lock = asyncio.Lock()
    await lock.acquire()
    # If an exception occurs here, lock is never released
    await asyncio.sleep(1)
    # Oops, forgot lock.release()

# GOOD: use async with
async def good():
    lock = asyncio.Lock()
    async with lock:
        await asyncio.sleep(1)
    # Lock automatically released, even on exception
```

### 3. Unawaited Coroutines — Silently Lost Exceptions

```python
async def main():
    # BAD: exception is silently lost
    asyncio.create_task(might_fail())
    
    # GOOD: handle via TaskGroup or gather with return_exceptions
    async with asyncio.TaskGroup() as tg:
        tg.create_task(might_fail())

asyncio.run(main())
```

When a task created with `create_task` raises an exception, Python logs it but does NOT propagate it to the caller. The exception is effectively lost unless you `await` the task or use `TaskGroup`.

### 4. Creating Event Loop in Different Thread

```python
# BAD: trying to use asyncio from a non-main thread without setup
def thread_fn():
    asyncio.run(main())  # This works, but creates a separate loop

# To communicate between threads and event loop:
def thread_fn(loop: asyncio.AbstractEventLoop):
    future = asyncio.run_coroutine_threadsafe(my_coro(), loop)
    result = future.result(timeout=5.0)
```

### 5. Mixing Sync and Async Libraries

```python
# BAD: mixing sync requests with async code
async def fetch():
    return requests.get("https://example.com")  # Blocks event loop!

# GOOD: use async client
async def fetch():
    async with httpx.AsyncClient() as client:
        return await client.get("https://example.com")
```

### 6. Exception in gather Without return_exceptions

```python
# BAD: first exception cancels nothing, but other tasks keep running
# and you have no way to get their results
results = await asyncio.gather(task1, task2, task3)
# If task2 raises, the exception propagates here
# task1 and task3 are NOT cancelled and keep running in background

# GOOD: use return_exceptions=True for partial failure handling
results = await asyncio.gather(
    task1, task2, task3,
    return_exceptions=True,
)

# BEST: use TaskGroup for automatic cancellation on failure
async with asyncio.TaskGroup() as tg:
    tg.create_task(task1_coro())
    tg.create_task(task2_coro())
    tg.create_task(task3_coro())
# If any fails, all others are cancelled
```

## 10. FastAPI Async Patterns

### async def Endpoints

```python
from fastapi import FastAPI, BackgroundTasks

app = FastAPI()

# async def — does NOT block the event loop during I/O waits
@app.get("/users/{user_id}")
async def get_user(user_id: int):
    user = await db.fetch_user(user_id)  # Async DB call
    return user

# Regular def — runs in a thread pool (for sync libraries)
@app.get("/sync-users/{user_id}")
def get_user_sync(user_id: int):
    user = sync_db.fetch_user(user_id)  # Sync DB call
    return user
```

**FastAPI's async behavior**: If you declare `async def`, FastAPI runs the endpoint directly on the event loop. If you declare regular `def`, it runs in a thread pool (via `run_in_threadpool`). Both work, but `async def` is preferred for I/O-bound endpoints.

### BackgroundTasks

```python
@app.post("/generate")
async def generate_report(request: ReportRequest, background_tasks: BackgroundTasks):
    # Return immediately, process in background
    background_tasks.add_task(process_report, request.id)
    return {"status": "processing", "id": request.id}
```

**Note**: `BackgroundTasks` runs tasks after the response is sent but still on the event loop. For heavy CPU work, use `run_in_executor` inside the background task.

### Lifespan Events (Python 3.7+ / FastAPI)

```python
from contextlib import asynccontextmanager
from fastapi import FastAPI

@asynccontextmanager
async def lifespan(app: FastAPI):
    # Startup: initialize resources
    app.state.client = httpx.AsyncClient()
    app.state.redis = await redis.connect()
    print("Application started")
    yield
    # Shutdown: cleanup
    await app.state.client.aclose()
    await app.state.redis.close()
    print("Application stopped")

app = FastAPI(lifespan=lifespan)
```

### Async Middleware

```python
@app.middleware("http")
async def add_process_time(request: Request, call_next):
    start = time.perf_counter()
    response = await call_next(request)  # Async — doesn't block
    duration = time.perf_counter() - start
    response.headers["X-Process-Time"] = str(duration)
    return response
```

### Streaming Response (SSE)

```python
from fastapi.responses import StreamingResponse

@app.get("/stream")
async def stream_response():
    async def generate():
        async for token in stream_llm(client, prompt):
            yield f"data: {json.dumps({'token': token})}\n\n"
        yield "data: [DONE]\n\n"

    return StreamingResponse(
        generate(),
        media_type="text/event-stream",
    )
```

## 11. Python 3.11+ Features

### TaskGroup (3.11)

Already covered in Section 3. The key advantages over `gather`:
- Automatic cancellation of remaining tasks on failure
- Dynamic task addition during execution
- `ExceptionGroup` for collecting all exceptions

```python
async def main():
    try:
        async with asyncio.TaskGroup() as tg:
            tg.create_task(might_fail())
            tg.create_task(will_succeed())
    except* ValueError as e:
        # Handle ValueError specifically using except*
        print(f"Value errors: {e.exceptions}")
    except* Exception as e:
        print(f"Other errors: {e.exceptions}")
```

### asyncio.timeout() (3.11)

Already covered in Section 7. Replaces `asyncio.wait_for()` for most use cases.

### asyncio.to_thread() (3.9)

Already covered in Section 8. Simplified API for `run_in_executor` with default thread pool.

### ExceptionGroup and except* (3.11)

```python
async def main():
    try:
        async with asyncio.TaskGroup() as tg:
            tg.create_task(task_a())  # Might raise ValueError
            tg.create_task(task_b())  # Might raise TypeError
            tg.create_task(task_c())  # Might raise ValueError
    except* ValueError as eg:
        print(f"ValueErrors: {eg.exceptions}")
        # eg.exceptions is a list of all ValueError instances
    except* TypeError:
        print("Got TypeError")
    except ExceptionGroup:
        print("Other exception group")
```

### Eager Task Factory (3.12)

```python
asyncio.set_event_loop_policy(
    asyncio.DefaultEventLoopPolicy()
)
loop = asyncio.new_event_loop()
loop.set_task_factory(asyncio.eager_task_factory)
```

Tasks start executing immediately during creation (before being scheduled). Benefits:
- Avoids loop scheduling overhead for coroutines that complete synchronously
- Useful for cached/memoized coroutines that often don't block

### asyncio.timeout() as Context Manager (3.11)

```python
# Reschedulable timeout
async def main():
    async with asyncio.timeout(None) as cm:
        # Don't know timeout yet
        await some_setup()
        # Now we know: 10 seconds from now
        cm.reschedule(asyncio.get_running_loop().time() + 10.0)
        await long_running_task()
```

## 12. Performance

### uvloop

```python
import uvloop
import asyncio

asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())
```

Performance gains:
- **2-4x** faster I/O operations vs default SelectorEventLoop
- Uses `libuv` (Node.js's event loop library)
- Production standard for uvicorn, Sanic, aiohttp services
- No code changes beyond setting the policy

### Uvicorn Workers

```bash
# Production: multiple workers (each with own event loop = true parallelism)
uvicorn app:app --host 0.0.0.0 --port 8000 --workers 4 --loop uvloop

# Workers = number of CPU cores (for I/O-bound)
# For CPU-bound mixed workloads, use fewer workers
```

Each worker is a separate process with its own event loop and GIL — achieving true parallelism across requests.

### Connection Pool Sizing

```python
import httpx

# For LLM API with rate limit of 60 RPM and 10 concurrent requests
async with httpx.AsyncClient(
    limits=httpx.Limits(
        max_connections=10,           # Match concurrency limit
        max_keepalive_connections=5,   # Keep ~50% alive for reuse
    ),
    timeout=httpx.Timeout(
        30.0,       # Total timeout
        connect=10.0,  # Connection timeout
    ),
) as client:
    ...
```

**Rules of thumb:**
- `max_connections` = your desired concurrency limit (not higher than API allows)
- `max_keepalive_connections` = ~50% of max_connections (balance reuse vs resource usage)
- One `AsyncClient` per application lifecycle (shared across all requests)

### Benchmarking Async Code

```python
import asyncio
import time

async def benchmark():
    start = time.perf_counter()
    await asyncio.gather(*[fetch_data() for _ in range(100)])
    elapsed = time.perf_counter() - start
    print(f"100 concurrent requests in {elapsed:.2f}s")

asyncio.run(benchmark())
```

**Common mistakes in benchmarking:**
- Forgetting to use `time.perf_counter()` instead of `time.time()`
- Benchmarking with `debug=True` enabled (adds overhead)
- Not warming up the event loop
- Ignoring connection pool warm-up time

## Interview Questions

**Q1: What happens when you call an `async def` function without `await`?**

Calling an `async def` function returns a coroutine object — no code inside the function executes. The coroutine must be either `await`ed (which runs it to completion and returns its result) or wrapped in a `Task` via `asyncio.create_task()` (which schedules it to run concurrently on the event loop). If neither is done, Python issues a `RuntimeWarning: coroutine was never awaited` and the coroutine is eventually garbage-collected without running.

**Q2: Explain the difference between `asyncio.gather` and `asyncio.TaskGroup`.**

`gather` runs awaitables concurrently and returns results in input order. By default, the first exception propagates immediately, but remaining tasks are NOT cancelled. With `return_exceptions=True`, exceptions become values in the result list. `TaskGroup` (3.11+) is a context manager that provides structured concurrency: if any task raises a non-cancellation exception, all remaining tasks are automatically cancelled, and exceptions are collected into an `ExceptionGroup`. TaskGroup also supports dynamic task addition during execution. For AI engineering, TaskGroup is preferred when you need cleanup guarantees (e.g., cancelling parallel LLM calls when one fails).

**Q3: How would you make 100 concurrent LLM API calls with proper error handling and rate limiting?**

Use a `Semaphore` for rate limiting (matching the API's concurrency limit), `httpx.AsyncClient` with connection pooling, and `asyncio.gather` with `return_exceptions=True`:

```python
async def batch_llm_calls(prompts: list[str], max_concurrent: int = 10):
    sem = asyncio.Semaphore(max_concurrent)

    async def call(prompt):
        async with sem:
            return await call_llm(client, prompt)

    async with httpx.AsyncClient(
        limits=httpx.Limits(max_connections=max_concurrent)
    ) as client:
        results = await asyncio.gather(
            *[call(p) for p in prompts],
            return_exceptions=True,
        )
    return results
```

This ensures: (1) no more than `max_concurrent` requests in flight, (2) connection reuse via pooling, (3) individual failures don't crash the batch.

**Q4: What happens when you use `time.sleep()` inside an async function? Why is this a problem?**

`time.sleep()` is a blocking call that holds the entire event loop for its duration. No other coroutines can execute during that time — the event loop is frozen. This defeats the purpose of async. Use `await asyncio.sleep()` instead, which yields control back to the event loop so other coroutines can run. In production, this bug manifests as increased latency for all concurrent requests. Enable `asyncio.run(debug=True)` to detect blocking calls automatically.

**Q5: Explain the difference between `asyncio.Lock` and `threading.Lock`. When would you use each?**

`asyncio.Lock` is a cooperative lock for coroutines within a single event loop — it can only be acquired/released via `await` and only works between asyncio tasks. `threading.Lock` is a preemptive lock for OS threads. Use `asyncio.Lock` when protecting shared state accessed by concurrent asyncio tasks (e.g., a shared result cache). Use `threading.Lock` when protecting shared state accessed by actual OS threads (e.g., when mixing `asyncio` with `ThreadPoolExecutor` and sharing state between the event loop thread and worker threads). They are NOT interchangeable.

**Q6: How does task cancellation work in asyncio? What is `CancelledError` and why should you usually re-raise it?**

When `task.cancel()` is called, `asyncio.CancelledError` is injected into the coroutine at the next `await` point. `CancelledError` subclasses `BaseException` (not `Exception`), so normal `except Exception` handlers won't catch it. You should re-raise it because: (1) `TaskGroup` and `asyncio.timeout()` use cancellation internally — swallowing `CancelledError` breaks them, (2) the cancellation is a cooperative signal that should propagate unless you have explicit cleanup to perform first. The correct pattern is `try/finally` for cleanup, then re-raise.

**Q7: Design an async service that streams LLM tokens to multiple clients simultaneously. What patterns and primitives do you use?**

Use `asyncio.Queue` for each client connection, `asyncio.Semaphore` to limit concurrent LLM API calls, and async generators for streaming:

```python
async def handle_client(websocket, prompt, semaphore):
    async with semaphore:
        queue = asyncio.Queue()
        producer = asyncio.create_task(stream_to_queue(queue, prompt))
        try:
            async for token in stream_from_queue(queue):
                await websocket.send(token)
        finally:
            producer.cancel()
```

Each client gets its own queue. The semaphore limits total API concurrency. The producer task streams tokens into the queue while the consumer sends them to the client. On disconnect, the producer is cancelled.

**Q8: What is uvloop and why would you use it instead of the default event loop?**

uvloop is a Cython reimplementation of asyncio's event loop using `libuv` (the C library behind Node.js). It provides 2-4x faster I/O performance by replacing Python's `SelectorEventLoop` with a highly optimized native loop. In production, set it via `asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())`. It's a drop-in replacement — no code changes beyond the policy. Not available on Windows. Standard in production deployments using uvicorn (`--loop uvloop`).

**Q9: How do you handle CPU-bound work in an asyncio application?**

CPU-bound work blocks the event loop because it doesn't involve `await` points. Solutions: (1) `asyncio.to_thread()` for lightweight CPU work — runs in a thread pool but still limited by GIL. (2) `loop.run_in_executor(ProcessPoolExecutor())` for heavy CPU work — runs in separate processes with their own GIL, achieving true parallelism. (3) For ML inference, consider batching multiple inferences into one process pool call. Pattern: async event loop handles I/O (LLM calls, HTTP) and dispatches CPU work (embedding, image processing) to process pools.

**Q10: Explain the "fire-and-forget" task pattern and its pitfalls.**

Fire-and-forget creates a task without awaiting it, allowing it to run in the background. The pitfall is that if you don't keep a strong reference, the task can be garbage-collected before completion. Also, any exception in the task is logged but not propagated — you lose the error. The safe pattern:

```python
background_tasks = set()
for item in items:
    task = asyncio.create_task(process(item))
    background_tasks.add(task)
    task.add_done_callback(background_tasks.discard)
```

Or use `TaskGroup` for guaranteed completion. For AI engineering, fire-and-forget is appropriate for logging, metrics, or non-critical side effects where failure shouldn't block the main flow.

**Q11: What is the difference between `asyncio.shield()` and `asyncio.timeout()`?**

`asyncio.timeout()` imposes a time limit — if the deadline is exceeded, the inner task is cancelled and `TimeoutError` is raised. `asyncio.shield()` prevents cancellation from reaching the inner task — when the outer coroutine is cancelled, the shielded task continues running. They solve opposite problems: timeout limits execution time; shield protects against cancellation. You can combine them: shield a critical task inside a timeout, so the task is protected from external cancellation but still has a time budget.

**Q12: When building a FastAPI service that calls LLM APIs, should all endpoints be `async def`?**

Not necessarily. Use `async def` for endpoints that perform I/O-bound async operations (async HTTP calls, async DB queries). Use regular `def` for endpoints that do CPU-bound work or call synchronous libraries — FastAPI automatically runs them in a thread pool via `run_in_threadpool`. The key test: if the endpoint body contains `await`, use `async def`. If it only calls sync functions, use `def`. Mixing is fine and FastAPI handles both correctly. For an LLM service, `async def` is the right choice since LLM API calls are I/O-bound.

## Key Terminology

**Event Loop** -- The central execution engine in asyncio that schedules and runs coroutines, manages I/O multiplexing via OS mechanisms (epoll/kqueue/IOCP), and executes callbacks. Runs in a single thread using cooperative multitasking — coroutines must explicitly yield control via `await`.

**Coroutine** -- An object that can suspend and resume its execution. Created by calling an `async def` function. Must be awaited or wrapped in a Task to execute. A coroutine function (`async def`) is distinct from a coroutine object (the result of calling the function).

**Task** -- A Future-like object that wraps a coroutine and schedules it for execution on the event loop. Created via `asyncio.create_task()` or `TaskGroup.create_task()`. The event loop runs one Task at a time — when a Task awaits, other Tasks can run.

**Future** -- A low-level awaitable representing an eventual result. The application-level API rarely creates Futures directly. Used internally by asyncio and some library APIs. `loop.run_in_executor()` returns a Future.

**TaskGroup** -- Python 3.11+ context manager providing structured concurrency for tasks. Automatically cancels remaining tasks on failure, collects exceptions into ExceptionGroup, and ensures all tasks complete before exiting. Preferred over `gather` for most use cases.

**Structured Concurrency** -- Programming pattern where tasks are organized into scopes with guaranteed completion. TaskGroup implements this: all spawned tasks complete (or are cancelled) before the scope exits. Prevents leaked tasks and lost exceptions.

**uvloop** -- Cython reimplementation of asyncio's event loop using libuv. Provides 2-4x faster I/O performance. Drop-in replacement via `asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())`. Production standard for async Python services (not available on Windows).

**CancelledError** -- Exception raised in a coroutine when `task.cancel()` is called. Subclasses `BaseException` (not `Exception`). Should typically be re-raised after cleanup. Swallowing it breaks TaskGroup and asyncio.timeout() behavior.

**Semaphore** -- Synchronization primitive that limits concurrent access to N coroutines. Essential for rate limiting LLM API calls. `asyncio.Semaphore(N)` allows N coroutines to proceed; others wait until a slot is available.

**Connection Pooling** -- Reusing HTTP connections across requests to avoid TCP handshake overhead per request. In httpx/aiohttp, achieved by creating a single `AsyncClient` and sharing it across all requests. Pool size should match concurrency limits.

## Cross-References

- **cs_fundamentals/concurrency** -- Broader concurrency concepts (mutex, semaphore, deadlock, race condition, GIL). This topic focuses on Python-specific asyncio implementation. The concurrency topic covers OS-level threading primitives; this topic covers asyncio equivalents and when to use each.
- **cs_fundamentals/computer_networking** -- HTTP/2 multiplexing, SSE (Server-Sent Events), WebSocket — underlying protocols for async streaming in AI services
- **role_specific/senior_ai_engineer** -- Async Programming for AI Systems section (concurrent LLM calls, streaming, backpressure, FastAPI async endpoints)
- **production_engineering/llm_in_production** -- LLM gateway patterns, rate limiting as defense layer, connection pool sizing for multi-provider LLM routing
- **system_design/rate_limiter** -- Rate limiting design patterns applicable to asyncio.Semaphore-based LLM API rate limiting
