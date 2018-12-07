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
Task::Task(const std::string& ser_task, int n_iter, SessResDict * sess_rdict) {
	try {
		this->n_iter = n_iter;
		this->req_res = new TaskResDict(sess_rdict);
		this->deserialize(ser_task);
		this->status = TS_IDLE;
	} catch (Task_Exception& e) { throw Task_Exception(e.what(), ERR_TASK_CONSTR_FUNC, e.get_traceback()); }
}

Task::~Task() {
	delete this->req_res;
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

	try {
		tok_count = n_tok_split(ser_task, SER_TASK_DELIM, toks);

		this->name.assign(toks[0]);
		this->busy_time = str_to_int(toks[1]);
		this->idle_time = str_to_int(toks[2]);
		this->wait_time = 0;
		this->current_iter = 0;
		this->tid = -1;
		
		for (int i = 3; i < tok_count; i++) {
			this->req_res->deser_and_add(toks[i]);
		}
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
 */
//void Task::set_start_time(HR_Clock::time_point start_time) {
//	this->start_time = start_time;
//}

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
	usleep(time * 1000);
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
	fprintf(stdout, TASK_FINISH_ITER_MSG, this->name.c_str(), int (this->tid), (this->current_iter+1), runtime);
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
		mutex_lock(&sess_res_lock);
		obtained_res = this->req_res->acquire_res();
		if (obtained_res == false) {
			this->wait(10);
		}
		mutex_unlock(&sess_res_lock);
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
 * 
 *
 * Parameters: None
 * Return Value: True if Task has run n iterations, false otherwise.
 * Throws: None
 */
bool Task::is_done() {
	if (this == NULL) { std::cout << "NULL TASK\n"; }
	if (this->n_iter == this->current_iter) { return true; }
	else { return false; }
}

void Task::change_status(TaskStatus st) {
	this->status = st;
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
	if (this == NULL) { std::cout << "NULL\n"; }
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
