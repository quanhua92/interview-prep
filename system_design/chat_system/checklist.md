# Design a Chat System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is this 1:1 messaging only, or do we also support group chats? What is the max group size?
  - [ ] What is the message retention policy? Do messages expire, or are they stored indefinitely?
  - [ ] Do we need to support media attachments (images, videos, files) and what are the size limits?
- [ ] List functional requirements (3-5 items):
  - [ ] Send and receive real-time 1:1 messages
  - [ ] Support group chats with multiple participants
  - [ ] Show online/presence status of users
  - [ ] Support message delivery receipts (sent, delivered, read)
  - [ ] Handle media attachments and file sharing
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: messages delivered in <100ms
  - [ ] High availability: 99.99% uptime
  - [ ] Scalability: support millions of concurrent connections
  - [ ] Ordering: messages must appear in causal order within a conversation
  - [ ] Reliability: no message loss, at-least-once delivery
- [ ] State your scale estimates (users, requests, storage):
  - [ ] ~500M total users, ~10M DAU
  - [ ] ~5M concurrent connections at peak
  - [ ] ~100K messages/sec peak
  - [ ] ~10TB new message storage per year

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Chat Service] -> [WebSocket Gateway] -> [Message Queue] -> [DB + Cache]
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/messages` — send a message (push)
  - [ ] WebSocket `/ws` — receive messages in real-time (long-lived connection)
  - [ ] `GET /api/conversations` — fetch conversation list (pull, on reconnect)
  - [ ] `GET /api/conversations/{id}/messages` — fetch message history (pull, pagination)
- [ ] Note the read:write ratio and where caching helps:
  - [ ] Write-heavy at peak (real-time messaging), reads are bursty (on open/reconnect)
  - [ ] Cache user session info and presence status
  - [ ] Cache recent messages per conversation for fast load
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain WebSocket connection management:
  - [ ] Use WebSocket for persistent bi-directional connections
  - [ ] WebSocket gateway servers maintain live connections
  - [ ] Use a service registry / presence service to track which gateway a user is connected to
  - [ ] Handle reconnection with message catch-up on reconnect
  - [ ] Fallback to long polling if WebSocket is unavailable
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `POST /api/conversations` -> `{"conversation_id": "...", "participants": [...]}`
  - [ ] `POST /api/conversations/{id}/messages` -> `{"message_id": "...", "timestamp": "..."}`
  - [ ] `GET /api/conversations` -> `[{"id": "...", "last_message": "...", "unread": 5}]`
  - [ ] `GET /api/conversations/{id}/messages?cursor=xxx&limit=50` -> `[messages]`
  - [ ] WebSocket events: `message.new`, `message.read`, `presence.update`
- [ ] Sketch the database schema:
  - [ ] Table `users`: `id`, `username`, `last_seen`, `status`
  - [ ] Table `conversations`: `id`, `type (dm/group)`, `created_at`, `updated_at`
  - [ ] Table `conversation_participants`: `conversation_id (FK)`, `user_id (FK)`, `joined_at`, `last_read_message_id`
  - [ ] Table `messages`: `id`, `conversation_id (FK)`, `sender_id (FK)`, `content`, `message_type`, `created_at`, `media_url`
- [ ] Discuss SQL vs NoSQL trade-off:
  - [ ] SQL for user/conversation metadata (relational, consistency-critical)
  - [ ] NoSQL (Cassandra) for messages: time-series by conversation_id, easy horizontal partitioning, high write throughput
- [ ] Walk through the message delivery flow end-to-end:
  - [ ] Sender sends message -> Chat Service persists to DB -> publishes to Message Queue -> WebSocket Gateway receives -> routes to recipient's gateway -> delivers via WebSocket
  - [ ] If recipient offline: store unread count, push notification, deliver on reconnect

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss caching strategy:
  - [ ] Redis for presence status (user online/offline, last seen)
  - [ ] Cache recent N messages per conversation for fast UI load
  - [ ] Cache conversation metadata and participant lists
- [ ] Explain scaling/partitioning approach:
  - [ ] Horizontal scaling of WebSocket gateways (stateless routing via presence service)
  - [ ] Partition messages by `conversation_id` (each conversation lives on a shard)
  - [ ] Partition presence data by `user_id` hash
- [ ] Address single points of failure:
  - [ ] Multiple WebSocket gateway instances behind load balancer
  - [ ] Message queue (Kafka) for durability between send and deliver
  - [ ] Multi-AZ database deployment
- [ ] Handle presence at scale and message ordering:
  - [ ] Presence: heartbeats from client, Redis with TTL for session, gossip or pub/sub for propagation
  - [ ] Ordering: use server-assigned monotonically increasing IDs (Snowflake, hybrid logical clock, or per-conversation sequence number)
  - [ ] Handle out-of-order delivery: buffer and reorder on client, or use Lamport timestamps
- [ ] Discuss monitoring and observability:
  - [ ] WebSocket connection count and reconnect rate
  - [ ] Message delivery latency (p50, p95, p99)
  - [ ] Queue backlog and consumer lag

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
