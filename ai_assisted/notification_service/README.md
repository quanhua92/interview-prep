# Problem 06: Notification Service (Write-Heavy)

**Role:** Backend Engineer
**Duration:** 45-60 minutes
**Difficulty:** Hard
**Format:** System Design Prototyping → Feature Build-Out

---

## Background

Our platform needs to send notifications to users across three channels: **Email**, **SMS**, and **Push**. We process millions of notification requests per day — it's a heavily write-dominated system.

Notifications can be triggered by system events (account verification, password reset) or user actions (someone liked your post, you have a new message). Each notification has different urgency levels.

You'll build the core queuing and delivery engine.

## Functional Requirements

1. Accept a notification request containing: `user_id`, `channel` (email/sms/push), `message`, `priority` (low/normal/high).
2. **Queue** the notification for async delivery.
3. **Deliver** the notification via the correct channel (simulate with a log — no real sending needed).
4. Track delivery **status** (pending, sent, failed).
5. Support **retries** for failed deliveries (up to 3 attempts with exponential backoff).

## Non-Functional Requirements

- The system must be **idempotent** — retrying the same notification should not send it twice.
- High-priority notifications should be processed before low-priority ones.
- The system should handle 10,000 notifications/second at peak.
- Failed notifications should not block the processing of other notifications.

## Constraints

- Single-server implementation for the initial version.
- Simulate channel delivery with `print()` or logging (no real SMTP/SMS/Push SDK).
- Use in-memory queues (no external message broker for v1).
- Each notification has a unique `notification_id` (UUID).

## Starter Interface

```python
from dataclasses import dataclass
from enum import Enum

class Channel(Enum):
    EMAIL = "email"
    SMS = "sms"
    PUSH = "push"

class Priority(Enum):
    LOW = 0
    NORMAL = 1
    HIGH = 2

class Status(Enum):
    PENDING = "pending"
    SENT = "sent"
    FAILED = "failed"

@dataclass
class Notification:
    id: str
    user_id: str
    channel: Channel
    message: str
    priority: Priority
    status: Status = Status.PENDING
    attempts: int = 0

class NotificationService:
    def submit(self, notification: Notification) -> None:
        """Queue a notification for delivery."""
        ...

    def process_next(self) -> Notification | None:
        """Process the next highest-priority notification. Returns it or None if queue is empty."""
        ...

    def get_status(self, notification_id: str) -> Status | None:
        """Check the delivery status of a notification."""
        ...
```

---

## Follow-Up Questions

### Follow-Up 1: Idempotency
> "Our retry mechanism re-submits failed notifications. How do you guarantee a user never receives the same notification twice, even with retries?"

- Use `notification_id` as the idempotency key.
- Where do you track "already sent"? (In-memory set, database, Redis)
- What if the delivery succeeds but the acknowledgment is lost? (At-least-once vs. exactly-once delivery.)

### Follow-Up 2: Priority Queuing
> "Password reset emails are HIGH priority. Marketing emails are LOW. But our queue is flooded with marketing — how do you ensure high-priority items get processed first?"

- Implement a **priority queue** (heap-based) instead of FIFO.
- What about **starvation**? Low-priority items might never be processed. Implement aging or fair scheduling.
- How does this change when you have multiple workers consuming from the queue?

### Follow-Up 3: Multi-Channel Preferences
> "Users have preferences: some want only email, some want push + email, some want all three. A single notification request might need to be delivered to multiple channels."

- Design a **fan-out** mechanism where one request becomes N channel-specific deliveries.
- How do you track status per channel? (One notification → multiple delivery records.)
- If email succeeds but push fails, what's the overall status?

### Follow-Up 4: Rate Limiting Per User
> "Users shouldn't be spammed. We want to limit notifications to 10/hour per user, with urgent system messages exempt."

- Combine this with the rate limiter pattern (Problem 03).
- How do you classify "urgent system messages" vs. regular notifications?
- Where does the rate limit check go — at submission time or at delivery time?
