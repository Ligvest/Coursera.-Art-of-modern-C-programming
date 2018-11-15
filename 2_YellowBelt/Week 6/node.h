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

bool compareDate(Comparison cmp, Date left, Date right);
bool compareEvent(Comparison cmp, std::string left, std::string right);


class Node {
public:
	virtual bool Evaluate(Date date, std::string sEvent) = 0;		
};

class EmptyNode : public Node {
public:
	bool Evaluate(Date date, std::string sEvent) override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison cmp, Date date);
	bool Evaluate(Date date, std::string sEvent) override;

private:
	Date _date;
	Comparison _cmp;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison cmp, std::string sEvent);
	bool Evaluate(Date date, std::string sEvent) override;

private:
	std::string _sEvent;
	Comparison _cmp;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation logical_op, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
	bool Evaluate(Date date, std::string sEvent) override;
private:
	LogicalOperation _logical_op;
	std::shared_ptr<Node> _left;
	std::shared_ptr<Node> _right;
};