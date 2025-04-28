# Project 2 - Functional Decomposition and Barrier Synchronization

## Own-Choice Quantity: Predator Population

For my own-choice quantity, I implemented predators in the ecosystem.

1. Each predator eats approximately 1 deer per month
2. Predator population growth depends on the deer-to-predator ratio:
   - If the ratio is <= 4.0 (abundant food), the predator population increases by 0-2
   - If the ratio is >= 2.0 (sufficient food), the predator population changes by -1 to +1
   - If the ratio is < 2.0 (scarce food), the predator population decreases by 0-2

The predator population fits into the simulation by creating a balancer for the deer population.

## Simulation Data


## Simulation Graph

## Analysis of Patterns
