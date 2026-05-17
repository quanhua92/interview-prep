# Geohashing and Spatial Indexing

Source: [Geohashing (CalibreOS)](https://www.calibreos.com/learn/hld-geohashing)

## One-Liner
Encode 2D geographic coordinates into 1D keys that preserve spatial locality, enabling O(log N) proximity queries instead of O(N) full-table scans.

## Functional Requirements
- Find nearby points of interest within a given radius (e.g., coffee shops within 1 km)
- Support proximity search at various scales (building-level to city-level)
- Rank results by distance, rating, or multi-factor scoring
- Handle both static data (businesses, venues) and dynamic data (drivers, couriers)
- Support combined geo + full-text + filter queries (e.g., "coffee shops within 5 km, open now, rated > 4.0")

## Non-Functional Requirements
- Query latency under 20 ms for 50M points at 10K QPS
- Support global scale with uniform behavior across all latitudes
- Handle high-frequency location updates (drivers updating GPS every 4 seconds)
- Read-heavy workload for static data; write-heavy for dynamic data
- Consistent candidate retrieval regardless of cell boundary placement

## Key Scale Questions
- 50M businesses, 10K search QPS (Yelp-scale)
- 500K concurrent active drivers updating positions every 4 seconds (Uber-scale)
- Geohash precision 6 cell (~0.6 km x 1.2 km): ~2,400 businesses in Midtown Manhattan vs 2 in rural Wyoming
- At 10K QPS on 10M businesses with naive lat/lng B-tree: 100 billion Haversine evaluations per second
- Storage: 52-bit integer geohash per point + metadata

## Core Components
- **Spatial Index**: geohash / S2 / quad-tree / BKD tree -- the 1D encoding that enables proximity queries
- **Geohash Encoder**: interleaves longitude and latitude bits to produce a base-32 string (Z-order/Morton curve)
- **9-Cell Boundary Fix**: always query center cell + 8 neighbors to handle Z-order boundary discontinuities
- **Two-Phase Search**: Phase 1 (coarse) -- spatial index scan for ~500-2,000 candidates; Phase 2 (exact) -- Haversine distance filter on candidates
- **Haversine Filter**: exact spherical distance computation applied only to the candidate set, never as a primary filter

## Key Design Decisions

### Spatial Index Choice
- **Option A: Geohash (Z-order encoding)**: Simple string prefix search on B-tree index. Used by Redis GEORADIUS/GEOSEARCH. Boundary discontinuity is the critical limitation. Best for: simple proximity, <1M static points, prototypes
- **Option B: Google S2 (Hilbert curve)**: Near-uniform cell area at all latitudes. Better locality preservation than Z-order. Multi-scale indexing (30 levels). Best for: global products needing consistent behavior (Google Maps, Foursquare, Snap Maps)
- **Option C: Quad-tree**: Adaptive partitioning -- dense areas get subdivided, sparse areas stay coarse. In-memory, microsecond lookups. Best for: dynamic point sets with high-frequency updates (Uber early dispatch)
- **Option D: BKD tree (Elasticsearch)**: Log-structured k-d tree combining geo + full-text + numeric filters in one query. ~10-20 ms for 50M points. Best for: static data with rich filtering (Yelp, Booking.com)

### Geohash Precision Selection
- **Option A: Precision 4 (~45 km x 45 km)**: City-level clustering, country zoom, 50-200 km radius
- **Option B: Precision 5 (~2.4 km x 4.9 km)**: Neighborhood search, 5-40 km radius
- **Option C: Precision 6 (~0.6 km x 1.2 km)**: Local business search (Yelp default), 1-5 km radius
- **Option D: Precision 8 (~38 m x 19 m)**: Building-level precision, delivery pin, <100 m radius

### Query Execution Strategy
- **Option A: Single-phase Haversine**: Compute exact distance for every row. O(N). Never do this at scale
- **Option B: Two-phase (recommended)**: Spatial index narrows to ~2,000 candidates (O(log N)), then Haversine filters to exact radius (O(K)). Geo phase is expensive I/O; Haversine is cheap compute

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/nearby?lat=&lng=&radius=&category= | Search nearby points of interest |
| POST | /api/locations | Add or update a location point |
| GET | /api/nearby/drivers?lat=&lng=&radius= | Find nearby dynamic entities (drivers, couriers) |
| GET | /api/geohash?lat=&lng=&precision= | Encode coordinates to geohash |

## Database Schema
| Column | Type | Notes |
|--------|------|-------|
| id | BIGINT | PK |
| name | VARCHAR | Point of interest name |
| lat | FLOAT | Latitude |
| lng | FLOAT | Longitude |
| geohash5 | VARCHAR(5) | Precision-5 geohash, indexed |
| geohash6 | VARCHAR(6) | Precision-6 geohash, indexed |
| location | GEOGRAPHY | PostGIS: GEOGRAPHY(POINT, 4326) with GiST index |
| rating | FLOAT | For multi-factor ranking |
| category | VARCHAR | For category filtering |

## Deep Dive Topics
- **Z-order boundary problem**: Adjacent geographic points can have completely different geohash prefixes if they straddle a cell boundary. The mandatory fix: always query 9 cells (center + 8 neighbors)
- **Hilbert vs Z-order curve**: Hilbert curve has no jump between quadrants -- points close in 1D ordering are always close in 2D space. Z-order zigzags, creating worse boundary discontinuities
- **Geohash polar latitude problem**: Cells near the poles are physically much smaller than equatorial cells at the same precision. A prefix query in Helsinki returns 4x fewer candidates than Miami. S2 solves this with uniform-area cells
- **Uber H3 hexagonal grids**: Each hexagonal cell has exactly 6 equidistant neighbors (no corner vs edge asymmetry). Reduces false-positive candidates by ~30% vs 9-cell rectangular query. Used for surge pricing, demand prediction, ML features
- **BKD tree internals**: Log-structured variant of k-d tree with merge-based updates (similar to LSM trees). Combines geo filter (BKD range scan), text filter (inverted index), and numeric filter (doc values) in a single Lucene query pass
- **Redis GEOADD/GEOSEARCH**: 52-bit integer geohash stored as sorted set score. In-memory, sub-ms latency, but not durable -- production systems back it with PostgreSQL/DynamoDB and rebuild on restart

## Spatial Index Decision Matrix
| Scenario | Best Choice | Why | Real-World User |
|----------|-------------|-----|-----------------|
| Static data + full-text search | Elasticsearch BKD tree | BKD + inverted index in one query; ~10-20ms for 50M points | Yelp, Booking.com |
| Dynamic locations, high write rate | Redis GEOADD/GEOSEARCH | In-memory sorted set; O(log N) write; sub-ms latency | Uber (pre-H3), DoorDash |
| Ultra-high-frequency updates + custom dispatch | In-memory quad-tree | Microsecond lookup; no network round-trip | Uber early dispatch |
| Global scale, uniform across latitudes | Google S2 cells | Hilbert-curve locality; uniform area; multi-scale | Google Maps, Foursquare |
| Hexagonal grid for coverage/routing | Uber H3 | Equidistant neighbors; best circle approximation | Uber zone planning, Meta |
| Small-to-medium static + SQL joins | PostGIS (GiST index) | ST_DWithin with GiST; full SQL expressiveness; up to ~10M points | Real estate, logistics |
| Simple proximity, <1M points | Geohash prefix in Postgres | Single index, prefix scan, trivial to implement | Internal tools, MVPs |
| Production proximity at scale | Elasticsearch + Redis (dual-tier) | ES for ranked search; Redis for real-time updates; decoupled | Yelp + Uber combined |

## Interview Questions
1. You're building a proximity service for 50M static businesses. Walk through how you'd choose between geohash, Google S2, Elasticsearch BKD trees, and PostGIS.
2. Explain the Z-order curve and why it creates the boundary problem. How does the Hilbert curve in S2 reduce -- but not eliminate -- this problem?
3. Walk through exactly why Uber built an in-memory quad-tree for driver dispatch rather than using Redis GEORADIUS or PostgreSQL.
4. A candidate says: "I'll use a geohash index in Postgres for the restaurant search." Walk through what they're missing and what questions the interviewer will ask.

## Follow-Up Variations
- How would you handle a search radius larger than 2x the geohash cell size (9 cells are not enough)?
- How do you invalidate and rebuild cached geo query results when businesses open/close?
- What happens when a city has 100x more points per cell than a rural area (quad-tree vs geohash)?
- How would you combine geo search with personalization (different rankings per user)?
- How do you handle the Earth's curvature for very large search radii (>100 km)?
