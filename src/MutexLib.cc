/**
 * CMPUT 379 - Assignment 4
 * File Name: MutexLib.cc
 * Student Name: Jacob Bakker
 *
 * Implements basic functions for creating, locking, and unlocking
 * mutexes to be used in synchronizing threads.
 *
 * CITATION: The following 3 functions are taken from the file "raceC.c" provided
 * in the CMPUT 379 document "Experiments involving race conditions in multithreaded
 * programs".
 */

#include "MutexLib.h"


/**
 * Function: mutex_init
 * -----------------------
 * Initialize "mutex"
 *
 * Parameters:
 * 	- mutex: pthread mutex
 * Return Value: None
 * Throws: None
 * CITATION: See the citation at the top of the file.
 */
void mutex_init(pthread_mutex_t * mutex) {
	if (pthread_mutex_init(mutex, NULL) != 0) { return; }
}

/**
 * Function: mutex
 * -----------------------
 * Locks "mutex". If "mutex" is already locked, this function blocks
 * until it is unlocked.
 *
 * Parameters:
 * 	- mutex: pthread mutex
 * Return Value: None
 * Throws: None
 * CITATION: See the citation at the top of the file.
 */
void mutex_lock(pthread_mutex_t * mutex) {
	if (pthread_mutex_lock(mutex) != 0) { return; }
}

/**
 * Function: mutex
 * -----------------------
 * Unlocks "mutex".
 *
 * Parameters:
 * 	- mutex: pthread mutex
 * Return Value: None
 * Throws: None
 * CITATION: See the citation at the top of the file.
 */
void mutex_unlock(pthread_mutex_t * mutex) {
	if (pthread_mutex_unlock(mutex) != 0) { return; }
}	
