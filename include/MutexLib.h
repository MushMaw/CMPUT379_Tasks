/**
 * CMPUT 379 - Assignment 4
 * File Name: MutexLib.h
 * Student Name: Jacob Bakker
 *
 * Implements basic functions for creating, locking, and unlocking
 * mutexes to be used in synchronizing threads.
 *
 * CITATION: The following 3 functions are taken from the file "raceC.c" provided
 * in the CMPUT 379 document "Experiments involving race conditions in multithreaded
 * programs".
 */

#if !defined(MUTEX_LIB_H)
#define MUTEX_LIB_H 1

#include "pthread.h"
#include "stdlib.h"

void mutex_init(pthread_mutex_t * mutex);
void mutex_lock(pthread_mutex_t * mutex);
void mutex_unlock(pthread_mutex_t * mutex);

#endif
