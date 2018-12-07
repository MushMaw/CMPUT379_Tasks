#include "MutexLib.h"


void mutex_init(pthread_mutex_t * mutex) {
	if (pthread_mutex_init(mutex, NULL) != 0) { return; }
}

void mutex_lock(pthread_mutex_t * mutex) {
	if (pthread_mutex_lock(mutex) != 0) { return; }
}

void mutex_unlock(pthread_mutex_t * mutex) {
	if (pthread_mutex_unlock(mutex) != 0) { return; }
}	
