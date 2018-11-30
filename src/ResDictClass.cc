/**
 * CMPUT 379 - Assignment 4
 * File Name: ResourceClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#include "ResDictClass.h"


void ResDictClass::deser_and_add(std::string& ser_res) {
	std::deque<std::string> toks;
	int tok_count = 0, res_value = 0;

	try {
		tok_count = n_tok_split(ser_res, RES_DELIM, toks);
		if (tok_count != SER_RES_TOK_COUNT) { throw ResDict_Exception(ERR_RES_TOK_COUNT, ERR_RESDICT_DESER_ADD_FUNC); }

		res_value = str_to_int(toks[1]);
		this->set_res(toks[0], res_value);
	} catch { Parse_Exception& e) { throw ResDict_Exception(e.what(), ERR_RESDICT_DESER_ADD_FUNC, e.get_traceback()); }
}

void ResDictClass::set_res(std::string& res_name, int value) {
	this->rdict[res_name] = value;
}

/**
 * Session Resource Dictionary class methods
 */

void SessResDict::acquire_res(TaskResDict* request_res) {
	return;
}

void SessResDict::release_res(TaskResDict* acquire_res) {
	return;
}

void SessResDict::print() {
	return;
}

/**
 * Task Resource Dictionary class methods
 */

void TaskResDict::acquire_res() {
	this->has_acq_res = this->sess_res->acquire_res(this);
}

void TaskResDict::release_res() {
	this->sess_res->release_res(this);
}

void TaskResDict::print() {

}
