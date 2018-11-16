#pragma once
#include "date.h"
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <functional>

class Database {
public:
	void Add(const Date& new_date, const std::string& new_event = "");	
	void Print(std::ostream& os) const;
	std::string Last(Date date) const;
	
	int RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate);
	std::vector<std::string> FindIf(std::function<bool(const Date& date, const std::string& event)> predicate) const;

private:
	std::map < Date, std::set<std::string> > getEventByDate;
	std::map < Date, std::vector<std::string> > getVecEventsByDate;
};