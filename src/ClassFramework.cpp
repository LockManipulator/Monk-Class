#include "ClassFramework.h"

//uint8_t ClassFramework::addClassType(int id, string name) {
//	this->classTypeMap.insert(make_pair(id, string));
//	return this->classTypeMap.size();
//}

void ClassFramework::initialise() {
	this->classTypes = new char[sizeof(map<int, string>)];
}
 