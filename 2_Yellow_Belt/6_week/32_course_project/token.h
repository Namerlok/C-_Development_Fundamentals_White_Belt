/*
 * token.h
 *
 *  Created on: 4 сент. 2020 г.
 *      Author: Zarka
 */
#pragma once

#ifndef TOKEN_H_
#define TOKEN_H_

#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

enum class TokenType {
	DATE,
	EVENT,
	COLUMN,
	LOGICAL_OP,
	COMPARE_OP,
	PAREN_LEFT,
	PAREN_RIGHT,
};

struct Token {
	const string value;
	const TokenType type;
};

vector<Token> Tokenize(istream& cl);

#endif /* TOKEN_H_ */


/* авторское решение
#pragma once

#include <sstream>
#include <vector>
using namespace std;

enum class TokenType {
  DATE,
  EVENT,
  COLUMN,
  LOGICAL_OP,
  COMPARE_OP,
  PAREN_LEFT,
  PAREN_RIGHT,
};

struct Token {
  const string value;
  const TokenType type;
};

vector<Token> Tokenize(istream& cl);
 */

