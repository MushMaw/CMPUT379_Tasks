/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskMonitorClass.h
 * Student Name: Jacob Bakker
 *
 *
 */

#include <string>
#include <vector>

#include "TaskMonitorClass.h"
#include "TaskClass.h"
 
class TaskMonitor {
	private:
		TaskManager * task_mngr;
		TStat_Dict tstat_dict;
		std::vector<std::string> tname_list;
		int mtime;
	public:
		TaskMonitor(TaskManager * task_mgnr);
	
		void poll_task_status;
		void print();
		void run();
}
