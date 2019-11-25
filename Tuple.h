#ifndef TUPLE_H_
#define TUPLE_H_
#include <iostream>
#include <vector>
#include <string>
#include "Predicate.h"
using namespace std;

class Tuple : public vector<string> {
public:
	Tuple() {}
	Tuple(Predicate factPredicate) {
		for (size_t i = 0; i < factPredicate.getParameter().size(); i++) {
			this->push_back(factPredicate.getParameter().at(i));
		}
	}
	string toString();
	friend ostream& operator<<(ostream& os, Tuple myTuple);

private:


};

#endif



