# CS 475 - Project 4: Vectorized Array Multiplication and Multiplication/Reduction using SSE
**Name:** Luke Scovel  
**Email:** scovell@oregonstate.edu  
**Project Number:** 4  
**Project Name:** Vectorized Array Multiplication and Multiplication/Reduction using SSE

## Machine Information
* rabbit.engr.oregonstate.edu
* CentOS Linux release 7.9.2009 (Core)
* g++ compiler
```LEVEL1_ICACHE_SIZE                 32768
LEVEL1_DCACHE_SIZE                 32768
LEVEL2_CACHE_SIZE                  262144
LEVEL3_CACHE_SIZE                  20971520
```

## Performance Data
![graph](image.png)

## Performance Analysis

* What patterns are you seeing in the speedups?

The speedups generally average around 5x, with the non-SIMD code being about .25 higher until it hits the L2 cache size (65536 * 4 bytes/float = 262144 bytes, 256 KB). After that, the speed up is about the same for both until it hits 1048576 bytes (1 MB), where the non-SIMD code starts to slow down faster than the SIMD code, dipping to 2x before averaging around 3x speedup while SIMD stays around 5x.

* Are they consistent across a variety of array sizes?

SIMD is very consistent across all array sizes, while non-SIMD hits some highs and some lows. 

* Why or why not, do you think? 

The non-SIMD code is not consistent because it is not optimized for the cache sizes, while SIMD is optimized for the cache sizes. The SIMD code is also more efficient in terms of memory access patterns, which leads to better performance.

## What I did
I simply implemented the c++ code required for array multiplication and created a script to run through it and output the results to a csv file.