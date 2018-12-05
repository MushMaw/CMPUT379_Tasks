/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskClass.h
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(TASK_CLASS_H)
#define TASK_CLASS_H 1

#include <chrono>

#include "ResDictClass.h"
#include "parselib.h"
#include "a4constants.h"
#include "TB_Exception.h"

#define SER_TASK_DELIM ' '

#define TASK_PRINT_HEADER "\t(%s, runTime= %d msec, idleTime= %d msec):\n"
#define TASK_PRINT_TID "\t(tid= %d)\n"
#define TASK_PRINT_RUN_WAIT_COUNTS "\t(RUN: %d times, WAIT: %d msec)\n"

#define ERR_SER_TASK_TOK_COUNT "Invalid format for serialized Task\n"

#define ERR_TASK_CONSTR_FUNC std::string("Task::Task")
#define ERR_TASK_DESER_FUNC std::string("Task::deserialize()")


enum TaskStatus {TS_WAIT, TS_IDLE, TS_BUSY}
const std::string tstat_str_arr[] = { "WAIT", "IDLE", "BUSY" };

class Task {
	private:
		std::string name;
		int tid, n_iter, current_iter;
		int wait_time, busy_time, idle_time;

		ResDict * req_res;
		TaskStatus status;
		Timer * timer;

	public:
		Task(std::string& ser_task);
		std::string get_name() { return this->name; }
		TaskStatus get_status() { return this->status; }

		void deserialize(std::string& ser_task);
		void set_start_time(HR_Clock::time_point start_time);
		int get_runtime();

		static void start_task_thread(void *context)
		void wait(int time);
		void * run();
		void print_finish_iter();
}

#endif
