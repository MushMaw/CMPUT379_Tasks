/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskManagerClass.h
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(TASK_MANAGER_CLASS_H)
#define TASK_MANAGER_CLASS_H 1

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "TaskClass.h"
#include "TB_ExceptionClass.h"
#include "MutexDecl.h"
#include "MutexLib.h"

#define TSK_MNGR_PRINT_START "System Tasks:\n"
#define TSK_MNGR_PRINT_IDX "[%d] "

#define ERR_TASK_MNGR_LIMIT_REACHED "Cannot add Task: Maximum number of Tasks reached\n"

#define ERR_TASK_MNGR_CONSTR_FUNC std::string("TaskManager()")

typedef std::map<std::string, TaskStatus> TStat_Dict;

class TaskMngr_Exception : public TB_Exception {
	public:
		TaskMngr_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) :
		TB_Exception(msg, cur_func, func_traceback) {}
		TaskMngr_Exception(const char* msg, const std::string cur_func) :
		TB_Exception(msg, cur_func) {}
};

class TaskManager {
	private:
		int tcount;
		std::map<std::string, Task *> task_dict;
		std::vector<std::string> tname_list;
		std::vector<pthread_t> task_tid_list;
	public:
		TaskManager();
		~TaskManager();
		int get_tcount() { return this->tcount; }
		std::vector<std::string> get_tname_list() { return this->tname_list; }		

		void add_task(Task * new_task);
		void poll_task_status(TStat_Dict& tstat_dict);
		Task * get_task(const std::string& tname);
		void run_all();
		void print_all();
		bool all_tasks_done();
};

#endif
