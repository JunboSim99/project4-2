#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Parser.h"
#include "Scanner.h"
#include "Relation.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char * argv[]) {

	//#Union test cases1
	//Scheme scheme1;
	//scheme1.push_back("Cat");
	//scheme1.push_back("Dog");
	//scheme1.push_back("Fish");
	//Relation relation1("Alpha", scheme1);
	//Tuple tuple1;
	//tuple1.push_back("1");
	//tuple1.push_back("2");
	//tuple1.push_back("3");
	//Tuple tuple2;
	//tuple2.push_back("4");
	//tuple2.push_back("5");
	//tuple2.push_back("6");
	//relation1.addTuple(tuple1);
	//relation1.addTuple(tuple2);
	//Scheme scheme2;
	//scheme2.push_back("Lion");
	//scheme2.push_back("Tiger");
	//scheme2.push_back("Lizard");
	//Relation relation2("Beta", scheme2);
	//Tuple tuple3;
	//tuple3.push_back("7");
	//tuple3.push_back("8");
	//tuple3.push_back("9");
	//Tuple tuple4;
	//tuple4.push_back("10");
	//tuple4.push_back("11");
	//tuple4.push_back("12");
	//relation2.addTuple(tuple3);
	//relation2.addTuple(tuple4);
	//cout << relation1.toStirng();
	//cout << relation2.toStirng() << endl << endl;
	//cout << "Unioned Relation" << endl;
	//Relation relation3 = relation1.unionWith(relation2);
	//cout << relation3.toStirng();


	//#Union test cases2
	//Scheme scheme1;
	//scheme1.push_back("Cat");
	//scheme1.push_back("Dog");
	//scheme1.push_back("Fish");
	//Relation relation1("Alpha", scheme1);
	//Tuple tuple1;
	//tuple1.push_back("1");
	//tuple1.push_back("2");
	//tuple1.push_back("3");
	//Tuple tuple2;
	//tuple2.push_back("4");
	//tuple2.push_back("5");
	//tuple2.push_back("6");
	//relation1.addTuple(tuple1);
	//relation1.addTuple(tuple2);
	//Scheme scheme2;
	//scheme2.push_back("Lion");
	//scheme2.push_back("Tiger");
	//scheme2.push_back("Lizard");
	//Relation relation2("Beta", scheme2);
	//Tuple tuple3;
	//tuple3.push_back("1");
	//tuple3.push_back("2");
	//tuple3.push_back("3");
	//Tuple tuple4;
	//tuple4.push_back("4");
	//tuple4.push_back("5");
	//tuple4.push_back("6");
	//relation2.addTuple(tuple3);
	//relation2.addTuple(tuple4);
	//cout << relation1.toStirng();
	//cout << relation2.toStirng() << endl << endl;
	//cout << "Unioned Relation" << endl;
	//Relation relation3 = relation1.unionWith(relation2);
	//cout << relation3.toStirng();


	//#Join test cases1 
	/*Scheme scheme1;
	scheme1.push_back("Cat");
	scheme1.push_back("Dog");
	scheme1.push_back("Fish");
	Relation relation1("Alpha", scheme1);
	Tuple tuple1;
	tuple1.push_back("1");
	tuple1.push_back("2");
	tuple1.push_back("5");
	Tuple tuple2;
	tuple2.push_back("1");
	tuple2.push_back("4");
	tuple2.push_back("1");
	Tuple tuple3;
	tuple3.push_back("2");
	tuple3.push_back("3");
	tuple3.push_back("2");
	Tuple tuple4;
	tuple4.push_back("3");
	tuple4.push_back("3");
	tuple4.push_back("2");
	Tuple tuple5;
	tuple5.push_back("6");
	tuple5.push_back("7");
	tuple5.push_back("4");
	relation1.addTuple(tuple1);
	relation1.addTuple(tuple2);
	relation1.addTuple(tuple3);
	relation1.addTuple(tuple4);
	relation1.addTuple(tuple5);
	Scheme scheme2;
	scheme2.push_back("Cat");
	scheme2.push_back("Fish");
	scheme2.push_back("Bird");
	scheme2.push_back("Bunny");
	Relation relation2("Beta", scheme2);
	Tuple tuple6;
	tuple6.push_back("3");
	tuple6.push_back("4");
	tuple6.push_back("2");
	tuple6.push_back("4");
	Tuple tuple7;
	tuple7.push_back("6");
	tuple7.push_back("4");
	tuple7.push_back("9");
	tuple7.push_back("2");
	Tuple tuple8;
	tuple8.push_back("4");
	tuple8.push_back("3");
	tuple8.push_back("2");
	tuple8.push_back("7");
	Tuple tuple9;
	tuple9.push_back("1");
	tuple9.push_back("5");
	tuple9.push_back("2");
	tuple9.push_back("4");
	Tuple tuple10;
	tuple10.push_back("1");
	tuple10.push_back("5");
	tuple10.push_back("8");
	tuple10.push_back("3");
	relation2.addTuple(tuple6);
	relation2.addTuple(tuple7);
	relation2.addTuple(tuple8);
	relation2.addTuple(tuple9);
	relation2.addTuple(tuple10);
	cout << relation1.toStirng();
	cout << relation2.toStirng() << endl << endl;
	cout << "Joined Relation" << endl;
	Relation relation3 = relation1.join(relation2);
	cout << relation3.toStirng();*/

	//#Join test cases2 
	/*Scheme scheme1;
	scheme1.push_back("Cat");
	scheme1.push_back("Dog");
	scheme1.push_back("Fish");
	Relation relation1("Alpha", scheme1);
	Tuple tuple1;
	tuple1.push_back("1");
	tuple1.push_back("2");
	tuple1.push_back("5");
	Tuple tuple2;
	tuple2.push_back("1");
	tuple2.push_back("4");
	tuple2.push_back("1");
	Tuple tuple3;
	tuple3.push_back("2");
	tuple3.push_back("3");
	tuple3.push_back("2");
	Tuple tuple4;
	tuple4.push_back("3");
	tuple4.push_back("3");
	tuple4.push_back("2");
	Tuple tuple5;
	tuple5.push_back("6");
	tuple5.push_back("7");
	tuple5.push_back("4");
	relation1.addTuple(tuple1);
	relation1.addTuple(tuple2);
	relation1.addTuple(tuple3);
	relation1.addTuple(tuple4);
	relation1.addTuple(tuple5);
	Scheme scheme2;
	scheme2.push_back("Cat");
	scheme2.push_back("Fish");
	scheme2.push_back("Bird");
	scheme2.push_back("Bunny");
	Relation relation2("Beta", scheme2);
	Tuple tuple6;
	tuple6.push_back("3");
	tuple6.push_back("4");
	tuple6.push_back("2");
	tuple6.push_back("4");
	Tuple tuple7;
	tuple7.push_back("6");
	tuple7.push_back("4");
	tuple7.push_back("9");
	tuple7.push_back("2");
	Tuple tuple8;
	tuple8.push_back("4");
	tuple8.push_back("3");
	tuple8.push_back("2");
	tuple8.push_back("7");
	Tuple tuple9;
	tuple9.push_back("1");
	tuple9.push_back("5");
	tuple9.push_back("2");
	tuple9.push_back("4");
	Tuple tuple10;
	tuple10.push_back("1");
	tuple10.push_back("5");
	tuple10.push_back("8");
	tuple10.push_back("3");
	relation2.addTuple(tuple6);
	relation2.addTuple(tuple7);
	relation2.addTuple(tuple8);
	relation2.addTuple(tuple9);
	relation2.addTuple(tuple10);
	cout << relation1.toStirng();
	cout << relation2.toStirng() << endl << endl;
	cout << "Joined Relation" << endl;
	Relation relation3 = relation1.join(relation2);
	cout << relation3.toStirng();*/

	//**Actual Main
	ifstream input;
	input.open(argv[1]); //change to argv[1]
	Scanner myScanner(argv[1]); //change it to argv[1]
	myScanner.tokenize();
	Parser myParser(myScanner.getTokens());
	myParser.parse();
	Interpreter myInt(myParser.getDatalog());
	cout << myInt.toString();

	return 0;
}