#ifndef DATALOGPROGRAM_H_
#define DATALOGPROGRAM_H_
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"
using namespace std;

class datalogProgram {

public:
	string toString();
	string schemeString();
	string factString();
	string queriesString();
	string rulesString();
	string domainString();
	friend ostream& operator<<(ostream& os, datalogProgram d);
	void addSchemes(Predicate newScheme);
	void addFacts(Predicate newFact);
	void addQueries(Predicate newQuery);
	void addRules(Rule newRules);
	void addDomain(vector<string> factParameter);
	vector<Predicate> getScheme();
	vector<Predicate> getFact();
	vector <Predicate> getQuery();
	vector <Rule> getRule();
private:
	vector <Predicate> schemes;
	vector <Predicate> facts;
	vector <Predicate> queries;
	vector <Rule> rules;
	set <string> domain;

};

#endif


