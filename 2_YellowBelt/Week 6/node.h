#pragma once

#include "date.h"
#include <memory>
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

class Node {
public:
	virtual bool Evaluate(Date date, std::string sEvent) = 0;	
	bool compare(Date date) {}
};

class EmptyNode : public Node {
public:
	bool Evaluate(Date date, std::string sEvent) override { return true; }
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison cmp, Date date) : _cmp(cmp), _date(date) {}
	bool Evaluate(Date date, std::string sEvent) override { return true; }

private:
	Date _date;
	Comparison _cmp;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison cmp, std::string sValue) : _cmp(cmp), _sValue(sValue) {}
	bool Evaluate(Date date, std::string sEvent) override { return true; }

private:
	std::string _sValue;
	Comparison _cmp;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation logical_op, std::shared_ptr<Node> left, std::shared_ptr<Node> right) :
		_logical_op(logical_op), _left(left), _right(right) {}
	bool Evaluate(Date date, std::string sEvent) override { return true; }
private:
	LogicalOperation _logical_op;
	std::shared_ptr<Node> _left;
	std::shared_ptr<Node> _right;
};