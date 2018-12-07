/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskMonitorClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */
 
#include "TaskMonitorClass.h"
 

/**
 * Function: TaskMonitorConstructor
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
TaskMonitor::TaskMonitor(TaskManager * task_mngr, int mtime) {
	this->task_mngr = task_mngr;
	this->mtime = mtime;
}

/**
 * Function: poll_task_status
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void TaskMonitor::poll_task_status() {
	this->task_mngr->poll_task_status(this->tstat_dict);
}

/**
 * Function: print
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void TaskMonitor::print() {
	TStat_Dict::iterator it;
	TaskStatus tstat;
	std::string wait_line = TMONITOR_PRINT_WAIT_START;
	std::string run_line = TMONITOR_PRINT_RUN_START;
	std::string idle_line = TMONITOR_PRINT_IDLE_START;
	std::string tname("");
	
	for (it = this->tstat_dict.begin(); it != this->tstat_dict.end(); it++) {
		tname = it->first;
		tstat = it->second;
		switch(tstat) {
			case TS_WAIT:
				wait_line += tname + TMONITOR_PRINT_DELIM;
				break; 
			case TS_RUN:
				run_line += tname + TMONITOR_PRINT_DELIM;
				break;
			case TS_IDLE:
				idle_line += tname + TMONITOR_PRINT_DELIM;
				break;
		}
	}
	 
	std::cout << TMONITOR_PRINT_START;
	std::cout << wait_line << '\n';
	std::cout << TMONITOR_PRINT_WSPACE << run_line << '\n';
	std::cout << TMONITOR_PRINT_WSPACE << idle_line << '\n';
}

/**
 * Function: run
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void * TaskMonitor::run() {
	do {
		usleep(this->mtime * 1000);
		poll_task_status();

		mutex_lock(&tstat_try_lock); // Lock tasks from changing status
		mutex_lock(&monitor_print_lock); // Wait until all tasks currently changing status are done
		print(); // Print task statuses while they are unable to change them
		mutex_unlock(&monitor_print_lock); // Allow tasks to change status again
		mutex_unlock(&tstat_try_lock);
	} while (this->task_mngr->all_tasks_done() == false);
	return NULL;
}

/**
 * Function: start_monitor_thread
 * -----------------------
 * 
 *
 * Parameters: 
 *	context: Pointer to TaskMonitor object
 * Return Value: None
 * Throws: None
 */
void * TaskMonitor::start_monitor_thread(void* context) {
	return ((TaskMonitor *)context)->run();
}
