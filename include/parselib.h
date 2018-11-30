/**
 * CMPUT 379 - Assignment 3
 * File Name: parselib.h
 * Student Name: Jacob Bakker
 *
 * Implements basic string parsing functions such as splitting a string into tokens and converting
 * strings to integers.
 */

#if !defined(PARSELIB_H)
#define PARSELIB_H 1


#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <deque>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "a4constants.h"

#define ERR_PARSELIB_STR_TO_INT_FUNC std::string("str_to_int()")

#define ERR_PARSELIB_NON_INT_CHAR "Non-int char found\n"


class Parse_Exception : public Traceback_Exception {
	public:
		Parse_Exception(const char* msg, const std::string cur_func, const std::string func_traceback, int error_code) 
		: Traceback_Exception(msg, cur_func, func_traceback, error_code) {}
		Parse_Exception(const char* msg, const std::string cur_func, int error_code)
		: Traceback_Exception(msg, cur_func, error_code) {}
};

int str_to_int(std::string const& str);
int n_tok_split(std::string& str, std::string delim, std::deque<std::string>& toks);


#endif
