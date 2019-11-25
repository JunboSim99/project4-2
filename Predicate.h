#ifndef PREDICATE_H_
#define PREDICATE_H_
#include <string>
#include <iostream>
#include <vector>

using namespace std;
class Predicate {

public:
	Predicate() {}
	Predicate(string myID) : ID(myID) {}
	Predicate(string myID, vector<string> myParameter) : ID(myID), parameter(myParameter) {}
	string getID();
	string toString();
	friend ostream& operator<<(ostream& os, Predicate p);
	void addParameter(string param);
	vector <string> getParameter();
private:
	string ID;
	vector<string> parameter;

};

#endif

