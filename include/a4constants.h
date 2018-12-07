/**
 * CMPUT 379 - Assignment 4
 * File Name: a4constants.cc
 * Student Name: Jacob Bakker
 *
 * Contains constant values to be referenced by various source files like
 * the maximum number of resource types and running tasks.
 */

#if !defined(A4_CONSTANTS_H)
#define A4_CONSTANTS_H

#include <chrono>

typedef std::chrono::high_resolution_clock HR_Clock;
typedef std::chrono::milliseconds millisec;
typedef std::chrono::duration<double> raw_duration;

#define NRES_TYPES 10
#define NTASKS 25

#endif
