#include "SessionClass.h"


Session::Session(int argc, char *argv[]) {
	std::string arg_str("");
	try {
		arg_str = argv[1];
		this->parse_input_file(arg_str);
		arg_str = argv[2];
		this-mon_time = str_to_int(arg_str);
		arg_str = argv[3];
		this->n_iter = str_to_int(arg_str);

	} catch (Parse_Exception& e) { throw Sess_Exception(e.what, ERR_SESS_CONSTR_FUNC, e.get_traceback()); }

}

void Session::parse_input_file(const std::string& file_name) {
	std::ifstream input_file;
	std::string line("");

	input_file.open(file_name.c_str());

	while (input_file.getline(line)) {
		std::
	}

	input_file.close();
}

void Session::set_resource(const std::string& name, int value) {

}

void Session::set_task(const std::string& name, int busy_time, int idle_time, ResourceDict* res_dict) {

}
