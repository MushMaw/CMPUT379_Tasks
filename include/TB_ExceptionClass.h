/**
 * CMPUT 379 - Assignment 4
 * File Name: TB_Exception.h
 * Student Name: Jacob Bakker
 *
 *
 */

#if !defined(TB_EXCEPTION_CLASS_H)
#define TB_EXCEPTION_CLASS_H 1

#include <exception>
#include <string>

#define TB_EXC_PRINT_START "Exception Occurred:\n"
#define TB_EXC_TRACEBACK "	Traceback: "
#define TB_EXC_ERROR_MSG "	Error: "
#define TB_EXC_TRACEBACK_DELIM std::string(": ")

class TB_Exception : public std::runtime_error {
	std::string traceback;

	public:
		TB_Exception(const char* msg, const std::string cur_func, const std::string func_traceback);
		TB_Exception(const char* msg, const std::string cur_func);

		void print_msg_traceback();
		std::string get_traceback();
};
		

#endif
