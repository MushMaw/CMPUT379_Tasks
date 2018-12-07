/**
 * CMPUT 379 - Assignment 4
 * File Name: SessResDictClass.h
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(SESS_RES_DICT_CLASS)
#define SESS_RES_DICT_CLASS 1

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <deque>

#include "TB_ExceptionClass.h"
#include "parselib.h"
#include "TaskResDictClass.h"
#include "ResDictConstants.h"

#define SESS_RESDICT_PRINT_RES "\n%s: (maxAvail= %d, held=%d)\n"

class TaskResDict;

class SessResDict {
	private:
		ResDict rdict;
		std::vector<std::string> rname_list;
		//std::mutex res_mutex;

	public:
		int deserialize(const std::string& ser_res, std::string& res_name);
		void deser_and_add(const std::string& ser_res);
		void set_res(const std::string& res_name, int value);

		bool acquire_res(const TaskResDict* request_res);
		void release_res(const TaskResDict* acquire_res);

		void print();
};

#endif
