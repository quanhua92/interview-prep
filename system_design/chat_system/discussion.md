# Design a Chat System

## One-Liner
Real-time messaging platform supporting one-to-one and group conversations with message persistence and delivery guarantees.

## Functional Requirements
- Send and receive messages in real-time (1:1 and group chats)
- Show online/offline/typing presence indicators
- Message history with pagination
- Push notifications for offline users
- Message read receipts and delivery status

## Non-Functional Requirements
- Low-latency message delivery (<200ms)
- High availability (99.99% for messaging)
- Ordered message delivery within a conversation
- Support 1M concurrent WebSocket connections

## Key Scale Questions
- 50M DAU, 1M concurrent connections
- Average 500 messages/sec, peak 5,000 messages/sec
- Storage: ~1KB/message x 50M messages/day = ~50GB/day = ~18TB/year
- Average user has 50 conversations, group size up to 1,000

## Core Components
- **API Gateway**: authentication, connection management, SSL termination
- **WebSocket Service**: persistent connections, heartbeat, reconnection logic
- **Chat Service**: message routing, conversation management
- **Message Queue**: Kafka for async message delivery between services
- **Presence Service**: tracks online/offline/typing state (in-memory + Redis)
- **Notification Service**: push notifications for offline users (FCM/APNs)
- **Message Store**: persistent storage (Cassandra for time-series message data)

## Key Design Decisions

### Connection Management
- **Option A: WebSocket**: Full-duplex, low overhead per message, complex connection management
- **Option B: Long polling**: Simple, high overhead per message, easier to scale
- **Option C: Server-Sent Events**: Server-to-client only, no binary support

### Message Storage Architecture
- **Option A: Per-user message inbox**: Easy to paginate for a single user, duplicate messages for each participant, higher storage
- **Option B: Per-conversation message store**: Single copy of each message, requires fan-out on read for user's inbox view
- **Option C: Hybrid**: Store by conversation, maintain a user-conversation index for fast inbox lookup

### Message Ordering
- **Option A: Per-conversation sequence ID**: Simple ordering, single point of contention per conversation
- **Option B: Logical clocks (Lamport/vector)**: Distributed ordering, complex but no single bottleneck
- **Option C: Hybrid (sequence ID per shard)**: Balance between ordering guarantee and throughput

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/conversations | Create a new conversation |
| GET | /api/conversations | List user's conversations |
| GET | /ws | WebSocket connection endpoint |
| POST | /api/conversations/{id}/messages | Send a message (fallback HTTP) |
| GET | /api/conversations/{id}/messages | Fetch message history |
| PUT | /api/conversations/{id}/messages/{mid}/read | Mark message as read |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| message_id | VARCHAR | PK, sortable (Snowflake or ULID) |
| conversation_id | VARCHAR | Partition key |
| sender_id | VARCHAR | Sender user ID |
| content | TEXT | Message body |
| created_at | TIMESTAMP | Server timestamp |
| message_type | VARCHAR | text, image, file, system |

## Deep Dive Topics
- WebSocket connection lifecycle: heartbeat, reconnection, connection draining
- Handling network partitions: message queue durability, delivery guarantees (at-least-once)
- Group chat fan-out: sending to N users efficiently (push model vs pull model)
- Presence service design: heartbeat intervals, Redis pub/sub for state propagation

## Follow-Up Variations
- How would you support end-to-end encryption?
- How do you handle message editing and deletion (for all participants)?
- What happens when a user has 10,000 group chats and opens the app?
- How would you implement file/media sharing with thumbnail generation?
