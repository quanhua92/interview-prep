# Cloud Cost Optimization — Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is this about optimizing an existing system's costs or designing cost architecture for a new system?
  - [ ] What cloud provider(s) are we targeting (AWS, GCP, Azure, multi-cloud)?
  - [ ] What is the current monthly spend and what is the target reduction?
  - [ ] Are we optimizing compute, storage, networking, or all three?
  - [ ] Is there a Kubernetes cluster involved?
- [ ] List functional requirements (3-5 items):
  - [ ] Attribute costs to teams and services via tagging
  - [ ] Rightsize compute instances based on observed utilization
  - [ ] Purchase commitments (Savings Plans, RIs) for stable workloads
  - [ ] Implement S3 lifecycle policies for storage tier decay
  - [ ] Minimize egress costs (inter-AZ, internet, NAT gateway)
- [ ] List non-functional requirements (latency, availability, scale):
  - [ ] Cost visibility: tagged and attributable per team within 24 hours
  - [ ] Compute savings: 20-40% through rightsizing + commitments
  - [ ] Storage savings: 60-80% through lifecycle tiering
  - [ ] Budget alerts at 20% over baseline, wired to PagerDuty/Slack
- [ ] State your scale estimates (spend, instances, data volume):
  - [ ] Current monthly cloud spend and growth rate
  - [ ] Average EC2 CPU utilization (typically 10-20%, meaning 80% idle)
  - [ ] Data volume in S3 (e.g., 100TB of logs = $2,300/mo Standard vs $400/mo with lifecycle)
  - [ ] Inter-AZ traffic volume (e.g., 10TB/day = $30,000/month in internal traffic)
  - [ ] Number of Kubernetes nodes and average pod resource waste

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw the optimization sequence as a pipeline: Tag -> Rightsize -> Classify -> Commit -> Lifecycle -> Egress -> K8s -> FinOps
- [ ] Identify the main cost categories and their typical proportions:
  - [ ] Compute (EC2/EKS/RDS): typically 50-60% of cloud bill
  - [ ] Storage (S3/EBS/EFS): typically 15-20%
  - [ ] Data transfer/egress: typically 10-15% (often underestimated)
  - [ ] Managed services (CloudWatch, NAT Gateway, etc.): typically 10-15%
- [ ] Note the critical ordering: rightsizing MUST precede commitment purchasing
  - [ ] Buying RIs before rightsizing locks in a discount on a waste pattern
  - [ ] Savings Plans are preferred over RIs for flexibility ($/hr commitment, not instance-specific)
- [ ] Present the sequence and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Explain the optimization sequence with specifics:
  - [ ] Step 1 - Tag everything: mandatory tags (team, service, environment, cost-center) enforced via SCPs
  - [ ] Step 2 - Rightsize: use Compute Optimizer, p50 for batch workloads, p99 for online services
  - [ ] Step 3 - Classify workloads: baseline 24/7 -> Savings Plans; batch/ML -> Spot; spiky -> On-Demand
  - [ ] Step 4 - Purchase commitments: 1-yr Compute Savings Plans for steady-state baseline
  - [ ] Step 5 - Storage lifecycle: Standard (0-30d) -> S3-IA (30-90d) -> Glacier Instant (90-365d) -> Deep Archive or delete (365d+)
  - [ ] Step 6 - Audit egress: co-locate services in same AZ, VPC endpoints for S3/DynamoDB, CloudFront for internet egress
  - [ ] Step 7 - K8s efficiency: Karpenter replaces Cluster Autoscaler, VPA recommendation mode for pod rightsizing
  - [ ] Step 8 - Unit economics: cost per request, cost per user, cost per GB; showback -> chargeback
- [ ] Sketch the EC2 pricing tier comparison:
  - [ ] On-Demand: 0% discount, no commitment
  - [ ] Compute Savings Plan: ~66% discount, flexible across instance families
  - [ ] EC2 Instance Savings Plan: ~72% discount, locked to instance family
  - [ ] RI Standard 1-yr: ~40%, RI Standard 3-yr: ~60-70%
  - [ ] Spot: 70-90% discount, 2-min interruption notice
- [ ] Sketch the S3 lifecycle policy:
  - [ ] 0-30 days: S3 Standard ($0.023/GB)
  - [ ] 30-90 days: S3-IA ($0.0125/GB, save 46%)
  - [ ] 90-365 days: Glacier Instant ($0.004/GB, save 83%)
  - [ ] 365+ days: Glacier Deep Archive ($0.001/GB, save 96%) or delete
- [ ] Walk through the egress cost hierarchy:
  - [ ] Intra-AZ: free
  - [ ] Inter-AZ: $0.01/GB each way ($0.02 round-trip)
  - [ ] Internet egress: $0.09/GB via EC2/S3 vs $0.0085/GB via CloudFront (10x reduction)
  - [ ] NAT Gateway: $0.045/GB processing (avoid via VPC endpoints)
- [ ] Walk through the main optimization flow end-to-end:
  - [ ] Discovery: tag resources -> Cost Explorer per-team breakdown -> identify top spenders
  - [ ] Rightsizing: Compute Optimizer recommendations -> test on smaller instances 2 weeks -> apply
  - [ ] Commitment: after rightsizing, buy Savings Plans for baseline -> Spot for batch -> On-Demand for spikes
  - [ ] Storage: set lifecycle rules on every bucket -> enable Intelligent-Tiering for unknown access patterns
  - [ ] Egress: AZ affinity for chatty services -> VPC endpoints -> CloudFront CDN for internet-facing content

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss rightsizing methodology in depth:
  - [ ] Gather 14 days of CloudWatch/Prometheus metrics (CPU, memory, network, disk I/O)
  - [ ] Use p50 for batch jobs (control schedule, tolerate slower throughput), p99 for online services (need spike headroom + 20-30% buffer)
  - [ ] Memory is often the binding constraint, not CPU (Java services, ML inference, in-memory DBs)
  - [ ] Test one service at a time for 2 weeks; monitor latency, error rates, queue depth
  - [ ] Lyft cut costs 20% with this approach across ~50 services
- [ ] Explain spot instance strategy and risk mitigation:
  - [ ] Interruption rates are usually 1-5% for most instance types/AZs
  - [ ] Use Spot Fleet with diversification across multiple instance types and AZs
  - [ ] Implement checkpoint-every-30-minutes and spot interruption handlers for ML training
  - [ ] Without checkpointing, spot is a gamble; with checkpointing, spot is safe and standard
  - [ ] Netflix runs ~70% of compute on spot; typical ML clusters target 70% spot + 30% on-demand
- [ ] Address Kubernetes cost efficiency:
  - [ ] HPA scales pod replicas (20 pods peak, 3 at night = 85% savings during off-peak)
  - [ ] VPA fixes over-provisioning (recommendation-only mode first, then manual apply)
  - [ ] Karpenter replaces Cluster Autoscaler: provisions any node type, spot support via pod annotations, right-sizes nodes, consolidates workloads
  - [ ] Karpenter reduces node count 20-40% vs Cluster Autoscaler through better bin packing
  - [ ] Bin packing accuracy depends on accurate pod resource requests: VPA -> Goldilocks -> manual review
- [ ] Discuss FinOps maturity model:
  - [ ] Showback: teams see their spend, not charged (low friction, good starting point)
  - [ ] Chargeback: teams charged against budget (high friction, dramatically stronger optimization behavior)
  - [ ] Unit economics: cost per request, cost per active user, cost per GB processed
  - [ ] Budget alerts at 10-20% over 30-day rolling baseline, wired to PagerDuty/Slack
- [ ] Address the five most expensive cost mistakes:
  - [ ] Buying RIs before rightsizing (locks in waste pattern)
  - [ ] No S3 lifecycle policies (bills compound silently at Standard rates)
  - [ ] Ignoring inter-AZ egress in microservices ($50K+/month for 20-service architecture)
  - [ ] Over-provisioned K8s resource requests (4 CPU requested, 0.5 used = pay for 8x more nodes)
  - [ ] Spot without checkpointing (24-hour training job interrupted at hour 22 = restart from scratch)

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences: tag -> rightsize -> commit, with storage lifecycle, egress optimization, K8s bin packing, and FinOps unit economics
- [ ] State the trade-offs you made and why (flexibility of Savings Plans over RIs, spot interruption risk vs 70-90% savings, showback vs chargeback friction)
- [ ] Mention what you would improve with more time (automated rightsizing pipeline, real-time cost anomaly detection, Karpenter migration, chargeback integration with finance)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
