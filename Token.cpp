#include "Token.h"
#include <iostream>
#include<string>
#include<sstream>
using namespace std;


string Token::typetoString(TokenType type) {

	switch (type) {

	case COMMA:
		return "COMMA";
		break;

	case PERIOD:
		return "PERIOD";
		break;

	case Q_MARK:
		return "Q_MARK";
		break;

	case LEFT_PAREN:
		return "LEFT_PAREN";
		break;

	case RIGHT_PAREN:
		return "RIGHT_PAREN";
		break;

	case COLON:
		return "COLON";
		break;

	case COLON_DASH:
		return "COLON_DASH";
		break;

	case MULTIPLY:
		return "MULTIPLY";
		break;

	case ADD:
		return "ADD";
		break;

	case SCHEMES:
		return "SCHEMES";
		break;

	case FACTS:
		return "FACTS";
		break;

	case RULES:
		return "RULES";
		break;

	case QUERIES:
		return "QUERIES";
		break;

	case ID:
		return "ID";
		break;

	case STRING:
		return "STRING";
		break;

	case COMMENT:
		return "COMMENT";
		break;

	case UNDEFINED:
		return "UNDEFINED";
		break;

	case EOF_:
		return "EOF";
		break;

	}

	return "ERORR";
}


TokenType Token::getType() {
	return type;
}

string Token::toString() {
	ostringstream oss;
	oss << "(" << typetoString(type) << ",\"" << value << "\"," << line << ")";
	return oss.str();
}

ostream &operator<<(ostream& os, Token t) {
	os << t.toString();
	return os;
}

string Token::getValue() {
	return value;
}