# Project 0 - Array Multiplication Performance Analysis

## Machine Specification
I ran this program on the flip1 server.

## Performance Results
The program was run using arrays of size 10000 with both 1 thread and 4 threads:

- For 1 thread: Peak Performance = 440.28 MegaMults/Sec
- For 4 threads: Peak Performance = 1532.37 MegaMults/Sec

## Speedup Analysis
The speedup achieved by using 4 threads compared to 1 thread is:

Speedup = (Performance with 4 threads) / (Performance with 1 thread)
Speedup = 1532.37 / 440.28 = 3.48

## Why is the Speedup Less Than 4.0?
The speedup of 3.48 is less than the maximum of 4.0 because:

1. Amdahl’s law: There is always some fraction of the total operation that is
inherently sequential and cannot be parallelized 

2. Thread management: The program slows down due to managing the threads. 

## Parallel Fraction (Fp) Calculation
Using the formula: Fp = (4./3.)*(1. - (1./S))

Calculating Fp:
Fp = (4/3)*(1 - (1/3.48))
Fp = 0.950