/**
 * CMPUT 379 - Assignment 4
 * File Name: ResDictClass.h
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(RESOURCE_CLASS_H)
#define RESOURCE_CLASS_H 1

#include <string>
#include <iostream>
#include <map>
#include <deque>
#include <vector>

#include "TB_ExceptionClass.h"
#include "parselib.h"
#include "MutexDecl.h"

#define SER_RES_TOK_COUNT 2
#define SER_RES_DELIM ':'

#define TASK_RESDICT_PRINT_RES "\t%s: (needed= %d, held= %d)\n"
#define SESS_RESDICT_PRINT_START "System Resources:\n"
#define SESS_RESDICT_PRINT_RES "\t%s: (maxAvail= %d, held=%d)\n"

// Error messages
#define ERR_RES_TOK_COUNT "Invalid string for serialized Resource\n"

// Function names
#define ERR_RESDICT_DESER_FUNC std::string("ResDict::deserialize()")
#define ERR_SESS_RESDICT_DESER_ADD_FUNC std::string("SessResDict::deser_and_add()")
#define ERR_TASK_RESDICT_DESER_ADD_FUNC std::string("TaskResDict::deser_and_add()")

class SessResDict;
class TaskResDict;

typedef struct ResDictVal {
	int max_avail_res;
	int avail_res;
	int need_res;
	int held_res;
} ResDictVal;

class ResDict_Exception : public TB_Exception {
	public:
		ResDict_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) :
		TB_Exception(msg, cur_func, func_traceback) {}
		ResDict_Exception(const char* msg, const std::string cur_func) :
		TB_Exception(msg, cur_func) {}
};

class ResDict {
	public:
		std::map<std::string, ResDictVal> * rdict;
		std::vector<std::string> rname_list;

		ResDict();
		~ResDict();
		int deserialize(const std::string& ser_res, std::string& res_name);
		virtual void deser_and_add(const std::string& ser_res) {};

		virtual void print() {};
};

class SessResDict : public ResDict {
	public:
		//std::mutex res_mutex;
		int temp;

		void deser_and_add(const std::string& ser_res) override;

		bool acquire_res(std::map<std::string, ResDictVal> * req_res);
		bool if_res_avail(std::map<std::string, ResDictVal> * req_res);
		void release_res(std::map<std::string, ResDictVal> * acquire_res);

		void print() override;
};

class TaskResDict : public ResDict {
	public:
		SessResDict * sess_res;

		TaskResDict(SessResDict * sess_res);
		void deser_and_add(const std::string& ser_res) override;	

		bool acquire_res();
		void release_res();

		void print() override;
};

#endif
