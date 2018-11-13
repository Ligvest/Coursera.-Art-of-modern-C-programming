#pragma once

#include "date.h"
#include <string>

enum class LogicalOperation {
	Or,
	And
};

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

class Node {};
class EmptyNode {};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Date date, Comparison cmp) : _date(date), _cmp(cmp) {}
	
private:
	Date _date;
	Comparison _cmp;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison cmp, std::string sValue) : _cmp(cmp), _sValue(sValue) {}

private:
	std::string _sValue;
	Comparison _cmp;
};

class LogicalOperationNode {
public:
	LogicalOperationNode(LogicalOperation logical_op, std::shared_ptr<Node> left, std::shared_ptr<Node> right) :
		_logical_op(logical_op), _left(left), _right(right) {}

private:
	LogicalOperation _logical_op;
	std::shared_ptr<Node> _left;
	std::shared_ptr<Node> _right;
};