# Project 1 - Monte Carlo Simulation Analysis

## Probability Analysis
Based on the data with 500,000 trials, the probability of a successful hit is around 20.2%. The actual probability is probably very slightly higher.

## Performance Results
![charts](image.png)

## Speedup Analysis
The speedup from 1 thread to 4 threads is:
Speedup = 65.96 / 18.81 = 3.51

## Parallel Fraction (Fp) Calculation
Using the formula: Fp = (4/3)*(1 - (1/S))

Fp = (4/3)*(1 - (1/3.51))
Fp = 0.953

## Maximum Theoretical Speedup
Using Amdahl's Law, the maximum theoretical speedup regardless of the number of cores is:
Smax = 1/(1-Fp) = 1/(1-0.953) = 1/0.047 = 21.28

The maximum speedup we could achieve is approximately 21.28 times the single-threaded performance.