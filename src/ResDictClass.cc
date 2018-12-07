/**
 * CMPUT 379 - Assignment 4
 * File Name: ResDictClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#include "ResDictClass.h"


ResDict::ResDict() {
	this->rdict = new std::map<std::string, ResDictVal>;
}

ResDict::~ResDict() {
	delete this->rdict;
}

/**
 * Function: deserialize (ResDict)
 * -----------------------
 * 
 *
 * Parameters: 
 *	- ser_res: Resource string with format "name:value"
 *	- res_name: Stores Resource name taken from "ser_res"
 * Return Value: Resource value extracted from "ser_res"
 * Throws: ResDict_Exception
 */
int ResDict::deserialize(const std::string& ser_res, std::string& res_name) {
	std::deque<std::string> toks;
	int tok_count = 0, res_value = 0;

	try {
		tok_count = n_tok_split(ser_res, SER_RES_DELIM, toks);
		if (tok_count != SER_RES_TOK_COUNT) { throw ResDict_Exception(ERR_RES_TOK_COUNT, ERR_RESDICT_DESER_FUNC); }
		res_name = toks[0];
		res_value = str_to_int(toks[1]);
		return res_value;
	} catch (Parse_Exception& e) { throw ResDict_Exception(e.what(), ERR_RESDICT_DESER_FUNC, e.get_traceback()); }
}

/**
 * Session Resource Dictionary class methods
 */


/**
 * Function: deser_and_add (SessResDict)
 * -----------------------
 * 
 *
 * Parameters: 
 *	- ser_res: Resource string with format "name:value"
 * Return Value: None
 * Throws: ResDict_Exception
 */
void SessResDict::deser_and_add(const std::string& ser_res) {
	int res_value;
	std::string res_name("");
	ResDictVal rd_val;

	try {
		res_value = deserialize(ser_res, res_name);
		rd_val.avail_res = res_value;
		rd_val.max_avail_res = res_value;
		rd_val.held_res = 0;
		(*this->rdict)[res_name] = rd_val;
		this->rname_list.push_back(res_name);
	} catch (ResDict_Exception &e) { throw ResDict_Exception(e.what(), ERR_SESS_RESDICT_DESER_ADD_FUNC, e.get_traceback()); }
}


/**
 * Function: acquire_res (SessResDict)
 * -----------------------
 * 
 *
 * Parameters: 
 *	- request_res: Dictionary of requested resource names and values
 * Return Value: True if Resources were available and given, false otherwise.
 * Throws: None
 */
bool SessResDict::acquire_res(std::map<std::string, ResDictVal> * req_res) {
	int need_res;
	std::map<std::string, ResDictVal>::iterator it;
	std::string rname("");
	ResDictVal sess_rd_val, req_rd_val;
		
	if (this->if_res_avail(req_res) == false) { return false; }
	for (it = (*req_res).begin(); it != (*req_res).end(); it++) {
		rname = it->first;
		req_rd_val = it->second;
		need_res = req_rd_val.need_res;
		sess_rd_val = (*this->rdict)[rname];

		sess_rd_val.avail_res -= need_res;
		sess_rd_val.held_res += need_res;
		req_rd_val.held_res += need_res;

		(*this->rdict)[rname] = sess_rd_val;
		(*req_res)[rname] = req_rd_val;
	}
	return true;
}


/**
 * Function: if_res_avail (SessResDict)
 * -----------------------
 * 
 *
 * Parameters: 
 *	- request_res: Dictionary of requested resource names and values
 * Return Value: True if available, false otherwise
 * Throws: None
 */
bool SessResDict::if_res_avail(std::map<std::string, ResDictVal> * req_res) {
	int avail_res, need_res;
	std::string rname("");
	ResDictVal sess_rd_val, req_rd_val;
	std::map<std::string, ResDictVal>::iterator it, it_sess;

	it_sess = (*this->rdict).begin();
	for (it = (*req_res).begin(); it != (*req_res).end(); it++) {
		rname = it->first;
		sess_rd_val = (*this->rdict)[rname];
		req_rd_val = it->second;
		avail_res = sess_rd_val.avail_res;
		need_res = req_rd_val.need_res;
		if (avail_res < need_res) { return false; }
	}
	return true;
}


/**
 * Function: release_res (SessResDict)
 * -----------------------
 * 
 *
 * Parameters: Dictionary of acquired Resource names and values
 * Return Value: None
 * Throws: None
 */
void SessResDict::release_res(std::map<std::string, ResDictVal> * acquire_res) {
	int acq_res;
	std::string rname("");
	ResDictVal sess_rd_val, acq_rd_val;
	std::map<std::string, ResDictVal>::iterator it;

	for (it = (*acquire_res).begin(); it != (*acquire_res).end(); it++) {
		rname = it->first;
		acq_rd_val = it->second;
		acq_res = acq_rd_val.held_res;
		sess_rd_val = (*this->rdict)[rname];
		
		sess_rd_val.avail_res += acq_res;
		sess_rd_val.held_res -= acq_res;
		(*this->rdict)[rname] = sess_rd_val;

		acq_rd_val.held_res -= acq_res;
		(*acquire_res)[rname] = acq_rd_val;
	}
	return;
}


/**
 * Function:print
 * -----------------------
 * Prints each resource name, number of available units, and the amount
 * of that resource currently held by some set of Tasks.
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void SessResDict::print() {
	int max_avail, held_res, rcount = this->rname_list.size();
	std::string rname("");

	std::cout << SESS_RESDICT_PRINT_START;
	for (int i = 0; i < rcount; i++) {
		rname = this->rname_list[i];
		max_avail = (*this->rdict)[rname].max_avail_res;
		held_res = (*this->rdict)[rname].held_res;
		fprintf(stdout, SESS_RESDICT_PRINT_RES, rname.c_str(), max_avail, held_res);
	}
	std::cout << "\n";
}	

/**
 * Task Resource Dictionary class methods
 */

TaskResDict::TaskResDict(SessResDict * sess_rdict) {
	this->sess_res = sess_rdict;
}

/**
 * Function: deser_and_add (TaskResDict)
 * -----------------------
 * 
 *
 * Parameters: 
 *	ser_res: Resource string with format "name:value"
 * Return Value: None
 * Throws: ResDict_Exception
 */
void TaskResDict::deser_and_add(const std::string& ser_res) {
	int res_value;
	std::string res_name("");
	ResDictVal rd_val;

	try {
		res_value = deserialize(ser_res, res_name);
		rd_val.need_res = res_value;
		rd_val.held_res = 0;
		(*this->rdict)[res_name] = rd_val;
		this->rname_list.push_back(res_name);
	} catch (ResDict_Exception& e) { throw ResDict_Exception(e.what(), ERR_TASK_RESDICT_DESER_ADD_FUNC, e.get_traceback()); }
}


/**
 * Function: acquire_res (TaskResDict)
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
bool TaskResDict::acquire_res() {
	return this->sess_res->acquire_res(this->rdict);
}


/**
 * Function: release_res (TaskResDict)
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void TaskResDict::release_res() {
	this->sess_res->release_res(this->rdict);
}


/**
 * Function: print (TaskResDict)
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void TaskResDict::print() {
	int rcount = this->rname_list.size(), held_res_val = 0, req_res_val = 0;
	std::string rname("");	
	ResDictVal rd_val;

	for (int i = 0; i < rcount; i++) {
		rname = this->rname_list[i];
		rd_val = (*this->rdict)[rname];
		req_res_val = rd_val.need_res;
		held_res_val = rd_val.held_res;
		fprintf(stdout, TASK_RESDICT_PRINT_RES, rname.c_str(), req_res_val, held_res_val);
	}
	return;
}
