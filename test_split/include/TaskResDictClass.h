/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskResDictClass.h
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(TASK_RES_DICT_CLASS_H)
#define TASK_RES_DICT_CLASS_H 1

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <deque>

#include "TB_ExceptionClass.h"
#include "parselib.h"
#include "SessResDictClass.h"
#include "ResDictConstants.h"

#define TASK_RESDICT_PRINT_RES "\t%s: (needed= %d, held= %d)\n"

class SessResDict;

class TaskResDict {
	private:
		ResDict rdict;
		std::vector<std::string> rname_list;

		SessResDict * sess_res;
	public:	
		int deserialize(const std::string& ser_res, std::string& res_name);
		void deser_and_add(const std::string& ser_res);
		void set_res(const std::string& res_name, int value);

		void acquire_res();
		void release_res();

		void print();
};

#endif
