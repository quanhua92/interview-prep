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

struct Counter {
    value: f64,
}

struct Gauge {
    value: f64,
}

struct Histogram {
    observations: Vec<f64>,
}

struct MetricsStore {
    counters: std::collections::HashMap<String, Counter>,
    gauges: std::collections::HashMap<String, Gauge>,
    histograms: std::collections::HashMap<String, Histogram>,
}

impl MetricsStore {
    fn new() -> Self {
        todo!();
    }

    fn counter_inc(&mut self, name: &str, value: f64) {
        todo!();
    }

    fn gauge_set(&mut self, name: &str, value: f64) {
        todo!();
    }

    fn histogram_observe(&mut self, name: &str, value: f64) {
        todo!();
    }

    fn query(&self, metric_type: &str, name: &str) -> Option<String> {
        todo!();
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
