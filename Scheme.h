#ifndef SCHEME_H_
#define SCHEME_H_
#include <vector>
#include <iostream>
#include <string>
#include "Predicate.h"
using namespace std;

class Scheme : public vector<string> {
public:
	Scheme() {}
	Scheme(Predicate schemePredicate) {
		for (size_t i = 0; i < schemePredicate.getParameter().size(); ++i) {
			this->push_back(schemePredicate.getParameter().at(i));
		}
	}
	~Scheme() {}
	string toString();
private:

};

#endif

