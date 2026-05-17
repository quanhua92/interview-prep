# Cloud Cost Optimization: From Runaway Bills to Unit Economics

Source: [Cloud Cost Optimization: From Runaway Bills to Unit Economics (CalibreOS)](https://www.calibreos.com/learn/prod-cloud-cost-optimization)

## One-Liner
Reduce cloud spend systematically through rightsizing, commitment purchasing, storage lifecycle policies, egress optimization, Kubernetes bin packing, and FinOps unit economics.

## Functional Requirements
- Attribute cloud costs to teams and services (tagging, cost allocation)
- Rightsize compute instances based on observed utilization (p50 for batch, p99 for online)
- Purchase commitments (Savings Plans, Reserved Instances) to lock in discounts for stable workloads
- Implement S3 lifecycle policies that automatically decay data through storage tiers
- Minimize egress costs through AZ affinity, VPC endpoints, and CDN offloading
- Enable Kubernetes cost efficiency via HPA, VPA, and Karpenter bin packing
- Track unit economics (cost per request, cost per user, cost per GB processed)

## Non-Functional Requirements
- Cost visibility within 24 hours (tagged and attributable per team)
- 20-40% reduction in compute spend through rightsizing + commitments
- 60-80% reduction in storage costs through lifecycle tiering
- 10x reduction in internet egress via CloudFront CDN ($0.09/GB to $0.0085/GB)
- Budget alerts at 20% over baseline, wired to PagerDuty/Slack (not just email)
- FinOps chargeback integrated into sprint reviews for behavioral change

## Key Scale Questions
- 10-20% average CPU utilization across EC2 fleet (80% idle compute)
- $50K/month bill triggers CTO attention; $200K/month triggers platform hire; $500K/month triggers board-level unit economics review
- 100TB of logs: $2,300/month at S3 Standard vs ~$400/month with lifecycle policies
- 10TB/day inter-AZ traffic between microservices = $30,000/month in internal traffic
- Netflix runs ~70% of compute on spot instances, saving $60M+/year
- Lyft cut costs 20% purely by rightsizing EC2 instances

## Core Components
- **Cost Allocation Tags**: team, service, environment, cost-center on every resource; enforced via SCPs or Terraform
- **AWS Compute Optimizer**: free tool analyzing 14 days of CloudWatch metrics for rightsizing recommendations
- **Savings Plans**: flexible $/hour commitment across instance families (~66% discount for Compute, ~72% for EC2 Instance)
- **Reserved Instances**: specific instance-type commitment (~40% for 1-yr, ~60-70% for 3-yr)
- **Spot Instances**: 70-90% discount with 2-min interruption notice; for batch/ML/CI workloads
- **S3 Lifecycle Policies**: Standard -> S3-IA (30d) -> Glacier Instant (90d) -> Glacier Deep Archive (365d) or delete
- **CloudFront CDN**: internet egress from $0.09/GB to $0.0085/GB for high-volume content
- **VPC Endpoints**: eliminate NAT Gateway charges ($0.045/GB) for S3 and DynamoDB traffic
- **Karpenter**: replaces Cluster Autoscaler; topology-aware scheduling, spot support, bin packing, node consolidation
- **HPA/VPA**: Horizontal Pod Autoscaler for replica scaling; Vertical Pod Autoscaler for rightsizing requests
- **FinOps Dashboards**: cost per request, cost per user, cost per GB; showback vs chargeback

## Key Design Decisions

### Optimization Sequence (Must Follow This Order)
- **Option A: Buy RIs first**: Locks in discount on a waste pattern. RI is non-transferable to smaller instance type. Cannot change for a year. This is the #1 cost mistake.
- **Option B: Rightsize first, then commit**: Eliminate waste (80% idle) before purchasing commitments. Savings Plans then apply to the rightsized fleet. Correct order.
- **Option C: Tag first, rightsize second, commit third**: Add visibility before action. Without tagging, AWS Cost Explorer shows a total bill with no attribution. Full sequence: tag -> rightsize -> classify workloads -> purchase commitments -> lifecycle policies -> egress audit -> K8s efficiency -> unit economics dashboards.

### Workload Classification
- **Baseline 24/7 (no interruption tolerance)**: Reserved Instances or Savings Plans
- **Batch/ML training (can tolerate interruption and retry)**: Spot Instances (70-90% discount)
- **Spiky, unpredictable, short-lived**: On-Demand with autoscaling
- **Production pattern**: Savings Plans for baseline + Spot for batch + On-Demand for spikes

### Kubernetes Autoscaling Strategy
- **HPA**: Scales pod replicas based on CPU/custom metrics. Primary cost tool for online services. 20 pods at peak, 3 at night = 85% savings during off-peak.
- **VPA**: Analyzes historical usage, updates pod resource requests. Use in recommendation-only mode (requires pod restarts, incompatible with HPA on same metric).
- **Karpenter**: Replaces Cluster Autoscaler. Provisions any node type that fits pending pods. Supports spot instances via pod annotations. Right-sizes nodes. Consolidates workloads. 20-40% node count reduction vs Cluster Autoscaler.

## Cost Comparison Tables

### EC2 Pricing Tier Comparison
| Pricing Model | Discount vs On-Demand | Commitment | Interruption Risk | Best For |
|---------------|----------------------|------------|-------------------|----------|
| On-Demand | 0% | None | None | Short-lived, unpredictable, compliance-sensitive |
| Savings Plan (Compute) | ~66% | 1 or 3 yr $/hr | None | Baseline 24/7 load across any instance family |
| Savings Plan (EC2 Instance) | ~72% | 1 or 3 yr $/hr | None | Stable load in a specific instance family |
| RI (Standard 1-yr) | ~40% | 1 yr, specific type | None | Stable DB/service on fixed instance type |
| RI (Standard 3-yr) | ~60-70% | 3 yr, specific type | None | Core infrastructure with 3-yr certainty |
| Spot Instance | 70-90% | None | 2-min notice (AWS) | ML training, batch ETL, CI/CD, stateless web tier |

### S3 Storage Class Cost Comparison
| Storage Class | Storage $/GB/mo | Retrieval $/GB | Retrieval Time | Best Use Case |
|--------------|----------------|---------------|---------------|---------------|
| S3 Standard | $0.023 | Free | Milliseconds | Active data, last 30 days of logs |
| S3 Intelligent-Tiering | $0.023 + $0.0025/1K obj | Free | Milliseconds | Unknown access patterns, ML experiment artifacts |
| S3 Infrequent Access | $0.0125 | $0.01 | Milliseconds | Monthly-or-less access, historical datasets |
| Glacier Instant Retrieval | $0.004 | $0.03 | Milliseconds | Quarterly access, compliance archives |
| Glacier Flexible Retrieval | $0.0036 | $0.01 (bulk) | 3-5 hours | Annual access, regulatory archives |
| Glacier Deep Archive | $0.00099 | $0.0025 (bulk) | 12 hours | Compliance-only cold storage |

### Egress Cost Hierarchy
| Traffic Type | Cost | Notes |
|-------------|------|-------|
| Intra-AZ | Free | Same Availability Zone |
| Inter-AZ | $0.01/GB each way ($0.02 round-trip) | Most common surprise in microservices |
| Cross-region | $0.02-0.09/GB | Depends on region pair |
| Internet egress (EC2/S3) | $0.09/GB (first 10TB) | Tiered: $0.085, $0.07, $0.05 at higher volume |
| Internet egress (CloudFront) | $0.0085/GB | 10x reduction for CDN-eligible content |
| NAT Gateway | $0.045/GB | Avoid via VPC endpoints for S3/DynamoDB |

## Deep Dive Topics
- Rightsizing methodology: gather real utilization data (Compute Optimizer/Datadog/Prometheus) -> use p50 for batch, p99 for online -> test 2 weeks on smaller instance -> memory is often binding constraint (Java, ML inference, in-memory DB)
- Spot instance reliability: interruption rates usually 1-5% for most instance types in most AZs; use Spot Fleet with diversification across multiple instance types and AZs
- Bin packing accuracy: VPA recommendation mode -> Goldilocks dashboard -> manual review -> apply and monitor; over-provisioned requests (4 CPU requested, 0.5 CPU used) make bin packing impossible
- AZ affinity as cost decision: Karpenter's topology-aware scheduling places communicating pods in same AZ, eliminating inter-AZ charges
- FinOps maturity: showback (visibility, low friction) -> chargeback (teams charged against budget, high friction, strong behavior change)
- Checkpointing for spot: implement checkpoint-every-30-minutes and spot interruption handlers; without checkpointing, spot is a gamble

## Follow-Up Variations
- Your AWS bill tripled last quarter: walk through diagnosing and fixing it
- How do you decide between reserved instances, savings plans, and spot instances for a production workload?
- Design the cost architecture for a 50TB/day ML training pipeline
- How would you implement chargeback across 20 engineering teams with shared infrastructure?
- A team's training GPU cluster costs $200K/month but utilization is 15%: what do you do?
- Your Kubernetes cluster has 40% node waste from over-provisioned pod requests: fix it
