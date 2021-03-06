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
TaskMonitor::TaskMonitor(TaskManager * task_mngr) {
	this->tname_list = task_mngr->get_tname_list();
	this->task_mngr = task_mngr;
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
	int task_num = this->tname_list.size();
	TaskStatus tstat;
	std::string wait_line = TMONITOR_PRINT_WAIT_START;
	std::string run_line = TMONITOR_PRINT_RUN_START;
	std::string idle_line = TMONITOR_PRINT_IDLE_START;
	std::string tname("");
	
	for (int i = 0; i < task_num; i++) {
		tname = this->tname_list[i];
		tstat = this->tstat_dict[tname];
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
	std::cout << TMONITOR_PRINT_WSPACE << wait_line << '\n';
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
		usleep(this->mtime);
		poll_task_status();
		print();
	} while (this->task_mngr->all_tasks_done());
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
