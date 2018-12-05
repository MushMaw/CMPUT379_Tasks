/**
 * CMPUT 379 - Assignment 4
 * File Name: a4constants.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(A4_CONSTANTS_H)
#define A4_CONSTANTS_H

#include <chrono>

#define NRES_TYPES 10
#define NTASKS 25

typedef std::chrono::high_resolution_clock HR_Clock;
typedef std::chrono::milliseconds millisec;
typedef std::chrono::duration<double> raw_duration;

#endif
