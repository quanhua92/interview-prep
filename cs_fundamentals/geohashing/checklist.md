# Geohashing and Spatial Indexing — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is the data static (businesses, venues) or dynamic (drivers, couriers, live positions)?
  - [ ] What query radius range do we support (building-level to city-level)?
  - [ ] Do we need to combine geo search with full-text or category filtering?
  - [ ] Is this a global product (needs uniform behavior across latitudes) or single-region?
- [ ] List functional requirements (3-5 items):
  - [ ] Find nearby points within a given radius
  - [ ] Support various precision levels (block-level to city-level)
  - [ ] Rank results by distance, rating, or multi-factor scoring
  - [ ] Handle location updates for dynamic entities
  - [ ] Support combined geo + text + filter queries
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: queries under 20ms for 50M points
  - [ ] High throughput: 10K QPS for static search, 100K+ updates/sec for dynamic
  - [ ] Consistent behavior: no missed results at cell boundaries
  - [ ] Global correctness: uniform behavior at all latitudes
- [ ] State your scale estimates (points, queries, updates):
  - [ ] ~50M static businesses (Yelp-scale)
  - [ ] ~500K concurrent dynamic entities updating every 4 seconds (Uber-scale)
  - [ ] ~10K search QPS
  - [ ] Geohash precision-6 cell: ~2,400 businesses in dense areas, ~2 in sparse areas

## Phase 2: High-Level Design (3-5 min)
- [ ] Explain the core problem: B-tree indexes are 1D structures, geographic proximity is 2D
  - [ ] A composite (lat, lng) index scans O(N/k) rows, not O(log N)
  - [ ] The fix: encode 2D coordinates into a 1D key that preserves spatial locality
- [ ] Identify the main spatial indexing approaches:
  - [ ] Geohash (Z-order/Morton curve) -- string prefix search on B-tree
  - [ ] Google S2 (Hilbert curve) -- uniform-area cells, multi-scale
  - [ ] Quad-tree -- adaptive partitioning for dynamic points
  - [ ] BKD tree (Elasticsearch) -- geo + full-text combined
- [ ] Draw the two-phase search pattern:
  - [ ] Phase 1: spatial index narrows candidates from 50M to ~2,000 (O(log N))
  - [ ] Phase 2: Haversine exact distance filter on candidates (O(K))
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain geohash encoding and justify:
  - [ ] Bit-interleaving of longitude and latitude (Z-order/Morton curve)
  - [ ] Base-32 string encoding: shared prefix = geographic proximity
  - [ ] Precision table: 4 chars (~45 km), 5 chars (~2.4 km), 6 chars (~0.6 km), 8 chars (~38 m)
  - [ ] Prefix query: `WHERE geohash LIKE '9q8yy%'` becomes B-tree range scan
- [ ] State the boundary problem proactively (do not wait to be asked):
  - [ ] Z-order boundary discontinuity: adjacent points can have different prefixes
  - [ ] The mandatory fix: always query center cell + 8 neighbors = 9 cells total
  - [ ] SQL: `WHERE geohash6 IN (?, ?, ?, ?, ?, ?, ?, ?, ?)`
  - [ ] For large radii (>2x cell size), enumerate all intersecting cells
- [ ] Explain Haversine as the refinement pass:
  - [ ] Never use Haversine as primary filter (too expensive at scale)
  - [ ] Apply only to ~2,000 candidates from spatial index
  - [ ] ~2ms for 2,000 evaluations in Python; <0.5ms in Go/C++
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `GET /api/nearby?lat=&lng=&radius=&category=` -> `[{id, name, dist_km, rating}]`
  - [ ] `POST /api/locations` -> `{id, geohash}`
  - [ ] `GET /api/geohash?lat=&lng=&precision=` -> `{geohash: "9q8yy1"}`
- [ ] Sketch the database schema:
  - [ ] Table `locations`: `id`, `name`, `lat`, `lng`, `geohash5`, `geohash6`, `category`, `rating`
  - [ ] Indexes: B-tree on `geohash5`, B-tree on `geohash6`
  - [ ] PostGIS alternative: `location GEOGRAPHY(POINT, 4326)` with GiST index
- [ ] Discuss SQL vs NoSQL vs search engine trade-off:
  - [ ] PostgreSQL + geohash: simple, up to ~10M points, no extra infra
  - [ ] PostgreSQL + PostGIS: GiST index, spatial SQL, up to ~10M points
  - [ ] Elasticsearch BKD tree: geo + full-text combined, ~50M+ points, 10-20ms
  - [ ] Redis GEOADD: in-memory, dynamic updates, sub-ms, not durable
- [ ] Walk through the main flow end-to-end:
  - [ ] Query: user searches "coffee within 2 km" -> encode user location to geohash -> get 9 neighbor cells -> query DB for matching cells -> Haversine filter -> rank -> return top 20
  - [ ] Update: driver GPS update -> encode to geohash -> write to Redis sorted set (52-bit geohash as score) -> async persist to durable store

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss the Z-order boundary problem in depth:
  - [ ] Two points 15 meters apart can have geohash prefixes differing at character 5
  - [ ] 9-cell query fixes this for typical radii; large radii need cell enumeration
  - [ ] "State this proactively" -- it signals production-level understanding
- [ ] Compare spatial indexes and explain when to use which:
  - [ ] Geohash: simple prefix search, Redis GEORADIUS backend, good for MVPs
  - [ ] S2: Hilbert curve (better locality than Z-order), uniform area (fixes polar problem), Foursquare migrated from geohash to S2 for this reason
  - [ ] Quad-tree: adaptive density handling, in-memory, microsecond lookups for dynamic dispatch
  - [ ] BKD tree: Elasticsearch's log-structured k-d tree, combines geo + text + numeric in one Lucene query
  - [ ] H3: hexagonal cells with 6 equidistant neighbors (no corner vs edge asymmetry), ~30% fewer false positives
- [ ] Explain scaling/partitioning approach:
  - [ ] Elasticsearch: shard by geohash prefix or S2 cell for locality
  - [ ] Redis: single sorted set per region, or partition by geohash prefix
  - [ ] Quad-tree: one tree per region or city, rebuild periodically
- [ ] Address the dynamic vs static data distinction:
  - [ ] Static (businesses): Elasticsearch BKD tree or PostGIS GiST index
  - [ ] Dynamic (drivers): Redis sorted set or in-memory quad-tree
  - [ ] Dual-tier: Redis absorbs real-time updates, ES serves ranked search
- [ ] Handle the non-uniform density problem:
  - [ ] Geohash cells are fixed-size: dense areas return huge candidate sets
  - [ ] Quad-trees adapt: dense areas get more subdivisions
  - [ ] Elasticsearch handles this internally via BKD tree balancing
- [ ] Discuss the polar latitude problem:
  - [ ] Geohash cells near poles are physically smaller (longitude degrees shrink)
  - [ ] A query in Helsinki returns fewer candidates than identical query in Miami
  - [ ] S2 fixes this with cube-face projection and Hilbert curve ordering

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
