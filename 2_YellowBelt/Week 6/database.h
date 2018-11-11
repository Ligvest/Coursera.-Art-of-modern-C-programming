#pragma once
#include "date.h"
#include <map>
#include <set>
#include <algorithm>
#include <vector>

class Database {
public:
	void Add(const Date& new_date, const std::string& new_event = "");
	bool DeleteEvent(const Date& date, const std::string& event);
	int  DeleteDate(const Date& date);	
	void Print(std::ostream& os) const;

	template <typename _Pred>
	int RemoveIf(_Pred predicate);

	template <typename _Pred>
	std::vector<std::string> FindIf(_Pred date) const;

private:
	std::map < Date, std::set<std::string> > getEventByDate;
};