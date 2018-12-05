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
#include <vector>

#include "TaskClass.h"

#define TSK_MNGR_PRINT_IDX "[%d] "

typedef std::map<std::string, TaskStatus> TStat_Dict;

class TaskMngr_Exception : public TB_Exception {
	public:
		TaskMngr_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) :
		TB_Exception(msg, cur_func, func_traceback);
		TaskMngr_Exception(const char* msg, const std::string cur_func) :
		TB_Exception(msg, cur_func);
}

class TaskManager {
	private:
		std::map<std::string, Task *> task_dict;
		std::vector<std::string> tname_list;
		std::vector<pthread_t> task_tid_list;
	public:
		void add_task(Task * new_task);
		void poll_task_status(TStat_Dict tstat_dict);
		Task * get_task(const std::string& tname);
		void deser_and_add(const std::string& ser_task);
}
