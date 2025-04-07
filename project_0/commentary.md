# Project 0 - Array Multiplication Performance Analysis

## Machine Specification
I ran this program on the flip1 server.

## Performance Results
The program was run using arrays of size 10000 with both 1 thread and 4 threads:

- For 1 thread: Peak Performance = 436.66 MegaMults/Sec
- For 4 threads: Peak Performance = 1072.39 MegaMults/Sec

## Speedup Analysis
The speedup achieved by using 4 threads compared to 1 thread is:

Speedup = (Performance with 4 threads) / (Performance with 1 thread)
Speedup = 1072.39 / 436.66 = 2.46

## Why is the Speedup Less Than 4.0?
The speedup of 2.46 is less than the maximum of 4.0 because:


## Parallel Fraction (Fp) Calculation
Using the formula: Fp = (4./3.)*(1. - (1./S))

Calculating Fp:
Fp = (4/3)*(1 - (1/2.46))
Fp = (4/3)*(1 - 0.4065)
Fp = (4/3)*(0.5935)
Fp = 0.791

The parallel fraction of the code is approximately 0.791 or 79.1%, which is less than 1.0 as expected. This indicates that while a significant portion of our code is effectively parallelized, there are still sequential components and parallel inefficiencies limiting our overall speedup.
