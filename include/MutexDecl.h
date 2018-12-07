/**
 * CMPUT 379 - Assignment 4
 * File Name: MutexDecl.h
 * Student Name: Jacob Bakker
 *
 * Contains declarations for mutexes used by Session, Task, TaskManager,
 * and TaskMonitor instances.
 */

#if !defined(MUTEX_DECL_H)
#define MUTEX_DECL_H 1

#include "pthread.h"
#include "stdlib.h"

extern pthread_mutex_t thread_create_lock;
extern pthread_mutex_t sess_res_lock;

extern pthread_mutex_t change_status_count_lock;
extern pthread_mutex_t tstat_try_lock;
extern pthread_mutex_t monitor_print_lock;

extern int change_stat_count;

#endif 
