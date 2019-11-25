#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "datalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Predicate.h"
#include "Tuple.h"
#include "Rule.h"
using namespace std;

class Interpreter {
public:
	Interpreter(datalogProgram newDatalog) : datalog(newDatalog) {
		for (size_t i = 0; i < datalog.getScheme().size(); ++i) {
			Scheme newScheme(datalog.getScheme().at(i));
			string relationName = datalog.getScheme().at(i).getID();
			Relation newRelation(relationName, newScheme);
			database.insert(pair<string, Relation>(relationName, newRelation));
		}

		for (size_t i = 0; i < datalog.getFact().size(); ++i) {
			Tuple newTuple(datalog.getFact().at(i));
			string relationName = datalog.getFact().at(i).getID();
			map<string, Relation>::iterator iter;
			for (iter = database.begin(); iter != database.end(); ++iter) {
				if (iter->first == relationName) {
					iter->second.addTuple(newTuple);
				}
			}
		}
	}

	Relation evaluateQuery(Predicate queryPredicate);
	Relation evaluateRule(Rule newRule);
	string evaluateRules(vector<Rule> rules);
	bool isConstant(string param);
	string toString();
private:
	datalogProgram datalog;
	Database database;
	size_t numPass;
	//set <Tuple> addedTuples;
};

#endif

