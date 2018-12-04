/**
 * CMPUT 379 - Assignment 4
 * File Name: TaskManagerClass.cc
 * Student Name: Jacob Bakker
 *
 *
 */
 
 #include "TaskManager.h"
 
 void TaskManager::add_task(Task * new_task) {
	 std::string tname("");
	 
	 tname = new_task->get_name();
	 this->task_dict[tname] = new_task
	 this->tname_list.push_back(tname);
 }
 
 void TaskManager::poll_task_status(std::map<std::string, TaskStatus> tstat_dict) {
	for (auto const& [tname, task] : this->task_dict) {
		tstat_dict[tname] = task->get_status();
	}
 }
 
 Task * TaskManager::get_task(const std::string& tname) {
	return this->task_dict[tname];
 }
 
 void TaskManager::deser_and_add(const std::string& ser_task) {
	Task * new_task = NULL;
	
	try {
		new_task = new Task(ser_task);
		this->add_task(new_task);
	} catch (Task_Exception& e) { throw TaskMngr_Exception(e.what(), ERR_TASK_MNGR_DESER_ADD_FUNC, e.get_traceback()); }
 }