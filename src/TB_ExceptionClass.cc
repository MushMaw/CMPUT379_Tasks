/**
 * CMPUT 379 - Assignment 4
 * File Name: TB_Exception.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#include "TB_ExceptionClass.h"


TB_Exception::TB_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) : std::runtime_error(msg) {
	this->traceback = "";
	this->traceback += cur_func;
	this->traceback += TB_EXC_TRACEBACK_DELIM;
	this->traceback += func_traceback;
}

TB_Exception::TB_Exception(const char* msg, const std::string cur_func) : std::runtime_error(msg) {
	this->traceback = "";
	this->traceback += cur_func;
	this->error_code = error_code;
}

void TB_Exception::print_msg_traceback() {
	std::cerr << TB_EXC_PRINT_START;
	std::cerr << TB_EXC_TRACEBACK << this->traceback << "\n";
	std::cerr << TB_EXC_ERROR_MSG << this->what();
}

std::string TB_Exception::get_traceback() {
	return this->traceback();
}
