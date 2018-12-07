/**
 * CMPUT 379 - Assignment 4
 * File Name: TB_Exception.cc
 * Student Name: Jacob Bakker
 *
 * Implements a Traceback Exception class to be inherited by the unique
 * exception classes for each source file (where applicable).
 *
 * Functions may append their names to the exception traceback as it is
 * bubbled up through functions, allowing for a function traceback to be
 * displayed with error messages.
 */

#include "TB_ExceptionClass.h"

/**
 * Traceback Exception constructors
 */
TB_Exception::TB_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) : std::runtime_error(msg) {
	this->traceback = "";
	this->traceback += cur_func;
	this->traceback += TB_EXC_TRACEBACK_DELIM;
	this->traceback += func_traceback;
}

TB_Exception::TB_Exception(const char* msg, const std::string cur_func) : std::runtime_error(msg) {
	this->traceback = "";
	this->traceback += cur_func;
}

/**
 * Getters/setters for Traceback Exception
 */
std::string TB_Exception::get_traceback() {
	return this->traceback;
}

/**
 * Function: print_msg_traceback
 * -----------------------
 * Prints the exception error message and a function traceback to
 * stderr.
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void TB_Exception::print_msg_traceback() {
	std::cerr << TB_EXC_PRINT_START;
	std::cerr << TB_EXC_TRACEBACK << this->traceback << "\n";
	std::cerr << TB_EXC_ERROR_MSG << this->what();
}


