# Streaming Architecture for LLM Applications — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Problem Framing (2-3 min)
- [ ] State the core value: streaming transforms multi-second waits into real-time token delivery, reducing perceived latency
- [ ] Frame the scope:
  - [ ] LLMs generate token-by-token (prefill + decode); streaming shows first token in ~100ms vs waiting seconds for full response
  - [ ] All major LLM providers chose SSE as the streaming transport
  - [ ] Production streaming introduces new concerns: backpressure, connection management, partial parsing, cancellation
- [ ] State the key metrics:
  - [ ] TTFT (Time to First Token): < 1s interactive, < 5s batch
  - [ ] TPS (Tokens Per Second): > 30 interactive, > 100 batch
  - [ ] ITL (Inter-Token Latency): 1/TPS, < 33ms for smooth UX

## Phase 2: Transport Protocols — SSE, WebSocket, HTTP/2/3 (4-5 min)
- [ ] Explain SSE:
  - [ ] One-way server-to-client over HTTP, `data: <payload>\n\n` format
  - [ ] Built-in reconnection with `Last-Event-ID`
  - [ ] Required headers: `Content-Type: text/event-stream`, `Cache-Control: no-cache`, `X-Accel-Buffering: no`
  - [ ] Limitations: GET-only with native EventSource, HTTP/1.1 connection limit (6/domain), text-only
  - [ ] Workarounds: `@microsoft/fetch-event-source` for POST + headers; HTTP/2 eliminates connection limit
- [ ] Explain WebSocket:
  - [ ] Full-duplex after HTTP upgrade handshake
  - [ ] Binary capable, no built-in message framing
  - [ ] Requires heartbeat (ping/pong every 30s), custom reconnection, WebSocket-aware load balancer
  - [ ] When to use for LLM: voice input, collaborative editing, mid-stream client control, binary streaming
- [ ] Explain HTTP/2 impact:
  - [ ] Stream multiplexing eliminates SSE connection limit (6 concurrent → unlimited)
  - [ ] HPACK header compression
  - [ ] Single TCP connection for all streams
- [ ] Explain HTTP/3 / WebTransport:
  - [ ] QUIC-based, no head-of-line blocking, 0-RTT handshake
  - [ ] WebTransport as WebSocket successor; Chrome/Edge only as of 2025
  - [ ] Track for 2027+; not production-ready for full browser matrix
- [ ] Decision framework (3 questions):
  - [ ] Does client send continuous stream? → WebSocket
  - [ ] Data changes less than every 10s? → Polling
  - [ ] Otherwise? → SSE (right default for LLM streaming)

## Phase 3: LLM Token Streaming & Provider Differences (3-4 min)
- [ ] Walk through OpenAI streaming:
  - [ ] `stream=True` on `chat.completions.create`
  - [ ] Chunk: `choices[0].delta.content` (flat delta format)
  - [ ] Final chunk: `finish_reason` + optional `usage` (with `stream_options.include_usage`)
  - [ ] Cancellation: `signal` parameter via `asyncio.CancelledError`
- [ ] Walk through Anthropic streaming:
  - [ ] `client.messages.stream()` context manager
  - [ ] Event types: `message_start` → `content_block_start` → `content_block_delta` → `content_block_stop` → `message_delta` → `message_stop`
  - [ ] Richer structure: separate events for text and tool_use blocks
  - [ ] `async with` handles cleanup on cancel
- [ ] Walk through Google Gemini streaming:
  - [ ] `model.generate_content(prompt, stream=True)`
  - [ ] Chunks: `candidates[0].content.parts[0].text`
- [ ] State key difference: OpenAI flat delta vs Anthropic event-based (richer for tool calls)

## Phase 4: Async Iterators & Python Patterns (3-4 min)
- [ ] Explain async generator pattern:
  - [ ] `async def` with `yield` → `AsyncIterator`
  - [ ] Consumed with `async for`
  - [ ] Always use `try/finally` for cleanup
- [ ] Explain composition:
  - [ ] Async generators compose naturally (one consumes another)
  - [ ] Buffering generator: accumulate tokens, yield in batches
  - [ ] Merging multiple streams: `asyncio.Queue` + producer/consumer tasks
- [ ] Explain async context managers:
  - [ ] `@asynccontextmanager` for streaming resource lifecycle
  - [ ] Ensures cleanup even on exception or cancellation
- [ ] State common pitfalls:
  - [ ] Blocking event loop with sync I/O → use `asyncio.to_thread()`
  - [ ] Not closing stream on exception → resource leak
  - [ ] Forgetting `flush=True` → tokens appear in bursts
- [ ] Note: detailed async fundamentals in role_specific/senior_ai_engineer (cross-reference, don't duplicate)

## Phase 5: Backpressure Management (3-4 min)
- [ ] Define the problem: producer (LLM) faster than consumer (client/network) → unbounded buffer growth
- [ ] Walk through mechanisms:
  - [ ] Semaphore: `asyncio.Semaphore(N)` limits concurrent streams; reject with 429 when at 0
  - [ ] Bounded queue: `asyncio.Queue(maxsize=N)` between producer and consumer; block producer when full
  - [ ] Client-side: check `ws.bufferedAmount` on WebSocket
- [ ] State graceful degradation levels:
  - [ ] Normal: queue < 50% → stream normally
  - [ ] Throttled: queue 50-80% → batch tokens, reduce TPS
  - [ ] Backpressured: queue > 80% → pause production, drain
  - [ ] Rejected: semaphore at 0 → 429 with retry-after
- [ ] Drop vs queue decision:
  - [ ] Drop when at capacity and latency would exceed SLAs (fail fast)
  - [ ] Queue when brief bursts expected and headroom to catch up
  - [ ] Never queue indefinitely; always set max wait time

## Phase 6: Partial JSON Parsing (2-3 min)
- [ ] State the problem: LLM streaming structured output produces syntactically incomplete JSON mid-stream
- [ ] Walk through the accumulate-and-parse pattern:
  - [ ] Accumulate tokens in buffer
  - [ ] After stream completes, validate with `json.loads()`
  - [ ] Never parse incomplete JSON with `json.loads()` mid-stream
- [ ] Explain ijson:
  - [ ] SAX-style iterative JSON parser
  - [ ] Yields complete items without loading full document in memory
  - [ ] Good for large JSON streams; can extract items incrementally from growing buffer
- [ ] Explain tool call streaming:
  - [ ] OpenAI: accumulate `tc.function.arguments` across chunks
  - [ ] Parse complete JSON when `finish_reason: "tool_calls"`
  - [ ] Anthropic: `content_block_delta` events with incremental tool input
- [ ] Handle interrupted streams:
  - [ ] Log partial buffer with request ID
  - [ ] Return error event to client
  - [ ] Reconnect with Last-Event-ID to restart

## Phase 7: Streaming Orchestration & Client-Side (4-5 min)
- [ ] Explain streaming through agent chains:
  - [ ] Each step is an async generator yielding tokens/events
  - [ ] Orchestrator yields labeled events (step, agent, token)
  - [ ] Multi-agent parallel: `asyncio.as_completed()` for first-to-finish streaming
- [ ] Explain tool calls mid-stream:
  - [ ] Frameworks emit tool events: OpenAI Agents SDK (tool_called, tool_output_delta), LangChain (on_tool_start, on_tool_end), Vercel AI SDK (tool-call, tool-result)
  - [ ] Speculative tool calling: parse output stream for tool patterns, fire early (trades correctness for latency)
- [ ] Explain cancel propagation:
  - [ ] Client abort → server detects disconnect → cancel async task → close LLM connection → cancel pending tools → release semaphores
  - [ ] FastAPI: `await request.is_disconnected()` in streaming loop
  - [ ] Critical: free KV-cache blocks on cancel
- [ ] Explain client-side patterns:
  - [ ] Fetch ReadableStream: most flexible, any method/headers, manual SSE parsing
  - [ ] EventSource: simplest, auto-reconnect, GET-only
  - [ ] Vercel AI SDK `useChat`: React integration with abort on unmount
  - [ ] Progressive rendering: show tokens as they arrive, live markdown, debounced renders for fast streams

## Phase 8: Production Considerations (4-5 min)
- [ ] State connection limits:
  - [ ] Single server: ~10K concurrent SSE (~10-100KB per connection)
  - [ ] Nginx: tune `worker_connections 10000+`
  - [ ] AWS ALB: no fixed limit, idle timeout default 60s (extend to 300s+)
  - [ ] Browser HTTP/1.1: 6/domain (eliminated by HTTP/2)
- [ ] Walk through timeout configuration:
  - [ ] Nginx proxy_read_timeout: 60s → 300s
  - [ ] AWS ALB idle timeout: 60s → 300s
  - [ ] Inter-token gap timeout: 15-30s (detect stuck generation)
- [ ] Explain load balancing approaches:
  - [ ] Sticky sessions: simplest, sufficient for most SSE (state is the stream itself)
  - [ ] Redis Pub/Sub: for cross-instance events, ~1ms latency per event
  - [ ] Connection draining: graceful deploy, no dropped connections
- [ ] State the #1 production failure: proxy buffering
  - [ ] Fix: `X-Accel-Buffering: no` (Nginx), disable gzip for event-stream, disable buffering at every proxy layer
  - [ ] Diagnose with `curl -N` to isolate server vs proxy
- [ ] Walk through monitoring and alerting:
  - [ ] TTFT p99: page >2x baseline
  - [ ] TPS average: page <50% baseline
  - [ ] Concurrent streams: page >80% capacity
  - [ ] Stream abort rate: page >20%
  - [ ] Inter-token gap p99: page >10s
- [ ] Infrastructure sizing for 50K connections:
  - [ ] ~500MB memory at 10KB/connection
  - [ ] 5 instances behind ALB, 10K each, sticky sessions
  - [ ] Raise file descriptors to 65535+

## Practice Questions

1. Why do all major LLM providers use SSE? When would you choose WebSocket for an LLM app?
2. How does HTTP/2 change the SSE vs WebSocket decision for streaming?
3. Design a FastAPI SSE endpoint with proper cleanup on client disconnect.
4. How do you implement backpressure in a streaming LLM pipeline?
5. Parse partial JSON from a streaming LLM generating structured output — walk through the approach.
6. Compare streaming APIs: OpenAI flat delta vs Anthropic event-based vs Gemini chunked response.
7. How does streaming work through a multi-agent pipeline? How do you propagate cancellation?
8. Tokens arrive in a single burst in production but stream fine locally — debug it.
9. Size infrastructure for 50K concurrent SSE connections. What are the bottlenecks?
10. Implement client-side streaming in React with proper cleanup on navigation.
11. Design a reconnection strategy for SSE chat that doesn't lose tokens.
12. What metrics do you monitor for streaming endpoints? What do you page on?
13. How do you stream tool call events through an agent pipeline to the client?

## Phase 9: System Design Bridge (2-3 min)
- [ ] Connect to Multi-Model Gateway:
  - [ ] Gateway routes streaming endpoints; proxy buffering config is a gateway concern
  - [ ] Circuit breakers for streaming failures (provider goes down mid-stream)
- [ ] Connect to LLM in Production:
  - [ ] TTFT and ITL are core serving metrics (prefill vs decode)
  - [ ] KV-cache management — cancel must free cache blocks
  - [ ] Continuous batching supports streaming workloads
- [ ] Connect to SLO & Error Budgets:
  - [ ] Streaming SLOs (TTFT p99, connection error rate) allocated from error budget
  - [ ] Burn rate alerts for streaming regressions
- [ ] Connect to Security:
  - [ ] Auth for SSE (query params vs fetch-event-source headers)
  - [ ] PII redaction before streaming to external providers
- [ ] Connect to Senior AI Engineer:
  - [ ] Async programming section covers asyncio, connection pooling, backpressure (cross-reference, not duplicate)
  - [ ] FastAPI async endpoints as the serving layer
- [ ] Connect to Capacity Planning:
  - [ ] Sizing for concurrent connections; file descriptor limits; memory per connection
- [ ] Connect to Performance Profiling:
  - [ ] Identifying buffering bottlenecks; measuring TTFT/TPS regressions

## Phase 10: Wrap-Up & Synthesis (1-2 min)
- [ ] Summarize the 10 core competencies covered
- [ ] Key takeaway: SSE is the right default for LLM streaming; WebSocket only when bidirectional is required
- [ ] Production reality: proxy buffering is the #1 streaming failure; backpressure prevents OOM; cancel must free KV-cache
- [ ] Metrics matter: TTFT p99, TPS, concurrent streams, abort rate, inter-token gap
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
