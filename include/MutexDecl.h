#if !defined(MUTEX_DECL_H)
#define MUTEX_DECL_H 1

#include "pthread.h"
#include "stdlib.h"

extern pthread_mutex_t thread_create_lock;
extern pthread_mutex_t sess_res_lock;

extern pthread_mutex_t task_status_lock;
extern pthread_mutex_t tstat_try_lock;
extern pthread_mutex_t monitor_print_lock;

extern int change_stat_count;

#endif 
