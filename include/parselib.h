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
#include "TB_ExceptionClass.h"

#define ERR_PARSELIB_STR_TO_INT_FUNC std::string("str_to_int()")

#define ERR_PARSELIB_NON_INT_CHAR "Non-int char found\n"


class Parse_Exception : public TB_Exception {
	public:
		Parse_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) 
		: TB_Exception(msg, cur_func, func_traceback) {}
		Parse_Exception(const char* msg, const std::string cur_func)
		: TB_Exception(msg, cur_func) {}
};

int str_to_int(const std::string& str);
int n_tok_split(const std::string& str, char delim, std::deque<std::string>& toks, int n=0);
int get_first_tok(std::string& str, char delim, std::string& first_tok);

#endif
