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

enum TaskStatus {TS_WAIT, TS_IDLE, TS_BUSY}

class Task {
	private:
		std::string task_name;
		int tid, wait_time;
		int busy_time, idle_time, n_iter;

		ResDict * req_res;
		TaskStatus status;
		Timer * timer;

	public:
		Task(std::string& ser_task);

		void deserialize(std::string& ser_task);
		void wait(int time);
}

#endif
