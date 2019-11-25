#include "Rule.h" 
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

string Rule::toString() {
	ostringstream oss;
	oss << headPredicate << " :- ";
	for (unsigned int i = 0; i < predicateList.size(); ++i) {
		if (i == 0) {
			oss << predicateList[i];
		}
		else {
			oss << "," << predicateList[i];
		}
	}
	return oss.str();
}

ostream& operator<<(ostream& os, Rule r) {
	os << r.toString();
	return os;
}

void Rule::addPredicate(Predicate pred) {
	predicateList.push_back(pred);
}

vector <Predicate> Rule::getPredicateList() {
	return predicateList;
}

Predicate Rule::getHeadPredicate() {
	return headPredicate;
}