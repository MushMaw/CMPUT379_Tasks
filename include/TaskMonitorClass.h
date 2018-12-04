/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskManagerClass.h
 * Student Name: Jacob Bakker
 *
 *
 */
 
 class TaskMonitor {
	private:
		TaskManager * task_mngr;
		TStat_Dict tstat_dict;
		std::vector<std::string> tname_list;
	public:
		TaskMonitor(TaskManager * task_mgnr);
	
		void poll_task_status;
		void print();
		void run();
 }