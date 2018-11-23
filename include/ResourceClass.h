#if !defined(RESOURCE_CLASS_H)
#define RESOURCE_CLASS_H 1

#include <string>

class Resource {
	public:
		std::string name;
		int value;

		Resource(std::string& name, int value);
		Resource(std::string& ser_res);

		void deserialize(std::string& ser_res);
}

#endif
