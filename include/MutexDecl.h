#if !defined(MUTEX_DECL_H)
#define MUTEX_DECL_H 1

#include "pthread.h"
#include "stdlib.h"

extern pthread_mutex_t thread_create_lock;
extern pthread_mutex_t sess_res_lock;

#endif 
