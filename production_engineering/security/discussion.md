# Production Security Fundamentals

Source: [Security for Engineers: OWASP, Secrets, Supply Chain, and Least Privilege (CalibreOS)](https://www.calibreos.com/learn/prod-security-fundamentals)

## One-Liner
Apply defense-in-depth across application code (OWASP), secrets lifecycle, supply chain provenance, and IAM to build systems where secure behavior is the default.

## Functional Requirements
- Prevent injection attacks (SQL, command, LDAP) at the code level
- Enforce object-level authorization on every data access operation
- Manage secrets with rotation, never hardcode or rely solely on env vars
- Verify container image provenance from commit to running pod
- Scope IAM roles to minimum required permissions per service

## Non-Functional Requirements
- Secrets must rotate automatically without redeploy
- Service-to-service communication must be authenticated (mTLS)
- Supply chain must be auditable: know which components run where
- Blast radius of any single compromise must be bounded
- Security controls must be the path of least resistance for engineers

## Key Scale Questions
- OWASP Top 10 covers ~95% of production vulnerabilities; know the top 4 cold (Broken Access Control, Cryptographic Failures, Injection, Insecure Design)
- ~80% of codebases have dependencies with known CVEs (Log4Shell affected ~30K open-source packages as a transitive dependency)
- IDOR is consistently the highest-value bug bounty finding across all major platforms
- Capital One breach: SSRF + overpermissioned IAM role exfiltrated 100M+ records

## Core Components
- **OWASP Top 10 (2021)**: vulnerability taxonomy every engineer should know for code review
- **Parameterized Queries**: architectural fix for injection; input sanitization is insufficient
- **IDOR Prevention**: object-level authorization (`WHERE id = ? AND owner_id = ?`), UUIDs for external IDs
- **Secrets Manager (AWS) / Vault (HashiCorp)**: encrypted storage, automatic rotation, IAM-based access
- **External Secrets Operator (ESO)**: syncs secrets from store into K8s Secrets on a configurable interval
- **SBOM + Trivy/Snyk**: machine-readable inventory of all dependencies for rapid CVE response
- **Sigstore/cosign**: OIDC-backed image signing; admission webhooks reject unsigned images
- **SLSA Framework**: four levels of build pipeline hardening (L1 documented to L4 hermetic/reproducible)
- **IAM Workload Identity (IRSA/GCP Workload Identity)**: short-lived credentials via OIDC token exchange, no long-lived keys
- **mTLS (Istio/Linkerd)**: mutual authentication via sidecar proxies with automatic cert rotation

## Key Design Decisions

### Secrets Management Strategy
- **Option A: Environment variables**: better than hardcoded, but visible in `ps aux`, container specs, logs, crash dumps. No rotation mechanism.
- **Option B: AWS Secrets Manager**: encrypted with KMS, IAM-based access, auto-rotation for RDS/Redshift. Good for AWS-native workloads.
- **Option C: HashiCorp Vault**: dynamic secrets (short-lived DB credentials with TTL), PKI, SSH CA, cross-cloud. Best for complex patterns.
- **Recommended**: Use ESO for K8s so pods read K8s Secrets while the source of truth is the secret store. Rotation propagates without redeploy.

### Supply Chain Hardening
- **Option A: Dependabot/Renovate only**: automated PRs for CVEs, but PR fatigue leads to ignored updates.
- **Option B: SBOM + scanning in CI**: Syft generates SBOM, Trivy scans for CVEs. Queryable when new CVEs emerge.
- **Option C: Full SLSA pipeline**: signed provenance, hermetic builds, admission control. Most rigorous, highest engineering investment.
- **Recommended**: Start at B (SBOM + CI scanning), enforce image signing with cosign, target SLSA L2-L3.

### IAM Credential Model
- **Option A: IAM User + Access Key**: long-lived, manual rotation, frequently leaked. Never in production.
- **Option B: EC2 Instance Profile**: short-lived sessions via IMDS, auto-refreshed. Good for EC2.
- **Option C: EKS IRSA / GCP Workload Identity**: one IAM role per K8s ServiceAccount, OIDC-based, 1-hour tokens. Best for Kubernetes.
- **Recommended**: Use workload identity everywhere possible. One role per service per namespace.

## API Security Checklist
| Concern | Mitigation |
|---------|------------|
| SQL Injection | Parameterized queries; never concatenate user input |
| IDOR | Object-level authz: `WHERE id = ? AND owner_id = ?` |
| SSRF | IMDSv2, URL allowlisting, block RFC 1918 and 169.254.x.x |
| Path Traversal | Normalize with `os.path.realpath()`, verify starts with base dir |
| Secrets in logs | Log-scrubbing middleware for sensitive field names |
| Verbose errors | Generic error IDs in API responses; details internal only |
| Missing headers | HSTS, X-Content-Type-Options, CSP at load balancer level |
| Over-broad CORS | Explicit origin allowlist; never `*` on authenticated endpoints |

## Deep Dive Topics
- Defense-in-depth vs perimeter security: each layer (network, IAM, app code, mTLS) independently limits blast radius
- Threat modeling at design time: for every new service, enumerate what secrets it needs, what IAM role it runs as, and what happens if compromised
- Dynamic secrets vs static secrets: Vault creates short-lived DB credentials with TTL; eliminates long-lived password risk
- SPIFFE identity: `spiffe://cluster.local/ns/<namespace>/sa/<service-account>` encodes workload identity in mTLS certificates
- Cross-account IAM: role trust policies with time-limited sessions auditable in CloudTrail in both accounts

## Interview Signal by Level
- **L4/Mid**: Knows OWASP exists, explains SQL injection and parameterized queries, uses env vars for secrets, knows HTTPS matters
- **L5/Senior**: Distinguishes OWASP categories precisely (IDOR = broken access control, not auth), explains why env vars are still a risk, knows IAM roles vs users, has rotation strategy, explains mTLS and when needed
- **Staff**: Frames security as systems problem, threat models at design time, explains SLSA levels, knows workload identity, has opinions on defense-in-depth vs perimeter

## Follow-Up Variations
- How would you handle a Log4Shell-style vulnerability across 200 microservices?
- Design a secrets rotation strategy for a service that owns 50 database credentials
- How do you verify that the container running in production was built from an approved commit?
- A service is compromised via SSRF. What is the blast radius and how do you contain it?
