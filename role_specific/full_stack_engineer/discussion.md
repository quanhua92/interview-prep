# Full-Stack Engineer

Delivering end-to-end features spanning frontend, backend, and infrastructure with the ability to navigate trade-offs between depth and breadth.

## Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| Frontend Fundamentals | HTML/CSS/JS, a major framework (React/Vue/Angular), responsive design, accessibility | Build complete UI features; debug browser issues |
| Backend Fundamentals | REST/GraphQL APIs, server-side frameworks, authentication, request handling | Design and implement APIs end-to-end |
| API Design | RESTful conventions, GraphQL schemas, versioning, error handling, documentation | Design APIs that work well for frontend consumption |
| Database Management | SQL queries, ORM usage, migrations, basic indexing, data modeling for applications | Manage application data layer; handle migrations safely |
| Authentication & Security | Session/JWT auth, OAuth flows, XSS/CSRF prevention, secure headers | Implement auth flows; harden against common web vulnerabilities |
| Deployment & DevOps | Basic CI/CD, container fundamentals, environment management, deployment strategies | Deploy applications; understand the full delivery pipeline |
| System Integration | Third-party APIs, webhooks, service-to-service communication, data synchronization | Integrate external services; handle failure and retry logic |
| Trade-off Awareness | Depth vs breadth decisions, when to specialize, rapid prototyping vs production readiness | Make pragmatic technology choices; communicate limitations |

## Common Interview Topics

- Build a full-stack feature (e.g., real-time chat, file upload with preview)
- How do you structure a full-stack application (monolith vs separate repos)?
- Design the data model and API for a specific feature
- How do you handle authentication across frontend and backend?
- Describe your approach to error handling from frontend to backend
- How would you set up a CI/CD pipeline for a full-stack application?
- When would you choose a monolith vs microservices?
- How do you manage state between the client and server?
- Describe how you would optimize a slow page that involves API calls
- How do you approach testing across the full stack?

## Key Terminology

- **Monolith** -- Single deployable unit containing all application logic (frontend + backend)
- **BFF (Backend for Frontend)** -- Dedicated backend service tailored to a specific frontend client
- **SSR (Server-Side Rendering)** -- Generating HTML on the server for faster initial page loads and SEO
- **API gateway** -- Single entry point that routes requests to appropriate backend services
- **Optimistic update** -- Updating the UI immediately before server confirmation, rolling back on failure
- **ORM (Object-Relational Mapper)** -- Abstraction layer that maps database records to application objects
- **Environment parity** -- Keeping development, staging, and production environments consistent
- **Feature flag** -- Mechanism to enable or disable functionality without deploying new code

## Cross-References

- **System Design**: [URL Shortener](../../system_design/url_shortener/) (full end-to-end feature), [Chat System](../../system_design/chat_system/) (real-time full-stack), [Search Autocomplete](../../system_design/search_autocomplete/) (frontend + backend + caching)
- **CS Fundamentals**: Networking (HTTP, WebSockets, REST), Databases (SQL, ACID, indexing), Web Security (XSS, CSRF, CORS), Algorithms (for both frontend and backend coding rounds)
