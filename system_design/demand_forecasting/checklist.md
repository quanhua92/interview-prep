# Design a Demand Forecasting System — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] What type of demand? Rideshare pickups, delivery orders, or inventory units?
  - [ ] What is the forecast horizon? 1-hour (real-time), 24-hour (staffing), or 7-day (planning)?
  - [ ] What is the spatial granularity? City, neighborhood, or block level?
  - [ ] What actions will be taken on the forecast? Driver repositioning, surge pricing, or staffing?
  - [ ] What is the cost asymmetry? Overestimation (wasted supply) vs underestimation (poor UX)?
- [ ] List functional requirements (3-5 items):
  - [ ] Forecast demand per geographic zone at regular intervals (e.g., 5-min buckets)
  - [ ] Produce multi-quantile predictions (P10/P50/P90) for risk-aware decisions
  - [ ] Ingest real-time features: recent demand, driver supply, weather, events
  - [ ] Feed downstream systems: surge pricing, driver repositioning, staffing
  - [ ] Support multiple forecast horizons (1h, 24h) with different latency budgets
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Low latency: forecasts generated within 5 seconds per cycle
  - [ ] Accuracy: WMAPE < 10% for 1h-ahead, < 20% for 24h-ahead
  - [ ] Online adaptation: model adjusts to distribution shifts within hours
  - [ ] Spatial fairness: no zone type with error > 2x global average
- [ ] State your scale estimates (zones, predictions, storage):
  - [ ] ~5,000 H3 zones per major city, ~50 cities = 250K zones
  - [ ] 288 time buckets/day/zone = ~72M predictions/day globally
  - [ ] ~1M ride requests/day per major city
  - [ ] Storage: ~900GB/year for time-series demand data

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw a simple box diagram: Event Stream -> [Flink Aggregator] -> [Feature Store] -> [Temporal GNN] -> [Forecast API] -> [Surge Pricing / Driver Repositioning]
- [ ] Identify the main operations and their access patterns:
  - [ ] `GET /api/v1/forecasts/city/{city_id}` — read forecasts for all zones (high QPS, every 5 min)
  - [ ] `GET /api/v1/forecasts/{zone_id}` — read single zone forecast (moderate QPS)
  - [ ] `POST /api/v1/features/ingest` — ingest real-time feature update (high QPS, streaming)
  - [ ] `GET /api/v1/monitoring/drift` — drift status (low QPS, monitoring)
- [ ] Note the read:write pattern and where caching helps:
  - [ ] Forecast inference is read-heavy: every 5 min, all zones need fresh predictions
  - [ ] Feature ingestion is write-heavy stream: real-time events flowing in continuously
  - [ ] Cache forecasts in Redis with 5-min TTL; cache features in Feast online store
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain spatial modeling choice and justify:
  - [ ] Per-zone independent models (ARIMA/Prophet): simple baseline, misses spatial correlation
  - [ ] Temporal GNN with H3 graph: captures neighbor spillover, transfers to new zones
  - [ ] State your choice: Temporal GNN for production, classical models as ensemble members
- [ ] Define API endpoints with method, path, request/response:
  - [ ] `GET /api/v1/forecasts/{zone_id}?horizon=60min` -> `{"p50": 42, "p10": 30, "p90": 55, "model_version": "gnn_v3"}`
  - [ ] `GET /api/v1/forecasts/city/{city_id}?horizon=60min` -> array of zone forecasts
  - [ ] `GET /api/v1/monitoring/wmape` -> `{"1h_ahead": 0.08, "24h_ahead": 0.17}`
- [ ] Sketch the database schema:
  - [ ] Table `demand_events`: `zone_id`, `timestamp`, `request_count`, `completion_count`, `surge_multiplier`
  - [ ] Table `zone_features`: `zone_id` (PK), `zone_type`, `neighbor_ids` (array of adjacent H3 cells)
  - [ ] Table `forecasts`: `zone_id`, `forecast_time`, `p10`, `p50`, `p90`, `model_version`, `generated_at`
- [ ] Discuss data store choices:
  - [ ] Time-series demand data: ClickHouse or TimescaleDB for fast range queries on zone+time
  - [ ] Feature store: Feast for online/offline feature serving with point-in-time correctness
  - [ ] Spatial graph: stored as adjacency list; edge weights from distance or correlation
- [ ] Walk through the main flow end-to-end:
  - [ ] Real-time event ingestion: ride requests -> Flink computes sliding-window aggregations -> Feast online store
  - [ ] Forecast generation: GNN reads latest features from Feast, runs spatial aggregation + GRU, outputs P10/P50/P90 per zone
  - [ ] Serving: forecasts cached in Redis, consumed by surge pricing and driver repositioning services
  - [ ] Monitoring: drift detection compares rolling WMAPE to threshold, triggers retraining if exceeded

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss the feedback loop problem:
  - [ ] Forecast -> surge pricing -> reduced demand -> biased training data
  - [ ] Model oscillates between over/under estimation at surge thresholds
  - [ ] Mitigation: train on requests not completions; include surge as feature; holdout zones for causal data
- [ ] Explain the Temporal GNN architecture:
  - [ ] SAGEConv aggregates neighbor node features at each timestep (spatial)
  - [ ] GRU processes the spatially-enriched time series (temporal)
  - [ ] Multi-quantile output heads (P10/P50/P90) via pinball loss
  - [ ] Cyclical encoding for time features (sin/cos) to avoid discontinuity
- [ ] Discuss online learning strategy:
  - [ ] Warm-start fine-tuning: initialize from previous weights, few gradient steps
  - [ ] Drift-triggered: monitor rolling WMAPE, retrain only when drift detected
  - [ ] Separate short-horizon and long-horizon models to prevent catastrophic forgetting
  - [ ] Lyft finding: model from a month ago can be 30-40% worse in WMAPE during rapid changes
- [ ] Explain metric choices:
  - [ ] WMAPE over MAPE: handles near-zero demand zones, focuses on high-demand periods
  - [ ] MAPE fails: division by zero at y=0, inflated percentage for tiny absolute errors
  - [ ] Quantile loss for asymmetric costs (underforecast is worse than overforecast)
- [ ] Address failure modes:
  - [ ] Spatial independence: high errors cluster geographically -> use GNN
  - [ ] New zones (cold start): transfer from neighbors via graph structure, zone-type priors
  - [ ] Temporal leakage: strict point-in-time feature joins; offline WMAPE >> online = leakage signal
  - [ ] Stale weather: sub-15-min updates, ensemble weight toward classical models in extreme weather
- [ ] Discuss A/B testing approach:
  - [ ] Zone-level holdout, not user-level (geographic clusters)
  - [ ] Buffer zones between treatment and control to prevent spillover
  - [ ] Measure business outcomes (driver utilization, pickup wait time) not just WMAPE
  - [ ] Run 30+ days to capture full weekly seasonality

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
