# Real-Time Protocols -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is the communication bidirectional (chat, cursors, game input) or server-push-only (feeds, notifications, token streaming)?
  - [ ] What is the event frequency: high (multiple/sec) or low (<1/min)?
  - [ ] Will corporate proxies or restricted networks be a factor?
  - [ ] What is the concurrency target (hundreds, thousands, millions of connections)?
  - [ ] Are we on serverless infrastructure or long-lived servers?
  - [ ] Is sub-10ms latency required (gaming, trading) or is sub-100ms acceptable?
- [ ] List functional requirements (3-5 items):
  - [ ] Server can push data to clients proactively
  - [ ] Bidirectional communication if needed (chat typing, collaborative editing)
  - [ ] Automatic reconnection with event replay on disconnect
  - [ ] Scale across multiple backend servers
  - [ ] Fallback for restricted network environments
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: sub-ms for WebSocket/SSE, ~1 RTT for long polling
  - [ ] High concurrency: millions of persistent connections across gateway fleet
  - [ ] Reliability: auto-reconnect with exponential backoff and jitter
  - [ ] Minimal per-message overhead (2-14 bytes for WebSocket vs ~800 bytes for long polling)
- [ ] State your scale estimates (connections, servers, messages):
  - [ ] ~65K concurrent connections per server (default Linux, tunable to ~1M)
  - [ ] 1M connections => ~15+ gateway servers
  - [ ] 7.5M connections (Discord scale) => ~120-200 gateway servers
  - [ ] At 100K long-polling clients reconnecting once/sec: ~100K HTTP handshakes/sec

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [WebSocket Gateways] -> [Redis Pub/Sub] -> [Backend Services]
- [ ] Identify the main operations and their protocol mapping:
  - [ ] Bidirectional (chat, cursors, games) -> WebSocket with HTTP Upgrade handshake
  - [ ] Server-push-only (feeds, streaming tokens, notifications) -> SSE with `text/event-stream`
  - [ ] Low-frequency or legacy fallback -> Long Polling (HTTP request held open)
  - [ ] Sub-10ms with packet loss tolerance -> WebTransport (QUIC-based)
- [ ] Note the per-message overhead comparison:
  - [ ] Long Polling: ~800 bytes HTTP headers per message
  - [ ] SSE: ~50 bytes event frame overhead
  - [ ] WebSocket: 2-14 bytes frame header
  - [ ] WebTransport: minimal QUIC framing
- [ ] Present the protocol decision and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain protocol choice and justify:
  - [ ] WebSocket: full-duplex after HTTP Upgrade + 101 Switching Protocols. Required for bidirectional. 2-14 byte frame overhead
  - [ ] SSE: server-to-client only, HTTP-native, built-in auto-reconnect via EventSource + Last-Event-ID. Simpler than WebSocket for push-only
  - [ ] Long Polling: client sends HTTP request, server holds open until data or timeout (~30s). Stateless, proxy-friendly
  - [ ] WebTransport: QUIC-based, avoids TCP head-of-line blocking, reliable + unreliable datagrams. Limited browser support
- [ ] Define API endpoints with method, path, protocol:
  - [ ] `GET /events` (SSE) -> `Accept: text/event-stream` -> newline-delimited event stream
  - [ ] `WS /ws/{user_id}` -> HTTP Upgrade -> full-duplex binary/text frames
  - [ ] `GET /poll` (Long Polling) -> HTTP request held open -> response when data available
  - [ ] `POST /api/messages` -> publish to Redis Pub/Sub channel `user:{recipient_id}`
- [ ] Sketch the connection state and routing:
  - [ ] Local registry: `connections[user_id] = set of WebSocket connections` (multiple tabs per user)
  - [ ] Redis hash: `HSET user:connections user_B server_A_id` on connect, `HDEL` on disconnect
  - [ ] Redis Pub/Sub: pattern subscribe `user:*` for fan-out to correct gateway
- [ ] Walk through the main flow end-to-end:
  - [ ] Client connects to gateway via WebSocket Upgrade
  - [ ] Gateway registers connection locally + writes routing info to Redis
  - [ ] Client sends message -> gateway publishes to Redis Pub/Sub -> recipient's gateway delivers
  - [ ] On disconnect: gateway cleans up local registry + removes Redis routing entry

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss cross-server fan-out (the #1 scaling challenge):
  - [ ] Sticky sessions: LB routes same client to same server. Simple but breaks on server restart
  - [ ] Redis Pub/Sub fan-out: each gateway subscribes to channels for its users. Any server publishes, correct server delivers. Production standard (Discord uses Kafka, Slack uses pub/sub)
  - [ ] Connection state routing via Redis HSET/HGET for user-to-server mapping
- [ ] Explain HTTP/2 Server Push misconception:
  - [ ] NOT a real-time data channel; it is for asset preloading (CSS, JS)
  - [ ] Deprecated in Chrome 106 (Oct 2022) due to cache duplication
  - [ ] Correct alternative: `rel=preload` headers for asset preloading
- [ ] Address SSE connection limit:
  - [ ] HTTP/1.1: 6 persistent connections per origin; each SSE stream consumes one
  - [ ] HTTP/2: multiplexing removes the limit entirely; many SSE streams share one TCP connection
- [ ] Handle reconnection storm on server crash:
  - [ ] All clients disconnect and reconnect simultaneously (thundering herd)
  - [ ] Exponential backoff with jitter: `delay = min(base * 2^attempt + random(0, 1000ms), max_delay)`
  - [ ] SSE has built-in reconnect with `Last-Event-ID`; WebSocket requires custom implementation
- [ ] Discuss heartbeat/ping-pong for dead connection detection:
  - [ ] TCP connections can silently die (NAT timeout, proxy drop)
  - [ ] WebSocket ping/pong every 30s; close connection if no pong within timeout
- [ ] Address serverless incompatibility:
  - [ ] WebSocket and SSE require long-lived processes; serverless functions are ephemeral
  - [ ] Use managed WebSocket services (AWS API Gateway WebSocket, Pusher, Ably) or fall back to long polling

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the protocol choice in 2-3 sentences
- [ ] State the trade-offs you made and why (e.g., SSE over WebSocket for push-only, Redis Pub/Sub for scale)
- [ ] Mention what you would improve with more time (e.g., WebTransport migration when browser support matures, connection draining on graceful shutdown)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
