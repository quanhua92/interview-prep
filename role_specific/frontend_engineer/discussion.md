# Frontend Engineer

Building user interfaces that are fast, accessible, maintainable, and deliver a great user experience across devices.

## Core Competencies

| Area | Description | Proficiency Expectation |
|------|-------------|------------------------|
| JavaScript & TypeScript | Closures, prototypes, event loop, async/await, type systems, module systems | Explain JS internals; write type-safe application code |
| Framework Proficiency | React/Vue/Angular component lifecycle, hooks/Composition API, virtual DOM, reactivity | Build complex UIs; explain framework internals and trade-offs |
| CSS Architecture | BEM, CSS-in-JS, Tailwind, CSS Grid/Flexbox, specificity, responsive design | Build responsive layouts; choose and justify a CSS methodology |
| Web Performance | Core Web Vitals (LCP, FID, CLS), code splitting, lazy loading, tree shaking, bundling | Audit performance; propose and measure optimizations |
| Accessibility (a11y) | ARIA roles, semantic HTML, keyboard navigation, screen reader compatibility, WCAG | Build accessible interfaces; audit for a11y compliance |
| State Management | Local vs global state, Redux/Vuex/Pinia, context providers, server state caching | Choose appropriate state patterns; avoid over-engineering |
| Browser Rendering | Critical rendering path, layout, paint, compositing, reflow/repaint, GPU acceleration | Explain how browsers render pages; optimize rendering pipeline |
| Testing | Unit tests (Jest/Vitest), component tests, E2E (Cypress/Playwright), testing library | Write meaningful tests; describe a testing strategy |

## Common Interview Topics

- Explain the JavaScript event loop and how async operations work
- How does the virtual DOM work and why does it improve performance?
- Describe how you would optimize a slow-rendering page
- What is the critical rendering path and how do you optimize it?
- How do you manage global state in a large application?
- Explain closures and give a practical example
- How do you ensure accessibility in your components?
- Describe code splitting and lazy loading strategies
- What are the differences between CSS Grid and Flexbox?
- How would you implement infinite scroll?

## Key Terminology

- **Virtual DOM** -- Lightweight in-memory representation of the real DOM used for efficient diffing
- **Event loop** -- Mechanism that handles async callbacks, microtasks, and macrotasks
- **Critical rendering path** -- Sequence of steps the browser takes to convert HTML/CSS/JS into pixels
- **Core Web Vitals** -- Google's metrics for user experience: LCP, FID/INP, CLS
- **Tree shaking** -- Dead code elimination technique that removes unused exports during bundling
- **Hydration** -- Process of attaching event handlers to server-rendered HTML on the client
- **Reflow/Repaint** -- Browser recalculation of layout (reflow) or visual appearance (repaint)
- **Shadow DOM** -- Encapsulated DOM subtree that isolates component styles and markup

## Cross-References

- **System Design**: [URL Shortener](../../system_design/url_shortener/) (frontend forms), [Search Autocomplete](../../system_design/search_autocomplete/) (debounce, typeahead UX), [News Feed](../../system_design/news_feed/) (infinite scroll)
- **CS Fundamentals**: Networking (HTTP caching, CORS, REST), Algorithms (debounce, throttling), Web Security (XSS, CSRF, CSP)
