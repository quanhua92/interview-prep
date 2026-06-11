/*
 * P10: Metrics Aggregation Engine
 *
 * Simulate a Prometheus-style metrics aggregation system.
 * Ingest metric samples and compute aggregated results.
 *
 * Input: operations until "END":
 *   - COUNTER name value  (increment counter)
 *   - GAUGE name value     (set gauge)
 *   - HISTOGRAM name value (record observation)
 *   - QUERY type name      (query current value)
 *
 * For QUERY:
 *   - COUNTER: print cumulative sum
 *   - GAUGE: print last value
 *   - HISTOGRAM: print count, sum, min, max, avg
 *
 * Output: Result of each QUERY
 *
 * Skills: HashMap, metric types, aggregation
 */

use wasm_libs::*;
use std::collections::HashMap;

struct Counter { value: f64 }
struct Gauge { value: f64 }
struct Histogram { observations: Vec<f64> }

struct MetricsStore {
    counters: HashMap<String, Counter>,
    gauges: HashMap<String, Gauge>,
    histograms: HashMap<String, Histogram>,
}

impl MetricsStore {
    fn new() -> Self {
        MetricsStore {
            counters: HashMap::new(),
            gauges: HashMap::new(),
            histograms: HashMap::new(),
        }
    }

    fn counter_inc(&mut self, name: &str, value: f64) {
        self.counters
            .entry(name.to_string())
            .or_insert(Counter { value: 0.0 })
            .value += value;
    }

    fn gauge_set(&mut self, name: &str, value: f64) {
        self.gauges
            .entry(name.to_string())
            .or_insert(Gauge { value })
            .value = value;
    }

    fn histogram_observe(&mut self, name: &str, value: f64) {
        self.histograms
            .entry(name.to_string())
            .or_insert(Histogram { observations: Vec::new() })
            .observations.push(value);
    }

    fn query(&self, metric_type: &str, name: &str) -> Option<String> {
        match metric_type {
            "COUNTER" => self.counters.get(name).map(|c| format!("COUNTER {} {}", name, c.value)),
            "GAUGE" => self.gauges.get(name).map(|g| format!("GAUGE {} {}", name, g.value)),
            "HISTOGRAM" => self.histograms.get(name).map(|h| {
                let n = h.observations.len();
                if n == 0 {
                    format!("HISTOGRAM {} count=0 sum=0 min=0 max=0 avg=0", name)
                } else {
                    let sum: f64 = h.observations.iter().sum();
                    let min = h.observations.iter().cloned().fold(f64::INFINITY, f64::min);
                    let max = h.observations.iter().cloned().fold(f64::NEG_INFINITY, f64::max);
                    let avg = sum / n as f64;
                    format!("HISTOGRAM {} count={} sum={:.1} min={:.1} max={:.1} avg={:.1}",
                            name, n, sum, min, max, avg)
                }
            }),
            _ => None,
        }
    }
}

fn main() {
    let mut store = MetricsStore::new();

    loop {
        let line = read_line();
        if line == "END" { break; }
        let parts: Vec<&str> = line.split_whitespace().collect();
        match parts[0] {
            "COUNTER" => {
                let name = parts[1].to_string();
                let value: f64 = parts[2].parse().unwrap();
                store.counter_inc(&name, value);
                write_string(&format!("COUNTER {} +{}", name, value));
            }
            "GAUGE" => {
                let name = parts[1].to_string();
                let value: f64 = parts[2].parse().unwrap();
                store.gauge_set(&name, value);
                write_string(&format!("GAUGE {} ={}", name, value));
            }
            "HISTOGRAM" => {
                let name = parts[1].to_string();
                let value: f64 = parts[2].parse().unwrap();
                store.histogram_observe(&name, value);
                write_string(&format!("HISTOGRAM {} {}", name, value));
            }
            "QUERY" => {
                let metric_type = parts[1];
                let name = parts[2];
                match store.query(metric_type, name) {
                    Some(result) => write_string(&result),
                    None => write_string("NOT_FOUND"),
                }
            }
            _ => {}
        }
    }
    std::process::exit(0);
}
