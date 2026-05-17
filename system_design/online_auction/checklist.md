# Design an Online Auction System -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What auction format? (English ascending, Dutch descending, sealed-bid, Vickrey -- assume English unless told otherwise)
  - [ ] Is proxy (automatic) bidding required?
  - [ ] What is the expected scale? (concurrent auctions, peak bid rate, watchers per auction)
  - [ ] What is the anti-sniping policy? (extension window duration, max extension cap)
  - [ ] How are reserve prices handled? (public or private)
  - [ ] Is payment integrated or handled externally post-auction?
- [ ] List functional requirements (5-7 items):
  - [ ] Submit a bid for an active auction (must exceed current price + minimum increment)
  - [ ] Proxy bidding: auto-bid up to bidder's maximum, resolve multi-proxy races
  - [ ] Anti-sniping extension: extend end_time when bids arrive in final minutes
  - [ ] Real-time bid broadcast to all watchers via WebSocket/SSE
  - [ ] Auction state machine: UPCOMING -> ACTIVE -> CLOSING -> CLOSED (+ CANCELLED, NO_SALE)
  - [ ] Bid history: append-only, queryable per auction
  - [ ] Reserve price enforcement (hidden reserve, show "Reserve not met")
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Bid acceptance: p99 <200ms end-to-end
  - [ ] Broadcast latency: push to all watchers within 1 second
  - [ ] Scale: ~1M active auctions, ~10K bids/sec peak system-wide
  - [ ] Consistency: exactly one winner per auction, no split-brain on close
  - [ ] Availability: 99.99% for bid submission
- [ ] State your scale estimates:
  - [ ] ~1M active auctions at any moment
  - [ ] ~10K bids/sec system-wide; ~100 bids/sec on a single viral auction
  - [ ] ~50K concurrent WebSocket watchers across ~10 gateway servers
  - [ ] ~100 auction closes/sec at peak
  - [ ] Bid storage: ~10 GB per auction cycle
  - [ ] ~1K Kafka partitions needed

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Client -> LB -> [Bid Ingestion Service] -> Kafka (per-auction partition) -> [Auction Processor] -> [DB + Redis Cache]
- [ ] Draw the broadcast path: Auction Processor -> Kafka auction-events topic -> [WebSocket Gateway] -> Clients
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /api/auctions/{id}/bids` -- submit a bid (write, high contention on popular auctions)
  - [ ] `GET /api/auctions/{id}` -- get auction details (read, high QPS)
  - [ ] `POST /api/auctions` -- create auction listing (write, low QPS)
  - [ ] `POST /api/auctions/{id}/watch` -- subscribe to real-time updates
- [ ] Note the bid contention pattern and where Kafka partitioning helps:
  - [ ] Average: ~0.01 bids/sec/auction (low contention)
  - [ ] Viral auction close: ~100 bids/sec on one auction (high contention)
  - [ ] Per-auction Kafka partition converts concurrent bids into sequential processing
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain bid contention strategy and justify:
  - [ ] Pessimistic locking (SELECT FOR UPDATE): fails at ~10+ concurrent bids (convoy effect, connection pool exhaustion)
  - [ ] Optimistic locking (version CAS): retry storms under high contention; more total DB work
  - [ ] Kafka per-auction partition (production): single-threaded per auction; no locking; scales by adding partitions
  - [ ] State your choice and why (Kafka partition pattern is the eBay-scale answer)
- [ ] Explain proxy bidding resolution:
  - [ ] Bidder sets max; system auto-bids incrementally up to max
  - [ ] Two-proxy race: resolve incrementally in memory, publish only final price
  - [ ] Never expose proxy_max in API responses
- [ ] Explain anti-sniping extension:
  - [ ] Extend end_time by N minutes when bid arrives in final N minutes
  - [ ] Cap total extension via original_end_time + max_extension
  - [ ] Publish AuctionExtended event alongside BidPlaced
- [ ] Define API endpoints with method, path, description:
  - [ ] `POST /api/auctions` -> create auction
  - [ ] `GET /api/auctions/{id}` -> auction details (current_price, status, end_time)
  - [ ] `POST /api/auctions/{id}/bids` -> submit bid (manual or proxy)
  - [ ] `GET /api/auctions/{id}/bids` -> bid history
  - [ ] `POST /api/auctions/{id}/watch` -> subscribe to updates
- [ ] Sketch the database schema:
  - [ ] Table `auctions`: auction_id, seller_id, start_price, reserve_price, current_price, current_winner_id, status, end_time, original_end_time, version
  - [ ] Table `bids`: bid_id (UUID, client-generated for idempotency), auction_id, bidder_id, bid_amount, proxy_max, bid_type, bid_timestamp
  - [ ] Table `auction_watchers`: auction_id, user_id, notification_channel_id
  - [ ] Table `items`: item_id, seller_id, title, description, images_json
- [ ] Walk through the main flow end-to-end:
  - [ ] Bid submission: client sends bid -> Bid Ingestion validates -> publishes to Kafka partition keyed by auction_id -> Auction Processor consumes sequentially -> validates > current_price -> resolves proxy bids -> writes bid to DB -> updates auctions table -> publishes BidPlaced event -> WebSocket gateway fans out to watchers
  - [ ] Auction close: ClosingAuctions job publishes ScheduledClose to each partition -> processor drains pending bids (CLOSING state) -> transitions to CLOSED -> triggers winner notification + payment

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss the auction state machine in detail:
  - [ ] UPCOMING -> ACTIVE (scheduled job at start_time)
  - [ ] ACTIVE -> CLOSING (end_time reached, drain pending bids)
  - [ ] CLOSING -> CLOSED (all pending bids processed, winner determined)
  - [ ] ACTIVE -> CANCELLED (only before any bids)
  - [ ] CLOSED -> NO_SALE (reserve not met)
  - [ ] Emphasize CLOSING state: prevents in-flight bids from being silently dropped
- [ ] Explain scaling and partitioning:
  - [ ] Auctions table: sharded by auction_id to distribute write load
  - [ ] Bids table: partitioned by auction_id for single-shard bid history scans
  - [ ] Kafka: ~1K partitions for ~1M auctions; each partition handles ~1K auctions
  - [ ] WebSocket gateways: ~10 servers, each maintains local connection map per auction
- [ ] Handle failure modes:
  - [ ] Worker crash: Kafka consumer group rebalance; replacement replays from last offset; processor must be idempotent (check duplicate bid_id, guard current_price update with WHERE clause)
  - [ ] Redis cache stale writes on replay: use versioned SET NX pattern
  - [ ] Bid received after close: reject with AUCTION_CLOSED; CLOSING state provides 2-5 sec grace window
  - [ ] Server timestamps only: never trust client bid timestamps for anti-snipe checks
- [ ] Discuss auction close traffic spike (~100 closes/sec at peak):
  - [ ] ClosingAuctions job runs every 30 seconds, publishes ScheduledClose to each partition
  - [ ] Close processing distributed across all processor workers (no single bottleneck)
  - [ ] Stagger listing times with randomization for natural spreading
- [ ] Explain broadcast architecture trade-offs:
  - [ ] Kafka fan-out vs Redis Pub/Sub: Kafka preferred (already in pipeline, avoids extra network hop)
  - [ ] SSE for read-only watchers; WebSocket for active bidders
  - [ ] Gateway connection map is local per server; no cross-server coordination needed

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] Differentiate from ticketing: winner is highest bidder at close, not fastest requester
- [ ] State the key insight: Kafka per-auction partition converts distributed concurrency into single-threaded sequential processing -- same principle as stock exchange matching engines
- [ ] Mention trade-offs: eventual consistency for broadcasts, denormalized cache for current_price, idempotent processing for crash recovery
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
