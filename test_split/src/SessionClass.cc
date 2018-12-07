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
		if (argc != ARG_COUNT) { throw Sess_Exception(ERR_SESS_INVALID_ARGC, ERR_SESS_CONSTR_FUNC); }

		arg_str = argv[1];
		this->file_name = arg_str;
		arg_str = argv[2];
		this->mon_time = str_to_int(arg_str);
		arg_str = argv[3];
		this->n_iter = str_to_int(arg_str);
		
		this->res_dict = new SessResDict();
		this->task_mngr = new TaskManager();
	} catch (Parse_Exception& e) { throw Sess_Exception(e.what(), ERR_SESS_CONSTR_FUNC, e.get_traceback()); }
}

Session::~Session() {
	delete this->res_dict;
	delete this->task_mngr;
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
void Session::parse_input_file() {
	FILE * input_file = NULL;
	std::string line("t2 50 100 A:1 B:1"), first_tok("task");
	//char line_buffer[MAX_LINE_LENGTH + 1];

	try {
		std::cout << line << "\n";
		//this->parse_task_line(line);
		//memset(line_buffer, 0, sizeof(line_buffer));
		//input_file = fopen(file_name.c_str(), "r");
		//if (input_file == NULL) { throw Sess_Exception(ERR_INPUT_FILE_OPEN_FAIL, ERR_SESS_PARSE_IFILE_FUNC); }

		//while (fgets(line_buffer, sizeof(line_buffer), input_file)) {
		//while (1) {
			//std::cout << "reading next line\n";
			// If file is non-empty and not a comment
			//if (true) {
			//if (line_buffer[0] != '\n' && line_buffer[0] != '#') {
				// Get first token from line to determine its type
				//line = line_buffer;
				//line = line.substr(0, line.length() - 1);

				//get_first_tok(line, INPUT_FILE_DELIM_CHAR, first_tok);
				//std::cout << "First tok|" << first_tok << "|END\n";
				//if (first_tok == INPUT_FILE_TASK_START) {
					//std::cout << "Parsing task line\n";
					//this->parse_task_line(line);
				//} else if (first_tok == INPUT_FILE_RESOURCE_START) {
				//	this->parse_resource_line(line);
				//}
			//}
			//memset(line_buffer, 0, sizeof(line_buffer));
			//break;
		//}

		//fclose(input_file);
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
	std::string test_str("A:1");
	
	try {
		res_count = n_tok_split(res_line, INPUT_FILE_DELIM_CHAR, res_toks);
		for (int i = 0; i < res_count; i++) {
			//this->res_dict->deser_and_add(test_str);
			std::cout << res_toks[i] << "\n";
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
		new_task = new Task(task_line, this->n_iter);
		std::cout << "Task created yay\n";
		new_task->set_start_time(this->start_time);
		std::cout << "set start time for task\n";
		
		this->task_mngr->add_task(new_task);
		std::cout << "added task to mngr\n";

	} catch (Task_Exception& e) { throw Sess_Exception(e.what(), ERR_SESS_PARSE_TASK_LINE_FUNC, e.get_traceback()); }
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
	std::string test_tline("t1 50 100 A:1 B:1 Banana:3 Hello:95");
	std::string test_rline("A:1 B:1            C:5");
	
	try {
		std::cout << test_tline << "\n";
		this->parse_input_file();
		//this->task_mngr->run_all();
		//this->parse_task_line(test_tline);
		//this->parse_resource_line(test_rline);
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
	
