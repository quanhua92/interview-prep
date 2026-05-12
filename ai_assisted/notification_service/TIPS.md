# Tips: Notification Service

## Key Concepts to Know

- **Message Queue** — Decouples notification submission from delivery. Producer submits, consumer processes asynchronously.
- **Priority Queue** — A min-heap (or max-heap) where items are dequeued by priority rather than insertion order.
- **Idempotency** — The same operation performed multiple times produces the same result. Critical for retry safety.
- **Exponential Backoff** — Retry delay doubles each time: 1s, 2s, 4s, 8s... Prevents overwhelming a failing downstream service.
- **Fan-out** — One input message is delivered to multiple destinations. Common in pub/sub systems.

## Common Mistakes

| Mistake | Why It's Wrong |
|---------|---------------|
| Processing notifications synchronously on submit | Blocks the caller — defeats the purpose of async queuing |
| Using a simple FIFO queue with mixed priorities | Marketing floods drown out urgent notifications |
| Not tracking delivery status per attempt | Can't tell if a notification was sent, failed, or is pending |
| Retrying infinitely on failure | Wastes resources on permanently failed deliveries (bad address, etc.) |
| Not deduplicating on retry | User gets the same SMS 3 times |
| Combining all channel statuses into one | "Partial success" (email sent, push failed) is a real state |

## How to Prompt the AI Effectively

1. **Data model:** "Define a Notification dataclass with id, user_id, channel, message, priority, status, and attempt count."
2. **Queue implementation:** "Implement a priority queue using heapq. Higher priority items are dequeued first."
3. **Processing loop:** "Create a process_next() method that dequeues a notification, simulates delivery, and handles success/failure with retry logic."
4. **Idempotency:** "Add a set of sent notification_ids. Before processing, check if the notification was already sent."

## Retry Strategy

```python
MAX_RETRIES = 3
BACKOFF_BASE = 1  # seconds

def get_backoff_delay(attempt: int) -> float:
    """Exponential backoff: 1s, 2s, 4s for attempts 1, 2, 3."""
    return BACKOFF_BASE * (2 ** (attempt - 1))

# After failure:
if notification.attempts < MAX_RETRIES:
    notification.attempts += 1
    notification.status = Status.PENDING
    # Re-queue with delay (or schedule for later)
else:
    notification.status = Status.FAILED
    # Move to dead letter queue or log for manual review
```

## Architecture Patterns

```
Client → API Endpoint → Notification Service
                              │
                              ▼
                     ┌─────────────────┐
                     │  Priority Queue  │  (heap-based)
                     │  [HIGH/NORMAL/LOW]│
                     └─────────────────┘
                              │
                    ┌─────────┼─────────┐
                    ▼         ▼         ▼
              ┌─────────┐ ┌───────┐ ┌───────┐
              │ Email    │ │ SMS   │ │ Push  │
              │ Sender   │ │ Sender│ │ Sender│
              └─────────┘ └───────┘ └───────┘
                    │         │         │
                    └─────────┼─────────┘
                              ▼
                     Status Tracker
                    (idempotency log)
```

## What Interviewers Look For

- Clean separation between submission and processing (async queue pattern).
- Priority-aware queuing with awareness of starvation risks.
- Idempotency as a core design concern, not an afterthought.
- Practical retry strategy with exponential backoff and max retry limits.
- Ability to handle multi-channel fan-out with per-channel status tracking.
- Integration of cross-cutting concerns (rate limiting from Problem 03, user preferences).
