/**
 * CMPUT 379 - Assignment 4
 * File Name: ResourceClass.h
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(RESOURCE_CLASS_H)
#define RESOURCE_CLASS_H 1

#include <string>

#define SER_RES_TOK_COUNT 2
#define SER_RES_DELIM ':'

// Error messages
#define ERR_RES_TOK_COUNT "Invalid string for serialized Resource\n"

// Function names
#define ERR_RESDICT_DESER_ADD_FUNC std::string("ResDict::deserialize()")

class ResDict_Exception : public TB_Exception {
	public:
		ResDict_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) :
		TB_Exception(msg, cur_func, func_traceback);
		ResDict_Exception(const char* msg, const std::string cur_func) :
		TB_Exception(msg, cur_func);
}

class ResDict {
	private:
		std::map<std::string, int> rdict;
	public:
		void deser_and_add(std::string& ser_res);
		void set_res(std::string& res_name, int value);

		virtual void print();
}

class SessResDict : public ResDict {
	private:
		std::mutex res_mutex;

	public:
		bool acquire_res(const TaskResDict* request_res);
		void release_res(const TaskResDict* acquire_res);

		void print() override;
}

class TaskResDict : public ResDict {
	private:
		SessResDict * sess_res;
		bool has_acq_res;
	public:	
		void acquire_res();
		void release_res();

		void print() override;
}
#endif
