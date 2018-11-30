/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskClass.h
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(TASK_CLASS_H)
#define TASK_CLASS_H 1

#include "ResDictClass.h"
#include "parselib.h"
#include "a4constants.h"
#include "TB_Exception.h"

#define SER_TASK_DELIM ' '

#define ERR_TASK_CONSTR_FUNC std::string("Task::Task")
#define ERR_TASK_DESER_FUNC std::string("Task::deserialize()")

#define ERR_SER_TASK_TOK_COUNT "Invalid format for serialized Task\n"

enum TaskStatus {TS_WAIT, TS_IDLE, TS_BUSY}

class Task {
	private:
		std::string name;
		int tid, wait_time;
		int busy_time, idle_time, n_iter;

		ResDict * req_res;
		TaskStatus status;
		Timer * timer;

	public:
		Task(std::string& ser_task);

		void deserialize(std::string& ser_task);
		void wait(int time);
		std::string get_name();
		TaskStatus get_status();
}

#endif
