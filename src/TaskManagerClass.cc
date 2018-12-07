/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskManagerClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */
 
#include "TaskManagerClass.h"

TaskManager::TaskManager() {
	this->tcount = 0;
}

TaskManager::~TaskManager() {
	std::map<std::string, Task *>::iterator it;
	Task * task = NULL;
	for (it = this->task_dict.begin(); it != this->task_dict.end(); it++) {
		task = it->second;
		delete task;
	}
}

/**
 * Function: add_task
 * -----------------------
 * 
 *
 * Parameters: 
 *	- new_task: Pointer to Task to be added
 * Return Value: None
 * Throws: TaskMngrException
 */
void TaskManager::add_task(Task * new_task) {
	std::string tname("");
	this->tcount = 0;
	if (this->tcount >= NTASKS) { throw TaskMngr_Exception(ERR_TASK_MNGR_LIMIT_REACHED, ERR_TASK_MNGR_CONSTR_FUNC); }

	new_task->get_name(tname);
	this->task_dict[tname] = new_task;
	this->tname_list.push_back(tname);
	this->tcount++;
}

/**
 * Function: poll_task_status
 * -----------------------
 * 
 *
 * Parameters: 
 *	- tstat_dict: Stores status values for all Tasks held by this manager
 * Return Value: None
 * Throws: None
 */
void TaskManager::poll_task_status(TStat_Dict& tstat_dict) {
	std::map<std::string, Task *>::iterator it;
	std::string tname("");
	Task * task = NULL;

	for (it = this->task_dict.begin(); it != this->task_dict.end(); it++) {
		tname = it->first;
		task = this->task_dict[tname];
		tstat_dict[tname] = task->get_status();
	}
}

/**
 * Function: get_task
 * -----------------------
 * 
 *
 * Parameters: 
 *	tname: Name of Task
 * Return Value: Pointer to Task with name "tname"
 * Throws: none
 */
Task * TaskManager::get_task(const std::string& tname) {
	return this->task_dict[tname];
}


/**
 * Function: run_all
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void TaskManager::run_all() {
	pthread_t pt_id;
	std::map<std::string, Task *>::iterator it;
	Task * next_task = NULL;
	int tcount = this->tname_list.size();

	// For each task, create a thread and run the task on it
	for (it = this->task_dict.begin(); it != this->task_dict.end(); it++) {
		mutex_lock(&thread_create_lock);
		next_task = it->second;
		pthread_create(&pt_id, NULL, &Task::run_task_thread, next_task);
		this->task_tid_list.push_back(pt_id);
		mutex_unlock(&thread_create_lock);
	}

	// Wait until all task threads have terminated
	for (int i = 0; i < tcount; i++) {
		pt_id = this->task_tid_list[i];
		pthread_join(pt_id, NULL);
	}
}

/**
 * Function: print_all
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void TaskManager::print_all() {
	int tcount = this->tname_list.size();
	std::string tname("");
	
	std::cout << TSK_MNGR_PRINT_START;
	for (int i = 0; i < tcount; i++) {
		tname = this->tname_list[i];
		fprintf(stdout, TSK_MNGR_PRINT_IDX, i);
		this->task_dict[tname]->print();
	}
}

/**
 * Function: all_tasks_done
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: True if all Tasks have completed their n iterations, false otherwise
 * Throws: None
 */
bool TaskManager::all_tasks_done() {
	std::string tname("");
	std::map<std::string, Task *>::iterator it;
	Task * task = NULL;

	for (it = this->task_dict.begin(); it != this->task_dict.end(); it++) {
		task = it->second;
		if (task->is_done() == false) { return false; }
	}

	return true;
}
