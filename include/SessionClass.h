/**
 * CMPUT 379 - Assignment 4
 * File Name: SessionClass.h
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(SESSION_CLASS_H)
#define SESSION_CLASS_H 1

#include <string>
#include <map>

#include "ResDictClass.h"
#include "TaskClass.h"
#include "parselib.h"

class Sess_Exception : public TB_Exception {
	public:
		Sess_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) :
		TB_Exception(msg, cur_func, func_traceback);
		Sess_Exception(const char* msg, const std::string cur_func) :
		TB_Exception(msg, cur_func);
}

class Session {
	SessResDict * res_dict;
	std::vector<Task> task_list;
}

#endif
