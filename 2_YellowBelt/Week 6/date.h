#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class Date {
public:
	Date(int new_year = 0, int new_month = 0, int new_day = 0) : iYear(new_year), iMonth(new_month), iDay(new_day) {}

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	void ReadFromStream(std::istream& stream);

private:
	int iYear;
	int iMonth;
	int iDay;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
std::ostream& operator << (std::ostream& stream, const Date& date);
Date ParseDate(std::istringstream& is);