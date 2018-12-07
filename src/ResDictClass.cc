/**
 * CMPUT 379 - Assignment 4
 * File Name: ResDictClass.cc
 * Student Name: Jacob Bakker
 *
 * Implements Resource Dictionary classes for both the Session and its running
 * Tasks.
 *
 * Both types of dictionary implement a function for adding resources from strings
 * with the format "<res_name>:<value>". Both dictionaries also contain print methods
 * to be used for outputting their resource values after Tasks have finished executing.
 *
 * The Session ResDict stores the maximum available values for each of its resources in
 * addition to the number of currently available and held resource values. Given a dictionary
 * of resource names and requested values from Tasks, the Session ResDict can give/retrieve
 * resources to/from the Task ResDict.
 *
 * The Task ResDict stores the Tasks required and currently held Resources. It implements methods
 * for acquiring/releasing resources through the Session ResDict it is set to.
 */

#include "ResDictClass.h"


/**
 * ResDict constructor and destructor
 */
ResDict::ResDict() {
	this->rdict = new std::map<std::string, ResDictVal>;
}

ResDict::~ResDict() {
	delete this->rdict;
}

/**
 * Function: deserialize (ResDict)
 * -----------------------
 * Given a string "ser_res" with the format "<res_name>:<value>", sets
 * returns the resource value and sets "res_name" to its name.
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
 * Extracts and saves a resource name and value from the "ser_res" string.
 * Initially, the number of available resources for this new resource is set
 * to the number provided while the number of held resources is 0.
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
 * Given a dictionary of requested resource names and values, this method
 * first checks whether the specified resources are available and - if they
 * are - gives the requested resources and adjusts the values for available 
 * resources accordingly. 
 *
 * If any one of the requested resouces are not available, the method does
 * nothing and exits.
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
 * Given a dictionary of requested resource names and values, this method
 * determines whether all of the specified resources are available.
 *
 * Parameters: 
 *	- request_res: Dictionary of requested resource names and values
 * Return Value: True if all request resources are available, false otherwise
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
 * Given a dictionary of held resources, this method retrieves the resources - 
 * reducing the held resource values of the Task ResDict to 0 while readjusting
 * the number of available and held resources for the Session ResDict accordingly.
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
 * Function: print
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

/**
 * Task ResDict constructor
 */
TaskResDict::TaskResDict(SessResDict * sess_rdict) {
	this->sess_res = sess_rdict;
}

/**
 * Function: deser_and_add (TaskResDict)
 * -----------------------
 * Extracts and saves a resource name and value from the "ser_res" string.
 * The value represents the number of required resources of this type. 
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
 * Attempts to retrieve all requested resources from the Session ResDict. 
 *
 * Parameters: None
 * Return Value: True if the required resources were obtained, false otherwise.
 * Throws: None
 */
bool TaskResDict::acquire_res() {
	return this->sess_res->acquire_res(this->rdict);
}


/**
 * Function: release_res (TaskResDict)
 * -----------------------
 * Releases all currently held resources back to the Session ResDict.
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
 * Prints each resource name coupled with its number of required and currently
 * held units.
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
