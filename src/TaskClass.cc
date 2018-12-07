/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskClass.cc
 * Student Name: Jacob Bakker
 *
 * The Task class is responsible for the execution of Task threads that are capable
 * of acquiring/releasing resources from the Session, tracking the total wait time and
 * runtime of the Task and program respectively, and printing Task information on completing
 * individual iterations as well as entire executions.
 */

#include "TaskClass.h"


/**
 * Function: Task Constructor
 * -----------------------
 * Initializes Task oject from string. Intialally, the task status is IDLE similar to its
 * status on completing a single execution.
 *
 * Parameters: 
 *	- ser_task: Task string with format "name <busy_time> <idle_time> name1:value1 ..."
 *	- n_ter: The number of iterations executed each time the Task is run.
 *	- sess_rdict: The Resource Dictionary of the Session.
 * Return Value: None
 * Throws: Task_Exception
 */
Task::Task(const std::string& ser_task, int n_iter, SessResDict * sess_rdict) {
	try {
		this->n_iter = n_iter;
		this->current_iter = 0;
		this->req_res = new TaskResDict(sess_rdict);
		this->deserialize(ser_task);
		this->status = TS_IDLE;
		this->timer = new Timer();
	} catch (Task_Exception& e) { throw Task_Exception(e.what(), ERR_TASK_CONSTR_FUNC, e.get_traceback()); }
}

/**
 * Task destructor.
 */
Task::~Task() {
	delete this->req_res;
	delete this->timer;
}

/**
 * Function: deserialize
 * -----------------------
 * Initializes Task attributes from string.
 *
 * Parameters: 
 *	ser_task: Task string with format "name <busy_time> <idle_time> name1:value1 ..."
 * Return Value: None
 * Throws: Task_Exception
 */
void Task::deserialize(const std::string& ser_task) {
	std::deque<std::string> toks;
	int tok_count = 0;

	try {
		tok_count = n_tok_split(ser_task, SER_TASK_DELIM, toks);

		this->name.assign(toks[0]);
		this->busy_time = str_to_int(toks[1]);
		this->idle_time = str_to_int(toks[2]);

		this->wait_time = 0;
		this->current_iter = 0;
		this->tid = -1;
		
		// Add all subsequent resource name-value pairs to dictionary
		for (int i = 3; i < tok_count; i++) {
			this->req_res->deser_and_add(toks[i]);
		}
	} catch (Parse_Exception& e) { throw Task_Exception(e.what(), ERR_TASK_DESER_FUNC, e.get_traceback()); }
	  catch (ResDict_Exception& e) { throw Task_Exception(e.what(), ERR_TASK_DESER_FUNC, e.get_traceback()); }
}

/**
 * Function: run_task_thread
 * -----------------------
 * This method is intended to be passed to "pthread_create" along with a Task
 * object on creating a Task thread. 
 *
 * Parameters: 
 *	context: Pointer to Task object
 * Return Value: None
 * Throws: None
 */
void * Task::run_task_thread(void *context) {
	return ((Task *)context)->run();
}


/**
 * Function: set_start_time
 * -----------------------
 * Saves the start time of the "a4tasks" program for use in printing the time between
 * the program starting and the end of each Task iteration.
 *
 * Parameters: 
 *	- start_time: Starting time of program that created this Task object
 * Return Value: None
 * Throws: None
 */
void Task::set_start_time(HR_Clock::time_point start_time) {
	this->timer->set_start_time(start_time);
}

/**
 * Function: wait
 * -----------------------
 * Delays execution of the Task for "time" milliseconds.
 *
 * Parameters: 
 *	- time: Time in milliseconds
 * Return Value: None
 * Throws: None
 */
void Task::wait(int time) {
	usleep(time * 1000);
}
/**
 * Function: print_finish_iter
 * -----------------------
 * This method displays the Task's name, thread ID, iteration number, and runtime since
 * the program started. This is to be called after finishing a run iteration.
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void Task::print_finish_iter() {
	int runtime = this->get_runtime();
	fprintf(stdout, TASK_FINISH_ITER_MSG, this->name.c_str(), int (this->tid), (this->current_iter+1), runtime);
}

/**
 * Function: get_runtime
 * -----------------------
 * Returns the time in milliseconds between the start of the program and
 * the current time.
 *
 * Parameters: None
 * Return Value: Runtime in milliseconds
 * Throws: None
 */
int Task::get_runtime() {
	HR_Clock::time_point curr_time = HR_Clock::now();
	return this->timer->get_duration(curr_time);
}

/**
 * Function: acquire_res
 * -----------------------
 * Repeatedly attempts to acquire all needed resources from the Session.
 * On success, the method exits. On failure, the method stalls for 10 
 * milliseconds before attempting to acquire resources again.
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void Task::acquire_res() {
	int wait_time = 0;
	bool obtained_res = false;
	HR_Clock::time_point wait_start, wait_end;

	wait_start = HR_Clock::now();
	while (obtained_res == false) {
		mutex_lock(&sess_res_lock); // Lock other Tasks from getting resources
		obtained_res = this->req_res->acquire_res();
		if (obtained_res == false) {
			this->wait(10);
		}
		mutex_unlock(&sess_res_lock); // Allow other Tasks to get resources
	}
	// Save the amount of time spent waiting to obtain resources
	wait_end = HR_Clock::now();
	wait_time = get_duration(wait_start, wait_end);
	this->wait_time += wait_time;
}

/**
 * Function: release_res
 * -----------------------
 * Releases all held resources back to the Session ResDict.
 *
 * Parameters: None
 * Return Value: True if Task has run n iterations, false otherwise.
 * Throws: None
 */
void Task::release_res() {
	this->req_res->release_res();
}

/**
 * Function: print
 * -----------------------
 * Prints the Task's attributes including its status, the number of executed
 * iterations, and the total wait time over those iterations.
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void Task::print() {
	std::string stat_str("");
	switch (this->status) {
		case TS_RUN:
			stat_str = TS_RUN_STR; break;
		case TS_WAIT:
			stat_str = TS_WAIT_STR; break;
		case TS_IDLE:
			stat_str = TS_IDLE_STR; break;
	}
	fprintf(stdout, TASK_PRINT_HEADER, this->name.c_str(), stat_str.c_str(), this->busy_time, this->idle_time);
	fprintf(stdout, TASK_PRINT_TID, int (this->tid));
	this->req_res->print();
	fprintf(stdout, TASK_PRINT_RUN_WAIT_COUNTS, this->current_iter, this->wait_time);
	std::cout << "\n";
}

/**
 * Function: is_done
 * -----------------------
 * Determines whether the Task has executed all its iterations since starting.
 *
 * Parameters: None
 * Return Value: True if Task has run n iterations, false otherwise.
 * Throws: None
 */
bool Task::is_done() {
	if (this->n_iter == this->current_iter) { return true; }
	else { return false; }
}

/**
 * Function: change_status
 * -----------------------
 * This method sets the status of the Task to "st".
 *
 * Since Tasks are not allowed to change status while the Task Monitor is polling
 * and printing, the Task first attempts
 *
 * Parameters: None
 * Return Value: True if Task has run n iterations, false otherwise.
 * Throws: None
 * CITATION: The mutex system used for ensuring the Monitor cannot poll/print the Tasks' statuses
 *	     if they are being changed while not starving the Monitor is taken from the solution to
 *	     the "Second readers-writers problem" found here:
 *	     https://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem
 */
void Task::change_status(TaskStatus st) {
	mutex_lock(&tstat_try_lock); // Indicate task trying to change status
	mutex_lock(&change_status_count_lock); // Lock entry to number of tasks changing status

	change_stat_count++;
	// If this is the only task currently changing status, lock the monitor from printing
	if (change_stat_count == 1) { mutex_lock(&monitor_print_lock); }

	mutex_unlock(&change_status_count_lock); // Release locks for other tasks
	mutex_unlock(&tstat_try_lock);

	this->status = st;

	mutex_lock(&change_status_count_lock); // Lock entry to number of tasks changing status
	change_stat_count--;
	// If this is the last task currently changing status, unlock the monitor for printing
	if (change_stat_count == 0) { mutex_unlock(&monitor_print_lock); }
	mutex_unlock(&change_status_count_lock);
}

/**
 * Function: run
 * -----------------------
 * Executes a loop of acquiring resources, holding those resources for some amount of
 * time, then releasing them and idling for a perioud of time.
 *
 * Parameters: 
 *	n_iter: Number of times this Task should run
 * Return Value: None
 * Throws: 
 */
void * Task::run() {
	this->tid = pthread_self();
	this->current_iter = 0;
	while (this->current_iter < this->n_iter) {
		this->change_status(TS_WAIT);
		this->acquire_res();

		this->change_status(TS_RUN);
		this->wait(this->busy_time);
		this->release_res();

		this->change_status(TS_IDLE);
		this->wait(this->idle_time);

		this->print_finish_iter();
		this->current_iter++;
	}
	return NULL;
}
