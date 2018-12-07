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

#define TASK_RESDICT_PRINT_RES "\t%s: (needed= %d, held= %d)\n"

class ResDict;

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
