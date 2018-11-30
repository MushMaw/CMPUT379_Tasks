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
		
		for (int i = 3; i < tok_count; i++) {
			this->req_res->deserialize_res(toks[i]);
		}
	} catch (Parse_Exception& e) { throw Task_Exception(e.what, ERR_TASK_DESER_FUNC, e.get_traceback()); }
	  catch (ResDict_Exception& e) { throw Task_Exception(e.what, ERR_TASK_DESER_FUNC, e.get_traceback()); }
}

void Task::wait(int time) {
	usleep(time);
}
