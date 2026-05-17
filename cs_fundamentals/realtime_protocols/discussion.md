# Real-Time Protocols: WebSockets vs SSE vs Long Polling vs HTTP/2 Push

Source: [Realtime Protocols (CalibreOS)](https://www.calibreos.com/learn/hld-realtime-protocols)

## One-Liner
Choose the correct real-time communication protocol (WebSocket, SSE, Long Polling, HTTP/2 Server Push, or WebTransport) based on directionality, frequency, scale, and infrastructure constraints.

## Functional Requirements
- Server can push data to clients without waiting for a request (break the HTTP pull model)
- Support bidirectional communication for interactive apps (chat, collaborative editing)
- Support unidirectional server-push streams (live feeds, token streaming, notifications)
- Handle fallback for restricted network environments (corporate proxies, firewalls)
- Scale persistent connections across multiple backend servers

## Non-Functional Requirements
- Sub-millisecond delivery latency for high-frequency streams (SSE, WebSocket)
- Sub-100ms latency acceptable for most user-facing apps (long polling viable)
- Sub-10ms required for gaming and financial trading (WebTransport / QUIC)
- Millions of concurrent persistent connections across a gateway fleet
- Automatic reconnection with event replay on disconnect
- Minimal per-message overhead (WebSocket: 2-14 bytes vs Long Polling: ~800 bytes HTTP headers)

## Key Scale Questions
- Default Linux server handles ~65K concurrent TCP connections per port (tunable to ~1M)
- 1M connections requires ~15+ gateway servers at 65K each
- Discord serves ~7.5M concurrent WebSocket connections across ~120-200 gateway servers
- Slack handles over 1B WebSocket messages per day
- At 100K long-polling clients each reconnecting once/sec: 100K HTTP handshakes/sec (near Nginx capacity limit)

## Core Components
- **WebSocket Gateway Servers**: thin, stateless connection holders; each maintains a local connection registry (user_id -> set of WebSocket connections)
- **Shared Pub/Sub Layer (Redis Pub/Sub or Kafka)**: routes messages from any server to the server holding the target user's connection
- **Connection State Registry**: Redis hash mapping user_id to server_id so any server can route messages correctly
- **Load Balancer**: distributes connections; may use sticky sessions or rely on pub/sub fan-out
- **Client Reconnection Logic**: exponential backoff with jitter to prevent thundering herd on server restart

## Key Design Decisions

### Protocol Selection (Decision Framework)
- **Bidirectional required?** YES -> WebSocket. NO -> continue
- **High event frequency (>1/sec)?** YES -> SSE or WebSocket. NO -> Long Polling viable
- **TLS on port 443 available?** YES -> all protocols work. NO -> Long Polling safest fallback
- **Sub-10ms latency required?** YES -> WebTransport (if browser support OK). NO -> WebSocket or SSE sufficient
- **Serverless infrastructure?** YES -> Long Polling or managed WebSocket service (AWS API Gateway WebSocket)

### Cross-Server Fan-Out Strategy
- **Option A: Sticky sessions**: LB routes same client to same server via cookie/IP hash. Simple but breaks on server restart (all clients must reconnect)
- **Option B: Shared Pub/Sub (production standard)**: Each gateway subscribes to Redis Pub/Sub channels for its connected users. Any server publishes to Redis, which fans out to all subscribers. Used by Discord (Kafka) and Slack (pub/sub)
- **Option C: Hybrid**: Sticky sessions for small deployments, Redis Pub/Sub for large scale

### Handling Connection State
- On connect: `HSET user:connections user_B server_A_id`
- On disconnect: `HDEL user:connections user_B`
- Routing: publish to Redis Pub/Sub channel `user:{user_id}`, and the correct server self-identifies and delivers

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /events (SSE) | Open SSE stream with `Accept: text/event-stream` |
| WS | /ws/{user_id} | WebSocket upgrade handshake for bidirectional channel |
| GET | /poll (Long Polling) | HTTP request held open until data available or timeout |
| POST | /api/messages | Send a message (REST fallback for SSE hybrid) |
| POST | /api/push | Publish event to Redis Pub/Sub for fan-out |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| user_id | STRING | User identifier |
| server_id | STRING | Gateway server holding the connection (Redis HSET) |
| connected_at | TIMESTAMP | Connection start time |
| last_ping | TIMESTAMP | Last heartbeat pong received |
| channel | STRING | Redis Pub/Sub channel subscribed (e.g. `user:{id}`) |

## Deep Dive Topics
- **HTTP/2 Server Push misconception**: it is for asset preloading (push CSS/JS before browser requests), NOT real-time data delivery. Deprecated in Chrome 106 (Oct 2022) due to cache duplication. Use `rel=preload` instead
- **SSE connection limit under HTTP/1.1**: browsers allow 6 persistent connections per origin; each SSE stream consumes one slot. HTTP/2 multiplexing removes this limit entirely
- **WebTransport (QUIC)**: solves TCP head-of-line blocking that WebSocket suffers under packet loss. Provides reliable streams AND unreliable datagrams. Chrome 97+/Edge 97+ only; Firefox/Safari support limited as of 2025
- **Reconnection storm**: when a gateway server crashes, all clients reconnect simultaneously. Exponential backoff with jitter (`delay = min(base * 2^attempt + random(0, 1000ms), max_delay)`) spreads the load
- **Heartbeat/ping-pong**: TCP connections can silently die (NAT gateway drops after inactivity). WebSocket ping/pong every 30s detects dead connections
- **Serverless incompatibility**: WebSocket and SSE require long-lived processes; serverless functions terminate after each invocation. Use managed services (AWS API Gateway WebSocket, Pusher, Ably) on serverless

## Follow-Up Variations
- How would you design the real-time layer for a chat app with 10M concurrent users?
- A notification service uses WebSocket with 3 backend servers; messages on Server A never reach Server B clients. How do you fix this?
- ChatGPT streams tokens in real time. What protocol does OpenAI use and why?
- A trading platform needs sub-5ms price tick delivery. WebSocket or WebTransport?
- How do you handle a collaborative editor where 50 users edit simultaneously (Figma-style)?
- When would you choose Long Polling over WebSocket in a modern system?
