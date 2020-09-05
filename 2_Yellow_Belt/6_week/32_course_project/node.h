/*
 * node.h
 *
 *  Created on: 4 сент. 2020 г.
 *      Author: Zarka
 */
#pragma once

#ifndef NODE_H_
#define NODE_H_

#include "test_runner.h"
#include "date.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;

enum Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum LogicalOperation {
	Or,
	And
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;

protected:
	virtual ~Node() = default;
};

class EmptyNode : public Node {
public:
	//Node() {}
	bool Evaluate(const Date& date_, const string& event_) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp_, const Date& date_ );
	bool Evaluate(const Date& date_, const string& event_) const override;

private:
	const Comparison cmp;
	const Date date;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& cmp_, const string& event_);
	bool Evaluate(const Date& date_, const string& event_) const override;

private:
	const Comparison cmp;
	const string event;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation& logical_operation_,
			const shared_ptr<Node>& left_node_, const shared_ptr<Node>& right_node_);
	bool Evaluate(const Date& date_, const string& event_) const override;

private:
	const LogicalOperation logical_operation;
	const shared_ptr<Node> left_node;
	const shared_ptr<Node> right_node;
};

void TestNodeDateComparison();
void TestNodeEventComparison();
void TestNodeLogicalOperation();

#endif /* NODE_H_ */

/* авторское решение
#pragma once

#include "date.h"

#include <string>
#include <memory>
using namespace std;

struct Node {
  virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

struct EmptyNode : public Node {
  bool Evaluate(const Date& date, const string& event) const override;
};

enum class Comparison {
  Less,
  LessOrEqual,
  Equal,
  NotEqual,
  Greater,
  GreaterOrEqual,
};

class DateComparisonNode : public Node {
public:
  DateComparisonNode(Comparison comparison, const Date& value);
  bool Evaluate(const Date& date, const string& event) const override;

private:
  Comparison comparison_;
  Date value_;
};

class EventComparisonNode : public Node {
public:
  EventComparisonNode(Comparison comparison, const string& value);
  bool Evaluate(const Date& date, const string& event) const override;

private:
  Comparison comparison_;
  string value_;
};

enum class LogicalOperation {
  And,
  Or,
};

class LogicalOperationNode : public Node {
public:
  LogicalOperationNode(LogicalOperation operation, shared_ptr<Node> left, shared_ptr<Node> right);
  bool Evaluate(const Date& date, const string& event) const override;

private:
  LogicalOperation operation_;
  shared_ptr<Node> left_, right_;
};

void TestDateComparisonNode();
void TestEventComparisonNode();
void TestLogicalOperationNode();
 */

