#if !defined(SESSION_CLASS_H)
#define SESSION_CLASS_H 1

#include <string>
#include <map>

#include "TaskClass.h"

class Session {
	std::map<std::string, int> res_name_keys;
	std::vector<Task> task_list;
}

#endif
