# Owning a Costly Mistake

## What Interviewers Look For
- Whether you proactively raise your hand when something goes wrong, rather than waiting to be caught
- Transparency -- do you communicate the full scope of the impact to stakeholders promptly?
- Evidence of a concrete corrective action plan, not just an apology
- Whether you put safeguards in place to prevent the same mistake from happening again

## STAR Framework Refresher
| Letter | Meaning | Guiding Question |
|--------|---------|-----------------|
| S | Situation | Set the scene in 1-2 sentences |
| T | Task | What was your responsibility or goal? |
| A | Action | What specific steps did YOU take? (use "I", not "we") |
| R | Result | What was the outcome? (quantify if possible) |

## Common Mistakes
- Minimizing the impact of the mistake to make yourself look better ("it only affected a few users")
- Hiding the mistake or hoping no one notices -- this is a major red flag for interviewers
- Shifting blame to circumstances, tools, or other team members even partially
- Skipping the prevention step -- the most important part is what you did to ensure it never happens again

## Story Mining Prompts
Think about these situations from your experience:
- Deployed a bug to production that caused customer-facing impact (errors, downtime, data issues)
- Made a wrong architectural decision that cost the team significant time or effort to undo
- Accidentally deleted or corrupted data (even in a staging environment with broader implications)
- Broke a production service during a routine change or deployment
- Made a mistake in a config file, database query, or infrastructure change with real consequences

## Good vs Bad Examples

**Bad:** "I once pushed a bug to production. I fixed it quickly and we moved on."

This is bad because it has no detail on the impact, no communication to stakeholders, no root cause analysis, and no prevention measure.

**Good:** "I deployed a database schema change without a rollback plan, and it locked the payments table for 12 minutes during peak traffic. I immediately notified the on-call channel, reverted the migration, and confirmed the table was back to normal within 18 minutes. I then wrote a postmortem documenting the root cause: I had skipped the rollback step in my deployment checklist because I was rushing. I worked with the team to add a mandatory rollback field to our deployment template that CI would reject if left empty. In the year since, every schema change on our team has included a tested rollback plan."

## Variations to Prepare
- "Tell me about a time you made a significant mistake at work."
- "Describe a situation where something you did caused a problem for your team or customers."
- "Give me an example of a time you had to deliver bad news about something you did."
- "How do you handle it when you realize you've made a serious error?"
