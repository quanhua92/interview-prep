# Design a Demand Forecasting System

Source: [Demand Forecasting (CalibreOS)](https://www.calibreos.com/learn/mlsd-demand-forecasting)

## One-Liner
Predict future demand (e.g., ride requests, delivery orders) per geographic zone per time interval, using spatial-temporal ML that captures cross-zone correlations, adapts online to shifting conditions, and accounts for the feedback loop where forecasts drive pricing which changes actual demand.

## Functional Requirements
- Forecast demand per H3 zone at 5-minute intervals for 1-hour horizon (short-term) and 24-hour horizon (staffing)
- Support spatial granularity from neighborhood level (~50 zones/city) to block level (~5,000 zones/city)
- Ingest real-time features: recent demand, driver supply, weather, events, surge pricing state
- Produce multi-quantile forecasts (P10/P50/P90) for risk-aware supply decisions
- Feed forecasts into downstream systems: surge pricing engine, driver repositioning, staffing scheduler

## Non-Functional Requirements
- Forecast latency under 5 seconds for 1-hour-ahead predictions across all zones
- WMAPE < 10% for 1h-ahead, < 20% for 24h-ahead
- Online adaptation: model must adjust to distribution shifts within hours, not days
- Handle 5,000+ zones per city, updating every 5 minutes
- Spatially balanced accuracy: no zone type with MAE > 2x global

## Key Scale Questions
- ~5,000 H3 zones per major city, ~50 cities = 250K zones globally
- 5-minute intervals = 288 predictions/zone/day = ~72M predictions/day globally
- ~1M ride requests/day in a major city; feature vectors updated every 5 min
- Storage: time-series demand data ~10KB/zone/day x 250K zones x 365 days = ~900GB/year
- Read-heavy at inference: every 5 minutes, all zones need fresh forecasts

## Core Components
- **Feature Store (Feast)**: serves online features (recent demand, driver supply, weather) and offline features (historical seasonality, zone type)
- **Stream Processor (Flink)**: computes sliding-window aggregations (5/15/30 min demand) from real-time event stream
- **Spatial Graph Builder**: constructs H3 hexagonal adjacency graph; nodes = zones, edges = neighbor relationships
- **Temporal GNN (SAGEConv + GRU)**: spatial aggregation via GraphSAGE layers, temporal dynamics via GRU, outputs multi-quantile forecasts
- **Online Adaptation Layer**: drift detection monitors WMAPE degradation; triggers warm-start fine-tuning when drift exceeds threshold
- **Ensemble Meta-Learner**: combines GNN forecasts with classical baselines (Prophet, ARIMA) for robustness; classical models serve as fallback during extreme events
- **Forecast Serving API**: exposes predictions to downstream systems (surge pricing, driver repositioning)

## Key Design Decisions

### Spatial Modeling: Per-Zone vs Joint Graph
- **Per-zone independent models (ARIMA/Prophet per zone)**: simple, misses spatial autocorrelation. A concert spike in zone A also affects adjacent zones B and C. Independent models cannot use neighboring zone signals.
- **Joint spatial model (Temporal GNN)**: H3 zones as graph nodes, edges connect neighbors. SAGEConv aggregates neighbor signals at each timestep, GRU captures temporal dynamics. Captures spillover, transfers learning to new zones via graph connections.
- **Choice**: Temporal GNN for production. Independent models acceptable as v1 baseline or for long-horizon forecasts where spatial signal is weaker.

### Metric: MAPE vs WMAPE
- **MAPE (mean absolute percentage error)**: undefined when actual demand is 0; inflates errors for low-demand zones (3 AM zone with 0.1 vs 0.2 rides = 50% error, same as 500 vs 1000 at rush hour).
- **WMAPE (weighted MAPE = sum|y - y_hat| / sum(y))**: normalizes by total demand volume. Low-demand zones contribute little. Mirrors business impact.
- **Choice**: WMAPE as primary metric. Quantile loss (pinball) when under/overforecast costs are asymmetric.

### Online Learning Strategy
- **Incremental batch retraining**: hourly sliding window retrain. Simple but expensive for GNNs.
- **Warm-start fine-tuning**: initialize from previous weights, few gradient steps. 10-100x faster.
- **Drift-triggered retraining**: only retrain when drift detected (WMAPE degradation). Balances freshness and compute.
- **Online gradient descent**: continuous updates per mini-batch. Risk of catastrophic forgetting.
- **Choice**: Warm-start fine-tuning triggered by drift detection. Separate short-horizon and long-horizon models to prevent forgetting.

### Feedback Loop (Forecast -> Pricing -> Demand)
- Forecast drives surge pricing; surge pricing reduces actual demand; model trains on price-affected demand, not counterfactual demand. Creates oscillation: forecast high -> surge -> lower observed -> model reduces forecast -> no surge -> high observed -> repeat.
- **Mitigation**: train on ride requests (not completions); include surge multiplier as explicit feature; maintain holdout zones with no pricing intervention for causal ground truth.

## API Endpoints
| Method | Path | Description |
|--------|------|-------------|
| GET | /api/v1/forecasts/{zone_id}?horizon=60min | Get demand forecast for a zone |
| GET | /api/v1/forecasts/city/{city_id}?horizon=60min | Get forecasts for all zones in a city |
| POST | /api/v1/features/ingest | Ingest real-time feature update |
| GET | /api/v1/monitoring/drift | Get drift detection status per zone |
| GET | /api/v1/monitoring/wmape | Get WMAPE metrics by zone and horizon |

## Database Schema
| Table | Column | Type | Notes |
|-------|--------|------|-------|
| demand_events | zone_id | STRING | H3 hex ID |
| demand_events | timestamp | TIMESTAMP | 5-min bucket |
| demand_events | request_count | INT | Ride requests in bucket |
| demand_events | completion_count | INT | Completed rides |
| demand_events | surge_multiplier | FLOAT | Active surge at that time |
| zone_features | zone_id | STRING | H3 hex ID (PK) |
| zone_features | zone_type | STRING | Airport, residential, commercial, etc. |
| zone_features | neighbor_ids | ARRAY<STRING> | Adjacent H3 zones |
| forecasts | zone_id | STRING | H3 hex ID |
| forecasts | forecast_time | TIMESTAMP | Target time bucket |
| forecasts | p10 / p50 / p90 | FLOAT | Quantile forecasts |
| forecasts | model_version | STRING | GNN model version |
| forecasts | generated_at | TIMESTAMP | When forecast was produced |

## Deep Dive Topics
- **H3 geohashing**: Uber's hexagonal spatial indexing system. Hexagons tile the plane with equal-area cells and consistent neighbor counts (6 neighbors). Resolution 8 (~0.74 km^2) typical for rideshare. Graph construction: each H3 cell is a node, edges to its 6 neighbors.
- **Temporal GNN architecture**: SAGEConv layers aggregate neighbor node features (spatial), GRU processes the spatially-enriched time series (temporal). Multi-quantile output heads (P10/P50/P90) for uncertainty quantification.
- **Cyclical encoding**: encode hour-of-day, day-of-week as sin/cos pairs. Hour 23 and hour 0 are adjacent in time but 23 apart in integer encoding; sin/cos makes them geometrically close.
- **Drift detection**: monitor rolling WMAPE per zone cluster. When error exceeds threshold (e.g., 1.5x recent average), trigger warm-start fine-tuning on latest data window.
- **A/B testing with zone holdouts**: split by geographic zone clusters (not users). Use buffer zones between treatment and control to prevent spillover. Run for 30+ days to capture weekly seasonality.

## Follow-Up Variations
- How would you handle a new city launch with no historical demand data?
- What happens when a major event (concert, sports game) creates demand patterns not in training data?
- How would you design the system for inventory forecasting (SKU-level) instead of rideshare?
- How do you prevent the GNN from catastrophic forgetting when fine-tuning on recent data?
- What if forecasts need to be at 1-minute resolution instead of 5-minute?
