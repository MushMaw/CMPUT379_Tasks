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

#define INPUT_FILE_DELIM_CHAR ' '
#define INPUT_FILE_TASK_START std::string("task")
#define INPUT_FILE_RESOURCE_START std::string("resources")

class Sess_Exception : public TB_Exception {
	public:
		Sess_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) :
		TB_Exception(msg, cur_func, func_traceback);
		Sess_Exception(const char* msg, const std::string cur_func) :
		TB_Exception(msg, cur_func);
}

class Session {
	private:
		SessResDict * res_dict;
		TaskManager * task_mngr;
	
		void parse_input_file(const std::string& file_name);
		void parse_task_line(std::vector<std::string>& task_att_list)
		void parse_resource_line(std::deque<std::string>& res_str_list)
	public:
		Session(int argc, char *argv[]);
		void run();
		void print_results();
}

#endif
