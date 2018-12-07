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
#include <map>
#include <vector>

#include "TB_ExceptionClass.h"

#define SER_RES_TOK_COUNT 2
#define SER_RES_DELIM ':'

#define TASK_RESDICT_PRINT_RES "\t%s: (needed= %d, held= %d)\n"
#define SESS_RESDICT_PRINT_RES "\n%s: (maxAvail= %d, held=%d)\n"

// Error messages
#define ERR_RES_TOK_COUNT "Invalid string for serialized Resource\n"

// Function names
#define ERR_RESDICT_DESER_ADD_FUNC std::string("ResDict::deserialize()")

class SessResDict;
class TaskResDict;

typedef struct ResDictVal {
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
	private:
		std::map<std::string, ResDictVal> rdict;
		std::vector<std::string> rname_list;
	public:
		int deserialize(const std::string& ser_res, std::string& res_name);
		virtual void deser_and_add(const std::string& ser_res);
		virtual void set_res(const std::string& res_name, int value);

		virtual void print();
};

class SessResDict : public ResDict {
	private:
		//std::mutex res_mutex;
		int temp;

	public:
		void deser_and_add(const std::string& ser_res) override;
		void set_res(const std::string& res_name, int value) override;

		bool acquire_res(const TaskResDict* request_res);
		void release_res(const TaskResDict* acquire_res);

		void print() override;
};

class TaskResDict : public ResDict {
	private:
		SessResDict * sess_res;
	public:	
		void deser_and_add(const std::string& ser_res) override;
		void set_res(const std::string& res_name, int value) override;	

		void acquire_res();
		void release_res();

		void print() override;
};

#endif
