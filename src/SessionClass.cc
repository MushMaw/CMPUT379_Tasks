#include "SessionClass.h"


/**
 * Function: Session Constructor
 * -----------------------
 * 
 *
 * Parameters: 
 *	- argc: Argument count
 *	- argv: Argument array
 *	- start_time: Starting time of calling program (here, a4task)
 * Return Value: None
 * Throws: Sess_Exception
 */
Session::Session(int argc, char *argv[], HR_Clock::time_point start_time) {
	std::string arg_str("");
	try {
		arg_str = argv[1];
		this->parse_input_file(arg_str);
		arg_str = argv[2];
		this->mon_time = str_to_int(arg_str);
		arg_str = argv[3];
		this->n_iter = str_to_int(arg_str);
		
		this->res_dict = new SessResDict();
		this->task_mngr = new TaskManager();

	} catch (Parse_Exception& e) { throw Sess_Exception(e.what(), ERR_SESS_CONSTR_FUNC, e.get_traceback()); }

}

/**
 * Function: parse_input_file
 * -----------------------
 * 
 *
 * Parameters:
 *	- file_name: Name of input file
 * Return Value: None
 * Throws: Sess_Exception
 */
void Session::parse_input_file(const std::string& file_name) {
	std::ifstream input_file;
	std::string line(""), first_tok("");
	char line_buffer[MAX_LINE_LENGTH + 1];

	try {
		input_file.open(file_name.c_str());
		if (input_file.fail()) { throw Sess_Exception(ERR_INPUT_FILE_OPEN_FAIL, ERR_SESS_PARSE_IFILE_FUNC); }

		while (input_file.getline(line_buffer, MAX_LINE_LENGTH)) {
			// If file is non-empty and not a comment
			if (line_buffer[0] != '\n' && line_buffer[0] != '#') {
				// Get first token from line to determine its type
				line = line_buffer;
				get_first_tok(line, INPUT_FILE_DELIM_CHAR, first_tok);
				if (first_tok == INPUT_FILE_TASK_START) {
					this->parse_resource_line(line);
				} else if (first_tok == INPUT_FILE_RESOURCE_START) {
					this->parse_task_line(line);
				}
			}
			std::memset(line_buffer, 0, sizeof(line_buffer));
		}

		input_file.close();
	} catch (Sess_Exception& e) { throw Sess_Exception(e.what(), ERR_SESS_PARSE_IFILE_FUNC, e.get_traceback()); }
}

/**
 * Function: parse_resource_line
 * -----------------------
 * 
 *
 * Parameters: 
 *	- res_line: String of format "name1:value1 name2:value2 ..."
 * Return Value: None
 * Throws: Sess_Exception
 */
void Session::parse_resource_line(const std::string& res_line) {
	std::deque<std::string> res_toks;
	int res_count;
	
	try {
		res_count = n_tok_split(res_line, INPUT_FILE_DELIM_CHAR, res_toks);
		for (int i = 0; i < res_count; i++) {
			this->res_dict->deser_and_add(res_toks[i]);
		}
	} catch (ResDict_Exception& e) { throw Sess_Exception(e.what(), ERR_SESS_PARSE_RES_LINE_FUNC, e.get_traceback()); }
}

/**
 * Function: parse_task_line
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void Session::parse_task_line(const std::string& task_line) {
	Task * new_task = NULL;
	try {
		new_task = new Task(task_line);
		new_task->set_start_time(this->start_time);
	} catch (Task_Exception& e) { throw Task_Exception(e.what(), ERR_SESS_PARSE_TASK_LINE_FUNC, e.get_traceback()); }
}

/**
 * Function: run
 * -----------------------
 * 
 *
 * Parameters: None
 * Return Value: None
 * Throws: Sess_Exception
 */
void Session::run() {
	try {
		this->task_mngr->run_all();
		this->print_results();
	} catch (Sess_Exception& e) { throw Sess_Exception(e.what(), ERR_SESS_RUN_FUNC, e.get_traceback()); }
}

/**
 * Function: print
 * -----------------------
 * Prints the session resource values (number available and held)
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void Session::print_results() {
	this->res_dict->print();
	this->task_mngr->print_all();
}
	
