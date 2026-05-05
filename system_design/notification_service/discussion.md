# Design a Notification Service

## One-Liner
Centralized service to deliver multi-channel notifications (push, email, SMS, in-app) with user preferences, deduplication, and delivery guarantees.

## Functional Requirements
- Send notifications across multiple channels (push, email, SMS, in-app)
- Support user preference management (opt-in/out per channel and category)
- Deduplicate identical notifications
- Guarantee at-least-once delivery
- Retry failed deliveries with backoff

## Non-Functional Requirements
- High throughput (10M notifications/day)
- Low-latency push delivery (<1s for push, <5min for email)
- Highly available (no notification loss)
- Process notifications asynchronously (non-blocking for calling services)

## Key Scale Questions
- 10M notifications/day, peak 500 notifications/sec
- Average 3 channels per notification = 30M delivery attempts/day
- User base: 100M users, each with preference config
- Retry multiplier: average 1.5 attempts per notification = 45M total attempts/day

## Core Components
- **Notification API**: receive notification requests from other services
- **Notification Queue**: priority queue (Kafka) for async processing
- **Preference Service**: store and retrieve user notification preferences
- **Deduplication Service**: filter duplicate notifications using idempotency key
- **Channel Dispatchers**: separate workers for push (FCM/APNs), email (SES/SendGrid), SMS (Twilio)
- **Delivery Tracker**: track delivery status and retry logic
- **Rate Limiter**: per-user rate limiting to prevent notification spam

## Key Design Decisions

### Delivery Model
- **Option A: Push model**: Service pushes notifications to users proactively. Real-time, requires webhook/FCM setup
- **Option B: Pull model**: Users poll for new notifications. Simple, higher latency, wasteful for inactive users
- **Option C: Hybrid**: Push for real-time channels (push notification, WebSocket), pull for in-app notification center

### Deduplication Strategy
- **Option A: Idempotency key in DB**: Store sent notification keys, check before sending. Reliable, but DB lookups
- **Option B: Bloom filter**: Probabilistic, fast, small memory, small false positive rate (acceptable for dedup)
- **Option C: Time-windowed dedup (Redis SET with TTL)**: Only dedup within a time window. Good for burst scenarios

### Retry Strategy
- **Option A: Fixed interval retry**: Simple, but can overwhelm downstream services
- **Option B: Exponential backoff with jitter**: Standard approach, prevents thundering herd, good for transient failures
- **Option C: Dead letter queue after N retries**: Manual inspection for permanently failing deliveries

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/notifications | Send a notification |
| GET | /api/notifications | List user's notifications |
| PUT | /api/notifications/preferences | Update user preferences |
| PATCH | /api/notifications/{id}/read | Mark as read |
| GET | /api/notifications/{id}/status | Check delivery status |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| notification_id | VARCHAR | PK, UUID |
| user_id | BIGINT | Target user |
| idempotency_key | VARCHAR | Unique constraint for dedup |
| channel | VARCHAR | push, email, sms, in_app |
| status | VARCHAR | pending, sent, failed, delivered |
| retry_count | INT | Current retry attempt |
| created_at | TIMESTAMP | Creation time |

## Deep Dive Topics
- Priority queue implementation: Kafka with per-channel topic partitioning for ordered delivery
- User preference matching: evaluating rules at send time vs pre-computed preference matrix
- Push notification flow: your server -> APNs/FCM -> device, handling device tokens and token rotation
- At-least-once delivery semantics and idempotent receivers

## Follow-Up Variations
- How would you handle notification batching and digest emails (e.g., "You have 10 new notifications")?
- What happens when the push provider (APNs/FCM) is down?
- How do you implement notification grouping and smart summaries?
- How would you support A/B testing of notification content and timing?
