# Generate Random Point in a Circle

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 478, Glassdoor

---

## Question Description

Given the radius and the position of the center of a circle, implement the class `Solution` that supports the method `randPoint()` which generates a uniform random point inside the circle.

A point on the circumference of the circle is considered to be in the circle.

Implement the `Solution` class:
*   `Solution(double radius, double x_center, double y_center)` initializes the object with the radius of the circle `radius` and the position of the center `(x_center, y_center)`.
*   `randPoint()` returns a random point inside the circle as a 2-element array `[x, y]`.

### Examples
*   **Input**:
    `["Solution", "randPoint", "randPoint", "randPoint"]`
    `[[1.0, 0.0, 0.0], [], [], []]`
    *   **Output**: `[null, [-0.02493, -0.38077], [0.82314, 0.38945], [0.36572, 0.17248]]`
    *   **Explanation**: 
        ```cpp
        Solution solution = new Solution(1.0, 0.0, 0.0);
        solution.randPoint(); // returns [-0.02493, -0.38077]
        solution.randPoint(); // returns [0.82314, 0.38945]
        solution.randPoint(); // returns [0.36572, 0.17248]
        ```

---

## Detailed Solution (C++)

There are two primary methods to solve this problem: **Rejection Sampling** and **Polar Coordinates with Inverse CDF (Transform Method)**. Both are detailed below.

### Method 1: Rejection Sampling (Loop-based)
We generate a random point inside a square of side length $2R$ centered at $(0, 0)$. A point $(x, y)$ is accepted if $x^2 + y^2 \le R^2$; otherwise, it is rejected and we try again. Once accepted, we translate the point to the circle's center.
*   **Probability of Acceptance**: $\frac{\text{Area of Circle}}{\text{Area of Square}} = \frac{\pi R^2}{4 R^2} = \frac{\pi}{4} \approx 78.5\%$.
*   **Expected Iterations**: $\frac{4}{\pi} \approx 1.27$ attempts.

### Method 2: Polar Coordinates with Inverse CDF (Analytical $O(1)$)
If we naive-sample a radius $r$ uniformly in $[0, R]$ and an angle $\theta$ uniformly in $[0, 2\pi]$, points will clump near the center because the area of a circle grows quadratically ($A = \pi r^2$).
To distribute points uniformly, we use **Inverse Transform Sampling**:
1. The Probability Density Function (PDF) for the radius is proportional to the circumference: $f(r) = \frac{2r}{R^2}$.
2. The Cumulative Distribution Function (CDF) is $F(r) = \frac{r^2}{R^2}$.
3. Set $U$ to a uniform random float in $[0, 1)$, and solve for $r$:
   $$U = \frac{r^2}{R^2} \implies r = R \sqrt{U}$$
4. Generate $\theta = 2\pi \cdot U_2$ and calculate $x = x_c + r \cos\theta, y = y_c + r \sin\theta$.

### Standard C++ Production Code (Method 2: Analytical $O(1)$)

```cpp
#include <vector>
#include <random>
#include <cmath>

class Solution {
private:
    double r;
    double xc;
    double yc;
    std::mt19937 gen;
    std::uniform_real_distribution<double> dis;

public:
    Solution(double radius, double x_center, double y_center)
        : r(radius), xc(x_center), yc(y_center), gen(std::random_device{}()), dis(0.0, 1.0) {}
    
    std::vector<double> randPoint() {
        double u1 = dis(gen); // For radius scaling
        double u2 = dis(gen); // For angle theta
        
        double current_r = r * std::sqrt(u1);
        const double pi = std::acos(-1.0);
        double theta = u2 * 2.0 * pi;
        
        return {xc + current_r * std::cos(theta), yc + current_r * std::sin(theta)};
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code (Method 2: Analytical $O(1)$)

Below is the Python implementation using the Polar Inverse CDF method.

```python
import math
import random
from typing import List

class Solution:

    def __init__(self, radius: float, x_center: float, y_center: float):
        """
        Initializes the circle parameters.
        """
        self.radius = radius
        self.x_center = x_center
        self.y_center = y_center

    def randPoint(self) -> List[float]:
        """
        Generates a uniform random point inside the circle in O(1) time.
        """
        # Generate two uniform random floats in [0.0, 1.0)
        u1 = random.random()
        u2 = random.random()
        
        # Apply Inverse CDF for uniform area distribution
        r = self.radius * math.sqrt(u1)
        theta = u2 * 2.0 * math.pi
        
        x = self.x_center + r * math.cos(theta)
        y = self.y_center + r * math.sin(theta)
        
        return [x, y]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Rejection Sampling vs. Inverse CDF Performance in Python
*   In Python, function call overhead is high. Rejection sampling requires a `while True` loop that averages $1.27$ iterations but can theoretically run indefinitely.
*   The Polar method using `math.sqrt`, `math.cos`, and `math.sin` executes in constant time with exactly two calls to `random.random()`, making it more predictable and generally faster in Python than loop-based rejection sampling.

### 2. High Precision Float Math
*   Python's built-in `float` type is a C double (64-bit float). This guarantees $53$ bits of precision, which is more than sufficient for the radius bounds of $10^8$.

---

## Complexity Analysis

### Method 1: Rejection Sampling
| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(1)$ average | On average, $\frac{4}{\pi} \approx 1.27$ attempts are needed. Worst-case is unbounded (but probability of high iterations decays exponentially). |
| **Space Complexity** | $\mathcal{O}(1)$ | Constant auxiliary memory. |

### Method 2: Polar Coordinates (Inverse CDF)
| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(1)$ deterministic | Guaranteed single-pass execution without loops. |
| **Space Complexity** | $\mathcal{O}(1)$ | Constant auxiliary memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Which method is preferred if generating random numbers is extremely expensive?
*   **Answer**: If generating random numbers is expensive, **Rejection Sampling** uses an average of $2 \times 1.27 = 2.54$ random numbers per point. The **Polar method** uses exactly $2$ random numbers per point. Thus, the Polar method is more efficient in its consumption of random entropy.
*   Conversely, if trigonometric operations (`cos`, `sin`, `sqrt`) are extremely expensive (e.g., on low-end embedded systems lacking a Floating Point Unit / FPU), **Rejection Sampling** is preferred because it only uses basic multiplications and additions ($x^2 + y^2 \le R^2$).

### Q2: How would you extend this to generate a random point on a 3D sphere?
*   **Answer**: 
    *   **Rejection Sampling**: Generate $(x, y, z)$ in a $[-R, R]^3$ cube and reject if $x^2 + y^2 + z^2 > R^2$. The acceptance rate drops to $\frac{\frac{4}{3}\pi R^3}{8 R^3} = \frac{\pi}{6} \approx 52.4\%$.
    *   **Analytical Method (Spherical Coordinates)**: We can use Inverse Transform Sampling or Normal distributions. For a solid sphere, the radius CDF is $F(r) = \frac{r^3}{R^3} \implies r = R \sqrt[3]{U}$. The direction can be sampled uniformly on the sphere's surface by generating three independent Gaussian variables, normalizing them, and scaling by $r$.

---

## Pro-Tip: How to Impress the Interviewer

*   **Derive the $\sqrt{U}$ relationship**: Do not just write `r = radius * sqrt(u)`. Walk the interviewer through the calculus:
    1. The area of a thin ring of radius $r$ is $2\pi r \, dr$.
    2. Integrate from $0$ to $r$ to get the cumulative area: $\pi r^2$.
    3. Normalize by total area $\pi R^2$ to get the CDF: $P(R \le r) = \frac{r^2}{R^2}$.
    4. Set $U = \frac{r^2}{R^2}$ and solve for $r$: $r = R\sqrt{U}$.
    This shows mathematical rigour and a deep understanding of probability theory.
*   **Compare Hardware Constraints**: Discuss the hardware trade-offs between rejection sampling (which needs simple ALU math but has branching and variable latency) and the analytical method (which is constant-time/non-branching but uses complex trigonometric execution units). This is a hallmark of senior systems engineering.
