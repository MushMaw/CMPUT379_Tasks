/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#include "TaskClass.h

Task::Task(std::string& ser_task) {
	try {
		this->req_res = new ResDict();
		this->timer = new Timer();
		this->deserialize(ser_task);
	} catch (Task_Exception& e) { throw Task_Exception(e.what(), ERR_TASK_CONSTR_FUNC, e.get_traceback()); }
}

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

static void Task::run_task_thread(void *context) {
	return ((Task *)context)->run();
}

void Task::set_start_time(int start_time) {
	this->start_time = start_time;
}

void Task::wait(int time) {
	usleep(time);
}

void Task::print_finish_iter() {
	int runtime = this->get_runtime;
	fprintf(stdout, TASK_FINISH_ITER_MSG, this->name.c_str(), tid, (this->current_iter+1), runtime);
}

int Task::get_runtime() {
	return 0;
}

void Task::print() {
	fprintf(stdout, TASK_PRINT_HEADER, this->name.c_str(), this->run_time, this->idle_time);
	fprintf(stdout, TASK_PRINT_TID, this->tid);
	this->req_res->print();
	fprintf(stdout, TASK_PRINT_RUN_WAIT_COUNTS, this->run_iters, this->wait_time);
	std::cout << "\n";
}

void Task::run(int n_iter) {
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
