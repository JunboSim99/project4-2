#ifndef DATABASE_H_
#define DATABASE_H_
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "Relation.h"
using namespace std;

class Database : public map<string, Relation> {
public:
	Database() {}
private:
};

#endif