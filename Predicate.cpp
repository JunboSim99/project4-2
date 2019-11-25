#include "Predicate.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

string Predicate::toString() {
	ostringstream oss;
	oss << ID << "(";
	for (unsigned int i = 0; i < parameter.size(); ++i) {
		if (i == 0) {
			oss << parameter[i];
		}
		else {
			oss << "," << parameter[i];
		}
	}
	oss << ")";
	return oss.str();
}

ostream& operator<<(ostream& os, Predicate p) {
	os << p.toString();
	return os;
}

void Predicate::addParameter(string param) {
	parameter.push_back(param);
}

string Predicate::getID() {
	return ID;
}

vector <string> Predicate::getParameter() {
	return parameter;
}