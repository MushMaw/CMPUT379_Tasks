/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskMonitorClass.h
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(TASK_MONITOR_CLASS_H)
#define TASK_MONITOR_CLASS_H 1

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "TaskClass.h"
#include "TaskManagerClass.h"

#define TMONITOR_PRINT_START "monitor: "
#define TMONITOR_PRINT_WSPACE "         "
#define TMONITOR_PRINT_WAIT_START "[WAIT] "
#define TMONITOR_PRINT_RUN_START "[RUN] "
#define TMONITOR_PRINT_IDLE_START "[IDLE] "
#define TMONITOR_PRINT_DELIM " "
 
class TaskMonitor {
	private:
		TaskManager * task_mngr;
		TStat_Dict tstat_dict;
		int mtime;
	public:
		TaskMonitor(TaskManager * task_mgnr, int mtime);
		~TaskMonitor() {};
	
		void poll_task_status();
		void print();
		void * run();
		static void * start_monitor_thread(void * context);
};

#endif
