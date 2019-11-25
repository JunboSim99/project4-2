#include <iostream>
#include <string>
#include <cctype>
#include <exception>
#include "Parser.h"
using namespace std;

void Parser::parse() {

	try {
		parseDatalog();
	}
	catch (Token error) {
		cout << "Failure!" << endl;
		cout << "  " << error << endl;
		return;
	}
	/*cout << "Success!" << endl;
	cout << dp;*/
}

void Parser::match(TokenType type) {
	if (tokens[index].getType() == type) {
		++index;
	}
	else if (tokens[index].getType() == COMMENT) {
		++index;
		match(type);
	}
	else {
		throw tokens[index];
	}
}
void Parser::parseDatalog() {
	match(SCHEMES);
	match(COLON);
	parseScheme();
	parseSchemeList();
	match(FACTS);
	match(COLON);
	parseFactList();
	dp.addDomain(domain);
	match(RULES);
	match(COLON);
	parseRuleList();
	match(QUERIES);
	match(COLON);
	parseQuery();
	parseQueryList();
}
void Parser::parseScheme() {

	if (tokens[index].getType() == COMMENT) {
		++index;
		parseScheme();
	}
	else {

		p = Predicate(tokens[index].getValue());
		match(ID);
		match(LEFT_PAREN);
		p.addParameter(tokens[index].getValue());
		match(ID);
		parseIDList();
		match(RIGHT_PAREN);
		dp.addSchemes(p);
	}
}
void Parser::parseSchemeList() {
	if (tokens[index].getType() == FACTS) {
		return;
	}
	else if (tokens[index].getType() == COMMENT) {
		++index;
		parseSchemeList();
	}
	else {
		parseScheme();
		parseSchemeList();
	}

}
void Parser::parseFact() {

	if (tokens[index].getType() == COMMENT) {
		++index;
		parseFact();
	}
	else {
		p = Predicate(tokens[index].getValue());
		match(ID);
		match(LEFT_PAREN);
		p.addParameter(tokens[index].getValue());
		domain.push_back(tokens[index].getValue());
		match(STRING);
		parseStringList();
		match(RIGHT_PAREN);
		match(PERIOD);
		dp.addFacts(p);
	}
}
void Parser::parseFactList() {
	if (tokens[index].getType() == RULES) {
		return;
	}
	else if (tokens[index].getType() == COMMENT) {
		++index;
		parseFactList();
	}

	else {
		parseFact();
		parseFactList();

	}

}
void Parser::parseRule() {

	if (tokens[index].getType() == COMMENT) {
		++index;
		parseRule();
	}

	else {
		parseHeadPredicate();
		r = Rule(p);
		match(COLON_DASH);

		p = Predicate(tokens[index].getValue());
		parsePredicate();

		parsePredicateList();
		match(PERIOD);
		dp.addRules(r);
	}
}
void Parser::parseRuleList() {
	if (tokens[index].getType() == QUERIES) {
		return;
	}

	else if (tokens[index].getType() == COMMENT) {
		++index;
		parseRuleList();
	}

	else {
		parseRule();
		parseRuleList();
	}
}
void Parser::parseQuery() {
	if (tokens[index].getType() == COMMENT) {
		++index;
		parseQuery();
	}
	else {
		p = Predicate(tokens[index].getValue());
		parsePredicate();
		match(Q_MARK);
		dp.addQueries(p);
	}
}
void Parser::parseQueryList() {
	if (tokens[index].getType() == EOF_) {
		return;
	}
	else if (tokens[index].getType() == COMMENT) {
		++index;
		parseQueryList();
	}
	else {
		parseQuery();
		parseQueryList();
	}
}
void Parser::parseIDList() {
	if (tokens[index].getType() == RIGHT_PAREN) {
		return;
	}

	else {
		match(COMMA);
		p.addParameter(tokens[index].getValue());
		match(ID);
		parseIDList();
	}
}
void Parser::parseStringList() {
	if (tokens[index].getType() == RIGHT_PAREN) {
		return;
	}

	else {
		match(COMMA);
		p.addParameter(tokens[index].getValue());
		domain.push_back(tokens[index].getValue());
		match(STRING);
		parseStringList();
	}

}
void Parser::parsePredicate() {

	match(ID);
	match(LEFT_PAREN);
	p.addParameter(parseParameter());
	parseParameterList();
	match(RIGHT_PAREN);
	r.addPredicate(p);
}
void Parser::parseHeadPredicate() {

	p = Predicate(tokens[index].getValue());
	match(ID);
	match(LEFT_PAREN);
	p.addParameter(tokens[index].getValue());
	match(ID);
	parseIDList();
	match(RIGHT_PAREN);
}
void Parser::parsePredicateList() {

	if (tokens[index].getType() == PERIOD) {
		return;
	}

	else {
		match(COMMA);
		p = Predicate(tokens[index].getValue());
		parsePredicate();
		parsePredicateList();
	}

}
string Parser::parseParameter() {
	string param;
	if (tokens[index].getType() == STRING)
	{
		//p.addParameter(tokens[index].getValue());
		param = tokens[index].getValue();
		match(STRING);
		return param;
	}
	else if (tokens[index].getType() == ID)
	{
		//p.addParameter(tokens[index].getValue());
		param = tokens[index].getValue();
		match(ID);
		return param;
	}

	else {
		return parseExpression();
	}
}
void Parser::parseParameterList() {
	if (tokens[index].getType() == RIGHT_PAREN) {
		return;
	}

	else {
		match(COMMA);
		p.addParameter(parseParameter());
		parseParameterList();
	}
}
string Parser::parseExpression() {
	string expression = "(";
	match(LEFT_PAREN);
	expression += parseParameter();
	expression += parseOperator();
	expression += parseParameter();
	expression += ")";
	match(RIGHT_PAREN);

	return expression;
}
string Parser::parseOperator() {

	if (tokens[index].getType() == ADD) {
		match(ADD);
		return "+";
	}
	else if (tokens[index].getType() == MULTIPLY) {
		match(MULTIPLY);
		return "*";
	}
	else {
		throw tokens[index];
	}
}

datalogProgram Parser::getDatalog() {
	return dp;
}