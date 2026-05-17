# Design a Shopping Cart & Checkout -- Working Checklist

Use this checklist each time you practice. Check items as you verbalize them.
The goal is to work through ALL items without referring to discussion.md.

## Phase 1: Requirements (2-3 min)
- [ ] State the problem back to the interviewer in your own words
- [ ] Ask clarifying questions:
  - [ ] Is the cart session-scoped (guest) or tied to a logged-in user, or both?
  - [ ] Is the price snapshot captured at add time or re-fetched at checkout?
  - [ ] Is inventory reserved on add or only at checkout submit?
  - [ ] Do we need promotions, coupons, and tax calculation?
  - [ ] Is multi-currency or guest checkout in scope?
- [ ] List functional requirements (3-5 items):
  - [ ] Users can add, update, and remove items from a cart
  - [ ] Cart persists across sessions; anonymous cart merges on login
  - [ ] Promotions are applied via a pluggable strategy engine
  - [ ] Checkout validates cart, reserves inventory, charges payment, creates Order
  - [ ] Submit is idempotent: same idempotency key yields exactly one Order
- [ ] List non-functional requirements:
  - [ ] Money as integer cents, never float
  - [ ] Cart is mutable and short-lived; Order is immutable and permanent
  - [ ] Optimistic concurrency for multi-tab/device edits
  - [ ] Cart persistence via repository abstraction (SQL, Redis, or DynamoDB)
- [ ] State key invariants:
  - [ ] One successful checkout with one idempotency key yields exactly one `order_id`
  - [ ] A paid Order is an immutable fact; catalog price changes never rewrite past orders

## Phase 2: High-Level Design (3-5 min)
- [ ] Draw the aggregate boundaries: Cart (mutable) vs Order (immutable)
- [ ] Identify core entities and their relationships:
  - [ ] `Cart` (aggregate root) -> contains `LineItem` collection
  - [ ] `LineItem` -> embeds `ProductSnapshot` (frozen price at add time)
  - [ ] `Order` (separate aggregate) -> receives copies of line snapshots
  - [ ] `CheckoutService` -> orchestrates via `PaymentPort`, `InventoryPort`, `TaxPort`
- [ ] Identify the main operations and their access patterns:
  - [ ] `POST /cart/{id}/items` -- add item to cart (write)
  - [ ] `PATCH /cart/{id}/items/{line_id}` -- update quantity (write)
  - [ ] `DELETE /cart/{id}/items/{line_id}` -- remove item (write)
  - [ ] `POST /cart/{id}/checkout` -- submit with idempotency key (write, critical)
  - [ ] `GET /cart/{id}` -- get cart with totals (read)
- [ ] Note why Cart and Order must be separate aggregates:
  - [ ] Cart is a working document; Order is a legal/financial record
  - [ ] Conflating them ("just mark cart paid") is not auditable
  - [ ] Order receives snapshot copies so catalog changes do not rewrite history
- [ ] Present the diagram and get alignment

## Phase 3: Core Component Design (5-8 min)
- [ ] Define key classes with their fields:
  - [ ] `ProductSnapshot`: `product_id`, `title`, `unit_cents` (MoneyCents), `currency` (frozen dataclass)
  - [ ] `LineItem`: `line_id`, `snapshot: ProductSnapshot`, `qty`, `options` (value objects)
  - [ ] `Cart`: `cart_id`, `customer_id` (nullable), `session_id`, `items: List[LineItem]`, `version`
  - [ ] `Order`: `order_id`, `lines: List[LineItem]` (copies), `status` (CREATED/PAID/FULFILLED/CANCELLED)
  - [ ] `IdempotentOrderFactory`: `_done: Dict[str, str]`, `create_once(idem_key, build_fn)`
- [ ] Explain ProductSnapshot vs live Product reference:
  - [ ] Snapshot freezes price at add time to prevent retroactive cart changes
  - [ ] A LineItem that only stores `product_id` and re-fetches live price causes wrong totals and disputes
- [ ] Sketch the CheckoutService as a thin orchestrator:
  - [ ] `submit(cart_id, idempotency_key)` -> validate -> `InventoryPort.reserve()` -> build Order draft -> `PaymentPort.charge()` -> persist
  - [ ] Ports are interfaces, mockable, swappable for tests
- [ ] Explain the idempotency mechanism:
  - [ ] Check idempotency table for existing successful submission before any Order insert
  - [ ] Same key + different body must error (Stripe semantics)
  - [ ] At-least-once transport with idempotent handler
- [ ] Walk through the main flow end-to-end:
  - [ ] Add to cart: create `ProductSnapshot` from catalog, append `LineItem` to `Cart`
  - [ ] Checkout: validate cart -> reserve inventory -> copy lines to Order -> charge -> persist
  - [ ] Merge on login: `CartMergePolicy` unions by `product_id + options`, sums quantities, resolves price conflicts

## Phase 4: Deep Dive (5-10 min, interviewer-directed)
- [ ] Discuss optimistic concurrency control:
  - [ ] `cart_version` on the aggregate, `expected_version` on every mutating request
  - [ ] `UPDATE ... WHERE cart_id=? AND version=?` -- zero rows = 409 Conflict
  - [ ] Client refetches and retries; no long-lived locks on hot session rows
- [ ] Explain inventory reservation trade-offs:
  - [ ] Advisory until submit: correct for most catalog goods, rare oversell on flash
  - [ ] Reserve-on-add with TTL: needed for scarce SKUs, requires orphan sweeper
  - [ ] State which model applies and when to switch
- [ ] Discuss PromotionEngine design:
  - [ ] `PromotionRule` strategy pattern (BOGO, category discount, free shipping)
  - [ ] Engine walks lines, returns `PriceAdjustment` list
  - [ ] Cart has zero knowledge of promotion rules (SRP)
- [ ] Address scaling considerations:
  - [ ] Cart document can migrate to Redis/DynamoDB; only `CartRepository` changes
  - [ ] Anonymous carts: TTL-based expiration; logged-in carts: persist until checkout
  - [ ] Sticky routing to same shard for read-your-writes
- [ ] Discuss cart merge edge cases:
  - [ ] Price mismatch between anonymous cart snapshot and catalog: reprice, warn, or split?
  - [ ] Must run merge in one transaction with single version bump
- [ ] Handle PCI/security concerns:
  - [ ] Never store PAN/CVV on Cart; use PSP tokens only
  - [ ] Domain idempotency key is separate from Stripe's key; mirror at submit with own uniqueness on `(tenant, idempotency_key)`

## Phase 5: Wrap-Up (2-3 min)
- [ ] Summarize the design in 2-3 sentences:
  - [ ] Cart is a mutable aggregate with ProductSnapshots for audit-safe pricing
  - [ ] CheckoutService orchestrates via injected ports with idempotent submit
  - [ ] Order is an immutable fact, sealed at payment, never rewritten by catalog changes
- [ ] State the trade-offs you made and why
- [ ] Mention what you would improve with more time (partial shipments, marketplace multi-seller, cart expiration)
- [ ] Ask the interviewer if they have questions

## Practice Notes
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
- Date: _______  Score: ___/10  Notes:
