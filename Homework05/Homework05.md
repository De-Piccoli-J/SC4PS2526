# Homework 5:

This folder contains a C program computing Legendre polynomials using recurrence relations, and a Python script for error visualization.


- `legendre.c`: Implements forward recurrence, backward recurrence (Miller's algorithm), and a high-precision `long double` reference computation.
- `plot.py`: Generates plots of absolute and relative errors.


### Questions & Answers

**Why does the three-term recurrence have a "dominant" and a "minimal" solution, and why does forward recurrence tend to amplify the dominant mode, leading to instability?**
Second-order linear recurrences yield two independent solutions. As the degree increases, one typically grows rapidly (dominant) while the other decays (minimal). In forward recurrence, finite-precision floating-point round-off errors inevitably introduce a tiny fraction of the dominant solution. This error grows exponentially as you iterate, quickly overwhelming the minimal solution.

**Why does backward recurrence suppress the unstable solution and is therefore stable (Miller’s idea)?**
Iterating backwards reverses the growth behavior: the mathematically dominant solution decays, and the minimal solution grows. Starting with an arbitrary guess at a high degree ensures that any dominant error component rapidly vanishes as you step downward, allowing the minimal solution to emerge clearly. 

**How does this relate to conditioning vs. stability?**
* **Conditioning** describes the mathematical problem: Legendre polynomials are well-conditioned near $x=1$, meaning the exact true answer is not highly sensitive to small changes in $x$.
* **Stability** describes the algorithm: An algorithm is unstable if it internally amplifies rounding errors (like forward recurrence trying to find a minimal solution). Thus, an unstable algorithm can fail even when solving a perfectly well-conditioned problem.