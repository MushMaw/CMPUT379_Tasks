/**
 * CMPUT 379 - Assignment 4
 * File Name: SessionClass.cc
 * Student Name: Jacob Bakker
 *
 * The Session class acts as the main class of the "a4tasks" program. It handles
 * the initialization of all system resources, Tasks, the Task Manager, and the 
 * Task Monitor. Once the Manager and Monitor are prepared, they are both made to
 * run and monitor the simulation respectively. Once done, the Session class displays
 * the results and exits.
 */

#include "SessionClass.h"

// Mutexes for thread creation and Session resources
pthread_mutex_t thread_create_lock;
pthread_mutex_t sess_res_lock;

// Mutexes for monitor thread and changing task status
pthread_mutex_t change_status_count_lock;
pthread_mutex_t tstat_try_lock;
pthread_mutex_t monitor_print_lock;
// Track number of task threads currently trying to change status
int change_stat_count;

/**
 * Function: Session Constructor
 * -----------------------
 * Initializes the Session using command line arguments.
 *
 * Parameters: 
 *	- argc: Argument count
 *	- argv: Argument array
 *	- start_time: Starting time of calling program (here, a4task)
 * Return Value: None
 * Throws: Sess_Exception
 */
Session::Session(int argc, char *argv[]) {
	std::string arg_str("");
	HR_Clock::time_point start_time = HR_Clock::now();

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
		this->timer = new Timer(start_time);

		mutex_init(&thread_create_lock);
		mutex_init(&sess_res_lock);

		mutex_init(&change_status_count_lock);
		mutex_init(&tstat_try_lock);
		mutex_init(&monitor_print_lock);
		change_stat_count = 0;
	} catch (Parse_Exception& e) { throw Sess_Exception(e.what(), ERR_SESS_CONSTR_FUNC, e.get_traceback()); }
}

/**
 * Session destructor
 */
Session::~Session() {
	delete this->res_dict;
	delete this->task_mngr;
	delete this->monitor;
	delete this->timer;
}

/**
 * Function: parse_input_file
 * -----------------------
 * Reads the input file and initializes all resource values and Tasks
 * specified in it.
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
 * Extracts all resource name-value pairs from the "res_line" string, then
 * saves them to the Session's resource dictionary.
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
 * Creates a new Task using attributes taken from the "task_line" string,
 * then saves the Task to the Session's Task Manager.
 *
 * Parameters: 
 *	- task_line: String of format "task_name <busytime> <idletime> name1:value1..."
 * Return Value: None
 * Throws: Sess_Exception
 */
void Session::parse_task_line(const std::string& task_line) {
	Task * new_task = NULL;
	try {
		new_task = new Task(task_line, this->n_iter, this->res_dict);
		new_task->set_start_time(this->timer->get_start_time());
		
		this->task_mngr->add_task(new_task);

	} catch (Task_Exception& e) { throw Sess_Exception(e.what(), ERR_SESS_PARSE_TASK_LINE_FUNC, e.get_traceback()); }
}

/**
 * Function: start_monitor
 * -----------------------
 * This method creates a new thread and runs the Task Monitor on it.
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void Session::start_monitor() {
	mutex_lock(&thread_create_lock);
	pthread_create(&this->mon_tid, NULL, &TaskMonitor::start_monitor_thread, this->monitor);
	mutex_unlock(&thread_create_lock);
}

/**
 * Function: wait_for_monitor
 * -----------------------
 * This method blocks until the Task Monitor has exited its thread.
 * This is intended to be called once the Task Manager has finished 
 * running all Tasks.
 *
 * Parameters: None
 * Return Value: None
 * Throws: Sess_Exception
 */
void Session::wait_for_monitor() {
	pthread_join(this->mon_tid, NULL);
}

/**
 * Function: run
 * -----------------------
 * This method initializes all resource and task instances from an input file,
 * starts threads for both the Tasks and the Task Monitor, and - once the Tasks
 * and Task Monitor have finished - prints the results of the simulation.
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
 * Prints the simulation results including the Session resource values,
 * the Task attributes including resource values and waiting time, and
 * the total runtime of the entire program.
 *
 * Parameters: None
 * Return Value: None
 * Throws: None
 */
void Session::print_results() {
	std::cout << "\n";
	this->res_dict->print();
	this->task_mngr->print_all();
	fprintf(stdout, SESS_PRINT_RUNTIME, this->timer->get_duration());
}
	
