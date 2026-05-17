# Design a Shopping Cart & Checkout

Source: [LLD Case Study: Online Shopping Cart & Checkout (CalibreOS)](https://www.calibreos.com/learn/lld-shopping-cart)

## One-Liner
Design a production-grade shopping cart with immutable product snapshots, idempotent checkout, and clear Cart-vs-Order aggregate boundaries.

## Requirements

### Functional Requirements
- Add, update, and remove items from a cart (guest and authenticated)
- Persist cart across sessions (merge anonymous cart on login)
- Apply promotions and discounts via a pluggable strategy
- Calculate tax by jurisdiction
- Checkout: validate cart, reserve inventory, charge payment, create an immutable Order
- Support idempotent submit to prevent duplicate orders on retry

### Non-Functional Requirements
- Money stored as integer cents (never float)
- Cart is mutable and short-lived; Order is immutable and permanent
- Optimistic concurrency control for multi-tab/device edits
- Cart persistence via repository abstraction (swap SQL for Redis/DynamoDB)

### Clarifying Questions
- Cart ownership: session-scoped vs logged-in user (need both, merge on login)
- Price source: snapshot at add time vs live catalog (snapshot to avoid disputes)
- Inventory: advisory on add vs reserve at checkout (advisory for general goods, reserve for scarce SKUs)
- Multi-currency: Money in minor units + Currency on cart; FX is a separate service

## Key Concepts

### Core Entities
- **Cart** (aggregate root): mutable working document, holds `CartId`, `CustomerId` (nullable), `session_id`, collection of `LineItem`s
- **LineItem**: holds `line_id`, `ProductSnapshot`, `quantity`, `options` (size/color as value objects)
- **ProductSnapshot** (frozen value object): `product_id`, `title`, `unit_cents` (MoneyCents), `currency` -- captured at add time so catalog reprices do not retroactively alter the cart
- **Order** (separate aggregate): immutable post-checkout record, states: `CREATED`, `PAID`, `FULFILLED`, `CANCELLED`
- **PriceAdjustment**: output of promotion engine, applied as line-level discounts

### Key Patterns
- **Aggregate Root**: Cart and Order are separate aggregates with different lifecycles
- **ProductSnapshot**: freeze price at add time to prevent catalog repricing from altering open carts
- **Strategy Pattern**: `PromotionRule` implementations (BOGO, category discount, free shipping threshold) plugged into `PromotionEngine`
- **Idempotent Receiver**: `IdempotentOrderFactory.create_once(idem_key, build_fn)` -- checks idempotency table before Order insert
- **Port/Adapter**: `PaymentPort`, `InventoryPort`, `TaxPort` as interfaces on `CheckoutService`; Cart stays a pure domain aggregate with no network I/O

### Not-Hire Mistakes
- Using `float` for money
- `User.shoppingList` as a string array of SKUs
- No `Order` entity ("just mark cart paid")
- Ignoring idempotency and retries on mobile clients
- Singleton `Cart` in global scope
- Storing PAN/CVV on Cart (PCI violation)
- Hardcoding coupon logic as `if coupon_code == 'X'` inside Cart methods

## Decisions

### Cart vs Order Boundary
- Cart is mutable, short-lived, keyed by `(customer_id, session_id)` with TTL
- Order is immutable, permanent, created once on successful checkout
- Order receives copies of line snapshots so catalog changes never rewrite historical charges
- Wrong: "we just mark cart paid" -- not auditable, conflates two aggregates

### Price Snapshot Timing
- Snapshot per line at add time (default): avoids customer shock and audit disputes
- Alternative: snapshot at checkout (risk: customer sees different price than expected)
- Must state the business rule explicitly during merge-on-login price conflicts

### Inventory Reservation Model
| Model | Correct For | Risk |
|-------|-------------|------|
| Advisory until submit | Most catalog goods | Rare oversell on flash unless checkout locks |
| Reserve-on-add with TTL | Scarce SKUs, sneaker drops | Orphaned reservations need sweeper |
| Eternal client-side hold | Nothing real | Inventory drift |

### Cart Merge on Login
- `CartMergePolicy` (default: union by `product_id + options`, sum quantities)
- Price conflict resolution: must state one rule -- reprice line, keep snapshot, or split into "stale price" line

### CheckoutService Design
- Thin orchestrator with injected ports: `PaymentPort.charge()`, `InventoryPort.reserve()`, `TaxPort.calculate()`
- `submit(cart_id, idempotency_key)` checks idempotency table before any Order insert
- Same key + different body must error (Stripe semantics), not silently reuse

## Deep Dives

### Idempotent Checkout Flow
1. Client sends `POST /checkout` with `idempotency_key`
2. Look up prior submission with that key -- if found, return existing Order
3. Validate cart (non-empty, items still available)
4. Call `InventoryPort.reserve()` inside checkout transaction
5. Build Order draft from cart line snapshots (copies, not references)
6. Call `PaymentPort.charge()`
7. Persist Order in one transaction (or use sagas in distributed systems)
8. Return Order with `order_id`

### Optimistic Concurrency on Cart
- `cart_version` (integer) on the aggregate
- Every mutating API carries `expected_version`
- `UPDATE carts SET payload=?, version=version+1 WHERE cart_id=? AND version=?` -- zero rows means 409 Conflict, client refetches
- For guest merge: run merge inside one transaction + single version bump

### Scaling Session State
- Cart document migrates to Redis/DynamoDB at scale; only `CartRepository` changes
- DynamoDB conditional writes (`attribute_not_exists`) give CAS semantics
- Anonymous carts: Redis TTL (~days); logged-in carts: persist until checkout or policy purge
- Sticky routing to same shard via `cart_id` for read-your-writes consistency

### PromotionEngine Architecture
- Engine walks cart lines and returns `PriceAdjustment` list
- Each `PromotionRule` is a strategy: BOGO, category percent off, free shipping threshold
- Cart does not know BOGO -- SRP preserved
- Line-level discounts (Amazon/Shopify style), not a single BigDecimal on Product

## Follow-Ups
- How would you handle partial shipments (split Order into Shipment aggregates)?
- What happens when a promotion conflicts with a price snapshot from a different era?
- How do you handle cart expiration and abandoned cart recovery?
- How would you implement a "save for later" feature within the cart?
- What changes for a marketplace with multiple sellers in one cart?
