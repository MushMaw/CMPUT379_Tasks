#if !defined(MUTEX_LIB_H)
#define MUTEX_LIB_H 1

#include "pthread.h"
#include "stdlib.h"

void mutex_init(pthread_mutex_t * mutex);
void mutex_lock(pthread_mutex_t * mutex);
void mutex_unlock(pthread_mutex_t * mutex);

#endif
