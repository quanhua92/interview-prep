# DevOps/SRE -- Prep Checklist

Use this checklist to track your preparation progress across core DevOps and Site Reliability Engineering competencies. Aim to complete every item before your interview window opens.

## Topic Prep Checklist per Competency

- [ ] **Linux and Networking**: Review file systems, process management, networking fundamentals (TCP/IP, DNS, load balancing, OSI model), and shell scripting.
- [ ] **Containerization**: Master Docker fundamentals (Dockerfile, multi-stage builds, image optimization) and container orchestration with Kubernetes (pods, services, deployments, namespaces).
- [ ] **CI/CD Pipelines**: Practice designing automated build, test, and deployment pipelines using GitHub Actions, GitLab CI, or Jenkins; understand deployment strategies.
- [ ] **Infrastructure as Code**: Be proficient with Terraform or Pulumi; understand state management, modules, and drift detection.
- [ ] **Monitoring and Alerting**: Review Prometheus, Grafana, and the three pillars of observability (metrics, logs, traces); design effective SLIs/SLOs/SLAs.
- [ ] **Incident Management**: Prepare to discuss incident response processes, blameless post-mortems, runbooks, and on-call practices.
- [ ] **Security and Compliance**: Understand DevSecOps principles, secrets management (Vault), container security scanning, and least-privilege access.
- [ ] **Cloud Platforms**: Be familiar with core services on at least one major cloud provider (AWS, GCP, or Azure) including compute, storage, networking, and IAM.
- [ ] **Reliability Engineering**: Understand chaos engineering (failure injection, game days), capacity planning, common failure modes, redundancy strategies, and failover mechanisms.
- [ ] **Toil and Blast Radius**: Be prepared to discuss reducing toil through automation, measuring blast radius of changes, and limiting the impact of failures.

## Practice Questions

1. How would you design a CI/CD pipeline that supports blue-green deployments with automatic rollback?
2. Explain the difference between a Deployment, a StatefulSet, and a DaemonSet in Kubernetes.
3. How do you define meaningful SLIs, SLOs, and SLAs for a web service?
4. Describe how you would migrate a legacy application to Kubernetes without downtime.
5. What is your approach to managing secrets across multiple environments in a CI/CD pipeline?
6. How would you debug a Kubernetes pod that is stuck in CrashLoopBackOff?
7. Explain how Terraform state works and how you would handle state locking in a team environment.
8. Design a monitoring stack for a microservices architecture. What would you collect and how?
9. How do you handle an incident where a production service is degraded but not completely down?
10. What is the difference between horizontal pod autoscaler and cluster autoscaler in Kubernetes?
11. Describe how you would implement infrastructure as code for a multi-region deployment.
12. How would you set up network policies in Kubernetes to restrict traffic between services?
13. Explain the concept ofGitOps and how tools like ArgoCD or Flux implement it.
14. What strategies would you use to reduce cloud infrastructure costs without sacrificing reliability?
15. Describe a chaos engineering experiment you would run to test the resilience of a production system.

## System Design Bridge Items

- [ ] Review [Distributed Cache](../../system_design/distributed_cache/) for infrastructure scaling, cache deployment patterns, and operational monitoring.
- [ ] Study [Rate Limiter](../../system_design/rate_limiter/) for deployment considerations, monitoring at scale, and distributed rate limiting infrastructure.
- [ ] Connect container orchestration knowledge to [Ticket Booking](../../system_design/ticket_booking/) for understanding concurrency handling, failover, and high-availability design.
- [ ] Review the distributed systems section for understanding consensus, leader election, and partition tolerance.
- [ ] Map monitoring and observability knowledge to the system reliability and failure handling sections.

## Practice Log

- [ ] 2026-05-__: Completed Linux, networking, and containerization deep-dive
- [ ] 2026-05-__: Walked through CI/CD pipeline and IaC design problems
- [ ] 2026-05-__: Mock interview session covering all DevOps/SRE competency areas
