# Concurrency — Self-Assessment Checklist

Use this checklist to gauge your readiness for concurrency-related interview questions. Check off items as you can confidently explain them without notes.

## Concept Self-Assessment

- [ ] Can you explain the difference between concurrency and parallelism?
- [ ] Can you describe common concurrency problems such as race conditions, deadlocks, and livelocks?
- [ ] Can you explain how mutexes, semaphores, and monitors differ in controlling access to shared resources?
- [ ] Can you describe the difference between synchronous, asynchronous, and non-blocking I/O?
- [ ] Can you explain thread-safe data structures and the principle of immutability in concurrent programming?

## Explain-Out-Loud Prompts

- [ ] Explain how you would design a thread-safe rate limiter that supports concurrent requests.
- [ ] Walk through a scenario where a race condition leads to a bug, and explain how to fix it.
- [ ] Describe how the actor model handles concurrency and compare it to shared-memory approaches.

## Common Questions Practice

- [ ] What is the difference between a mutex and a spinlock? When would you use each?
- [ ] Explain how compare-and-swap (CAS) works and how it enables lock-free data structures.
- [ ] What is a condition variable and how does it differ from a mutex? Describe how it is used with the producer-consumer pattern.
- [ ] What are the pros and cons of using threads vs. async/await for concurrent tasks?
- [ ] How does the GIL in Python affect multithreaded programs, and what are the workarounds?
- [ ] Explain how a thread pool works and why creating unlimited threads is problematic.

## Practice Log

- [ ] 2026-05-06 — Reviewed race conditions and mutexes; practiced explaining concurrency vs. parallelism.
- [ ] ______________ — ________________________________________________________________
- [ ] ______________ — ________________________________________________________________
