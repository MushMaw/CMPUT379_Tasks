/**
 * CMPUT 379 - Assignment 4
 * File Name: ResourceClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#include "ResDictClass.h"


int ResDictClass::deserialize(const std::string& ser_res, std::string& res_name) {
	std::deque<std::string> toks;
	int tok_count = 0, res_value = 0;

	try {
		tok_count = n_tok_split(ser_res, RES_DELIM, toks);
		if (tok_count != SER_RES_TOK_COUNT) { throw ResDict_Exception(ERR_RES_TOK_COUNT, ERR_RESDICT_DESER_ADD_FUNC); }

		res_name = toks[0];
		res_value = str_to_int(toks[1]);
	} catch { (Parse_Exception& e) { throw ResDict_Exception(e.what(), ERR_RESDICT_DESER_ADD_FUNC, e.get_traceback()); }
}

/**
 * Session Resource Dictionary class methods
 */

void SessResDict::deser_and_add(const std::string& ser_res) {
	int res_value;
	std::string res_name("");
	ResDictVal rd_val;

	try {
		res_value = deserialize(ser_res, res_name);
		rd_val.avail_res = res_value;
		rd_val.held_res = 0;
		this->rdict[res_name] = rd_val;
	} catch (ResDict_Exception &e) { throw ResDict_Exception(e.what(), ERR_SESS_RESDICT_DESER_ADD_FUNC, e.get_traceback()); }
}

void SessResDict::acquire_res(TaskResDict* request_res) {
	int avail_res, need_res;

	if (this->is_res_avail(request_res) == false) { return false; }
	for (auto const& rname : request_res) {
		need_res = request_res->rdict[rname].need_res;
		this->rdict[res_name].avail_res -= need_res;
		this->rdict[res_name].held_res += need_res;
	}
}

bool SessResDict::if_res_avail(const TaskResDict* request_res) {
	int avail_res, need_res;

	for (auto const& rname : request_res) {
		avail_res = this->rdict[rname].avail_res;
		need_res = request_res->rdict[rname].need_res;
		if (avail_res < need_res) { return false; }
	}
	return true;
}

void SessResDict::release_res(TaskResDict* acquire_res) {
	int acq_res;

	for (auto const& rname : acquire_res) {
		acq_res = acquire_res->rdict[rname].held_res;
		this->rdict[rname].avail_res += acq_res;
		this->rdict[rname].held_res -= acq_res;
		acquire_res->rdict[rname].held_res -= acq_res;
	}
	return;
}

void SessResDict::print() {
	int max_avail, avail_res, held_res, rcount = this->rname_list.size();
	std::string rname("");

	for (int i = 0; i < rcount; i++) {
		rname = this->rname_list[i];
		avail_res = this->rdict[rname].avail_res;
		held_res = this->rdict[rname].held_res;
		fprintf(stdout, SESS_RESDICT_PRINT_RES, rname.c_str(), max_avail, held_res);
	}
}	

/**
 * Task Resource Dictionary class methods
 */

void TaskResDict::deser_and_add(std::string& ser_res) {
	int res_value;
	std::string res_name("");
	ResDictVal rd_val;

	try {
		res_value = deserialize(ser_res, res_name);
		rd_val.need_res = res_value;
		rd_val.held_res = 0;
		this->rdict[res_name] = rd_val;
	} catch (ResDict_Exception& e) { throw ResDict_Exception(e.what(), ERR_TASK_RESDICT_DESER_ADD_FUNC, e.get_traceback()); }
}

bool TaskResDict::acquire_res() {
	return this->sess_res->acquire_res(this);
}

void TaskResDict::release_res() {
	this->sess_res->release_res(this);
}

void TaskResDict::print() {
	int rcount = this->rname_list.size(), int held_res_val = 0;
	std::string rname("");	

	for (int i = 0; i < rcount; i++) {
		rname = this->rname_list[i];
		req_res_val = this->rdict[rname];

		if (this->has_all_res) { held_res_val = req_res_val; }
		else { held_res_val = 0; }

		fprintf(stdout, TASK_RESDICT_PRINT_RES, rname.c_str(), req_res_val, held_res_val);
	}
	return;
}
