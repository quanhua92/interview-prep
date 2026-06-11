# Streaming Architecture for LLM Applications

Sources:
- [SSE vs WebSockets vs Polling: 2026 Decision Guide (FlowVerify)](https://www.flowverify.co/blog/sse-websockets-polling-guide-2026)
- [Streaming AI Responses with WebSockets, SSE, and gRPC (Pranav Prakash)](https://medium.com/@pranavprakash4777/streaming-ai-responses-with-websockets-sse-and-grpc-which-one-wins-a481cab403d3)
- [Streaming for LLM Apps: SSE vs WebSockets (Hivenet)](https://www.hivenet.com/post/llm-streaming-sse-websockets)
- [OpenAI Agents SDK — Streaming](https://openai.github.io/openai-agents-python/streaming/)
- [LangChain Streaming Docs](https://docs.langchain.com/oss/python/langchain/streaming)
- [AI SDK — Stopping Streams (Vercel)](https://ai-sdk.dev/docs/advanced/stopping-streams)
- [FastAPI Server-Sent Events for LLM Streaming (Medium)](https://medium.com/@2nick2patel2/fastapi-server-sent-events-for-llm-streaming-smooth-tokens-low-latency-1b211c94cff5)
- [Revisable by Design: A Theory of Streaming LLM Agent Architectures (arXiv)](https://arxiv.org/html/2604.23283v1)
- [WebSockets vs Server-Sent Events (GetStream.io)](https://getstream.io/blog/websocket-sse/)
- [WebSockets vs Server-Sent Events (Ably)](https://ably.com/blog/websockets-vs-sse)
- [OpenAI Chat Completions API — Streaming](https://platform.openai.com/docs/api-reference/chat/create)
- [Anthropic Messages API — Streaming](https://docs.anthropic.com/en/api/messages-streaming)
- [Google Gemini API — Streaming](https://ai.google.dev/api/generate-content#method:-models.generatecontent.stream)
- [FastAPI StreamingResponse Documentation](https://fastapi.tiangolo.com/advanced/custom-response/#streamingresponse)
- [ijson — Iterative JSON Parser](https://pypi.org/project/ijson/)
- [json-stream — Streaming JSON Parser](https://pypi.org/project/json-stream/)

## One-Liner
Production LLM streaming transforms a multi-second wait into real-time token delivery — requiring mastery of transport protocols (SSE, WebSocket, HTTP/2 chunked), async iteration patterns, backpressure management, partial JSON parsing, streaming orchestration through agent chains, and operational concerns like connection limits, timeouts, reconnection, and load-balancing stateful connections.

## Core Competencies Table

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| SSE (Server-Sent Events) | Protocol details, implementation in Python/FastAPI and JavaScript/EventSource, reconnection with Last-Event-ID, proxy compatibility, Content-Type headers, when SSE is the right default | Implement a production SSE endpoint in FastAPI; explain why all major LLM providers chose SSE; handle reconnection and event IDs |
| WebSocket | Full-duplex communication, connection lifecycle, ping/pong heartbeat, message framing, when to use vs SSE for LLM apps, stateful connection management | Decide SSE vs WebSocket for a given LLM feature; implement a WebSocket endpoint with heartbeat and backpressure; handle connection cleanup |
| HTTP/2 and HTTP/3 Streaming | Chunked transfer encoding, stream multiplexing, connection coalescing under HTTP/2, QUIC-based HTTP/3 streaming, WebTransport | Explain how HTTP/2 eliminates SSE connection limits; describe when HTTP/3/WebTransport matters for LLM streaming |
| LLM Token Streaming | Provider streaming APIs (OpenAI, Anthropic, Gemini), delta format, chunk structure, usage reporting in final chunk, abort/cancel semantics | Parse streaming responses from all three major providers; implement abort/cancel with proper resource cleanup; extract usage metadata |
| Async Iterators in Python | `async for`, async generators with `yield`, `AsyncIterator` protocol, converting sync to async, async context managers for streaming resources | Write production async generators that wrap LLM streaming APIs; implement proper cleanup with `try/finally` and async context managers |
| Backpressure Management | Flow control mechanisms, semaphores for concurrency limiting, queue depth monitoring, buffered amount checking, graceful degradation under load | Design a backpressure-aware streaming pipeline; implement semaphore-based concurrency control; detect and handle slow consumers |
| Partial JSON Parsing | Incremental parsing of incomplete JSON, ijson and json-stream libraries, handling streaming object deltas, accumulating partial chunks | Parse partial JSON objects from streaming LLM structured output; use ijson for memory-efficient large JSON processing |
| Streaming Orchestration | Streaming through agent chains, tool call events mid-stream, cancel/abort propagation, speculative tool calling, multi-agent streaming coordination | Orchestrate streaming through a multi-step agent pipeline; propagate cancellation through tool calls; handle mid-stream tool execution events |
| Client-Side Streaming | Fetch ReadableStream API, EventSource, rendering tokens progressively, abort controller, reconnection strategies | Implement client-side streaming consumption in both vanilla JS and React; handle abort, reconnection, and progressive rendering |
| Production Considerations | Connection limits per server/instance, idle timeouts, keep-alive configuration, load balancing stateful connections, monitoring streaming metrics (TTFT, TPS) | Size infrastructure for streaming workloads; configure load balancers for long-lived SSE connections; set alerting on streaming SLOs |

## 1. SSE (Server-Sent Events)

### Protocol Overview

SSE is a one-way server-to-client streaming protocol built on HTTP. The server keeps the response open indefinitely, pushing data frames formatted as:
```
data: <payload>\n\n
```

Each event can include:
- `id:` — unique event ID for reconnection replay
- `event:` — event type name (defaults to "message")
- `data:` — payload (one per line; multiple `data:` lines are concatenated with `\n`)
- `retry:` — reconnection interval in milliseconds

The browser's native `EventSource` API handles reconnection automatically and sends a `Last-Event-ID` header when reconnecting, allowing the server to resume from the last received event.

### Required Headers

```http
Content-Type: text/event-stream
Cache-Control: no-cache, no-store
Connection: keep-alive
X-Accel-Buffering: no    # Nginx: disable proxy buffering
```

### Why All Major LLM Providers Chose SSE

Every major LLM provider (OpenAI, Anthropic, Google Gemini, Mistral, Cohere) exposes streaming via SSE. Reasons:

1. **One-way data flow matches LLM generation** — tokens flow server-to-client; the client's only input is the initial request. Bidirectional capacity adds no value during generation.
2. **HTTP compatibility** — SSE runs over standard HTTP. No upgrade handshake, no special proxy support needed. Works through Nginx, Cloudflare, AWS ALB, and API gateways with minimal configuration.
3. **Built-in reconnection** — `EventSource` reconnects automatically with `Last-Event-ID`, providing at-least-once delivery semantics. WebSockets require custom reconnection logic.
4. **Simple mental model** — one request, one long response. Matches the LLM request/response pattern exactly.

### SSE Limitations

| Limitation | Impact | Workaround |
|-----------|--------|------------|
| GET-only with native EventSource | Cannot send request body or auth headers | Use `@microsoft/fetch-event-source` for POST + custom headers |
| HTTP/1.1 connection limit (6 per domain) | Caps concurrent SSE streams per origin | HTTP/2 eliminates this; multiplexing over single connection |
| Text-only (no binary) | Cannot stream binary data (images, audio) | WebSocket or HTTP/3 streams for binary payloads |
| No client-to-server mid-stream messaging | Cannot send interrupts, preferences mid-generation | WebSocket or separate POST endpoints for mid-stream control |

### FastAPI SSE Implementation

```python
from fastapi import FastAPI
from fastapi.responses import StreamingResponse
import asyncio

app = FastAPI()

async def stream_tokens(prompt: str):
    async for chunk in llm_client.stream(prompt):
        token = chunk.choices[0].delta.content or ""
        yield f"data: {json.dumps({'token': token})}\n\n"
    yield "data: [DONE]\n\n"

@app.get("/chat/stream")
async def chat_stream(prompt: str):
    return StreamingResponse(
        stream_tokens(prompt),
        media_type="text/event-stream",
        headers={
            "Cache-Control": "no-cache, no-store",
            "X-Accel-Buffering": "no",
        }
    )
```

### Client-Side EventSource

```javascript
const es = new EventSource('/chat/stream?prompt=hello');
es.onmessage = ({ data }) => {
  if (data === '[DONE]') { es.close(); return; }
  const { token } = JSON.parse(data);
  document.getElementById('output').textContent += token;
};
es.onerror = () => console.error('Connection dropped; auto-reconnecting...');
```

For POST requests with auth headers, use `@microsoft/fetch-event-source`:
```javascript
import { fetchEventSource } from '@microsoft/fetch-event-source';

fetchEventSource('/chat/stream', {
  method: 'POST',
  headers: { 'Authorization': `Bearer ${token}`, 'Content-Type': 'application/json' },
  body: JSON.stringify({ prompt: 'hello' }),
  onmessage({ data }) {
    if (data === '[DONE]') return;
    processToken(JSON.parse(data));
  }
});
```

## 2. WebSocket

### When to Use WebSocket vs SSE for LLM Apps

Use WebSocket when:
- The client must send a **continuous stream** to the server (e.g., real-time collaborative editing, voice input, live cursor tracking)
- Mid-generation **client-to-server control** is required (cancel, adjust parameters, provide feedback)
- **Binary data** must flow both directions (audio/video streaming with AI)
- **Multi-turn agent interaction** where the client sends new instructions mid-generation

Use SSE when:
- The interaction is a single request-response (chat completion, summarization, code generation)
- The client only sends one request and receives a streamed response
- Simple proxy infrastructure is preferred
- Standard LLM API patterns are sufficient

### Protocol Handshake

WebSocket begins as an HTTP request with an upgrade header:
```http
GET /ws HTTP/1.1
Host: example.com
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
Sec-WebSocket-Version: 13
```

Server responds with `101 Switching Protocols`, then the connection is a raw TCP socket (frame-based, not HTTP).

### Connection Lifecycle

| Phase | Detail |
|-------|--------|
| **Handshake** | HTTP upgrade → 101 Switching Protocols |
| **Open** | Full-duplex message exchange (text or binary frames) |
| **Ping/Pong** | Server sends Ping, client responds Pong (heartbeat, typically 30s interval) |
| **Close** | Close frame with status code; TCP FIN after acknowledged |

### FastAPI WebSocket Implementation

```python
from fastapi import FastAPI, WebSocket, WebSocketDisconnect
import asyncio, json

app = FastAPI()

@app.websocket("/ws/chat")
async def websocket_chat(websocket: WebSocket):
    await websocket.accept()
    try:
        while True:
            data = await websocket.receive_text()
            request = json.loads(data)
            async for chunk in llm_client.stream(request["prompt"]):
                token = chunk.choices[0].delta.content or ""
                if websocket.client_state.name == "CONNECTED":
                    await websocket.send_text(json.dumps({"token": token}))
                else:
                    break
            await websocket.send_text(json.dumps({"done": True}))
    except WebSocketDisconnect:
        pass
```

### Backpressure in WebSocket

WebSocket has `bufferedAmount` on the client side — bytes queued but not yet sent. On the server side (Python), use a bounded queue or semaphore:

```python
send_queue = asyncio.Queue(maxsize=100)

async def producer(websocket, prompt):
    async for chunk in llm_client.stream(prompt):
        if send_queue.full():
            await send_queue.put(None)  # signal slow consumer
            break
        await send_queue.put(chunk.choices[0].delta.content)
    await send_queue.put("[DONE]")

async def consumer(websocket):
    while True:
        item = await send_queue.get()
        if item is None or item == "[DONE]":
            break
        await websocket.send_text(json.dumps({"token": item}))
```

### WebSocket Connection Management in Production

| Concern | Pattern |
|---------|---------|
| **Heartbeat** | Server sends Ping every 30s; client Pongs. If no Pong in 60s, close connection |
| **Reconnection** | Exponential backoff starting at 1s, capped at 30s, with jitter. Send session ID on reconnect |
| **Stateful scaling** | Redis Pub/Sub for cross-instance message routing. Sticky sessions as simpler alternative |
| **Connection limits** | Per-instance: ~10K WebSocket connections. Per-process: memory-limited (~10-100KB per connection) |
| **Cleanup** | `try/finally` in handler; periodic sweep of zombie connections; `on_shutdown` hook for graceful drain |

### Operational Complexity

WebSockets require:
- Load balancers that support the HTTP upgrade handshake (AWS ALB, NGINX with `proxy_set_header Upgrade`, Cloudflare with WebSocket enabled)
- Sticky sessions or Redis Pub/Sub for horizontal scaling
- Custom heartbeat/reconnection logic
- Per-connection state management

This is significantly more operational overhead than SSE, which is why SSE remains the right default for most LLM streaming.

## 3. HTTP/2 and HTTP/3 Streaming

### HTTP/2 Stream Multiplexing

HTTP/2 multiplexes multiple streams over a single TCP connection. This has a direct impact on SSE:

| Aspect | HTTP/1.1 | HTTP/2 |
|--------|----------|--------|
| Concurrent SSE connections | 6 per domain (browser limit) | Unlimited (multiplexed) |
| Connection overhead | One TCP connection per SSE stream | Single TCP connection for all streams |
| Header compression | None | HPACK compression |
| Connection limits for streaming | Real bottleneck at 6 streams | Effectively eliminated |

**Practical impact**: On HTTP/2, a single page can open hundreds of SSE streams without hitting connection limits. This eliminates the primary SSE limitation from the HTTP/1.1 era.

Most web applications in 2026 run over HTTP/2 by default (enabled in all major browsers, CDNs, and web servers).

### HTTP/2 Server Push (Deprecated)

HTTP/2 Server Push was meant to proactively send resources before the client requests them. It has been deprecated in favor of `<link rel="preload">` and 103 Early Hints. Not relevant for LLM streaming.

### Chunked Transfer Encoding

HTTP streaming (including SSE) relies on chunked transfer encoding — the server sends data in chunks without specifying Content-Length upfront. The response is terminated by a zero-length chunk.

```
HTTP/2 200
content-type: text/event-stream

data: {"token": "Hello"}\n\n
data: {"token": " world"}\n\n
data: [DONE]\n\n
```

### HTTP/3 and QUIC

HTTP/3 runs over QUIC (UDP-based), offering:
- **No head-of-line blocking** — packet loss on one stream doesn't block others
- **Faster connection establishment** — 0-RTT and 1-RTT handshake (vs TCP 2-RTT)
- **Connection migration** — seamless when switching networks (mobile)

### WebTransport

WebTransport is the HTTP/3 successor to WebSockets:
- Bidirectional and unidirectional streams natively
- Support for unreliable datagrams (for gaming, real-time)
- Production-ready in Chrome and Edge as of 2025

**Current status**: Not yet a practical replacement for WebSockets across the full browser matrix. Track for 2027+. For most teams building today, SSE covers LLM streaming and WebSockets cover bidirectional needs.

## 4. LLM Token Streaming

### How Providers Stream

#### OpenAI Chat Completions (SSE)

```python
from openai import AsyncOpenAI

client = AsyncOpenAI()
stream = await client.chat.completions.create(
    model="gpt-4o",
    messages=[{"role": "user", "content": "Explain streaming"}],
    stream=True,
    stream_options={"include_usage": True},
)

async for chunk in stream:
    delta = chunk.choices[0].delta
    if delta.content:
        print(delta.content, end="")
    if chunk.usage:
        print(f"\nTokens: {chunk.usage}")
```

Chunk structure per SSE event:
```json
{
  "id": "chatcmpl-abc123",
  "object": "chat.completion.chunk",
  "choices": [{
    "index": 0,
    "delta": {
      "role": "assistant",
      "content": "Hello"
    },
    "finish_reason": null
  }]
}
```

Final chunk has `finish_reason: "stop"` (or `"length"`, `"content_filter"`, `"tool_calls"`) and optionally includes `usage` fields when `stream_options.include_usage` is set.

#### Anthropic Messages (SSE)

```python
import anthropic

client = anthropic.AsyncAnthropic()
async with client.messages.stream(
    model="claude-sonnet-4-20250514",
    max_tokens=1024,
    messages=[{"role": "user", "content": "Explain streaming"}],
) as stream:
    async for event in stream:
        if event.type == "content_block_delta":
            print(event.delta.text, end="")
```

Event types in order:
1. `message_start` — message metadata, model, usage
2. `content_block_start` — block index, type (text/tool_use)
3. `content_block_delta` — delta text or tool input JSON
4. `content_block_stop` — end of block
5. `message_delta` — stop_reason, usage (output tokens)
6. `message_stop` — stream complete

Anthropic's event-based structure is richer than OpenAI's flat delta format, enabling better client-side handling of tool calls and multi-block responses.

#### Google Gemini (SSE)

```python
import google.generativeai as genai

model = genai.GenerativeModel("gemini-2.5-pro")
response = model.generate_content(
    "Explain streaming",
    stream=True,
)
for chunk in response:
    print(chunk.text, end="")
```

Gemini streams `GenerateContentResponse` chunks, each containing partial text in `candidates[0].content.parts[0].text`.

### Streaming Key Metrics

| Metric | Definition | Target |
|--------|-----------|--------|
| **TTFT** (Time to First Token) | Latency from request to first generated token; dominated by prefill | < 1s interactive, < 5s batch |
| **TPS** (Tokens Per Second) | Throughput of token generation after first token | > 30 for interactive, > 100 for batch |
| **ITL** (Inter-Token Latency) | Time between consecutive tokens; 1/TPS | < 33ms for smooth UX |

### Abort/Cancel Semantics

All three providers support cancellation:
- **OpenAI**: Pass `signal` parameter (from `anyio.create_task_group` or `asyncio.CancelledError`) to `create()`
- **Anthropic**: The `async with client.messages.stream()` context manager handles cleanup on cancel
- **Google**: Cancel the async iteration or use `AbortController`-like patterns

**Critical**: Cancel must free server-side KV-cache blocks immediately. Inference engines (vLLM, TGI) release KV-cache on connection close.

## 5. Async Iterators in Python

### The Async Generator Pattern

Async generators are the foundation of LLM streaming in Python. An async generator function uses `yield` inside an `async def`:

```python
async def token_stream(prompt: str) -> AsyncIterator[str]:
    """Wraps an LLM provider's streaming API as an async generator."""
    stream = await client.chat.completions.create(
        model="gpt-4o",
        messages=[{"role": "user", "content": prompt}],
        stream=True,
    )
    try:
        async for chunk in stream:
            content = chunk.choices[0].delta.content
            if content:
                yield content
    finally:
        await stream.close() if hasattr(stream, 'close') else None
```

Consumed with `async for`:
```python
async for token in token_stream("Explain backpressure"):
    print(token, end="", flush=True)
```

### Composing Async Generators

Async generators compose naturally — one generator can consume another:

```python
async def stream_with_buffer(prompt: str, buffer_size: int = 5) -> AsyncIterator[str]:
    """Accumulates tokens into chunks of buffer_size before yielding."""
    buffer = []
    async for token in token_stream(prompt):
        buffer.append(token)
        if len(buffer) >= buffer_size:
            yield "".join(buffer)
            buffer.clear()
    if buffer:
        yield "".join(buffer)
```

### Converting Multiple Streams

`asyncio.gather` for parallel streams, merging with `asyncio.Queue`:

```python
async def merge_streams(*streams: AsyncIterator[str]) -> AsyncIterator[str]:
    queue = asyncio.Queue()
    async def producer(stream):
        async for item in stream:
            await queue.put(item)
        await queue.put(None)
    tasks = [asyncio.create_task(producer(s)) for s in streams]
    finished = 0
    while finished < len(streams):
        item = await queue.get()
        if item is None:
            finished += 1
        else:
            yield item
    for t in tasks:
        t.cancel()
```

### Async Context Managers for Streaming Resources

```python
from contextlib import asynccontextmanager

@asynccontextmanager
async def llm_stream_session(prompt: str):
    stream = await client.chat.completions.create(
        model="gpt-4o",
        messages=[{"role": "user", "content": prompt}],
        stream=True,
    )
    try:
        yield stream
    finally:
        if hasattr(stream, 'close'):
            await stream.close()
```

### Common Pitfalls

| Pitfall | Consequence | Fix |
|---------|-------------|-----|
| Blocking the event loop with sync I/O inside async generator | All concurrent streams stall | Use `asyncio.to_thread()` for sync operations |
| Not closing the underlying stream on exception | Resource leak; connection stays open | `try/finally` in every async generator |
| Using `asyncio.sleep(0)` to "yield" | Fragile, doesn't actually guarantee fairness | Use proper `await` on real I/O operations |
| Forgetting `flush=True` on print | Tokens appear in bursts, not incrementally | Always flush when writing streamed output |

## 6. Backpressure Management

### The Problem

When the LLM produces tokens faster than the client can consume them (network congestion, slow rendering, downstream processing), buffers grow unbounded. Without backpressure, this leads to:
- Memory exhaustion on the server
- Dropped connections
- Increased latency for all concurrent requests

### Mechanisms

#### Semaphores for Concurrency Limiting

```python
MAX_CONCURRENT_STREAMS = 50
stream_semaphore = asyncio.Semaphore(MAX_CONCURRENT_STREAMS)

async def stream_handler(prompt: str):
    async with stream_semaphore:
        async for token in llm_client.stream(prompt):
            yield token
```

Rejects requests beyond the limit with HTTP 429 or 503:
```python
async def stream_endpoint(prompt: str):
    if stream_semaphore.locked() and stream_semaphore._value == 0:
        raise HTTPException(status_code=429, detail="Too many concurrent streams")
    return StreamingResponse(stream_handler(prompt), media_type="text/event-stream")
```

#### Queue Depth Monitoring

```python
WRITE_BUFFER_SIZE = 1000

async def backpressure_aware_stream(prompt: str) -> AsyncIterator[str]:
    queue = asyncio.Queue(maxsize=WRITE_BUFFER_SIZE)
    done = asyncio.Event()

    async def producer():
        try:
            async for token in llm_client.stream(prompt):
                if done.is_set():
                    break
                if queue.full():
                    done.set()
                    break
                await queue.put(token)
        finally:
            await queue.put(None)

    producer_task = asyncio.create_task(producer())
    try:
        while True:
            token = await asyncio.wait_for(queue.get(), timeout=30.0)
            if token is None:
                break
            yield token
    except asyncio.TimeoutError:
        pass
    finally:
        done.set()
        producer_task.cancel()
```

#### Client-Side Backpressure (WebSocket)

```javascript
// Check bufferedAmount before sending
if (ws.bufferedAmount > MAX_BUFFER) {
    await new Promise(resolve => {
        const check = () => {
            if (ws.bufferedAmount <= MAX_BUFFER) resolve();
            else setTimeout(check, 100);
        };
        check();
    });
}
```

#### Graceful Degradation Levels

| Level | Condition | Action |
|-------|-----------|--------|
| **Normal** | Queue depth < 50% capacity | Stream tokens normally |
| **Throttled** | Queue depth 50-80% | Batch tokens into larger chunks, reduce TPS |
| **Backpressured** | Queue depth > 80% | Pause production, drain queue, resume |
| **Rejected** | Semaphore at 0 | Return 429 with retry-after header |

### When to Drop vs Queue

- **Drop requests** when: the system is at capacity and latency would exceed SLAs. Better to fail fast than queue requests that will time out.
- **Queue requests** when: brief bursts are expected and the system has headroom to catch up within the timeout window.
- **Never queue indefinitely**: always set a maximum wait time (e.g., 30s) before rejecting.

## 7. Partial JSON Parsing

### The Problem

When LLMs generate structured output (tool calls, JSON objects) via streaming, the client receives partial JSON that is syntactically incomplete. For example:
```
{"name": "John
```
is not valid JSON and will fail `json.loads()`.

### Use Cases

1. **Streaming tool call arguments** — LLM generates tool invocation as JSON; client needs to show partial progress
2. **Streaming structured responses** — LLM generates a JSON response that should be rendered progressively
3. **Incrementally building large JSON** — Avoid holding entire document in memory

### Libraries

#### ijson — Iterative JSON Parser

```python
import ijson

# Parse a large JSON file without loading it all into memory
with open("large.json", "rb") as f:
    objects = ijson.items(f, "records.item")
    for obj in objects:
        process(obj)
```

ijson yields Python objects as it encounters complete items. For streaming LLM output, accumulate chunks into a buffer and parse incrementally:

```python
import ijson

async def parse_streaming_json(token_stream: AsyncIterator[str]) -> AsyncIterator[dict]:
    buffer = ""
    async for token in token_stream:
        buffer += token
        try:
            # Try to extract complete objects from the buffer
            for item in ijson.items(iter([buffer.encode()]), "item"):
                yield item
                buffer = ""  # Reset after successful parse
        except ijson.JSONError:
            continue  # Incomplete JSON, wait for more tokens
```

#### json-stream — Token-Level Streaming JSON

```python
from json_stream import load

async def parse_json_tokens(token_stream: AsyncIterator[str]):
    buffer = ""
    async for token in token_stream:
        buffer += token
        try:
            data = load(iter([buffer]))
            # Access fields as they become available
            if data.name:  # transient access
                yield {"name": str(data.name)}
            if data.age:
                yield {"age": int(data.age)}
        except Exception:
            continue
```

### Practical Pattern: Accumulate and Parse

The most common production pattern for LLM streaming JSON:

```python
async def stream_json_response(prompt: str) -> AsyncIterator[str]:
    json_buffer = ""
    async for token in llm_client.stream(prompt):
        json_buffer += token
        yield token  # Forward raw tokens to client
    # After stream completes, validate the full JSON
    try:
        json.loads(json_buffer)
        yield "data: {\"valid\": true}\n\n"
    except json.JSONDecodeError as e:
        yield f"data: {{\"valid\": false, \"error\": \"{str(e)}\"}}\n\n"
```

### Handling Incomplete JSON on Disconnect

When a stream is interrupted mid-JSON:
1. Log the partial buffer with a unique request ID for debugging
2. Return an error event to the client: `data: {"error": "stream_interrupted", "partial": true}\n\n`
3. If the client reconnects (SSE with Last-Event-ID), restart the generation from the last complete checkpoint

### Tool Call Streaming

For LLMs that stream tool call arguments as JSON, the OpenAI SDK handles this:

```python
async for chunk in stream:
    delta = chunk.choices[0].delta
    if delta.tool_calls:
        for tc in delta.tool_calls:
            # tc.function.arguments is partial JSON string
            print(f"Tool {tc.id}: {tc.function.arguments}", end="")
```

Accumulate `tc.function.arguments` across chunks, then parse the complete JSON when `finish_reason: "tool_calls"` is received.

## 8. Streaming Orchestration

### Streaming Through Agent Chains

In multi-step agent pipelines, each step produces a stream that feeds the next:

```python
async def orchestrator_stream(prompt: str) -> AsyncIterator[str]:
    # Step 1: Router LLM decides which agent to use
    router_output = ""
    async for token in llm_client.stream(router_prompt(prompt)):
        router_output += token
        yield f"data: {json.dumps({'step': 'routing', 'token': token})}\n\n"

    agent = parse_agent_selection(router_output)

    # Step 2: Agent LLM generates response
    async for token in llm_client.stream(agent_prompt(agent, prompt)):
        yield f"data: {json.dumps({'step': 'generation', 'token': token})}\n\n"
```

### Tool Calls Mid-Stream

Frameworks like OpenAI Agents SDK, LangGraph, and Vercel AI SDK emit events for tool calls within a stream:

| Framework | Event Types |
|-----------|------------|
| **OpenAI Agents SDK** | `raw_response_event`, `response_created`, `response_output_item_added`, `tool_called`, `tool_output_delta`, `response_completed` |
| **LangChain** | `on_chat_model_stream` (tokens), `on_tool_start`, `on_tool_end` (tool events) |
| **Vercel AI SDK** | `text-delta`, `tool-call`, `tool-result`, `step-finish`, `finish` |

Example with OpenAI Agents SDK:
```python
from agents import Agent, Runner, handoff

async def stream_agent_run():
    result = Runner.run_streamed(agent, messages)
    async for event in result.stream_events():
        if event.type == "response_output_item_added":
            if hasattr(event.item, 'content'):
                print(event.item.content, end="")
        elif event.type == "tool_called":
            print(f"\n[Calling tool: {event.name}]")
        elif event.type == "tool_output_delta":
            print(event.delta, end="")

    # Cancel mid-stream:
    # result.cancel()
```

### Cancel/Abort Propagation

Cancellation must propagate through the entire chain:
1. **Client sends abort** (closes SSE connection or calls `AbortController.abort()`)
2. **Server detects disconnect** (FastAPI: `request.is_disconnected()` in streaming loop)
3. **Upstream cancellation** — cancel the LLM API call, free KV-cache, cancel pending tool executions
4. **Resource cleanup** — close connections, release semaphores, log partial output

```python
@app.get("/stream")
async def stream(request: Request, prompt: str):
    async def generate():
        try:
            async for token in llm_client.stream(prompt):
                if await request.is_disconnected():
                    break
                yield f"data: {json.dumps({'token': token})}\n\n"
        except asyncio.CancelledError:
            pass
        finally:
            pass

    return StreamingResponse(generate(), media_type="text/event-stream")
```

### Speculative Tool Calling

GetStream.io describes speculative tool calling for voice AI: parse the LLM output stream for tool call tokens (detecting `{"name": "search", "arguments":` in the stream) and fire the tool call before the full arguments are complete. Shaves latency when tool calls are predictable but risks wasted execution on incorrect predictions.

### Multi-Agent Streaming Coordination

When multiple agents run in parallel and stream results:

```python
async def multi_agent_stream(prompt: str) -> AsyncIterator[str]:
    tasks = [
        asyncio.create_task(run_agent("researcher", prompt)),
        asyncio.create_task(run_agent("critic", prompt)),
        asyncio.create_task(run_agent("synthesizer", prompt)),
    ]
    queue = asyncio.Queue()
    for task in tasks:
        task.add_done_callback(lambda t: queue.put(t.result()))

    # Yield results as they complete
    for coro in asyncio.as_completed(tasks):
        result = await coro
        yield f"data: {json.dumps({'agent': result.agent, 'output': result.text})}\n\n"
```

## 9. Client-Side Streaming

### Fetch ReadableStream API (Vanilla JS)

The most flexible client-side streaming approach — works with any HTTP method, any headers:

```javascript
const response = await fetch('/chat/stream', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json', 'Authorization': `Bearer ${token}` },
  body: JSON.stringify({ prompt: 'Explain streaming' }),
  signal: abortController.signal,
});

const reader = response.body.getReader();
const decoder = new TextDecoder();
let buffer = '';

while (true) {
  const { done, value } = await reader.read();
  if (done) break;
  buffer += decoder.decode(value, { stream: true });

  // Parse SSE lines from buffer
  const lines = buffer.split('\n\n');
  buffer = lines.pop(); // Keep incomplete line in buffer
  for (const line of lines) {
    if (line.startsWith('data: ')) {
      const data = line.slice(6);
      if (data === '[DONE]') break;
      const { token } = JSON.parse(data);
      appendToOutput(token);
    }
  }
}
```

### EventSource API (Simplified SSE)

```javascript
const es = new EventSource('/chat/stream?prompt=hello');
es.addEventListener('token', (e) => appendToOutput(e.data));
es.addEventListener('done', () => es.close());
es.onerror = () => console.log('Reconnecting...');
```

### React Integration with AI SDK (Vercel)

```typescript
import { useChat } from 'ai/react';

function ChatComponent() {
  const { messages, input, handleInputChange, handleSubmit, isLoading, stop } = useChat();

  return (
    <div>
      {messages.map(m => (
        <div key={m.id}>{m.role}: {m.content}</div>
      ))}
      <form onSubmit={handleSubmit}>
        <input value={input} onChange={handleInputChange} />
        <button type="submit">Send</button>
        {isLoading && <button type="button" onClick={stop}>Stop</button>}
      </form>
    </div>
  );
}
```

### Progressive Rendering Tips

| Technique | Effect |
|-----------|--------|
| Show tokens as they arrive with a blinking caret | Users perceive generation as instant |
| Keep partial markdown live-rendered (react-markdown) | Code blocks, lists, and headers render incrementally |
| Close unclosed code fences on stream end | Prevents broken formatting on abrupt disconnect |
| Debounce re-renders for fast streams (>50 TPS) | Prevents excessive DOM updates |
| Let users copy partial output | Essential UX — users want to use partial results |

### Reconnection Strategies

For SSE (automatic with EventSource):
```javascript
const es = new EventSource('/stream');
// EventSource reconnects automatically with exponential backoff
// Override reconnect interval:
es.onerror = () => {
  console.log('Reconnecting...');
  // EventSource handles retry automatically
};
```

For fetch-based streaming:
```javascript
async function resilientStream(url, options, maxRetries = 3) {
  let lastEventId = null;
  for (let attempt = 0; attempt < maxRetries; attempt++) {
    try {
      const response = await fetch(url, {
        ...options,
        headers: { ...options.headers, ...(lastEventId && { 'Last-Event-ID': lastEventId }) },
      });
      // ... process stream, capture last event ID
      return; // Success
    } catch (err) {
      if (attempt === maxRetries - 1) throw err;
      await new Promise(r => setTimeout(r, 1000 * 2 ** attempt));
    }
  }
}
```

## 10. Production Considerations

### Connection Limits

| Layer | Limit | Notes |
|-------|-------|-------|
| **Single server process** | ~10K concurrent SSE connections | Memory-limited (~10-100KB per connection) |
| **Nginx reverse proxy** | `worker_connections` (default 1024) | Tune: `worker_connections 10000; worker_processes auto;` |
| **AWS ALB** | No fixed limit on idle connections | 1M+ connections per ALB, 60s default idle timeout (configurable to 4000s) |
| **Cloudflare** | 100 concurrent connections per free plan | Enterprise: no limit; use `CF-Connecting-IP` for real client IP |
| **Browser (HTTP/1.1)** | 6 per domain | Eliminated under HTTP/2 multiplexing |

### Timeout Configuration

| Timeout | Default | Recommended for LLM Streaming |
|---------|---------|------------------------------|
| **Nginx proxy_read_timeout** | 60s | 300s (long generations can take minutes) |
| **AWS ALB idle timeout** | 60s | 300s for streaming endpoints |
| **FastAPI/uvicorn worker timeout** | 300s | 300-600s for agent pipelines |
| **Client-side fetch timeout** | None | Set explicit abort timeout (e.g., 120s) |
| **Keep-alive (server)** | 75s | Match proxy timeout; enable TCP keepalive |
| **Inter-token timeout (server)** | N/A | 15-30s (if no token in 30s, check if LLM is stuck) |

### Load Balancing Stateful Connections

SSE and WebSocket connections are long-lived, making load balancing different from stateless HTTP:

**Approaches:**

| Approach | Pros | Cons |
|----------|------|------|
| **Sticky sessions (IP hash, cookie)** | Simple; state stays on one server | Imbalanced distribution; server failure drops connections |
| **Redis Pub/Sub** | Any server can produce events; connections balanced | Extra latency per event (~1ms); Redis as dependency |
| **Connection draining on deploy** | Graceful shutdown; no dropped connections | Slower deploys; requires coordination |
| **Peer-to-peer (gossip)** | No central dependency | Complex; eventual consistency issues |

For most LLM streaming, **sticky sessions are sufficient** — the state is the SSE stream itself, not shared application state. If the server dies, the client reconnects (SSE with Last-Event-ID) and hits a different server.

### Monitoring Streaming SLOs

Key metrics to monitor:

| Metric | Instrumentation | Alert Threshold |
|--------|---------------|-----------------|
| **TTFT p99** | Timestamp on first SSE event vs request received | > 2x baseline for 15 min |
| **TPS (tokens/sec) average** | Token count / generation duration | < 50% of baseline for 10 min |
| **Active concurrent streams** | Gauge counting open SSE connections | > 80% of max_connections |
| **Stream abort rate** | Counter: streams closed before `[DONE]` | > 20% (indicates UX or latency issue) |
| **Connection error rate** | Counter: SSE/WS connection failures | > 1% |
| **Inter-token gap p99** | Max time between consecutive tokens | > 10s (likely stuck generation) |
| **Queue depth (backpressure)** | Gauge: items in write buffer | > 80% capacity |
| **Rejected requests (429)** | Counter: requests rejected due to semaphore | > 0 sustained |

### Proxy Buffering Pitfalls

**The #1 streaming failure in production**: a proxy buffering the response and sending it as a single chunk.

| Proxy | Anti-Buffering Config |
|-------|----------------------|
| **Nginx** | `proxy_buffering off;` or `X-Accel-Buffering: no;` header |
| **AWS ALB** | No buffering by default for streaming responses |
| **Cloudflare** | Enterprise plan with streaming bypass; or `CF-Workers` bypass |
| **Kong** | `proxy_buffering off` in service/route config |
| **HAProxy** | `option http-no-delay` |

If tokens arrive in a single burst, check for buffering intermediary first.

### Infrastructure Sizing

For 10K concurrent SSE connections per instance:
- **Memory**: ~10KB per connection = ~100MB for 10K connections (manageable)
- **CPU**: Minimal — async I/O, not compute-heavy
- **File descriptors**: 10K connections = 10K open FDs; raise `ulimit -n` to 65535+
- **Event loop capacity**: Single-threaded async can handle 10K+ connections easily

WebSocket connections cost more (~50-100KB each for frame buffers) but are still manageable on a single instance.

## Interview Questions

1. **Why do all major LLM providers use SSE for streaming instead of WebSockets? What would make you choose WebSocket for an LLM application?**

   SSE is one-way over HTTP, matching the LLM generation pattern (single request, streamed response). It requires no upgrade handshake, works through all proxies, and has built-in reconnection. WebSockets add bidirectional communication and binary support that most LLM streaming doesn't need. Choose WebSocket when: the client sends continuous data mid-generation (voice input, collaborative editing), binary streaming is needed, or the interaction requires mid-stream client-to-server control (cancel via protocol vs HTTP abort).

2. **How does HTTP/2 change the SSE vs WebSocket decision?**

   HTTP/2 multiplexes multiple streams over a single TCP connection, eliminating the HTTP/1.1 limit of 6 concurrent connections per domain. This removes SSE's primary historical limitation. Under HTTP/2, SSE can support hundreds of concurrent streams without connection exhaustion, making it even harder to justify WebSocket's added complexity for one-way streaming.

3. **Design a FastAPI endpoint that streams LLM responses via SSE, including proper cleanup on client disconnect.**

   Use `StreamingResponse` with an async generator. Inside the generator, check `await request.is_disconnected()` each iteration to detect client disconnect and break early. Set `X-Accel-Buffering: no` header to prevent Nginx buffering. Use `try/finally` to clean up the LLM stream on exit (close the underlying HTTP connection to the provider). Return `[DONE]` event when generation completes successfully.

4. **How do you implement backpressure in a streaming LLM pipeline? What happens when the client is slower than the LLM?**

   Use an `asyncio.Queue(maxsize=N)` between the producer (LLM) and consumer (client). When the queue is full, the producer blocks (or pauses generation). Alternatively, use `asyncio.Semaphore` to limit concurrent streams at the server level. On the client side (WebSocket), check `bufferedAmount` before sending. If backpressure persists, escalate: throttle token production → pause generation → reject new requests with 429.

5. **How do you parse partial JSON from a streaming LLM that's generating structured output?**

   Accumulate tokens in a string buffer. After stream completion, validate the full JSON with `json.loads()`. For incremental parsing, use `ijson` to yield complete items as they become available in the buffer. For tool call arguments, accumulate the `function.arguments` field across streaming chunks and parse when `finish_reason: "tool_calls"` signals completion. Never try to parse mid-stream partial JSON with `json.loads()` — it will raise `JSONDecodeError`.

6. **Explain how streaming works through a multi-agent pipeline. How do you propagate cancellation?**

   Each agent step is an async generator that yields tokens/events. The orchestrator composes these generators — yielding routing events, then agent events. For tool calls, frameworks emit `tool_called` and `tool_result` events mid-stream. Cancellation propagates by: (1) detecting client disconnect (`request.is_disconnected()`), (2) cancelling the current async task, (3) the LLM SDK closes the HTTP connection on cancel, freeing KV-cache, (4) any pending tool executions are cancelled, (5) semaphores/queues are released in `finally` blocks.

7. **What metrics do you monitor for streaming LLM endpoints? What do you alert on?**

   Monitor: TTFT p99 (alert >2x baseline), TPS average (alert <50% baseline), active concurrent streams (alert >80% capacity), stream abort rate (alert >20%), connection error rate (alert >1%), inter-token gap p99 (alert >10s), queue depth for backpressure (alert >80%), and rejected requests (alert >0 sustained). Page on TTFT regression and connection error spikes. Dashboard everything else.

8. **Your streaming endpoint works locally but tokens arrive in a single burst in production. Walk through debugging.**

   This is proxy buffering. Check each layer: Nginx (`proxy_buffering off`), Cloudflare (enterprise streaming bypass), API gateway (response buffering setting), and Kubernetes Ingress (disable buffering). Verify `X-Accel-Buffering: no` is set in response headers. Also check if gzip compression is enabled — it buffers the response to compress. Disable compression for `text/event-stream`. Test with `curl -N` (no buffering) to isolate whether the issue is server-side or proxy-side.

9. **Compare the streaming APIs of OpenAI, Anthropic, and Google Gemini. What are the key differences?**

   OpenAI uses flat delta chunks with `choices[0].delta.content`. Optional `stream_options.include_usage` for token counts in final chunk. Anthropic uses an event-based model: `message_start`, `content_block_start`, `content_block_delta` (with text or tool input), `content_block_stop`, `message_delta`, `message_stop`. This provides richer structure for tool calls. Gemini streams `GenerateContentResponse` chunks with partial text in `candidates[0].content.parts[0].text`. All use SSE transport. OpenAI and Anthropic support abort signals; Gemini uses cancellation tokens.

10. **How do you size infrastructure for 50K concurrent SSE connections? What are the bottlenecks?**

    At ~10KB per connection: 50K connections = ~500MB memory (manageable). Bottlenecks are: (1) file descriptors — need `ulimit -n 65535+`, (2) reverse proxy — Nginx needs `worker_connections 50000+` and `worker_processes auto`, (3) load balancer idle timeout — AWS ALB default 60s, must extend to 300s+, (4) connection rate during spikes — need connection draining for graceful deploy. Architecture: 5 instances behind ALB, each handling 10K connections, with sticky sessions for SSE. Redis Pub/Sub not needed unless cross-instance events are required.

11. **How would you implement client-side streaming in React? What happens when the user navigates away mid-stream?**

    Use Vercel AI SDK `useChat` hook which handles streaming, abort, and cleanup automatically. The hook calls `AbortController.abort()` on component unmount, closing the SSE/fetch connection. Server detects disconnect via `request.is_disconnected()` and stops generation. For vanilla React, use `useEffect` cleanup to abort the fetch, and manage state accumulation in a ref (not state, to avoid re-render per token). Debounce renders for fast streams (>50 TPS) to prevent excessive DOM updates.

12. **Design the reconnection strategy for an SSE-based LLM chat that must not lose tokens on reconnect.**

    Use `Last-Event-ID` — the server assigns sequential event IDs (`id: 1`, `id: 2`, ...) to each SSE event. On reconnect, the browser sends the last received ID. The server replays from the next event. For tokens, store the complete text up to the last acknowledged event in a server-side buffer keyed by session ID. On reconnect, resume generation from the buffer state. Use Redis with TTL for the buffer. If the buffer expires or generation already completed, send the complete response. Client-side: accumulate tokens locally; on reconnect, send the accumulated length so the server can skip ahead.

## Key Terminology

**SSE (Server-Sent Events)** -- One-way server-to-client streaming protocol over HTTP. Data formatted as `data: <payload>\n\n` with optional `id:`, `event:`, and `retry:` fields. Browser `EventSource` API provides automatic reconnection with `Last-Event-ID`. Used by all major LLM providers (OpenAI, Anthropic, Gemini) for token streaming.

**WebSocket** -- Full-duplex communication protocol starting with HTTP upgrade to raw TCP. Supports bidirectional text and binary frames. Requires heartbeat (ping/pong), custom reconnection logic, and WebSocket-aware load balancers. Use for LLM apps only when client-to-server mid-stream communication is required.

**HTTP/2 Stream Multiplexing** -- Multiple HTTP request/response pairs multiplexed over a single TCP connection. Eliminates the HTTP/1.1 limit of 6 concurrent connections per domain, removing SSE's primary historical limitation. HPACK header compression reduces overhead per stream.

**TTFT (Time to First Token)** -- Latency from request submission to receipt of the first generated token. Dominated by prefill (processing all input tokens). Primary user-perceived latency metric for streaming LLM. Target: < 1s for interactive, < 5s for batch.

**TPS (Tokens Per Second)** -- Rate of token generation after the first token. Inverse of inter-token latency. Target: > 30 for interactive UX, > 100 for batch. Governed by memory bandwidth of the inference hardware (model_size / memory_bandwidth).

**Backpressure** -- Flow control mechanism preventing a fast producer (LLM) from overwhelming a slow consumer (client/network). Implemented via bounded queues, semaphores, and buffered amount monitoring. Without backpressure, unbounded buffer growth leads to memory exhaustion and dropped connections.

**Async Generator** -- Python function defined with `async def` containing `yield` statements. Produces values lazily via the `AsyncIterator` protocol, consumed with `async for`. Foundation pattern for wrapping LLM streaming APIs in composable, cancellable pipelines.

**Partial JSON Parsing** -- Incrementally parsing JSON from an incomplete byte/string stream using libraries like `ijson` (event-based SAX-style parsing) or by accumulating a buffer and parsing only when syntactically complete. Required for streaming LLM structured output and tool call arguments.

**Delta Format** -- The encoding used by LLM providers for streaming chunks. OpenAI sends `choices[0].delta.content` (incremental text), Anthropic sends event types (`content_block_delta` with `delta.text`), Gemini sends partial text in `candidates[0].content.parts[0].text`. All delta formats include a completion signal (finish_reason, message_stop).

**Speculative Tool Calling** -- Firing tool execution before the LLM finishes generating complete tool arguments, based on detecting tool call patterns in the output stream. Trades correctness for latency reduction. Must handle misprediction by cancelling or ignoring wasted tool executions.

**Connection Draining** -- Gracefully closing long-lived connections (SSE, WebSocket) during deployment by stopping new connections on the draining instance while allowing existing connections to complete or finish within a timeout window.

**WebTransport** -- HTTP/3-based API for bidirectional and unidirectional streams with unreliable datagram support. Successor to WebSockets. Production-ready in Chrome/Edge as of 2025. Not yet widely supported enough to replace WebSockets for production LLM applications.

## Cross-References

- **production_engineering/multi_model_gateway** — Gateway as the routing layer for streaming endpoints; proxy buffering configuration; circuit breakers for streaming failures
- **production_engineering/llm_in_production** — TTFT and ITL as core LLM serving metrics; KV-cache management; continuous batching; model sizing math
- **production_engineering/slo_error_budgets** — Streaming SLOs (TTFT p99, connection error rate) as part of error budget allocation; burn rate alerts for streaming regressions
- **production_engineering/security** — PII redaction before streaming to external providers; authentication for SSE endpoints (query params vs fetch-event-source)
- **role_specific/senior_ai_engineer** — Async Programming for AI Systems (asyncio, concurrent LLM calls, streaming responses, backpressure management, connection pooling); FastAPI async endpoints; observability span kinds for streaming traces
- **system_design/notification_service** — Event-driven architecture patterns (pub/sub for WebSocket scaling); connection management patterns shared with streaming
- **cs_fundamentals/computer_networking** — HTTP/2 multiplexing, TCP connection management, event-driven I/O, WebSocket protocol internals
- **production_engineering/capacity_planning** — Sizing for concurrent connections; file descriptor limits; memory per connection
- **production_engineering/performance_profiling** — Profiling streaming endpoints; identifying buffering bottlenecks; measuring TTFT and TPS regressions
