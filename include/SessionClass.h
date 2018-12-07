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
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "ResDictClass.h"
#include "TaskClass.h"
#include "TaskManagerClass.h"
#include "TaskMonitorClass.h"
#include "parselib.h"
#include "TB_ExceptionClass.h"
#include "a4constants.h"
#include "MutexDecl.h"
#include "MutexLib.h"
#include "TimerClass.h"

#define ARG_COUNT 4

#define INPUT_FILE_DELIM_CHAR ' '
#define MAX_LINE_LENGTH 100
#define INPUT_FILE_TASK_START std::string("task")
#define INPUT_FILE_RESOURCE_START std::string("resources")

#define SESS_PRINT_RUNTIME "Running time= %d msec\n"

#define ERR_INPUT_FILE_OPEN_FAIL "Unable to open input file\n"
#define ERR_SESS_INVALID_ARGC "format: a4tasks inputFile monitorTime NITER\n"

#define ERR_SESS_CONSTR_FUNC std::string("Session()")
#define ERR_SESS_PARSE_IFILE_FUNC std::string("parse_input_file()")
#define ERR_SESS_PARSE_RES_LINE_FUNC std::string("parse_resource_line()")
#define ERR_SESS_PARSE_TASK_LINE_FUNC std::string("parse_task_line()")
#define ERR_SESS_RUN_FUNC std::string("run()")

class Sess_Exception : public TB_Exception {
	public:
		Sess_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) :
		TB_Exception(msg, cur_func, func_traceback) {}
		Sess_Exception(const char* msg, const std::string cur_func) :
		TB_Exception(msg, cur_func) {}
};

class Session {
	private:
		int n_iter, mon_time;
		pthread_t mon_tid;
		std::string file_name;
		SessResDict * res_dict;
		TaskManager * task_mngr;
		TaskMonitor * monitor;
		Timer * timer;
	
		void parse_input_file();
		void parse_task_line(const std::string& task_line);
		void parse_resource_line(const std::string& res_line);

		void start_monitor();
		void wait_for_monitor();
	public:
		Session(int argc, char *argv[]);
		~Session();
		void run();
		void print_results();
};

#endif
