# Portfolio Showcase

## Overview
How to present your projects, GitHub profile, writing samples, and demos in a way that demonstrates real capability and gives interviewers concrete material to discuss.

## Best Practices
- Curate 3-5 projects that demonstrate range -- include different domains, technologies, and levels of complexity
- For each project, prepare a 2-minute walkthrough that covers the problem, your approach, the technical decisions, and the result
- Keep your GitHub profile clean -- pin your best repos, write clear README files, and remove or archive abandoned projects
- Include a live demo or screenshots whenever possible -- seeing working software is far more compelling than reading code
- Write a concise README for every project: what it does, tech stack, architecture overview, and how to run it
- For writing samples (blog posts, tech talks, documentation), pick pieces that show clear thinking and depth, not just topic coverage
- Link everything from one central location -- a personal site or a single "Projects" section on your resume
- Make sure your portfolio is accessible and loads quickly -- broken links or slow pages lose credibility instantly

## Structure / Framework
For each portfolio piece, prepare these four elements:
1. **Problem Statement** (15 seconds): What real problem does this solve? Avoid "I built this to learn X."
2. **Technical Approach** (30-45 seconds): What architecture, patterns, or tools did you choose and why? Show trade-off thinking.
3. **Key Challenge** (20-30 seconds): What was the hardest part and how did you solve it? This is where interviewers probe depth.
4. **Outcome and Next Steps** (15 seconds): What was the result? What would you improve with more time?

## Good vs Bad Examples

**Bad (project description):** "Full Stack Todo App -- Built a todo application using React and Node.js. Features include CRUD operations and user authentication."

This is bad because it is a generic project with no differentiation, no mention of technical decisions, and no indication of what was learned or what makes it interesting.

**Good (project description):** "Real-time collaborative document editor. Built using CRDTs for conflict-free state synchronization across clients. Chose Yjs over OT because it simplified the server architecture to a pure relay layer. The hardest part was handling concurrent edits to the same paragraph -- I resolved this by implementing per-paragraph CRDT instances instead of one document-level instance. Deployed on Railway with WebSocket connections through a Redis backplane."

This is good because it demonstrates awareness of advanced concepts, explains a concrete technical decision with reasoning, shows problem-solving depth, and includes deployment details.

## Common Mistakes
- Having too many projects with no curation -- 20 shallow projects are less impressive than 3 deep ones
- Writing no README or a README that just says how to install dependencies -- missing the chance to explain design decisions
- Including only tutorial projects or course assignments with no personal extension or originality
- Using a GitHub profile photo or bio that is blank or unprofessional -- treat your profile as part of your resume
- Forgetting to mention a project during an interview even though it is on your resume -- if it is listed, be ready to discuss it
- Demo links that are broken, require complex setup, or depend on services that are no longer running
