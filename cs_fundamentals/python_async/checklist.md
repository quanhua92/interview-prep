# Python Async/Await & asyncio — Self-Assessment Checklist

Use this checklist to gauge your readiness for Python asyncio interview questions. Check off items as you can confidently explain them without notes.

## Concept Self-Assessment

- [ ] Can you explain what the asyncio event loop does and how it schedules coroutines?
- [ ] Can you describe the difference between a coroutine function and a coroutine object, and why calling an async function doesn't execute it?
- [ ] Can you explain the three awaitable types (coroutine, Task, Future) and when each is used?
- [ ] Can you compare `asyncio.gather`, `asyncio.wait`, `asyncio.as_completed`, and `TaskGroup`?
- [ ] Can you describe when to use `asyncio.Lock`, `Semaphore`, `Event`, and `Queue`?
- [ ] Can you explain what happens when you block the event loop and how to detect it?
- [ ] Can you explain the difference between `asyncio.shield()` and `asyncio.timeout()`?
- [ ] Can you describe when to use `ThreadPoolExecutor` vs `ProcessPoolExecutor` from async code?
- [ ] Can you explain `CancelledError` and why it should typically be re-raised?
- [ ] Can you describe how uvloop improves performance and when to use it?

## Explain-Out-Loud Prompts

- [ ] Walk through the lifecycle of a coroutine from `async def` to completion on the event loop.
- [ ] Explain why `asyncio.create_task(fetch())` without saving the reference or awaiting the result is dangerous.
- [ ] Design a system that makes 100 concurrent LLM API calls with rate limiting and partial failure handling.
- [ ] Explain the difference between structured concurrency (TaskGroup) and unstructured (create_task + gather) and why it matters.
- [ ] Walk through what happens when a task is cancelled — from `cancel()` to `CancelledError` injection to cleanup.

## Common Questions Practice

- [ ] What happens when you call `time.sleep()` inside an `async def` function? Why is it a problem?
- [ ] Explain the difference between `asyncio.gather(return_exceptions=True)` and `TaskGroup` for error handling.
- [ ] How would you implement rate limiting for concurrent LLM API calls?
- [ ] What is the difference between `asyncio.Lock` and `threading.Lock`?
- [ ] How do you handle CPU-bound work in an asyncio application?
- [ ] Explain the fire-and-forget task pattern and its pitfalls.
- [ ] How do you stream LLM tokens to multiple clients simultaneously using asyncio?
- [ ] What is uvloop and why would you use it in production?
- [ ] When should FastAPI endpoints use `async def` vs regular `def`?
- [ ] Explain `asyncio.to_thread()` and when to use it vs `run_in_executor` with `ProcessPoolExecutor`.
- [ ] What is `ExceptionGroup` and how does `except*` work in the context of `TaskGroup`?
- [ ] How do you size a connection pool for concurrent LLM API calls with httpx?

## Practice Log

- [ ] ______________ — ________________________________________________________________
- [ ] ______________ — ________________________________________________________________
- [ ] ______________ — ________________________________________________________________
