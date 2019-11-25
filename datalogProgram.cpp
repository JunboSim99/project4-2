#include "datalogProgram.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

string datalogProgram::toString() {
	ostringstream oss;
	oss << schemeString();
	oss << factString();
	oss << rulesString();
	oss << queriesString();
	oss << domainString();
	return oss.str();
}

string datalogProgram::schemeString() {
	ostringstream oss;
	oss << "Schemes(" << schemes.size() << "):" << endl;
	for (unsigned int i = 0; i < schemes.size(); ++i) {
		oss << "  " << schemes[i] << endl;
	}
	return oss.str();
}
string datalogProgram::factString() {
	ostringstream oss;
	oss << "Facts(" << facts.size() << "):" << endl;
	for (unsigned int i = 0; i < facts.size(); ++i) {
		oss << "  " << facts[i] << "." << endl;
	}
	return oss.str();
}
string datalogProgram::queriesString() {
	ostringstream oss;
	oss << "Queries(" << queries.size() << "):" << endl;
	for (unsigned int i = 0; i < queries.size(); ++i) {
		oss << "  " << queries[i] << "?" << endl;
	}
	return oss.str();
}
string datalogProgram::rulesString() {
	ostringstream oss;
	oss << "Rules(" << rules.size() << "):" << endl;
	for (unsigned int i = 0; i < rules.size(); ++i) {
		oss << "  " << rules[i] << "." << endl;
	}
	return oss.str();
}
string datalogProgram::domainString() {
	ostringstream oss;
	oss << "Domain(" << domain.size() << "):" << endl;
	set<string>::iterator domainITR;
	for (domainITR = domain.begin(); domainITR != domain.end(); ++domainITR) {
		oss << "  " << *domainITR << endl;
	}
	return oss.str();
}

ostream& operator<<(ostream& os, datalogProgram d) {
	os << d.toString();
	return os;
}

void datalogProgram::addSchemes(Predicate newScheme) {
	schemes.push_back(newScheme);
}
void datalogProgram::addFacts(Predicate newFact) {
	facts.push_back(newFact);
}
void datalogProgram::addQueries(Predicate newQuery) {
	queries.push_back(newQuery);
}
void datalogProgram::addRules(Rule newRules) {
	rules.push_back(newRules);
}
void datalogProgram::addDomain(vector<string> factParameter) {
	for (unsigned int i = 0; i < factParameter.size(); ++i) {
		domain.insert(factParameter[i]);
	}
}

vector<Predicate> datalogProgram::getScheme() {
	return schemes;
}

vector<Predicate> datalogProgram::getFact() {
	return facts;
}

vector <Predicate> datalogProgram::getQuery() {
	return queries;
}

vector <Rule> datalogProgram::getRule() {
	return rules;
}