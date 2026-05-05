# DevOps/SRE

Building and maintaining reliable, scalable infrastructure through automation, monitoring, and incident response practices.

## Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| CI/CD Pipelines | Build, test, deploy automation; pipeline stages; artifact management; rollback strategies | Design a full CI/CD pipeline; optimize for speed and reliability |
| Containers & Orchestration | Docker images, Kubernetes pods/services/deployments, Helm charts, resource management | Debug cluster issues; design a multi-service deployment |
| Infrastructure as Code | Terraform, CloudFormation, Pulumi, state management, modules, drift detection | Provision infrastructure declaratively; manage state safely |
| Monitoring & Alerting | Prometheus, Grafana, Datadog; metrics, dashboards, alerting rules, runbooks | Design an observability stack; reduce alert fatigue |
| Incident Management | Incident response流程, postmortems, blameless culture, war rooms, severity levels | Lead incident response; write effective postmortems |
| SLA/SLO/SLI | Defining reliability targets, error budgets, SLO-based alerting, reliability vs velocity | Set meaningful SLOs; make data-driven reliability decisions |
| Reliability Engineering | Chaos engineering, capacity planning, failure modes, redundancy, failover | Design for failure; perform capacity planning |
| Networking & Security | DNS, load balancing, TLS, VPC, firewall rules, secrets management, zero trust | Configure network architecture; manage secrets securely |

## Common Interview Topics

- Design a CI/CD pipeline for a microservices application
- Explain how Kubernetes handles pod scheduling and autoscaling
- How would you migrate from VMs to containers?
- Design a monitoring and alerting strategy for a production system
- Walk through how you would handle a production outage
- Explain Terraform state and how you would manage it in a team
- How do you define SLOs and error budgets?
- Describe a chaos engineering experiment you would run
- How do you manage secrets and credentials across environments?
- Design a blue-green deployment strategy with rollback capability

## Key Terminology

- **Error budget** -- Allowable amount of unreliability within an SLO before action is required
- **Toil** -- Repetitive, manual operational work that provides no enduring value
- **Blast radius** -- Scope of impact when a failure or change occurs in the system
- **Chaos engineering** -- Disciplined approach to identifying weaknesses by injecting controlled failures
- **Immutable infrastructure** -- Replacing rather than modifying infrastructure to ensure consistency
- **Helm** -- Package manager for Kubernetes that templates and deploys applications
- **Canary deployment** -- Releasing changes to a small subset of users before full rollout
- **Runbook** -- Documented procedures for responding to specific operational scenarios

## Cross-References

- **System Design**: [Distributed Cache](../../system_design/distributed_cache/) (infrastructure scaling), [Rate Limiter](../../system_design/rate_limiter/) (deployment and monitoring), [Ticket Booking](../../system_design/ticket_booking/) (concurrency and failover)
- **CS Fundamentals**: Networking (TCP/IP, DNS, load balancing), Operating Systems (processes, memory, file systems), Distributed Systems (consensus, replication, CAP theorem), Security (TLS, encryption, IAM)
