# Design an Online Auction System

Source: [Online Auction (CalibreOS)](https://www.calibreos.com/learn/hld-online-auction)

## One-Liner
Design an eBay-scale real-time auction system with bid contention handling via per-auction Kafka queue serialization, proxy bidding, anti-sniping extension windows, and WebSocket-based bid broadcasting.

## Functional Requirements
- Submit a bid for an active auction; bid must exceed current price + minimum increment; atomic with <200ms p99 latency
- Proxy bidding: auto-bid incrementally on behalf of a bidder up to their stated maximum; resolve multi-proxy races
- Anti-sniping extension: extend auction end_time by a fixed window (e.g., 5 min) when a bid arrives within the final minutes
- Real-time bid broadcast to all watchers via WebSocket/SSE within 1 second of bid acceptance
- Auction state machine: UPCOMING -> ACTIVE -> CLOSING -> CLOSED; also handle CANCELLED and NO_SALE states
- Bid history: append-only, queryable per auction; support ~50 bids avg per auction, up to ~500 for popular items
- Reserve price enforcement: hidden reserve; display "Reserve not met" without revealing the amount

## Non-Functional Requirements
- ~1M active auctions concurrently
- Peak bid rate: ~10K bids/sec system-wide; up to ~100 bids/sec on a single viral auction
- Bid acceptance latency: p99 <200ms end-to-end
- Broadcast latency: bid update pushed to all watchers within 1 second
- Consistency: exactly one winning bid per auction; no split-brain on close
- Availability: 99.99% for bid submission; eventual consistency acceptable for watcher broadcasts

## Key Scale Questions
- 1M active auctions; average bid rate ~0.01 bids/sec/auction (low per-auction contention)
- Viral auctions: up to ~100 bids/sec at close time
- Bid storage: ~50 bids/auction x 1M auctions x 200 bytes/bid ~ 10 GB per cycle
- WebSocket watchers: ~50K total across ~10 gateway servers = ~5K connections/server
- Auction close rate: ~100 closes/sec at peak
- Kafka partitions: ~1K partitions needed (1M auctions / ~1K auctions per partition)

## Core Components
- **Bid Ingestion Service**: receives bids from clients, validates basic constraints, publishes to Kafka
- **Kafka (per-auction partition)**: routes bids by `auction_id` as partition key; guarantees ordering per auction
- **Auction Processor Workers**: consume partitions sequentially; validate, resolve proxy bids, update state, write to DB, publish events
- **WebSocket Gateway**: Kafka consumer that fans out bid events to connected watchers per auction
- **Auction Service**: CRUD for auction listings, manages state machine transitions
- **Closing Scheduler Job**: periodic job that publishes `ScheduledClose` messages to each auction's partition
- **Notification Service**: winner emails/push, payment initiation (triggered on CLOSED transition)

## Key Design Decisions

### Bid Contention Strategy
- **Option A: Pessimistic locking (SELECT FOR UPDATE)**: serializes bids behind a DB row lock; convoy effect at 10+ concurrent bids; connection pool exhaustion on viral auctions. Disqualifying at senior+ level.
- **Option B: Optimistic locking (version CAS)**: read-validate-update with retry; avoids lock holding but causes retry storms under high contention; more total DB work than pessimistic.
- **Option C: Per-auction Kafka partition (production)**: partition by `auction_id`; single processor per partition; no DB locking. Converts distributed concurrency into single-threaded sequential processing per auction. System-wide throughput scales by adding partitions. This is the eBay-scale answer.

### Proxy Bidding Resolution
- Bidders set a maximum; the system auto-bids incrementally up to that max
- Two-proxy race: resolve incrementally in memory before publishing; show only final resolved price to watchers
- Auction processor maintains a sorted list of active proxy bidders; runs resolution loop on each incoming bid
- Never publish intermediate proxy increments as separate events

### Anti-Sniping Extension
- If a bid arrives within `extension_window` seconds of `end_time`, extend `end_time` by `extension_window`
- Cap total extension via `original_end_time + max_extension` to prevent indefinite auctions
- Publish `AuctionExtended` event alongside `BidPlaced` so watchers update countdown timers

### Real-Time Broadcast Architecture
- Two layers: event publication (Kafka `auction-events` topic) and fan-out (WebSocket gateway)
- Each gateway server maintains an in-memory `{auction_id: [connections]}` map; no cross-server coordination needed
- SSE for read-only watchers; WebSocket for active bidders. Production systems often use both.

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| POST | /api/auctions | Create a new auction listing |
| GET | /api/auctions/{id} | Get auction details (current_price, status, end_time) |
| POST | /api/auctions/{id}/bids | Submit a bid (manual or proxy with max_amount) |
| GET | /api/auctions/{id}/bids | Get bid history for an auction |
| POST | /api/auctions/{id}/watch | Subscribe to real-time bid updates |
| DELETE | /api/auctions/{id} | Cancel auction (only before any bids) |

## Database Schema
| Table | Key Columns | Write Pattern | Notes |
|-------|-------------|---------------|-------|
| auctions | auction_id, item_id, seller_id, start_price, reserve_price, current_price, current_winner_id, bid_count, start_time, end_time, original_end_time, status, version | Updated on every bid accept; ~10K writes/sec peak | Denormalized cache of bid state; sharded by auction_id |
| bids | bid_id (UUID, client-generated), auction_id, bidder_id, bid_amount, proxy_max (nullable), bid_timestamp, bid_type (MANUAL/PROXY/SNIPE_PROTECTION), created_at | Append-only; never updated or deleted | Source of truth; audit trail; partitioned by auction_id |
| auction_watchers | auction_id, user_id, notification_channel_id, created_at | Written on watch click; low rate | For close notifications (email/push); not for WebSocket state |
| items | item_id, seller_id, title, description, category, images_json | Written at listing creation; rarely updated | CDN-cacheable; images in S3/object storage |

Key principle: **bids table is the append-only source of truth**; `current_price` and `current_winner_id` on auctions table are a denormalized cache. If cache is corrupted, recompute from bids table.

## Deep Dive Topics
- **Auction state machine**: six states (UPCOMING, ACTIVE, CLOSING, CLOSED, CANCELLED, NO_SALE). The CLOSING state is critical -- it drains bids already in the Kafka queue at close time so in-flight bids are not silently dropped.
- **Auction close traffic spike**: ClosingAuctions job publishes `ScheduledClose` messages to each auction's Kafka partition; close processing is distributed across all processor workers; no single bottleneck.
- **Worker crash recovery**: Kafka consumer group rebalance reassigns partitions; replacement replays from last committed offset; bid processor must be idempotent (check duplicate bid_id, guard with `WHERE current_price < :new_price`).
- **Redis cache invalidation**: `current_price` cached in Redis for reads; use versioned writes (`SET NX` with version counter) to reject stale updates on crash replay.
- **Bid contention strategy comparison**: Pessimistic locking fails at ~10+ concurrent bids; optimistic CAS causes retry storms; Kafka per-auction partition eliminates both issues.
- **Proxy bidder confidentiality**: never expose `proxy_max` in API responses; only show `current_price` to other bidders.

## Follow-Up Variations
- How would you support Dutch (descending price) or sealed-bid auction formats?
- What happens if two proxy bidders have the same maximum -- how do you break the tie?
- How would you handle payment integration and escrow for the winning bidder?
- What if the auction processor worker crashes mid-proxy-resolution -- how do you ensure consistency?
- How would you design a "Buy It Now" feature alongside auction bidding?
- How do you handle a seller who wants to cancel an auction that already has bids?
