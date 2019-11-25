#ifndef TOKEN_H_
#define TOKEN_H_
#include <iostream>
#include <string>
using namespace std;


enum TokenType {
	COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID,
	STRING, COMMENT, UNDEFINED, EOF_
};


class Token {
public:
	Token(TokenType newtype, string newvalue, int newline) : type(newtype), value(newvalue), line(newline) {}

	string typetoString(TokenType type);
	string toString();
	friend ostream& operator<<(ostream& os, Token t);

	TokenType getType();
	string getValue();

private:
	TokenType type;
	string value;
	int line;
};

#endif


