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

#define TMONITOR_PRINT_START
 
class TaskMonitor {
	private:
		TaskManager * task_mngr;
		TStat_Dict tstat_dict;
		std::vector<std::string> tname_list;
		int mtime;
	public:
		TaskMonitor(TaskManager * task_mgnr);
	
		void poll_task_status();
		void print();
		void run();
};

#endif
