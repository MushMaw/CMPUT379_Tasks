/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#include "TaskClass.h"


/**
 * Function: Task Constructor
 * -----------------------
 * 
 *
 * Parameters: 
 *	- ser_task: Task string with format "name <busy_time> <idle_time> name1:value1 ..."
 * Return Value: None
 * Throws: Task_Exception
 */
Task::Task(const std::string& ser_task, int n_iter) {
	try {
		this->n_iter = n_iter;
		std::cout << "set n_iter\n";
		this->req_res = new TaskResDict();
		std::cout << "defined res dict\n";
		this->deserialize(ser_task);
	} catch (Task_Exception& e) { throw Task_Exception(e.what(), ERR_TASK_CONSTR_FUNC, e.get_traceback()); }
}


/**
 * Function: deserialize
 * -----------------------
 * 
 *
 * Parameters: 
 *	ser_task: Task string with format "name <busy_time> <idle_time> name1:value1 ..."
 * Return Value: None
 * Throws: Task_Exception
 */
void Task::deserialize(const std::string& ser_task) {
	std::deque<std::string> toks;
	int tok_count = 0;

	std::cout << "in task deser\n";
	try {
		tok_count = n_tok_split(ser_task, SER_TASK_DELIM, toks);

		this->name.assign(toks[0]);
		this->busy_time = str_to_int(toks[1]);
		this->idle_time = str_to_int(toks[2]);
		this->wait_time = 0;
		
		std::cout << "tok count: " << tok_count << "\n";
		for (int i = 3; i < tok_count; i++) {
			std::cout << "iter: " << i << "\n";
			this->req_res->deser_and_add(toks[i]);
		}
		std::cout << "Out of for loop\n";
	} catch (Parse_Exception& e) { throw Task_Exception(e.what(), ERR_TASK_DESER_FUNC, e.get_traceback()); }
	  catch (ResDict_Exception& e) { throw Task_Exception(e.what(), ERR_TASK_DESER_FUNC, e.get_traceback()); }
}

/**
 * Function: run_task_thread
 * -----------------------
 * 
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
 * 
 *
 * Parameters: 
 *	- start_time: Starting time of program that created this Task object
 * Return Value: None
 * Throws: None
 
void Task::set_start_time(HR_Clock::time_point start_time) {
	this->start_time = start_time;
}*/

/**
 * Function: wait
 * -----------------------
 * 
 *
 * Parameters: 
 *	- time: Time in milliseconds
 * Return Value: None
 * Throws: None
 */
void Task::wait(int time) {
	usleep(time);
}
/**
 * Function: print_finish_iter
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void Task::print_finish_iter() {
	int runtime = this->get_runtime();
	fprintf(stdout, TASK_FINISH_ITER_MSG, this->name.c_str(), tid, (this->current_iter+1), runtime);
}

/**
 * Function: get_runtime
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: Runtime in milliseconds
 * Throws: None
 */
int Task::get_runtime() {
	return 0;
}

void Task::acquire_res() {
	int wait_time = 0;
	bool obtained_res = false;
	HR_Clock::time_point wait_start, wait_end;

	wait_start = HR_Clock::now();
	while (obtained_res == false) {
		obtained_res = this->req_res->acquire_res();
		if (obtained_res == false) {

		}
	}
	wait_end = HR_Clock::now();
	wait_time = get_duration(wait_start, wait_end);
	this->wait_time += wait_time;
}

void Task::release_res() {
	this->req_res->release_res();
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
void Task::print() {
	fprintf(stdout, TASK_PRINT_HEADER, this->name.c_str(), this->busy_time, this->idle_time);
	fprintf(stdout, TASK_PRINT_TID, this->tid);
	this->req_res->print();
	fprintf(stdout, TASK_PRINT_RUN_WAIT_COUNTS, this->current_iter, this->wait_time);
	std::cout << "\n";
}

/**
 * Function: is_done
 * -----------------------
 * 
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
 * Function: run
 * -----------------------
 * 
 *
 * Parameters: 
 *	n_iter: Number of times this Task should run
 * Return Value: None
 * Throws: 
 */
void * Task::run() {
	this->current_iter = 0;
	while (this->current_iter < this->n_iter) {
		this->acquire_res();

		this->wait(this->busy_time);
		this->release_res();
		this->wait(this->idle_time);

		this->print_finish_iter();
		this->current_iter++;
	}
	return NULL;
}
