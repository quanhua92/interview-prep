# Bit Manipulation

## One-Liner
Manipulate individual bits of integers to solve problems with O(1) or O(n) time and O(1) space using XOR self-inverse, Brian Kernighan's algorithm, and bitmask enumeration.

## Core Bit Properties (Must Know)
These six properties cover 90% of bit manipulation interview problems:

1. `a ^ a = 0` -- a number XOR'd with itself is zero
2. `a ^ 0 = a` -- a number XOR'd with zero is itself
3. XOR is commutative and associative: `a ^ b ^ a = b`
4. `n & (n-1)` -- clears the lowest set bit of n
5. `n & (-n)` -- isolates the lowest set bit of n (two's complement)
6. `n & (n-1) == 0` iff n is a power of 2 (and n > 0)

## Key Techniques

### 1. XOR Self-Inverse: Eliminate Pairs
- XOR all elements together; duplicates cancel to 0 (a^a=0); the unique element survives (a^0=a).
- Works for any number of pairs: `[1,2,1,3,2]` -> `1^2^1^3^2 = (1^1)^(2^2)^3 = 0^0^3 = 3`.
- Used for: find the unique number where all others appear exactly twice.

### 2. Brian Kernighan's Algorithm: Count Set Bits
- `n & (n-1)` clears the rightmost set bit of n.
- Loop: `while n != 0: count += 1; n = n & (n-1)`.
- Runs exactly once per set bit -- O(k) where k = number of set bits, much faster than testing each bit individually O(32).
- Alternatives: Python's `bin(n).count('1')` or Java's `Integer.bitCount(n)` (hardware popcount, O(1)).

### 3. Power of Two Check
- A power of 2 has exactly one set bit: 8 = 1000, 16 = 10000.
- `n & (n-1)` (which clears one bit) equals 0 for powers of 2.
- Check: `n > 0 and (n & (n-1)) == 0` (handle n=0 explicitly).
- Used in: hash table size validation, memory alignment checks, segment tree implementation.

### 4. Bit Masking: Subset Enumeration
- For n elements, each subset can be represented as an n-bit mask.
- Enumerate all 2^n subsets: `for mask in range(1 << n)`, iterate from 0 to 2^n - 1.
- Check if bit i is set: `(mask >> i) & 1`.
- Iterate only over set bits in a mask: `temp = mask; while temp: i = temp.bit_length()-1; use element i; temp &= temp-1`.

### 5. Isolate and Extract Bits
- Get bit at position i: `(n >> i) & 1`
- Set bit at position i: `n | (1 << i)`
- Clear bit at position i: `n & ~(1 << i)`
- Toggle bit at position i: `n ^ (1 << i)`
- Lowest set bit: `n & (-n)` (because -n = ~n + 1 in two's complement)
- Clear lowest set bit: `n & (n - 1)`

## Problem Templates

### Single Number (one element appears once, all others twice)
```python
def single_number(nums: list[int]) -> int:
    result = 0
    for n in nums:
        result ^= n
    return result
# O(n) time, O(1) space
```

### Missing Number (0 to n, one missing)
```python
def missing_number(nums: list[int]) -> int:
    n = len(nums)
    result = n  # start with n (not in array indices 0..n-1)
    for i, num in enumerate(nums):
        result ^= i ^ num
    return result
# Alternative: expected sum = n(n+1)/2; return expected - sum(nums)
# XOR approach avoids integer overflow for large n
```

### Count Set Bits (Hamming Weight)
```python
def hamming_weight(n: int) -> int:
    count = 0
    while n:
        n &= n - 1   # clear rightmost set bit
        count += 1
    return count
# O(k) where k = number of set bits
```

### Subsets Using Bitmask
```python
def all_subsets(nums: list[int]) -> list[list[int]]:
    n = len(nums)
    result = []
    for mask in range(1 << n):   # 2^n masks
        subset = []
        for i in range(n):
            if (mask >> i) & 1:  # bit i set -> include nums[i]
                subset.append(nums[i])
        result.append(subset)
    return result
# O(n * 2^n)
```

### Single Number III (two unique numbers, all others appear twice)
```python
def single_number_iii(nums: list[int]) -> list[int]:
    # Step 1: XOR all nums -> a ^ b (where a, b are the two unique numbers)
    xor_ab = 0
    for n in nums: xor_ab ^= n

    # Step 2: find a bit where a and b differ (any set bit of xor_ab)
    diff_bit = xor_ab & (-xor_ab)   # isolate lowest set bit

    # Step 3: split nums into two groups by that bit; XOR each group
    a = b = 0
    for n in nums:
        if n & diff_bit: a ^= n
        else:             b ^= n
    return [a, b]
# O(n) time, O(1) space
```

## Common Mistakes
- **Forgetting n=0 for power-of-two check:** `0 & (0-1) = 0`, so the formula says 0 is a power of 2. Always add `n > 0` guard.
- **Integer overflow in missing number via sum:** `n(n+1)/2` for n = 10^9 overflows 32-bit int. Use XOR approach or Python (arbitrary precision). In Java: use `long` for the sum.
- **XOR swap edge case -- same variable:** `a ^= a` -> a = 0. Never use XOR swap when a and b might alias (e.g., `swap(arr[i], arr[i])`). Only use when guaranteed i != j.
- **Shift by more than 31 in Java (undefined behavior in C/C++):** `1 << 32` in Java = `1 << 0 = 1` (shift wraps modulo 32). In C/C++, shifting >= word size is undefined behavior. Use `1L << n` for long-sized shifts.
- **Treating bitmask problems as requiring extra space:** When "all elements appear k times except one," count bits at each position modulo k instead of using a HashMap. O(32k) time, O(1) space.

## Interview Communication Tips
- For "find the unique element": verbalize the XOR intuition before coding -- "XOR has two useful properties: a number XOR'd with itself is 0, and a number XOR'd with 0 is itself. So if I XOR all elements together, pairs cancel to 0 and the unique element survives."
- For power of two: "A power of 2 has exactly one set bit. Subtracting 1 flips all bits below that set bit and clears it. So `n & (n-1)` is 0 if and only if n has exactly one bit set."
- Show you understand the underlying bit representation, not just memorized the trick.

## Scoring Rubric (What Interviewers Evaluate)
- **6/10:** Knows basic bitwise operators. Can solve simple bitmask problems with some hints.
- **8/10:** Immediately recognizes XOR self-inverse for "find single number." Knows Brian Kernighan's algorithm for counting set bits. Implements subset enumeration with bitmasks. Explains the `n & (n-1)` trick.
- **10/10:** Derives XOR solution from first principles. Extends single-number to "every element appears 3 times" using bit counting. Explains two's complement to justify `n & (-n)`. Knows full bit-twiddling hacks (SWAR popcount, parallel prefix). Names real applications: Redis bitmaps, bloom filters, chess engine move generation.

## Signal Words
"find the unique number," "find the missing number," "count the number of 1 bits," "subsets of a set," "check if power of 2," "swap without a temp variable."

## Key Variants
1. **Brian Kernighan's algorithm** -- `n &= (n - 1)` clears lowest set bit
2. **XOR trick** -- pairs cancel out, leaving the unique element
3. **DP + bit manipulation** -- `ans[i] = ans[i >> 1] + (i & 1)` for counting bits

## Follow-Up Variations
- "Every element appears 3 times except one" -- count bits at each position modulo 3, O(32n) time, O(1) space.
- "Find two unique numbers where all others appear twice" -- Single Number III approach above.
- "Reverse bits of a 32-bit unsigned integer."
- "Maximum AND value of any pair in an array."
- "Count number of subsets with a given XOR value."

Source: [Bit Manipulation: XOR Tricks, Bit Masking & Power-of-Two Patterns (CalibreOS)](https://www.calibreos.com/learn/dsa-bit-manipulation)

---

# Math and Number Theory

## One-Liner
Apply modular arithmetic throughout (not just at return), use GCD/LCM with overflow-safe formulas, select sieve vs Miller-Rabin by scale, precompute factorials for O(1) nCr queries, and know when Fermat's little theorem fails.

## Signal Words
"return answer mod 10^9+7", "how many trailing zeros", "largest number divisible by", "count pairs with GCD equal to", "number of ways to choose k items from n", "is prime", "count primes up to N."

## The Five Number Theory Primitives for FAANG Interviews
1. **Modular arithmetic** -- distributive property, fast power, modular inverse
2. **GCD/LCM** -- Euclidean algorithm, integer overflow fix
3. **Primality testing** -- sieve for N <= 10^7, Miller-Rabin for N <= 10^12
4. **Prime factorization** -- trial division with the sqrt insight
5. **Combinatorics** -- nCr mod p via Fermat's little theorem

## Modular Arithmetic: The Rules and the Traps

### Four Properties
- `(a + b) % m = ((a % m) + (b % m)) % m`
- `(a - b) % m = ((a % m) - (b % m) + m) % m` -- the `+m` prevents negative results
- `(a * b) % m = ((a % m) * (b % m)) % m`
- `(a / b) % m != (a % m) / (b % m)` -- division has NO direct modular analog, requires modular inverse

### Python vs C++/Java Trap
- Python: `-7 % 3 = 2` (mathematical modulo)
- C++/Java: `-7 % 3 = -1` (remainder with sign of dividend)
- Cross-language fix: `((a % m) + m) % m` guarantees non-negative result

### Fast Modular Exponentiation
- Always use `pow(base, exp, mod)` -- O(log exp)
- Never use `base**exp % mod` -- computes full power first; for `pow(2, 10**9)` this produces ~300 million digits before reduction

### The When-To-Apply Rule
If the problem says "return answer mod 10^9+7", apply mod after **every** multiplication and addition throughout the algorithm. Appears in ~40% of FAANG DP problems. The modulus 10^9+7 is chosen because it is prime (enables Fermat's little theorem), fits in int32 when doubled (safe int64 intermediates), and is large enough to prevent collisions.

### Modular Arithmetic Template
```python
MOD = 10**9 + 7

def mod_add(a: int, b: int) -> int:
    return (a + b) % MOD

def mod_sub(a: int, b: int) -> int:
    return (a - b + MOD) % MOD  # +MOD prevents negative result

def mod_mul(a: int, b: int) -> int:
    return (a * b) % MOD

def mod_pow(base: int, exp: int, mod: int = MOD) -> int:
    return pow(base, exp, mod)  # ALWAYS use three-argument pow()

# Modular inverse via Fermat's little theorem
# PRECONDITION: mod must be PRIME and gcd(a, mod) = 1
def mod_inv_fermat(a: int, mod: int = MOD) -> int:
    return pow(a, mod - 2, mod)

# DP example: count paths mod 10^9+7, apply mod at each step
def count_paths(grid: list[list[int]]) -> int:
    m, n = len(grid), len(grid[0])
    dp = [[0] * n for _ in range(m)]
    dp[0][0] = 1
    for i in range(m):
        for j in range(n):
            if i == 0 and j == 0:
                continue
            top  = dp[i-1][j] if i > 0 else 0
            left = dp[i][j-1] if j > 0 else 0
            dp[i][j] = (top + left) % MOD  # mod at every addition
    return dp[m-1][n-1]
```

## GCD and LCM: Euclidean Algorithm and Integer Overflow

- Euclidean algorithm: `gcd(a, b) = gcd(b, a % b)`, base case `gcd(a, 0) = a`. O(log min(a, b)).
- Each step replaces the larger number with the remainder; remainders decrease geometrically (Lame's theorem).
- For two 9-digit numbers, terminates in at most ~60 steps.

### LCM Overflow Trap
- **WRONG**: `a * b // gcd(a, b)` -- computes `a * b` first, overflows when a, b ~ 10^9 in C++/Java
- **CORRECT**: `a // gcd(a, b) * b` -- gcd divides a exactly, intermediate stays bounded by a
- For LCM of a list: `result = lcm(result, x)` iteratively. LCM can grow exponentially with distinct primes.
- If problem asks for LCM mod p, compute via prime factorization (max exponent per prime), NOT by applying mod to the LCM formula -- LCM does not distribute over mod.

### Non-Obvious Application
GCD identifies whether two fractions reduce to the same value: `a/b == c/d` as reduced fractions iff `a // gcd(a,b) == c // gcd(c,d)` and `b // gcd(a,b) == d // gcd(c,d)`.

### GCD/LCM Template
```python
import math

# Iterative form preferred in interviews -- no recursion depth risk
def gcd_iter(a: int, b: int) -> int:
    while b:
        a, b = b, a % b
    return a

# LCM: divide FIRST to avoid overflow
def lcm(a: int, b: int) -> int:
    return a // math.gcd(a, b) * b

# LCM of a list
def lcm_list(nums: list[int]) -> int:
    result = nums[0]
    for x in nums[1:]:
        result = lcm(result, x)
    return result

# GCD of a list
def gcd_list(nums: list[int]) -> int:
    result = nums[0]
    for x in nums[1:]:
        result = math.gcd(result, x)
    return result
```

## Prime Sieve and Factorization: Algorithm Selection by Scale

### Sieve of Eratosthenes
- O(n log log n) time, O(n) space. Finds all primes up to N.
- Why O(n log log n) and not O(n log n)? Total work = n * sum(1/p) over primes p <= n. By Mertens' theorem, this sum grows as log log n (dramatically slower than the harmonic series log n).
- Inner loop starts at p^2, not 2p: multiples below p^2 were already marked by smaller primes.
- Use for N <= 10^7 (~10MB boolean array).

### Algorithm Selection Decision
- N <= 10^7: Sieve (boolean array)
- N <= 10^12: Miller-Rabin primality test for individual numbers (O(k log^2 N) with k=7 fixed witnesses, deterministic for all N < 3.3 x 10^24)
- Never sieve for N > 10^7 in a timed interview -- causes MLE or TLE.

### Prime Factorization via Trial Division
- O(sqrt(n)) per number. No precomputation needed.
- Key insight: if n has a prime factor p > sqrt(n), there can be at most ONE such factor (two would multiply to > n).
- After dividing out all factors up to sqrt(n), any remaining `n > 1` is itself prime. Missing the `if n > 1` check silently loses one factor (e.g., 14 = 2 x 7, loop exits with n = 7 remaining).

### Smallest Prime Factor (SPF) Sieve
- Variant that stores the smallest prime factor for each number up to N.
- With SPF precomputed, any number up to N can be factorized in O(log n) by repeatedly dividing by `spf[n]`.

### Primes Template
```python
def sieve_of_eratosthenes(n: int) -> list[int]:
    """All primes up to n. O(n log log n). Use when n <= 10^7."""
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    p = 2
    while p * p <= n:
        if is_prime[p]:
            for multiple in range(p * p, n + 1, p):
                is_prime[multiple] = False
        p += 1
    return [i for i in range(2, n + 1) if is_prime[i]]

def spf_sieve(n: int) -> list[int]:
    """Smallest Prime Factor sieve. O(n log log n). Enables O(log n) factorization."""
    spf = list(range(n + 1))
    p = 2
    while p * p <= n:
        if spf[p] == p:
            for multiple in range(p * p, n + 1, p):
                if spf[multiple] == multiple:
                    spf[multiple] = p
        p += 1
    return spf

def factorize_with_spf(n: int, spf: list[int]) -> dict[int, int]:
    """O(log n) factorization using precomputed SPF sieve."""
    factors: dict[int, int] = {}
    while n > 1:
        p = spf[n]
        while n % p == 0:
            factors[p] = factors.get(p, 0) + 1
            n //= p
    return factors

def factorize_trial(n: int) -> dict[int, int]:
    """Trial division: O(sqrt(n)). KEY: check if n > 1 after loop."""
    factors: dict[int, int] = {}
    d = 2
    while d * d <= n:
        while n % d == 0:
            factors[d] = factors.get(d, 0) + 1
            n //= d
        d += 1
    if n > 1:  # remaining n is prime (the unique factor > sqrt(original n))
        factors[n] = factors.get(n, 0) + 1
    return factors
```

## Fast Exponentiation and Matrix Exponentiation

### Binary Exponentiation
- Computes `base^exp` in O(log exp).
- If exp is even: `base^exp = (base^2)^(exp/2)`. If odd: `base^exp = base * base^(exp-1)`.
- `pow(base, exp, mod)` applies modular reduction at each squaring step, keeping intermediates below mod^2 (~10^18 for mod = 10^9+7).

### Matrix Exponentiation
- Binary exponentiation extends to matrices (matrix multiplication is associative).
- Any linear recurrence with fixed coefficients can be expressed as matrix multiplication, enabling O(log n) computation.
- Fibonacci: `M = [[1,1],[1,0]]`; then `M^n[0][1] = F(n)`. For n = 10^18: ~60 iterations vs O(n) DP's impossible 10^18 steps.
- Extends to: tribonacci (3x3), number of tilings, number of paths in graph after exactly k steps.
- **Implementation trap**: matrix multiplication order matters. Verify with n=2 or n=3 before trusting the matrix form.

### Fast Exponentiation Template
```python
MOD = 10**9 + 7

def fast_pow(base: int, exp: int, mod: int = MOD) -> int:
    """O(log exp). In practice: use pow(base, exp, mod) which does this internally."""
    result = 1
    base %= mod
    while exp > 0:
        if exp & 1:
            result = result * base % mod
        base = base * base % mod
        exp >>= 1
    return result

def mat_mul(A, B, mod):
    """2x2 matrix multiplication with modular reduction."""
    n = len(A)
    C = [[0] * n for _ in range(n)]
    for i in range(n):
        for k in range(n):
            if A[i][k] == 0:
                continue
            for j in range(n):
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod
    return C

def mat_pow(M, exp, mod):
    """Matrix binary exponentiation. O(k^3 log exp) for k x k matrix."""
    n = len(M)
    result = [[1 if i == j else 0 for j in range(n)] for i in range(n)]
    while exp > 0:
        if exp & 1:
            result = mat_mul(result, M, mod)
        M = mat_mul(M, M, mod)
        exp >>= 1
    return result

def fibonacci_large(n: int, mod: int = MOD) -> int:
    """F(n) in O(log n) via matrix exponentiation. Use when n > 10^7."""
    if n <= 0:
        return 0
    M = [[1, 1], [1, 0]]
    result = mat_pow(M, n, mod)
    return result[0][1]  # F(n) is at position [0][1]
```

## Combinatorics with Modular Inverse: nCr mod p

- Formula: `nCr = n! / (r! * (n-r)!)` involves division, which has no direct modular analog. Need the **modular inverse** of the denominator.

### Fermat's Little Theorem
- If p is prime and gcd(a, p) = 1, then `a^(p-1) = 1 (mod p)`, so `a^(-1) = a^(p-2) (mod p)`.
- Modular inverse of r! is `pow(factorial(r), p-2, p)`.

### Two Preconditions You Must State in an Interview
1. **p must be prime** -- Fermat's theorem requires the multiplicative group (Z/pZ)* to have order p-1. For composite m, use Extended Euclidean Algorithm instead.
2. **r < p** -- when r >= p, `r!` contains p as a factor, so `r! mod p = 0` and the inverse is undefined. For r >= p, apply Lucas' theorem.

### Precomputation Trick for Multiple nCr Queries
- Compute `inv_fact[N] = pow(fact[N], p-2, p)` with one modular exponentiation.
- Fill backward: `inv_fact[i] = inv_fact[i+1] * (i+1) % p` using the identity `(i!)^(-1) = ((i+1)!)^(-1) * (i+1)`.
- Total preprocessing: O(N + log p) -- one exponentiation plus N multiplications, instead of O(N log p) for computing each inverse separately.

### Combinatorics Template
```python
MOD = 10**9 + 7

class Combinatorics:
    """Precomputes factorials and inverse factorials for O(1) nCr queries.
    PRECONDITION: MOD must be prime (required for Fermat's little theorem).
    For composite mod, use Extended Euclidean for modular inverse instead.
    """
    def __init__(self, max_n: int):
        self.fact = [1] * (max_n + 1)
        for i in range(1, max_n + 1):
            self.fact[i] = self.fact[i - 1] * i % MOD

        self.inv_fact = [1] * (max_n + 1)
        self.inv_fact[max_n] = pow(self.fact[max_n], MOD - 2, MOD)
        for i in range(max_n - 1, -1, -1):
            self.inv_fact[i] = self.inv_fact[i + 1] * (i + 1) % MOD

    def ncr(self, n: int, r: int) -> int:
        """nCr mod MOD in O(1). Returns 0 for r < 0 or r > n."""
        if r < 0 or r > n:
            return 0
        return self.fact[n] * self.inv_fact[r] % MOD * self.inv_fact[n - r] % MOD

# Fallback: Extended Euclidean when MOD is not prime
def extended_gcd(a: int, b: int) -> tuple[int, int, int]:
    """Returns (gcd, x, y) such that a*x + b*y = gcd."""
    if b == 0:
        return a, 1, 0
    g, x, y = extended_gcd(b, a % b)
    return g, y, x - (a // b) * y

def mod_inv_extended(a: int, m: int) -> int:
    """Works for any m where gcd(a, m) = 1, prime or composite."""
    g, x, _ = extended_gcd(a % m, m)
    if g != 1:
        raise ValueError("Inverse doesn't exist: gcd(a,m) != 1")
    return x % m
```

## Math Patterns Quick Reference

| Pattern | Algorithm / Formula | Complexity | Preconditions | Common Trap |
|---------|-------------------|------------|--------------|-------------|
| Mod arithmetic | Distributive property | O(1) per op | None | Applying mod only at return; negative result in C++/Java without +m fix |
| Fast power | `pow(base, exp, mod)` | O(log exp) | None | Using `base**exp % mod` -- computes full power before reduction |
| GCD | Euclidean: `gcd(a,b)=gcd(b,a%b)` | O(log min(a,b)) | Both positive | Deep recursion for large inputs; prefer iterative |
| LCM | `a // gcd(a,b) * b` | O(log min(a,b)) | Both positive | `a*b // gcd` overflows int64 when a,b ~10^9 in C++/Java |
| Primality (small N) | Sieve of Eratosthenes | O(n log log n) | N <= 10^7 | Running sieve for N > 10^7; inner loop at 2p instead of p^2 |
| Primality (large N) | Miller-Rabin, 7 witnesses | O(k log^2 N) | None | Not using deterministic witnesses for N < 3.3x10^24 |
| Factorization | Trial division to sqrt(n) | O(sqrt(n)) | n > 0 | Missing `if n > 1` after loop -- loses prime factor > sqrt(n) |
| Modular inverse | `pow(a, p-2, p)` via Fermat | O(log p) | p prime, gcd(a,p)=1 | Using on composite mod or when gcd(a,p)>1 -- silently wrong |
| nCr mod p | Precomputed fact/inv_fact | O(N) prep + O(1) query | p prime, r < p | Computing each inv_fact[i] separately: O(N log p) vs O(N) |
| Fibonacci large n | Matrix exponentiation | O(log n) | None | Using O(n) DP for n > 10^8 -- TLE; forgetting mod in mat mul |

## Common Mistakes in Math Problems

- **Applying mod only at the return statement**: intermediate values overflow before you reach the return. Apply `% MOD` after every multiplication and every addition.
- **Using Fermat's theorem on composite modulus**: if the problem uses mod 12, mod 100, or any non-prime, `pow(a, mod-2, mod)` produces silently wrong answers. Always verify the modulus is prime first. Extended Euclidean Algorithm is the correct fallback.
- **LCM overflow with the naive formula**: `a * b // gcd(a,b)` overflows 32-bit integers for a,b ~ 10^9 in C++/Java. Use `a // gcd(a,b) * b`. In Python this never overflows, but know the fix for C++ interview discussions.
- **Forgetting the large prime factor in trial division**: after the `while d*d <= n` loop, check `if n > 1`. This remaining n is itself prime. Missing this silently drops one factor (e.g., 14 = 2 x 7).
- **Power of 2 check without n > 0 guard**: `n & (n-1) == 0` returns True for n=0. Always write `n > 0 and (n & (n-1)) == 0`.

## Interview Communication Tips

- When you see "return answer mod 10^9+7": say "I will apply modular arithmetic at every multiplication and addition throughout the algorithm, not just at the return, to prevent intermediate overflow." Define `MOD = 10**9 + 7` at the top.
- For GCD/LCM: state "I am using `a // gcd(a,b) * b` for LCM, dividing first prevents integer overflow in languages with fixed-width integers." This signals production awareness.
- For primality: ask "what is the scale of N?" If N <= 10^7, sieve. If N <= 10^12, Miller-Rabin. For sieve complexity, say "O(n log log n)" and explain: "the total work is n times the sum of 1/p over primes, which by Mertens' theorem grows as log log n."
- For nCr mod p: before writing the formula, state "This requires the modulus to be prime, which 10^9+7 is. If the modulus were composite, I would use the Extended Euclidean Algorithm instead." This one sentence is the senior-level differentiator.

Source: [Math and Number Theory Patterns: Modular Arithmetic, Primes, and Combinatorics (CalibreOS)](https://www.calibreos.com/learn/dsa-math-number-theory)
