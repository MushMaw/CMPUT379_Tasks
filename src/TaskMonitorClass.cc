/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskMonitorClass.cc
 * Student Name: Jacob Bakker
 *
 * Implements a monitor for running Tasks intended to be run concurrently
 * on its own thread while Tasks execute. 
 *
 * The Task Monitor periodically polls the running Tasks for their current status
 * (idling, running, waiting) through their Task Manager before printing their statuses 
 * to the terminal. Once all Tasks have finished running all of their iterations, the 
 * Monitor terminates.
 *
 * While polling and printing Task statuses, the Task Monitor locks all Tasks not currently
 * changing status from doing so until the Monitor has successfully polled and printed their
 * current statuses. During this time, Tasks will have their execution blocked until the Monitor
 * is done.
 */
 
#include "TaskMonitorClass.h"
 

/**
 * Function: TaskMonitorConstructor
 * -----------------------
 *
 * Parameters: 
 *	- task_mngr: The Task Manager of the monitored Tasks.
 *	- mtime: Millisecond interval between Monitor poll and print operations.
 * Return Value: Task Monitor object.
 * Throws: None
 */
TaskMonitor::TaskMonitor(TaskManager * task_mngr, int mtime) {
	this->task_mngr = task_mngr;
	this->mtime = mtime;
}

/**
 * Function: poll_task_status
 * -----------------------
 * Polls the current status of Tasks using the Task Manager.
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
 * Prints the current statuses of all monitored Tasks.
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
	
	// Append each task's name to the line containing their status.
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
 * While the monitored Tasks are still executing, this method polls and
 * prints the statuses of all Tasks in intervals of "mtime" milliseconds.
 *
 * Tasks are prevented from changing their status while the Monitor polls 
 * and prints their statuses.
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 * CITATION: The mutex system used for ensuring the Monitor cannot poll/print while Tasks are
 *	     changing status while not starving the Monitor is taken from the solution to the
 *	     "Second readers-writers problem" found here:
 *	     https://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem
 */
void * TaskMonitor::run() {
	do {
		usleep(this->mtime * 1000);

		mutex_lock(&tstat_try_lock); // Lock tasks from changing status
		mutex_lock(&monitor_print_lock); // Wait until all tasks currently changing status are done

		poll_task_status(); // Poll and print task statuses while they are unable to change them
		print(); 

		mutex_unlock(&monitor_print_lock); // Allow tasks to change status again
		mutex_unlock(&tstat_try_lock);
	} while (this->task_mngr->all_tasks_done() == false);
	return NULL;
}

/**
 * Function: start_monitor_thread
 * -----------------------
 * The method is used in the "pthread_create" call for the Monitor
 * thread to allow the Monitor to run on starting the thread.
 *
 * Parameters: 
 *	context: Pointer to TaskMonitor object.
 * Return Value: None
 * Throws: None
 */
void * TaskMonitor::start_monitor_thread(void* context) {
	return ((TaskMonitor *)context)->run();
}
