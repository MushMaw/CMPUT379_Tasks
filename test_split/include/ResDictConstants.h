#if !defined(RESDICT_CONSTANTS_H)
#define RESDICT_CONSTANTS_H 1

#include "TB_ExceptionClass.h"

typedef struct ResDictVal {
	int max_avail_res;
	int avail_res;
	int need_res;
	int held_res;
} ResDictVal;

class ResDict_Exception : public TB_Exception {
	public:
		ResDict_Exception(const char* msg, const std::string cur_func, const std::string func_traceback) :
		TB_Exception(msg, cur_func, func_traceback) {}
		ResDict_Exception(const char* msg, const std::string cur_func) :
		TB_Exception(msg, cur_func) {}
};

#endif
