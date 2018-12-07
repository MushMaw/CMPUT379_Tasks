/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskResDictClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#include "TaskResDictClass.h"

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
int TaskResDict::deserialize(const std::string& ser_res, std::string& res_name) {
	std::deque<std::string> toks;
	int tok_count = 0, res_value = 0;

	try {
		std::cout << "Ser res: " << ser_res << "\n";
		tok_count = n_tok_split(ser_res, SER_RES_DELIM, toks);
		if (tok_count != SER_RES_TOK_COUNT) { throw ResDict_Exception(ERR_RES_TOK_COUNT, ERR_RESDICT_DESER_FUNC); }
		std::cout << "Tok 0|" << toks[0] << "| Tok 1|" << toks[1] << "|\n";
		res_name = toks[0];
		res_value = str_to_int(toks[1]);
		return res_value;
	} catch (Parse_Exception& e) { throw ResDict_Exception(e.what(), ERR_RESDICT_DESER_FUNC, e.get_traceback()); }
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
		res_value = this->deserialize(ser_res, res_name);
		rd_val.need_res = res_value;
		rd_val.held_res = 0;
		this->rdict[res_name] = rd_val;
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
	std::string rname("");
	int needed_res = 0, rcount = this->rname_list.size();
	ResDictVal rd_val;
	bool got_res = false;

	got_res = this->sess_res->acquire_res(this->rdict);
	if (got_res) {
		
	} else {
		return false;
	}
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
	this->sess_res->release_res(this);
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
