/*
 * condition_parser.h
 *
 *  Created on: 4 сент. 2020 г.
 *      Author: Zarka
 */
#pragma once

#ifndef CONDITION_PARSER_H_
#define CONDITION_PARSER_H_

#include "node.h"
#include "token.h"
#include "date.h"

#include <map>
#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

#endif /* CONDITION_PARSER_H_ */

/* Авторское решение
#pragma once

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();

 */

