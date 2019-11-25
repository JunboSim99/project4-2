#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <map>
#include "Relation.h"
using namespace std;

void Relation::addTuple(Tuple newTuple) {
	data.insert(newTuple);
}

string Relation::toStirng() {
	ostringstream oss;
	set<Tuple>::iterator itr;
	Tuple currentTuple;
	for (itr = data.begin(); itr != data.end(); ++itr) {
		currentTuple = *itr;
		oss << "  ";
		for (size_t i = 0; i < currentTuple.size(); i++) {
			/*for (size_t j = i + 1; j < currentTuple.size(); j++) {
				if (attributeList.at(i) == attributeList.at(j)) {
					this->project(attributeList);
				}
			}*/
			if (i == currentTuple.size() - 1) {
				oss << attributeList.at(i) << "=" << currentTuple.at(i);
			}
			else {
				oss << attributeList.at(i) << "=" << currentTuple.at(i) << ", ";
			}
		}
		oss << endl;
	}
	return oss.str();
}

Relation Relation::select(size_t column, string val) {

	Relation newRelation(this->relationName, this->attributeList);
	set<Tuple>::iterator iter;
	for (iter = data.begin(); iter != data.end(); ++iter) {
		if (iter->at(column) == val) {
			newRelation.addTuple(*iter);
		}
	}

	return newRelation;
}

Relation Relation::select(size_t column1, size_t column2) {

	Relation newRelation(this->relationName, this->attributeList);
	for (size_t i = 0; i < newRelation.attributeList.size(); ++i) {
		for (size_t j = i + 1; j < newRelation.attributeList.size(); ++j) {
			if (newRelation.attributeList.at(i) == newRelation.attributeList.at(j)) {
				newRelation.attributeList.erase(attributeList.begin() + j);
			}
		}
	}

	set<Tuple>::iterator iter;
	for (iter = data.begin(); iter != data.end(); ++iter) {
		if (iter->at(column1) == iter->at(column2)) {
			newRelation.addTuple(*iter);
		}
	}
	return newRelation;
}

Relation Relation::project(Scheme columns) {
	Relation newRelation(this->relationName, columns);
	set<Tuple>::iterator iter;
	for (iter = data.begin(); iter != data.end(); ++iter) {
		Tuple newTuple;
		for (size_t i = 0; i < columns.size(); ++i) {
			for (size_t j = 0; j < this->attributeList.size(); ++j) {
				if (columns.at(i) == this->attributeList.at(j)) {
					newTuple.push_back(iter->at(j));
				}
			}
		}
		newRelation.addTuple(newTuple);
	}
	return newRelation;
}

Relation Relation::rename(string oldName, string newName) {
	Relation newRelation(this->relationName, this->attributeList);
	set<Tuple>::iterator iter;
	for (iter = data.begin(); iter != data.end(); ++iter) {
		newRelation.addTuple(*iter);
	}
	for (size_t i = 0; i < attributeList.size(); ++i) {
		if (newRelation.attributeList.at(i) == oldName) {
			newRelation.attributeList.at(i) = newName;
			break;
		}
	}
	return newRelation;
}

Relation Relation::rename(string oldName, string newName, size_t excludeColumn) {
	Relation newRelation(this->relationName, this->attributeList);
	set<Tuple>::iterator iter;
	for (iter = data.begin(); iter != data.end(); ++iter) {
		newRelation.addTuple(*iter);
	}
	for (size_t i = 0; i < attributeList.size(); ++i) {
		if (i == excludeColumn) {
			continue;
		}
		else if (newRelation.attributeList.at(i) == oldName) {
			newRelation.attributeList.at(i) = newName;
			break;
		}
	}
	return newRelation;
}

Scheme Relation::combineSchemes(Scheme secondScheme){
	Scheme combinedScheme;
	for (size_t i = 0; i < attributeList.size(); ++i) {
		combinedScheme.push_back(attributeList.at(i));
	}
	for (size_t i = 0; i < secondScheme.size(); ++i) {
		bool isMatch = false;
		for (size_t j = 0; j < attributeList.size(); ++j) {
			if (secondScheme.at(i) == attributeList.at(j)) {
				isMatch = true;
				break;
			}
		}
		if (!isMatch) {
			combinedScheme.push_back(secondScheme.at(i));
		}
	}
	return combinedScheme;
}

bool Relation::isJoinable(Relation secondRelation, Tuple firstTuple, Tuple secondTuple) {
	
	map<size_t, size_t> matchingColumnNums;

	for (size_t i = 0; i < attributeList.size(); ++i) {
		for (size_t j = 0; j < secondRelation.attributeList.size(); ++j) {

			if (attributeList.at(i) == secondRelation.attributeList.at(j)) {
				matchingColumnNums.insert(pair<size_t, size_t>(i, j));
			}
		}
	}

	for (map <size_t, size_t>::iterator iter = matchingColumnNums.begin(); iter != matchingColumnNums.end(); ++iter) {
		if (firstTuple.at(iter->first) != secondTuple.at(iter->second)) {
			return false;
		}
	}

	return true;

	/*Scheme projectScheme;
	for (size_t i = 0; i < attributeList.size(); ++i) {
		for (size_t j = 0; j < secondRelation.attributeList.size(); ++j) {
			if (attributeList.at(i) == secondRelation.attributeList.at(j)) {
				projectScheme.push_back(attributeList.at(i));
			}
		}
	}

	for (set<Tuple>::iterator i = this->project(projectScheme).data.begin(); i != this->project(projectScheme).data.end(); ++i) {

		for (set<Tuple>::iterator j = secondRelation.project(projectScheme).data.begin(); j != secondRelation.project(projectScheme).data.end(); ++j) {
			if (*i == *j) {
				return true;
			}
		}
	}*/
}

Tuple Relation::combineTuples(Relation secondRelation, Tuple firstTuple, Tuple secondTuple){
	Tuple combinedTuple;
	for (size_t i = 0; i < firstTuple.size(); ++i) {
		combinedTuple.push_back(firstTuple.at(i));
	}
	for (size_t i = 0; i < secondRelation.attributeList.size(); ++i) {
		bool isMatch = false;
		for (size_t j = 0; j < attributeList.size(); ++j) {
			if (secondRelation.attributeList.at(i) == attributeList.at(j)) {
				isMatch = true;
				break;
			}
		}
		if (!isMatch) {
			combinedTuple.push_back(secondTuple.at(i));
		}
	}
	return combinedTuple;
}

Relation Relation::join(const Relation secondRelation) {
	Relation combinedRelation(relationName, this->combineSchemes(secondRelation.attributeList));

	for (set<Tuple>::iterator i = data.begin(); i != data.end(); ++i) {
		for (set<Tuple>::iterator j = secondRelation.data.begin(); j != secondRelation.data.end(); ++j) {

			if (isJoinable(secondRelation, *i, *j)) {
				combinedRelation.addTuple(this->combineTuples(secondRelation, *i, *j));
			}
		}
	}

	return combinedRelation;
}

Relation Relation::unionWith(const Relation secondRelation) {
	
	Relation unionedRelation(relationName, this->attributeList);

	for (set<Tuple>::iterator iter = data.begin(); iter != data.end(); ++iter) {
		unionedRelation.addTuple(*iter);
	}
	for (set <Tuple>::iterator iter = secondRelation.data.begin(); iter != secondRelation.data.end(); ++iter) {

		unionedRelation.addTuple(*iter);
		
	}

	return unionedRelation;
}

set<Tuple> Relation::getData() {
	return data;
}

Scheme Relation::getAttribute() {
	return attributeList;
}

string Relation::getrelationName() {
	return relationName;
}