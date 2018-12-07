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
#include <string>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "ResDictClass.h"
#include "parselib.h"
#include "a4constants.h"
#include "TB_ExceptionClass.h"
#include "MutexDecl.h"
#include "MutexLib.h"

#define SER_TASK_DELIM ' '

#define TS_WAIT_STR std::string("WAIT")
#define TS_RUN_STR std::string("RUN")
#define TS_IDLE_STR std::string("IDLE")

#define TASK_PRINT_HEADER "\t%s (%s, runTime= %d msec, idleTime= %d msec):\n"
#define TASK_PRINT_TID "\t(tid= %d)\n"
#define TASK_PRINT_RUN_WAIT_COUNTS "\t(RUN: %d times, WAIT: %d msec)\n"
#define TASK_FINISH_ITER_MSG "task: %s (tid= %d, iter= %d, time= %d msec)\n"

#define ERR_SER_TASK_TOK_COUNT "Invalid format for serialized Task\n"

#define ERR_TASK_CONSTR_FUNC std::string("Task::Task")
#define ERR_TASK_DESER_FUNC std::string("Task::deserialize()")


enum TaskStatus {TS_WAIT, TS_IDLE, TS_RUN};

class Task_Exception : public TB_Exception {
	public:
		Task_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) :
		TB_Exception(msg, cur_func, func_traceback) {}
		Task_Exception(const char* msg, const std::string cur_func) :
		TB_Exception(msg, cur_func) {}
};

class Task {
	private:
		std::string name;
		int n_iter, current_iter;
		pthread_t tid;
		int wait_time, busy_time, idle_time;
		//HR_Clock::time_point start_time;

		TaskResDict * req_res;
		TaskStatus status;

	public:
		Task(const std::string& ser_task, int n_iter, SessResDict * sess_rdict);
		~Task();
		void get_name(std::string& name) { name = this->name; }
		TaskStatus get_status() { return this->status; }

		void deserialize(const std::string& ser_task);
		//void set_start_time(HR_Clock::time_point start_time);
		int get_runtime();

		void acquire_res();
		void release_res();

		static void * run_task_thread(void *context);
		void wait(int time);
		void * run();
		void change_status(TaskStatus st);
		bool is_done();

		void print_finish_iter();
		void print();
};

#endif
