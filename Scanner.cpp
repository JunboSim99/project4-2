#include "Scanner.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

void Scanner::tokenize() {

	while (currentChar != EOF)
	{
		currentChar = input.get();

		switch (currentChar) {

		case ',':
			tokens.push_back(Token(COMMA, ",", line));
			//currentChar = ifs.get();
			break;

		case '.':
			tokens.push_back(Token(PERIOD, ".", line));
			//currentChar = ifs.get();
			break;

		case '?':
			tokens.push_back(Token(Q_MARK, "?", line));
			//currentChar = ifs.get();
			break;

		case '(':
			tokens.push_back(Token(LEFT_PAREN, "(", line));
			//currentChar = ifs.get();
			break;

		case ')':
			tokens.push_back(Token(RIGHT_PAREN, ")", line));
			//currentChar = ifs.get();
			break;

		case '*':
			tokens.push_back(Token(MULTIPLY, "*", line));
			//currentChar = ifs.get();
			break;

		case '+':
			tokens.push_back(Token(ADD, "+", line));
			//currentChar = ifs.get();
			break;

		case '\'':
			findString();
			break;

		case '#':
			findComment();
			break;

		case ':':
			nextChar = input.peek();
			if (nextChar == '-') {
				tokens.push_back(Token(COLON_DASH, ":-", line));
				currentChar = input.get();
				//currentChar = ifs.get();
				break;
			}
			else {
				tokens.push_back(Token(COLON, ":", line));
				//currentChar = ifs.get();
				break;
			}

		case '\n':
			line++;


			break;

		default:

			if (isalpha(currentChar)) {
				findID();
			}

			else if (isspace(currentChar)) {
				continue;
			}

			else if (currentChar != EOF) {
				string udValue;
				udValue += currentChar;
				tokens.push_back(Token(UNDEFINED, udValue, line));
				//currentChar = ifs.get();
			}
			//break;
		}
	}
	tokens.push_back(Token(EOF_, "", line));
}

void Scanner::findID() {
	string idValue;
	idValue += currentChar;
	//currentChar = ifs.get();

	while (isalnum(input.peek())) {
		currentChar = input.get();
		idValue += currentChar;

	}

	if (idValue == "Schemes") {
		tokens.push_back(Token(SCHEMES, "Schemes", line));
	}
	else if (idValue == "Facts") {
		tokens.push_back(Token(FACTS, "Facts", line));

	}
	else if (idValue == "Rules") {
		tokens.push_back(Token(RULES, "Rules", line));
	}
	else if (idValue == "Queries") {
		tokens.push_back(Token(QUERIES, "Queries", line));
	}
	else {
		tokens.push_back(Token(ID, idValue, line));
	}

	if (currentChar == '\n') {
		++line;
		return;
	}

}

void Scanner::findString() {

	string stringValue;
	int currentLine = line;
	bool eos = false;
	stringValue += currentChar;
	nextChar = input.peek();

	while (eos == false)
	{
		if (input.peek() == EOF)
		{
			tokens.push_back(Token(UNDEFINED, stringValue, currentLine));
			eos = true;
		}
		else
		{
			currentChar = input.get();
			switch (currentChar)
			{
			case '\n':
				line++;
				stringValue += currentChar;
				break;
			case '\'':
				stringValue += currentChar;
				nextChar = input.peek();
				if (nextChar != '\'')
				{
					tokens.push_back(Token(STRING, stringValue, currentLine));
					eos = true;
				}
				else
				{
					currentChar = input.get();
					stringValue += currentChar;
				}
				break;
			default:
				stringValue += currentChar;
				//break;
			}
		}
	}
}

void Scanner::findComment() {

	string commentValue;
	int currentLine = line;
	commentValue += currentChar;
	nextChar = input.peek();

	if (nextChar != '|') {

		currentChar = input.get();

		while (currentChar != '\n') {
			commentValue += currentChar;
			currentChar = input.get();
		}
		if (currentChar == '\n') {
			tokens.push_back(Token(COMMENT, commentValue, currentLine));
			line++;
		}
		return;
	}

	else {
		currentChar = input.get();
		commentValue += currentChar;
		currentChar = input.get();
		nextChar = input.peek();

		while ((currentChar != '|' || nextChar != '#') && nextChar != -1) {

			if (currentChar == '\n') { line++; }

			commentValue += currentChar;
			currentChar = input.get();
			nextChar = input.peek();
		}

		if (currentChar == '|' && nextChar == '#') {
			commentValue += currentChar;
			currentChar = input.get();
			commentValue += currentChar;
			tokens.push_back(Token(COMMENT, commentValue, currentLine));
			return;

		}

		else {
			if (currentChar == '\n') {
				commentValue += currentChar;
				line++;
			}
			tokens.push_back(Token(UNDEFINED, commentValue, currentLine));
			//currentChar = ifs.get();
			//line++;
			return;
		}

	}
}

void Scanner::printTokens() {


	for (unsigned int i = 0; i < tokens.size(); i++) {
		cout << tokens.at(i) << endl;
	}
	cout << "Total Tokens = " << tokens.size();
}

vector<Token> Scanner::getTokens() {
	return tokens;
}