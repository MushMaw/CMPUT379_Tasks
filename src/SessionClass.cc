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
		
		this->res_dict = new SessResDict();
		this->task_mngr = new TaskManager();

	} catch (Parse_Exception& e) { throw Sess_Exception(e.what, ERR_SESS_CONSTR_FUNC, e.get_traceback()); }

}

void Session::parse_input_file(const std::string& file_name) {
	std::ifstream input_file;
	std::string line("");
	std::deque<std::string> line_toks;
	int line_toks_count = 0;

	input_file.open(file_name.c_str());

	while (input_file.getline(line)) {
		if (line[0] != '\n' && line[0] != '#') {
			line_toks_count = tok_split(line, INPUT_FILE_DELIM_CHAR, line_toks);
			if (line_toks[0] == INPUT_FILE_TASK_START) {
				line_toks.pop_front();
				this->parse_resource_line(line_toks);
			} else if (line_toks[0] == INPUT_FILE_RESOURCE_START) {
				line_toks.pop_front();
				this->parse_task_line(line_toks);
			}
		}
	}

	input_file.close();
}

void Session::parse_resource_line(std::deque<std::string>& res_str_list) {
	int res_count;
	
	res_count = res_str_list.size();
	for (int i = 0; i < res_count; i++) {
		this->res_dict->deser_and_add(res_str_list[i]);
	}
}

void Session::parse_task_line(std::vector<std::string>& task_att_list) {
	
}
	