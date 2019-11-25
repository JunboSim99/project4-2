#include <iostream>
#include <string>
#include <set>
#include "Scheme.h"
#include <sstream>
using namespace std;

string Scheme::toString() {
	ostringstream oss;
	for (size_t i = 0; i < this->size(); i++) {
		oss << this->at(i);
	}
	return oss.str();
}