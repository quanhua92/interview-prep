# Senior Rust Developer -- Network, Security & High Performance Systems

Building secure, high-throughput network infrastructure in Rust: TLS termination, HTTP proxying, streaming data pipelines, and observability systems.

## Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Rust Language Mastery | Ownership, lifetimes, async/await, traits, macros, unsafe | Write zero-copy parsers, design trait-based abstractions, reason about Send/Sync |
| TLS/PKI & Crypto | TLS 1.2/1.3, rustls, PKI, Root CA, PEM, certificate chains | Explain TLS handshake, implement custom CA trust stores, debug certificate issues |
| HTTP/HTTPS Stack | HTTP parsing, CONNECT tunnel, streaming, chunked transfer, H2 | Build an HTTP proxy from scratch, handle bidirectional streaming |
| High Performance Systems | Zero-copy, memory layout, cache-friendly data structures, async runtime tuning | Profile with flamegraph, identify false sharing, optimize p99 latency |
| Monitoring & Observability | Prometheus metrics, Grafana dashboards, OpenTelemetry, distributed tracing | Instrument a Rust service with metrics/traces/logs, define SLIs/SLOs |
| Deployment | Docker, Fly.io, Vercel, Supabase | Containerize a Rust service, deploy edge workers, reason about cold starts |

## Technical Interview Questions

### Rust Fundamentals (Deep)

1. **Ownership & Borrowing**: Given a concurrent system processing TLS connections, how would you design the data flow to minimize cloning while satisfying the borrow checker? Walk through the lifetime annotations.
2. **Async Runtime**: Explain how tokio's scheduler works. What happens when you have 10,000 concurrent connections with mixed CPU and I/O work? How would you tune the runtime?
3. **Zero-Copy Parsing**: How would you parse an HTTP request header without copying data? Discuss `&[u8]` vs `bytes::Bytes` vs `Vec<u8>` and when to use each.
4. **Trait Design**: Design a trait for a `TlsConnector` that supports both rustls and native-tls backends. How would you handle connection pooling generically?
5. **Error Handling**: In a network proxy, connections can fail at many points. How would you design your error types? Discuss `thiserror` vs `anyhow` trade-offs.
6. **Unsafe Rust**: When would you use unsafe in a network/security system? Give concrete examples where it's justified and the safety invariants you must maintain.
7. **Memory Layout**: How does the allocator affect throughput in a proxy? When would you use a custom allocator (e.g., `tikv-jemallocator`)?

### TLS / PKI / Crypto

8. **TLS Handshake**: Walk through the TLS 1.3 handshake step by step. What are the key differences from TLS 1.2? Why is 1.3 faster?
9. **rustls Architecture**: How does rustls differ from OpenSSL-based TLS? What are the security and performance trade-offs?
10. **Certificate Chain Validation**: Describe how certificate chain validation works. What is the role of Root CA, intermediate CA, and end-entity certificates? How does OCSP stapling fit in?
11. **PKI Design**: You need to issue and manage certificates for thousands of microservices. How would you design the PKI infrastructure? (Think about automation, rotation, revocation.)
12. **TLS Termination**: You're building a TLS-terminating proxy. What configuration choices affect security vs performance? Discuss cipher suites, session resumption, 0-RTT.
13. **PEM Parsing**: How would you parse a PEM file in Rust? What are the encoding steps from DER to PEM? How do you handle different PEM types (certificate, private key, CSR)?

### HTTP Proxy & CONNECT Tunnel

14. **CONNECT Tunnel**: Explain how the HTTP CONNECT method establishes a tunnel. Walk through the proxy-client-target handshake. What are the security implications?
15. **Streaming Proxy**: How would you design a proxy that handles large file uploads/downloads without buffering the entire body? Discuss backpressure and flow control.
16. **HTTP/2 Proxying**: What challenges arise when proxying HTTP/2 connections vs HTTP/1.1? Discuss multiplexing, header compression (HPACK), and connection coalescing.
17. **Mitm Proxy**: How would you build a man-in-the-middle proxy that inspects HTTPS traffic? What are the trust and security implications? How would you generate on-the-fly certificates?
18. **Connection Pooling**: Design a connection pool for an HTTP proxy. How do you handle keep-alive, idle timeouts, max connections per host, and pool eviction?

### High Performance & Systems

19. **Latency Optimization**: You have a proxy with p50=5ms but p99=500ms. How would you diagnose and fix this? Walk through your profiling approach.
20. **False Sharing**: What is false sharing? How would you detect it in a multi-threaded proxy? How would you fix it?
21. **Memory Management**: In a high-throughput proxy processing 100k req/s, how would you minimize allocations? Discuss buffer pools, `BytesMut`, and arena allocators.
22. **io_uring vs epoll**: Compare io_uring and epoll for async I/O. How would you evaluate which to use in a Rust network service?
23. **Backpressure**: In a streaming pipeline (client -> proxy -> upstream), how do you handle backpressure when the upstream is slower than the client? Discuss strategies at each layer.

### Monitoring & Observability

24. **Metrics Design**: Design the Prometheus metrics for a TLS proxy. What would you expose? (Think about connections, handshake latency, certificate expiry, error rates.)
25. **Distributed Tracing**: How would you propagate trace context through a proxy that handles CONNECT tunnels? What are the challenges with encrypted traffic?
26. **OpenTelemetry in Rust**: How would you instrument a Rust/Axum service with OpenTelemetry? Walk through the setup and what you'd trace.
27. **Alerting Strategy**: Define SLIs, SLOs, and error budgets for a TLS proxy service. What alerts would you set up? How would you handle alert fatigue?

### System Design

28. **TLS Terminating Proxy**: Design a distributed TLS-terminating proxy that handles 1M concurrent connections. Discuss load balancing, session affinity, certificate distribution, and graceful reload.
29. **Certificate Rotation System**: Design an automated certificate rotation system for thousands of services. How do you ensure zero-downtime rotation?
30. **Secure Tunnel Service**: Design a secure tunnel service (like Cloudflare Tunnel or Ngrok) in Rust. What are the key components? How do you handle NAT traversal, reconnection, and multiplexing?

### Practical Coding (Take-Home Style)

31. **TCP Echo Proxy**: Implement a TCP proxy that forwards connections to an upstream server. Handle graceful shutdown, connection draining, and error propagation.
32. **HTTP Header Parser**: Write a zero-copy HTTP/1.1 request parser in Rust. Handle request line, headers, and body detection.
33. **Certificate Expiry Monitor**: Build a tool that checks certificate expiry for a list of domains and reports expiring certificates.
34. **Rate Limiter**: Implement a token bucket rate limiter as a Rust library. Make it thread-safe and async-compatible.
35. **Metrics Middleware**: Write an Axum middleware that records request duration, status codes, and path counts as Prometheus metrics.

## Key Terminology

- **TLS 1.3 0-RTT** -- Session resumption that sends application data in the first flight (trades security for latency)
- **CONNECT Tunnel** -- HTTP method that asks a proxy to open a raw TCP connection to a target (used for HTTPS proxying)
- **rustls** -- Pure-Rust TLS library (no OpenSSL), uses ring for crypto
- **PKI (Public Key Infrastructure)** -- Framework for managing certificates, CAs, and trust relationships
- **OCSP Stapling** -- Proxy attaching a cached OCSP response to reduce certificate revocation check latency
- **HPACK** -- Header compression for HTTP/2 (dynamic table, static table, Huffman coding)
- **False Sharing** -- Performance degradation when threads modify adjacent memory locations on the same cache line
- **Buffer Pool** -- Pre-allocated pool of reusable buffers to reduce allocation overhead in hot paths
- **io_uring** -- Linux async I/O interface using submission/completion queues (kernel 5.1+)
- **SLI/SLO** -- Service Level Indicator/Objective: measurable reliability targets (e.g., 99.9% request success rate)

## Rust Crate Reference

| Category | Crates |
|----------|--------|
| TLS | `rustls`, `native-tls`, `tokio-rustls` |
| HTTP Server | `axum`, `hyper`, `tower`, `tonic` |
| HTTP Client | `reqwest`, `hyper` |
| Crypto | `ring`, `rcgen` (cert gen), `x509-parser`, `pem` |
| Async Runtime | `tokio`, `async-std` |
| Bytes/Buffer | `bytes` (Bytes/BytesMut), `byteorder` |
| Metrics | `prometheus` (client), `metrics` (facade), `opentelemetry` |
| Serialization | `serde`, `serde_json` |
| Error Handling | `thiserror`, `anyhow` |
| CLI | `clap`, `env_logger`, `tracing` |
| Network | `socket2`, `tokio::net`, `hyper-util` |
| Tauri | `tauri` (desktop apps) |

## Cross-References

- **CS Fundamentals**: Networking (TCP/IP, HTTP, DNS), Operating Systems (epoll, memory, threads)
- **System Design**: [Rate Limiter](../../system_design/rate_limiter/), distributed systems concepts
- **Production Engineering**: Monitoring, reliability patterns, deployment strategies
- **Backend Engineer**: API design, observability, caching fundamentals

## Study Resources

- [rustls book](https://docs.rs/rustls/)
- [Tokio tutorial](https://tokio.rs/tokio/tutorial)
- [Hyper crate documentation](https://docs.rs/hyper/)
- [OpenTelemetry Rust](https://github.com/open-telemetry/opentelemetry-rust)
- [Let's Encrypt -- How It Works](https://letsencrypt.org/how-it-works/)
- [TLS 1.3 RFC 8446](https://datatracker.ietf.org/doc/html/rfc8446)
- [HPACK RFC 7541](https://datatracker.ietf.org/doc/html/rfc7541)
