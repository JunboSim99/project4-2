#include <iostream>
#include <string>
#include <sstream>
#include "Interpreter.h"
#include "Relation.h"
#include "Predicate.h"
#include "Rule.h"
#include <map>
using namespace std;

string Interpreter::evaluateRules(vector<Rule> rules) {

	ostringstream oss;

	if (rules.empty()) {
		return oss.str();
	}

	bool sameSize = false;
	while (!sameSize) {

		size_t preTupleNum = 0;
		size_t postTupleNum = 0;

		map<string, Relation>::iterator iter;
		for (iter = database.begin(); iter != database.end(); iter++) {
			preTupleNum = preTupleNum + iter->second.getData().size();
		}

		for (size_t i = 0; i < rules.size(); ++i) {
			oss << rules.at(i) << "." << endl;
			oss << evaluateRule(rules.at(i)).toStirng();
		}
		++numPass;

		for (iter = database.begin(); iter != database.end(); iter++) {
			postTupleNum = postTupleNum + iter->second.getData().size();
		}

		if (preTupleNum == postTupleNum) {
			sameSize = true;
		}
	}
	
	return oss.str();
}

Relation Interpreter::evaluateRule(Rule newRule) {

	vector<Relation> ruleRelations;
	Relation myRelation;

	//1.evaluate predicate
	for (size_t i = 0; i < newRule.getPredicateList().size(); ++i) {
		ruleRelations.push_back(evaluateQuery(newRule.getPredicateList().at(i)));
	}

	myRelation = ruleRelations.at(0);


	//2.join
	for (size_t i = 0; i < ruleRelations.size(); ++i) {
		myRelation = myRelation.join(ruleRelations.at(i));
	}

	//3.project
	Scheme projectScheme;
	for(size_t i = 0; i < newRule.getHeadPredicate().getParameter().size(); ++i){
		projectScheme.push_back(newRule.getHeadPredicate().getParameter().at(i));
	}
	myRelation = myRelation.project(projectScheme);

	//4.rename
	for (map<string, Relation>::iterator iter = database.begin(); iter != database.end(); ++iter) {
		if (iter->first == newRule.getHeadPredicate().getID()) {
			for (size_t i = 0; i < newRule.getHeadPredicate().getParameter().size(); ++i) {
				myRelation = myRelation.rename(newRule.getHeadPredicate().getParameter().at(i), iter->second.getAttribute().at(i));
			}
			break;
		}
	}

	Relation printRelation(myRelation.getrelationName(), myRelation.getAttribute());

	//union
	for (map<string, Relation>::iterator iter = database.begin(); iter != database.end(); ++iter) {
		if (iter->first == newRule.getHeadPredicate().getID()) {
			
			set <Tuple> tuple1 = myRelation.getData();
			for (set <Tuple>::iterator i = tuple1.begin(); i != tuple1.end(); ++i) {
				bool ifSeen = false;
				set <Tuple> tuple2 = iter->second.getData();
				if (!tuple2.empty()) {
					for (set <Tuple>::iterator j = tuple2.begin(); j != tuple2.end(); ++j) {
						if (*i == *j) {
							ifSeen = true; 
							break;
						}
					}
					if (!ifSeen) {
						printRelation.addTuple(*i);
					}
				}

				else {
					printRelation.addTuple(*i);
				}
			}


			database[iter->first] = iter->second.unionWith(myRelation);
			break;
		}
	}
	return printRelation;
}

Relation Interpreter::evaluateQuery(Predicate queryPredicate) {
	Relation currentRelation = database[queryPredicate.getID()];
	Scheme projectColumns;
	vector<string> columnNames;
	for (size_t i = 0; i < queryPredicate.getParameter().size(); ++i) {
		string currentParameter = queryPredicate.getParameter().at(i);
		if (isConstant(currentParameter)) {
			currentRelation = currentRelation.select(i, currentParameter);
		}
		else {
			projectColumns.push_back(currentRelation.getAttribute().at(i));
			columnNames.push_back(currentParameter);

			if (i > 0) {
				for (size_t j = i - 1; j >= 0; --j) {
					if (queryPredicate.getParameter().at(i) == queryPredicate.getParameter().at(j)) {
						projectColumns.pop_back();
						columnNames.pop_back();
						currentRelation = currentRelation.select(j, i);
						break;
					}
					if (j == 0) { break; }
				}
			}
		}
	}

	if (projectColumns.size() > 0) {
		currentRelation = currentRelation.project(projectColumns);
	}

	if (columnNames.size() > 0) {
		
		for (size_t i = 0; i < currentRelation.getAttribute().size(); ++i) {
			if ((i > 0) && columnNames.at(i - 1) == currentRelation.getAttribute().at(i)) {
				currentRelation = currentRelation.rename(currentRelation.getAttribute().at(i), columnNames.at(i), i-1);
			}
			else {
				currentRelation = currentRelation.rename(currentRelation.getAttribute().at(i), columnNames.at(i));
			}
		}
	}
	return currentRelation;
}

bool Interpreter::isConstant(string param) {
	if (param.at(0) == '\'') {
		return true;
	}
	else {
		return false;
	}
}

string Interpreter::toString() {
	ostringstream oss;
	Predicate currentQuery;
	Relation currentRelation;

	//do evaluaterules here
	oss << "Rule Evaluation" << endl;

	oss << evaluateRules(datalog.getRule()) << endl;

	oss << "Schemes populated after " << numPass <<" passes through the Rules." << endl << endl;

	oss << "Query Evaluation" << endl;
	for (size_t i = 0; i < datalog.getQuery().size(); ++i) {
		currentQuery = datalog.getQuery().at(i);
		oss << datalog.getQuery().at(i) << "? ";
		map<string, Relation>::iterator iter;
		for (iter = database.begin(); iter != database.end(); ++iter) {
			if (iter->first == currentQuery.getID()) {
				currentRelation = iter->second;
			}
		}
		if (evaluateQuery(currentQuery).getData().empty()) {
			oss << "No" << endl;
		}
		else if (currentQuery.getParameter() == currentRelation.getAttribute()) {
			oss << "Yes(" << evaluateQuery(currentQuery).getData().size() << ")" << endl;
			oss << evaluateQuery(currentQuery).toStirng();
		}
		else {
			bool allConstant = true;
			for (size_t j = 0; j < currentQuery.getParameter().size(); ++j) {
				if (!isConstant(currentQuery.getParameter().at(j))) {
					allConstant = false;
				}
			}

			if (allConstant) {
				oss << "Yes(" << evaluateQuery(currentQuery).getData().size() << ")" << endl;
			}
			else {
				oss << "Yes(" << evaluateQuery(currentQuery).getData().size() << ")" << endl;
				oss << evaluateQuery(currentQuery).toStirng();
			}
		}
	}
	return oss.str();
}