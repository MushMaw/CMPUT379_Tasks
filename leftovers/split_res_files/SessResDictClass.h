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

#define SESS_RESDICT_PRINT_RES "\n%s: (maxAvail= %d, held=%d)\n"

class ResDict;

class SessResDict : public ResDict {
	private:
		std::mutex res_mutex;

	public:
		void deser_and_add(const std::string& ser_res) override;
		void set_res(const std::string& res_name, int value) override;

		bool acquire_res(const TaskResDict* request_res);
		void release_res(const TaskResDict* acquire_res);

		void print() override;
};

#endif
