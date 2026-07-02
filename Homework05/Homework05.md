# Homework 5:

This folder contains a C program computing Legendre polynomials using recurrence relations, and a Python script for error visualization.


- `legendre.c`: Implements forward recurrence, backward recurrence (Miller's algorithm), and a high-precision `long double` reference computation.
- `plot.py`: Generates plots of absolute and relative errors.


### Questions & Answers
Every three-term recurrence relation has two linearly independent mathematical solutions. In most standard applications, these two solutions diverge in magnitude as the step index increases having a dominant and minimal solution

When evaluating Legendre polynomials within the standard domain $x \in (-1, 1)$, the recurrence relation behaves uniquely. The two independent solutions are the Legendre functions of the first kind, $P_\ell(x)$, and the second kind, $Q_\ell(x)$. 


$$P_\ell(\cos\theta) \sim \sqrt{\frac{2}{\pi \ell \sin\theta}} \cos\!\left((\ell+\tfrac{1}{2})\theta - \tfrac{\pi}{4}\right)$$

$$Q_\ell(\cos\theta) \sim \sqrt{\frac{\pi}{2\ell \sin\theta}} \sin\!\left((\ell+\tfrac{1}{2})\theta - \tfrac{\pi}{4}\right)$$

### Forward Case
  
   In the forward case both independent solutions to the recurrence $P_\ell(x)$ and $Q_\ell(x)$ decay at the exact same rate ($O(\ell^{-1/2})$). Because neither solution dominates the other, numerical errors do not compound exponentially. The forward iteration safely maintains machine precision.

### Backward Case
Miller's algorithm only works when computing a strictly minimal solution—one that decays exponentially faster than the alternative. Since $P_\ell$ and $Q_\ell$ share similar magnitudes in this domain, backward iteration cannot isolate $P_\ell$. It instead produces a corrupted, arbitrary mix of both functions, leading to massive relative errors.

### Connection to Spherical Harmonics
Zonal spherical harmonics, $Y_{\ell 0}$, are simply $P_\ell(x)$ multiplied by an exact constant: 

$$Y_{\ell 0}(\theta, \phi) = \sqrt{\frac{2\ell+1}{4\pi}}\,P_\ell(\cos\theta)$$

Because this scaling factor is small (roughly 2.0 for $\ell=50$), the stability of the forward recurrence translates directly into highly accurate spherical harmonics.