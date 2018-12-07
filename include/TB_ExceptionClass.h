/**
 * CMPUT 379 - Assignment 4
 * File Name: TB_Exception.h
 * Student Name: Jacob Bakker
 *
 * Implements a Traceback Exception class to be inherited by the unique
 * exception classes for each source file (where applicable).
 *
 * Functions may append their names to the exception traceback as it is
 * bubbled up through functions, allowing for a function traceback to be
 * displayed with error messages.
 */

#if !defined(TB_EXCEPTION_CLASS_H)
#define TB_EXCEPTION_CLASS_H 1

#include <iostream>
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
