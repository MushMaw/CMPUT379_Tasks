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
Task::Task(std::string& ser_task) {
	try {
		this->req_res = new ResDict();
		this->timer = new Timer();
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
void Task::deserialize(std::string& ser_task) {
	std::deque<std::string> toks;
	int tok_count = 0;

	try {
		tok_count = n_tok_split(ser_task, SER_TASK_DELIM, toks);
		if (tok_count != SER_TASK_TOK_COUNT) { throw Task_Exception(ERR_SER_TASK_TOK_COUNT, ERR_TASK_DESER_FUNC); }

		this->name.assign(toks[0]);
		this->busy_time = str_to_int(toks[1]);
		this->idle_time = str_to_int(toks[2]);
		this->wait_time = 0;
		
		for (int i = 3; i < tok_count; i++) {
			this->req_res->deserialize_res(toks[i]);
		}
	} catch (Parse_Exception& e) { throw Task_Exception(e.what, ERR_TASK_DESER_FUNC, e.get_traceback()); }
	  catch (ResDict_Exception& e) { throw Task_Exception(e.what, ERR_TASK_DESER_FUNC, e.get_traceback()); }
}

/**
 * Function: start_task_thread
 * -----------------------
 * 
 *
 * Parameters: 
 *	context: Pointer to Task object
 * Return Value: None
 * Throws: None
 */
static void Task::start_task_thread(void *context) {
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
 */
void Task::set_start_time(HR_Clock::time_point start_time) {
	this->start_time = start_time;
}

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
	int runtime = this->get_runtime;
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
	fprintf(stdout, TASK_PRINT_HEADER, this->name.c_str(), this->run_time, this->idle_time);
	fprintf(stdout, TASK_PRINT_TID, this->tid);
	this->req_res->print();
	fprintf(stdout, TASK_PRINT_RUN_WAIT_COUNTS, this->run_iters, this->wait_time);
	std::cout << "\n";
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
void * Task::run(int n_iter) {
	this->n_iter = n_iter;
	this->current_iter = 0;
	while (this->current_iter < this->n_iter) {
		this->acquire_res();

		this->wait(this->run_time);
		this->wait(this->idle_time);

		this->print_finish_iter();
		this->current_iter++
	}
	return NULL;
}
