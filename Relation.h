#ifndef RELATION_H_
#define RELATION_H_
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include "Tuple.h"
#include "Scheme.h"
using namespace std;

class Relation {
public:
	Relation() {}
	Relation(string newName, Scheme newScheme) : relationName(newName), attributeList(newScheme) {}
	void addTuple(Tuple newTuple);
	string toStirng();
	Relation select(size_t column, string val);
	Relation select(size_t column1, size_t column2);
	Relation project(Scheme columns);
	Relation rename(string oldName, string newName);
	Relation rename(string oldName, string newName, size_t excludeColumn);
	bool isJoinable(Relation secondRelation, Tuple firstTuple, Tuple secondTuple);
	Scheme combineSchemes(Scheme secondScheme);
	Tuple combineTuples(Relation secondRelation, Tuple firstTuple, Tuple secondTuple);
	Relation join(const Relation secondRelation);
	Relation unionWith(const Relation secondRelation);
	set <Tuple> getData();
	Scheme getAttribute();
	string getrelationName();
private:
	string relationName;
	Scheme attributeList;
	set <Tuple> data;

};

#endif

