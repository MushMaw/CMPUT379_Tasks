/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskResDictClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#include "TaskResDictClass.h"

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
	return this->sess_res->acquire_res(this);
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
