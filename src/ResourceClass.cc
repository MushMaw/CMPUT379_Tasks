#include "ResourceClass.h"


/**
 * Resource constructors
 */
Resource::Resource(std::string& name, int value) {
	this->name.assign(name);
	this->value = value;
}

Resource::Resource(std::string& ser_res) {
	// TODO: Use token parser from A3
	this->name.assign(ser_res); this->value = 0;
}
