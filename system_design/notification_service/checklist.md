# Design a Notification Service — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Which delivery channels do we support: push notifications, email, SMS, in-app, or all?
  - [ ] Are there priority levels (e.g., urgent security alert vs. marketing)? How does priority affect delivery?
  - [ ] Do users have per-channel notification preferences (e.g., email only for mentions, push for DMs)?
- [ ] List functional requirements (3-5 items):
  - [ ] Trigger notifications from various event sources (likes, comments, follows, system alerts)
  - [ ] Deliver notifications via multiple channels (push, email, SMS, in-app)
  - [ ] Respect user preferences (opt-in/opt-out per channel per notification type)
  - [ ] Guarantee at-least-once delivery for critical notifications
  - [ ] Support notification grouping and rate limiting (avoid spamming)
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: push notifications delivered in <1 second
  - [ ] High availability: 99.99% uptime for critical alerts
  - [ ] Scalability: handle millions of notifications per second across all channels
  - [ ] Reliability: at-least-once delivery guarantee, no silent drops
  - [ ] Idempotency: user should not receive duplicate notifications
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~500M users, ~10M DAU
  - [ ] ~100K notifications/sec at peak (across all channels)
  - [ ] ~1B notifications/day
  - [ ] Storage: ~500GB/day for notification logs

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Event Sources -> [Notification API] -> [Queue] -> [Dispatcher] -> [Push Provider / Email Service / SMS Gateway]
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/notify` — trigger a notification event (write, high QPS)
  - [ ] `GET /api/notifications` — fetch user's notification inbox (read, moderate QPS)
  - [ ] `PUT /api/notifications/preferences` — update user preferences (write, low QPS)
  - [ ] Async delivery via workers consuming from message queues
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Write-heavy: most operations are triggering and delivering notifications
  - [ ] Cache user preferences to avoid DB lookups on every notification
  - [ ] Cache notification inbox for fast reads
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain queue design and message flow:
  - [ ] Event sources publish notification events to a message queue (Kafka)
  - [ ] Topics can be partitioned by user_id for ordering
  - [ ] Consumers process events: check preferences, dedup, route to appropriate channels
  - [ ] Per-channel queues (push queue, email queue, SMS queue) with different priorities
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/notifications/send` -> `{"notification_id": "..."}`
  - [ ] `GET /api/notifications?cursor=xxx&limit=20` -> `[{"id": "...", "type": "like", "content": "...", "read": false}]`
  - [ ] `PUT /api/notifications/{id}/read` -> `200 OK`
  - [ ] `PUT /api/notifications/preferences` -> `{"push_enabled": true, "email_enabled": false, "...": "..."}`
- [ ] Sketch the database schema:
  - [ ] Table `notifications`: `id`, `user_id`, `type`, `title`, `body`, `data (JSON)`, `channel`, `status`, `created_at`, `read_at`
  - [ ] Table `user_preferences`: `user_id`, `channel`, `notification_type`, `enabled` (composite PK on user_id + channel + type)
  - [ ] Table `notification_templates`: `id`, `type`, `channel`, `template_body`
- [ ] Discuss SQL vs NoSQL trade-off:
  - [ ] User preferences: SQL (relational, strong consistency, low volume)
  - [ ] Notification inbox: NoSQL (Cassandra) partitioned by user_id, time-ordered
  - [ ] Notification logs / analytics: NoSQL or data warehouse for long-term storage
- [ ] Walk through the main flow end-to-end:
  - [ ] Event occurs -> producer publishes to Kafka -> Notification Worker consumes -> checks user preferences -> deduplicates -> routes to channel-specific queue -> Push Worker sends via APNs/FCM, Email Worker sends via SES, SMS Worker sends via Twilio -> update notification status

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss dedup strategy:
  - [ ] Use idempotency key (event_id + user_id + notification_type) to prevent duplicates
  - [ ] Store recent sent notification keys in Redis with short TTL (e.g., 1 hour)
  - [ ] Check dedup key before dispatching
- [ ] Explain retry logic:
  - [ ] Exponential backoff with jitter for transient failures (3-5 retries)
  - [ ] Separate retry queue per channel
  - [ ] After max retries, move to Dead Letter Queue (DLQ)
  - [ ] Alerting on DLQ entries for manual investigation
- [ ] Explain scaling/partitioning approach:
  - [ ] Kafka partitions by user_id for per-user ordering
  - [ ] Horizontal scaling of consumer workers per channel
  - [ ] Partition notification inbox by user_id
- [ ] Address single points of failure:
  - [ ] Kafka cluster with replication
  - [ ] Multi-AZ worker deployment
  - [ ] Third-party provider fallbacks (e.g., multiple email providers)
- [ ] Handle notification routing and rate limiting per user:
  - [ ] Rate limit: max N notifications per channel per hour/day per user
  - [ ] Grouping: batch similar notifications (e.g., "5 people liked your post")
  - [ ] Quiet hours: respect user-configured do-not-disturb windows
  - [ ] Priority queue: critical notifications bypass rate limits
- [ ] Discuss monitoring and observability:
  - [ ] Delivery success rate per channel
  - [ ] End-to-end latency (event trigger to delivery)
  - [ ] Queue depth and consumer lag
  - [ ] DLQ size and alerting

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
