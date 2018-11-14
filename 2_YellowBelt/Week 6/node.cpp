#pragma once

#include "node.h"

bool compareDate(Comparison cmp, Date left, Date right) {
	if (cmp == Comparison::Less) { return left < right; }
	else if (cmp == Comparison::LessOrEqual) { return left <= right; }
	else if (cmp == Comparison::Greater) { return left > right; }
	else if (cmp == Comparison::GreaterOrEqual) { return left >= right; }
	else if (cmp == Comparison::Equal) { return left == right; }
	else if (cmp == Comparison::NotEqual) { return left != right; }
	else { throw std::invalid_argument("Unknown compare operation"); }
}

//EmptyNode
bool EmptyNode::Evaluate(Date date, std::string sEvent) { return true; }

//DateComparisonNode
DateComparisonNode::DateComparisonNode(Comparison cmp, Date date) : _cmp(cmp), _date(date) {}
bool DateComparisonNode::Evaluate(Date date, std::string sEvent) { return compareDate(_cmp, _date, date); }

//EventComparisonNode
EventComparisonNode::EventComparisonNode(Comparison cmp, std::string sValue) : _cmp(cmp), _sValue(sValue) {}
bool EventComparisonNode::Evaluate(Date date, std::string sEvent) { return true; }

//LogicalOperationNode
LogicalOperationNode::LogicalOperationNode(LogicalOperation logical_op, std::shared_ptr<Node> left, std::shared_ptr<Node> right) :
		_logical_op(logical_op), _left(left), _right(right) {}
bool LogicalOperationNode::Evaluate(Date date, std::string sEvent) { return true; }