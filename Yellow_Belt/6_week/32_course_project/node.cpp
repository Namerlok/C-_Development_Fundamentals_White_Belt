/*
 * node.cpp
 *
 *  Created on: 4 сент. 2020 г.
 *      Author: Zarka
 */

#include "node.h"

bool EmptyNode::Evaluate(const Date& date_, const string& event_) const {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp_, const Date& date_ ) :
	cmp(cmp_), date(date_) {};

bool DateComparisonNode::Evaluate(const Date& date_, const string& event_) const {

	switch (cmp) {
		case Comparison::Less:
			return date_ < date;
		case Comparison::LessOrEqual:
			return date_ <= date;
		case Comparison::Greater:
			return date_ > date;
		case Comparison::GreaterOrEqual:
			return date_ >= date;
		case Comparison::Equal:
			return date_ == date;
		case Comparison::NotEqual:
			return date_ != date;
		default:
			cerr << "Undefined logical operation: " + to_string(cmp);
			return false;
	}
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp_, const string& event_) :
	cmp(cmp_), event(event_) {};

bool EventComparisonNode::Evaluate(const Date& date_, const string& event_) const {

	switch (cmp) {
		case Comparison::Less:
			return event_ < event;
		case Comparison::LessOrEqual:
			return event_ <= event;
		case Comparison::Greater:
			return event_ > event;
		case Comparison::GreaterOrEqual:
			return event_ >= event;
		case Comparison::Equal:
			return event_ == event;
		case Comparison::NotEqual:
			return event_ != event;
		default:
			cerr << "Undefined logical operation: " + to_string(cmp);
			return false;
	}
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation_,
		const shared_ptr<Node>& left_node_, const shared_ptr<Node>& right_node_) :
			logical_operation(logical_operation_), left_node(left_node_), right_node(right_node_) {}

bool LogicalOperationNode::Evaluate(const Date& date_, const string& event_) const {

	switch (logical_operation) {
		case LogicalOperation::Or:
			return left_node->Evaluate(date_, event_) || right_node->Evaluate(date_, event_);
		case LogicalOperation::And:
			return left_node->Evaluate(date_, event_) && right_node->Evaluate(date_, event_);
		default:
			cerr << "Undefined logical operation: " + to_string(logical_operation);
			return false;
	}
}

/* авторское решение
#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
  return true;
}

template <typename T>
bool CompareTo(const T& lhs, const T& rhs, Comparison cmp) {
  switch (cmp) {
  case Comparison::Less:
    return lhs < rhs;
  case Comparison::LessOrEqual:
    return lhs <= rhs;
  case Comparison::Equal:
    return lhs == rhs;
  case Comparison::NotEqual:
    return lhs != rhs;
  case Comparison::Greater:
    return lhs > rhs;
  case Comparison::GreaterOrEqual:
    return lhs >= rhs;
  }
  return false; // make compiler happy
}

DateComparisonNode::DateComparisonNode(Comparison comparison, const Date& value)
  : comparison_(comparison)
  , value_(value)
{
}

bool DateComparisonNode::Evaluate(const Date& date, const string&) const {
  return CompareTo(date, value_, comparison_);
}

EventComparisonNode::EventComparisonNode(Comparison comparison, const string& value)
  : comparison_(comparison)
  , value_(value)
{
}

bool EventComparisonNode::Evaluate(const Date&, const string& event) const {
  return CompareTo(event, value_, comparison_);
}

LogicalOperationNode::LogicalOperationNode(
    LogicalOperation operation, shared_ptr<Node> left, shared_ptr<Node> right
)
  : operation_(operation)
  , left_(left)
  , right_(right)
{
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
  switch (operation_) {
  case LogicalOperation::And:
    return left_->Evaluate(date, event) && right_->Evaluate(date, event);
  case LogicalOperation::Or:
    return left_->Evaluate(date, event) || right_->Evaluate(date, event);
  }
  return false; // make compiler happy
}
 */

