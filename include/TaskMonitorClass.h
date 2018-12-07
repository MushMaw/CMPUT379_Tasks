/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskMonitorClass.cc
 * Student Name: Jacob Bakker
 *
 * Implements a monitor for running Tasks intended to be run concurrently
 * on its own thread while Tasks execute. 
 *
 * The Task Monitor periodically polls the running Tasks for their current status
 * (idling, running, waiting) before printing their statuses to the terminal. Once
 * all Tasks have finished running all of their iterations, the Monitor terminates.
 *
 * While polling and printing Task statuses, the Task Monitor locks all Tasks not currently
 * changing status from doing so until the Monitor has successfully polled and printed their
 * current statuses. During this time, Tasks will have their execution blocked until the Monitor
 * is done.
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
