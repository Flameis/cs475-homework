# CS 475 - Parallel Programming

This repository contains the complete collection of projects for CS 475 - Parallel Programming course. Each project explores different aspects of parallel computing, performance optimization, and high-performance computing techniques.

## Course Overview

CS 475 focuses on parallel programming concepts including:
- Multi-threading with OpenMP
- GPU computing with CUDA
- OpenCL programming
- Message Passing Interface (MPI)
- Performance analysis and optimization
- Vectorization with SSE/SIMD

## Projects

### Project 0 - Array Multiplication Performance Analysis
**Focus:** OpenMP Threading and Performance Measurement
- Implementation of parallel array multiplication using OpenMP
- Performance analysis with 1 vs 4 threads
- Study of Amdahl's Law and parallel efficiency
- **Key Skills:** OpenMP pragmas, performance timing, speedup calculations

**Files:**
- `test.cpp` - Main implementation with OpenMP parallelization
- `writeup.md` - Performance analysis and results

### Project 1 - Monte Carlo Simulation
**Focus:** Parallel Monte Carlo Methods
- Multi-threaded Monte Carlo simulation using OpenMP
- Statistical analysis of parallel random number generation
- Performance scaling with thread count
- **Key Skills:** Random number generation, statistical analysis, thread-safe programming

**Files:**
- `skeleton.cpp` - Monte Carlo simulation implementation
- `results.csv` - Performance data across different thread counts
- `image.png` - Performance visualization charts

### Project 2 - Functional Decomposition
**Focus:** Ecosystem Simulation with Parallel Components
- Multi-threaded ecosystem simulation with deer, grain, and predator populations
- Custom implementation of predator-prey dynamics
- Functional decomposition of simulation components
- **Key Skills:** Producer-consumer patterns, barrier synchronization, functional decomposition

**Files:**
- `program.cpp` - Ecosystem simulation with predator implementation
- `results.csv` - Simulation data over time
- `image.png` - Population dynamics visualization

### Project 3 - K-Means Clustering Algorithm
**Focus:** Parallel Algorithm Implementation
- Implementation of K-Means clustering for US cities data
- Parallel processing of large datasets
- Geographic data analysis and state boundary optimization
- **Key Skills:** Algorithm parallelization, data partitioning, convergence analysis

**Files:**
- `proj03.cpp` - K-Means implementation with OpenMP
- `UsCities.data` - Dataset of 331 US cities
- `makefile` - Build configuration
- `vary.sh` - Script for parameter variation testing

### Project 4 - Vectorized Array Operations with SSE
**Focus:** SIMD Programming and Vectorization
- Implementation of vectorized array multiplication using SSE intrinsics
- Performance comparison between scalar and SIMD operations
- Cache performance analysis across different array sizes
- **Key Skills:** SSE intrinsics, vectorization, cache optimization

**Files:**
- `proj04.cpp` - SSE-optimized array operations
- `run.sh` - Automated testing script
- `results.csv` - Performance data across array sizes
- `image.png` - Performance comparison charts

### Project 5 - CUDA Monte Carlo Simulation
**Focus:** GPU Programming with CUDA
- GPU-accelerated Monte Carlo simulation
- Performance analysis across different block sizes and problem sizes
- Comparison with CPU-based implementations
- **Key Skills:** CUDA kernels, GPU memory management, parallel reduction

**Files:**
- `proj05.cu` - CUDA implementation of Monte Carlo simulation
- `helper_*.h` - CUDA utility headers
- `rundgx.sh`, `runrab.sh` - Execution scripts for different systems
- `results.csv` - GPU performance data

### Project 6 - OpenCL Quadratic Regression
**Focus:** Cross-Platform GPU Computing
- OpenCL implementation for quadratic regression analysis
- Performance optimization with different work group sizes
- Data parallel computing patterns
- **Key Skills:** OpenCL kernels, work group optimization, regression analysis

**Files:**
- `proj06.cpp` - Host code for OpenCL implementation
- `proj06.cl` - OpenCL kernel code
- `p6.data` - Input dataset
- `cl.h`, `cl_platform.h` - OpenCL headers

### Project 7 - Fourier Analysis with MPI
**Focus:** Distributed Computing and Message Passing
- MPI-based parallel Fourier transform implementation
- Signal processing and frequency analysis
- Distributed computing performance analysis
- **Key Skills:** MPI communication, distributed algorithms, signal processing

**Files:**
- `proj07.cpp` - MPI Fourier analysis implementation
- `bigsignal.bin`, `bigsignal.txt` - Signal data files
- `plot.csv` - Analysis results
- `rundgx.sh`, `runrab.sh` - Cluster execution scripts

## Build Instructions

### General Requirements
- GCC compiler with OpenMP support
- CUDA toolkit (for Project 5)
- OpenCL SDK (for Project 6)
- MPI implementation (for Project 7)

### Building Individual Projects

#### Projects 0-3 (OpenMP)
```bash
g++ -fopenmp -O3 -o program source.cpp -lm
```

#### Project 4 (SSE)
```bash
g++ -msse -O3 -o proj04 proj04.cpp -lm
```

#### Project 5 (CUDA)
```bash
nvcc -o proj05 proj05.cu
```

#### Project 6 (OpenCL)
```bash
g++ -o proj06 proj06.cpp -lOpenCL -lm
```

#### Project 7 (MPI)
```bash
mpic++ -o proj07 proj07.cpp -lm
```

### Using Provided Build Tasks
VS Code tasks are configured for C++ compilation:
- **C/C++: cl.exe build active file** - Microsoft Visual C++ compiler
- **C/C++: g++.exe build active file** - GNU GCC compiler (default)

## Performance Testing

Each project includes scripts for automated performance testing:
- `run.sh` / `vary.sh` - Parameter variation scripts
- `rundgx.sh` / `runrab.sh` - Cluster-specific execution scripts

Results are typically saved to `results.csv` files with corresponding visualization in `image.png` files.

## Key Learning Outcomes

1. **Parallel Programming Paradigms:**
   - Shared memory programming (OpenMP)
   - GPU computing (CUDA, OpenCL)
   - Distributed computing (MPI)

2. **Performance Analysis:**
   - Speedup and efficiency calculations
   - Amdahl's Law applications
   - Cache performance optimization
   - Scalability analysis

3. **Algorithm Parallelization:**
   - Data parallel algorithms
   - Task parallel decomposition
   - Reduction operations
   - Synchronization techniques

4. **Hardware Optimization:**
   - CPU vectorization with SSE
   - GPU architecture utilization
   - Memory hierarchy optimization
   - Load balancing strategies

## Author
**Luke Scovel**  
**Email:** scovell@oregonstate.edu  
**Course:** CS 475 - Parallel Programming

## Repository Information
- **Repository:** cs475-homework
- **Owner:** Flameis
- **Branch:** main

---

*Each project folder contains detailed writeups with implementation details, performance analysis, and results. Refer to individual `writeup.md` files for project-specific information.*