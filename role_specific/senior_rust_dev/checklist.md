# Senior Rust Developer -- Prep Checklist

Use this checklist to track your preparation for Senior Rust Developer positions focused on Network, Security, and High Performance Systems.

## Rust Deep Fundamentals

- [ ] **Ownership & Borrowing Review**: Revisit lifetimes, `Cow<T>`, `Arc<T>`/`RwLock<T>` patterns for shared mutable state in async contexts
- [ ] **Async/Await Deep Dive**: Understand tokio scheduler (multi-threaded, current-thread), task spawning, `select!`, cancellation safety
- [ ] **Zero-Copy I/O**: Practice parsing with `&[u8]`, `bytes::Bytes`, `BytesMut`; understand when copies happen
- [ ] **Trait Design**: Practice designing generic traits for pluggable backends (e.g., `TlsProvider`, `HttpClient`)
- [ ] **Error Handling**: Build layered error types with `thiserror`; practice `anyhow` for applications vs `thiserror` for libraries
- [ ] **Unsafe Rust**: Study when unsafe is justified in networking (FFI, raw pointer manipulation, `MaybeUninit`)

## TLS / PKI / Crypto

- [ ] **TLS 1.3 Handshake**: Draw out the full handshake flow (ClientHello -> ServerHello -> EncryptedExtensions -> Finished)
- [ ] **TLS 1.2 vs 1.3**: List all differences (cipher suites, key exchange, handshake rounds, 0-RTT)
- [ ] **rustls Internals**: Read rustls source for `ServerConfig`, `ClientConfig`, `TlsConnector`, certificate loading
- [ ] **PKI Chain**: Practice building certificate chains, understand Root CA -> Intermediate -> End Entity
- [ ] **Certificate Operations**: Implement cert generation with `rcgen`, parsing with `x509-parser`, PEM encoding/decoding
- [ ] **Session Resumption**: Understand session IDs, session tickets, and 0-RTT trade-offs
- [ ] **Cipher Suite Selection**: Know which suites are secure (AES-256-GCM, ChaCha20-Poly1305) and which are deprecated

## HTTP Proxy & CONNECT Tunnel

- [ ] **HTTP/1.1 Request/Response Format**: Parse request line, headers, body detection (Content-Length, chunked)
- [ ] **CONNECT Method**: Implement CONNECT handshake (client -> proxy -> upstream tunnel establishment)
- [ ] **Streaming Proxy**: Implement bidirectional copy with backpressure using `tokio::io::copy_bidirectional`
- [ ] **HTTP/2 Proxying**: Understand frame types, stream multiplexing, SETTINGS, WINDOW_UPDATE
- [ ] **Connection Management**: Implement connection pooling with idle timeout, max connections, eviction
- [ ] **MITM Proxy**: Understand on-the-fly certificate generation, dynamic trust anchor injection

## High Performance Systems

- [ ] **Profiling Tools**: Practice with `cargo flamegraph`, `perf`, `tokio-console`, `tracing` spans
- [ ] **Latency Optimization**: Practice identifying p99 outliers, tail latency amplification, CoDel
- [ ] **Memory Optimization**: Practice buffer pooling, `BytesMut` with capacity management, arena allocation
- [ ] **Concurrency Patterns**: Practice lock-free patterns, `crossbeam` channels, `dashmap`, `atomic` operations
- [ ] **False Sharing**: Detect with perf, fix with padding (`#[repr(align(64))]`), `CachePadded`
- [ ] **io_uring**: Understand the submission/completion queue model, compare with epoll throughput

## Monitoring & Observability

- [ ] **Prometheus in Rust**: Instrument a service with `prometheus` crate (counters, histograms, gauges)
- [ ] **OpenTelemetry**: Set up tracing + metrics export in an Axum service
- [ ] **Distributed Tracing**: Implement trace context propagation through proxy layers
- [ ] **SLI/SLO Design**: Define metrics for a proxy service (success rate, latency, certificate health)
- [ ] **Alerting**: Design alert thresholds, understand burn rate alerting, multi-window multi-burn-rate

## System Design Practice

- [ ] **TLS-Terminating Proxy**: Design a system handling 1M concurrent TLS connections (load balancer, cert distribution, graceful reload)
- [ ] **Certificate Rotation**: Design automated cert issuance, distribution, and rotation with zero downtime
- [ ] **Secure Tunnel**: Design a tunnel service handling NAT traversal, reconnection, multiplexing
- [ ] **Metrics Pipeline**: Design a metrics collection pipeline from 1000s of instances to a central store

## Practice Coding Exercises

- [ ] TCP echo proxy with graceful shutdown
- [ ] HTTP/1.1 request parser (zero-copy)
- [ ] Token bucket rate limiter (async, thread-safe)
- [ ] Certificate expiry checker (concurrent domain checking)
- [ ] Prometheus metrics middleware for Axum
- [ ] CONNECT tunnel proxy (minimal HTTPS proxy)
- [ ] Buffer pool implementation with `BytesMut`
- [ ] PEM file parser (DER decode, type detection)

## Practice Questions

1. Walk through the TLS 1.3 handshake. Why is it faster than 1.2?
2. How does rustls handle certificate verification? What trust anchors does it use?
3. Design a connection pool for an HTTP proxy. Handle keep-alive, max-per-host, eviction.
4. Your proxy has p50=5ms but p99=500ms. How do you diagnose this?
5. How would you propagate tracing context through an HTTPS CONNECT tunnel?
6. What happens when 10,000 TLS handshakes hit simultaneously? How does the CPU scale?
7. Design automated certificate rotation for a fleet of 1,000 microservices.
8. How would you minimize allocations in a streaming proxy at 100k req/s?
9. Compare `tokio-rustls` vs `native-tls` for a production proxy. When would you choose each?
10. How would you implement a token bucket rate limiter that works across multiple proxy instances?

## Mock Interview Log

- [ ] 2026-__-__: Rust fundamentals deep dive (ownership, async, zero-copy)
- [ ] 2026-__-__: TLS/PKI system design (certificate rotation, MITM proxy)
- [ ] 2026-__-__: Performance optimization (profiling, latency diagnosis)
- [ ] 2026-__-__: Full mock interview covering all competency areas
