# Homework 6
This folder contains a C programs that solve the proposed problems and related python scripts to plot the results when needed

1. **Coin tosses and LLN**  
   Generate 100,000 fair coin tosses with the LCG. Print the running fraction of heads and comment on the convergence to 0.5.

2. **Monte Carlo estimate of $\pi$**  
   Use two LCG streams to estimate $\pi$ for several sample sizes. Study how the error decreases as $N$ increases.

3. **Change of variables: $Y = U^2$**  
   Generate $U \sim \mathrm{Uniform}(0,1)$ with the LCG, transform to $Y = U^2$, and compare the histogram with the analytic density $f_Y(y)=1/(2\sqrt{y})$.

4. **Inverse transform exponential**  
   Use the formula $Y=-\ln(1-U)/\lambda$ with $\lambda=1.5$ to generate an exponential variable from the LCG output. Compare histogram and PDF.

5. **Empirical CDF**  
   For the exponential sample from Exercise 4, draw the empirical CDF and compare it to the exact CDF.

## Comments

1. The convergence is coherent with the $\sigma$ of the binomial distribution:
$$\sigma = \sqrt{\frac{p(1 - p)}{N}} = \sqrt{\frac{0.5 \times 0.5}{100000}} \approx 0.00158$$

2. It converge but it is slow (see plot) 
3. Histogram an PDF agree (see plot)
4. Histogram an PDF agree (see plot)
5. Empirical and Theorethical PDF agree (see plot)
 