#include "SessionClass.h"

// Mutexes for thread creation and Session resources
pthread_mutex_t thread_create_lock;
pthread_mutex_t sess_res_lock;

// Mutexes for monitor thread and changing task status
pthread_mutex_t task_status_lock;
pthread_mutex_t tstat_try_lock;
pthread_mutex_t monitor_print_lock;
// Track number of task threads currently trying to change status
int change_stat_count;

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
Session::Session(int argc, char *argv[]) { // HR_Clock::time_point start_time) {
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
		this->monitor = new TaskMonitor(this->task_mngr, this->mon_time);

		mutex_init(&thread_create_lock);
		mutex_init(&sess_res_lock);

		mutex_init(&task_status_lock);
		mutex_init(&tstat_try_lock);
		mutex_init(&monitor_print_lock);
		change_stat_count = 0;
	} catch (Parse_Exception& e) { throw Sess_Exception(e.what(), ERR_SESS_CONSTR_FUNC, e.get_traceback()); }
}

Session::~Session() {
	delete this->res_dict;
	delete this->task_mngr;
	delete this->monitor;
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
	std::string line(""), first_tok("");
	char line_buffer[MAX_LINE_LENGTH + 1];

	try {
		memset(line_buffer, 0, sizeof(line_buffer));
		input_file = fopen(file_name.c_str(), "r");
		if (input_file == NULL) { throw Sess_Exception(ERR_INPUT_FILE_OPEN_FAIL, ERR_SESS_PARSE_IFILE_FUNC); }

		while (fgets(line_buffer, sizeof(line_buffer), input_file)) {
			// If file is non-empty and not a comment
			if (line_buffer[0] != '\n' && line_buffer[0] != '#') {
				// Get first token from line to determine its type
				line = line_buffer;
				line = line.substr(0, line.length() - 1);

				get_first_tok(line, INPUT_FILE_DELIM_CHAR, first_tok);
				if (first_tok == INPUT_FILE_TASK_START) {
					this->parse_task_line(line);
				} else if (first_tok == INPUT_FILE_RESOURCE_START) {
					this->parse_resource_line(line);
				}
			}
			memset(line_buffer, 0, sizeof(line_buffer));
		}

		fclose(input_file);
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
		new_task = new Task(task_line, this->n_iter, this->res_dict);
		//new_task->set_start_time(this->start_time);
		//std::cout << "set start time for task\n";
		
		this->task_mngr->add_task(new_task);

	} catch (Task_Exception& e) { throw Sess_Exception(e.what(), ERR_SESS_PARSE_TASK_LINE_FUNC, e.get_traceback()); }
}

void Session::start_monitor() {
	mutex_lock(&thread_create_lock);
	pthread_create(&this->mon_tid, NULL, &TaskMonitor::start_monitor_thread, this->monitor);
	mutex_unlock(&thread_create_lock);
}

void Session::wait_for_monitor() {
	pthread_join(this->mon_tid, NULL);
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
		this->parse_input_file();
		this->start_monitor();
		this->task_mngr->run_all();
		this->wait_for_monitor();
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
	
