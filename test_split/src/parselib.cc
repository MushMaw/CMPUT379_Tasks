/**
 * CMPUT 379 - Assignment 4
 * File Name: parselib.cc
 * Student Name: Jacob Bakker
 *
 * 
 */


#include "parselib.h"


/**
 * Function: str_to_int
 * -----------------------
 * Returns integer conversion of string.
 *
 * Parameters:
 * 	- str: String to be converted to integer.
 * Return Value:
 * 	- Integer conversion of "str".
 * Throws:
 *	- Parse_Exception
 * CITATION: This function is identical to the Assignment 3 function "str_to_int" in "parselib.cc"
 */
int str_to_int(const std::string& str) {
	int output;
	char *c_ptr;

	output = strtol(str.c_str(), &c_ptr, 10);
	// Throw exception if non-numeric character is found in "str"
	if (*c_ptr) { throw Parse_Exception(ERR_PARSELIB_NON_INT_CHAR, ERR_PARSELIB_STR_TO_INT_FUNC); }
	
	return output;
}

/**
 * Function: n_tok_split
 * -----------------------
 * Splits string "str" into tokens by the delimiter "delim", then saves first
 * "n" tokens to "toks" container.
 * Tokens may be separated by an arbitrary number of delimiters. If no "n" value
 * is specified, all tokens will be saved to the "toks" list.
 *
 * Parameters:
 * 	- str: String to be split into tokens.
 *	- delim: String delimiter to split "str" by.
 *	- toks: Stores string tokens taken from "str".
 *	- n: Number of tokens to save. If left unspecified, all tokens will be saved.
 * Return Value:
 * 	- Number of tokens taken from "str".
 * Throws: None
 */
int n_tok_split(const std::string& str, char delim, std::deque<std::string>& toks, int n) {
	int str_len = 0, tok_start = -1, tok_len = 0, tok_count = 0;
	std::string token("");	
	char c;

	str_len = str.length();
	for (int i = 0; i < str_len; i++) {
		c = str[i];
		if (c != delim && tok_start < 0) {
			tok_start = i;
		} else if (c == delim && tok_start >= 0) {
			tok_len = i - tok_start;
			token = str.substr(tok_start, tok_len);
			toks.push_back(token);
			tok_count++;
			if (n > 0 && tok_count == n) { return tok_count; }
			tok_start = -1;
		} 
	}

	if (tok_start >= 0) {
		tok_len = str_len - tok_start;
		token = str.substr(tok_start, tok_len);
		toks.push_back(token);
		tok_count++;
	}
	return tok_count;
}	

/**
 * Function: split_first_tok
 * -----------------------
 * 
 *
 * Parameters: 
 *	- str: The string to be split after its first token
 *	- delim: String delimiter to split "str" by
 *	- first_tok: The first token extracted from "str".
 * Return Value: None
 * Throws: None
 */
int get_first_tok(std::string& str, char delim, std::string& first_tok) {
	int str_len = 0, tok_start = -1, tok_len = 0;
	char c;

	str_len = str.length();
	for (int i = 0; i < str_len; i++) {
		c = str[i];
		if (c != delim && tok_start < 0) {
			tok_start = i;
		} else if (c == delim && tok_start >= 0) {
			tok_len = i - tok_start;
			first_tok = str.substr(tok_start, tok_len);
			str = str.substr(i, str.length() - i);
			return tok_len;
		}
	}
	return 0;
}

/**
 * Function: get_duration
 * -----------------------
 * 
 *
 * Parameters: 
 *	- start: Start time.
 *	- end: End time.
 * Return Value: Duration in milliseconds.
 * Throws: None
 */
int get_duration(HR_Clock::time_point start, HR_Clock::time_point end) {
	millisec ms_dur;
	raw_duration raw_dur;
	int ms;

	raw_dur = std::chrono::duration_cast<raw_duration>(end - start);
	ms_dur = std::chrono::duration_cast<millisec>(raw_dur);
	ms = ms_dur.count();

	return ms;
}
