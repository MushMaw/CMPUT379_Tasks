/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskMonitorClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */
 
 #include "TaskMonitorClass.h"
 

 void TaskMonitor::TaskMonitor(TaskManager * task_mngr) : task_mngr(task_mgnr) {
	 this->tname_list = task_mngr->tname_list;
 }
 
 void TaskMonitor::poll_task_status() {
	 this->task_mngr->poll_task_status(this->tstat_dict);
 }
 
 void TaskMonitor::print() {
	 int task_num = this->tname_list.size();
	 TaskStatus tstat;
	 std::string wait_line = TMONITOR_PRINT_WAIT_START;
	 std::string run_line = TMONITOR_PRINT_RUN_START;
	 std::string idle_line = TMONITOR_PRINT_IDLE_START;
	 std::string tname("");
	 
	 for (int i = 0; i < task_num; i++) {
		 tname = this->tname_list[i];
		 tstat = this->tstat_dict[tname];
		 switch(tstat) {
			case TS_WAIT:
				wait_line += tname + TMONITOR_PRINT_DELIM;
				break; 
			case TS_RUN:
				run_line += tname + TMONITOR_PRINT_DELIM;
				break;
			case TS_IDLE:
				idle_line += tname + TMONITOR_PRINT_DELIM;
				break;
		 }
	 }
	 
	 std::cout << TMONITOR_PRINT_START;
	 std::cout << TMONITOR_PRINT_WSPACE << wait_line << '\n';
	 std::cout << TMONITOR_PRINT_WSPACE << run_line << '\n';
	 std::cout << TMONITOR_PRINT_WSPACE << idle_line << '\n';
 }
 
 void TaskMonitor::run() {
	 // TODO: Wait for n milliseconds, then poll and print
	 return;
 }