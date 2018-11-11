#include "date.h"


int Date::GetYear() const { return iYear; }
int Date::GetMonth() const { return iMonth; }
int Date::GetDay() const { return iDay; }

void Date::ReadFromStream(std::istream& stream) {
	int iY, iM, iD;
	std::string sDate;
	stream >> sDate;
	std::stringstream ss(sDate);


	ss >> iY;
	if (ss.peek() != '-') {
		throw std::invalid_argument("Wrong date format: " + sDate);
	}
	ss.ignore(1);
	ss >> iM;
	if (ss.peek() != '-') {
		throw std::invalid_argument("Wrong date format: " + sDate);
	}
	ss.ignore(1);
	ss >> iD;
	if (!ss.eof()) {
		throw std::invalid_argument("Wrong date format: " + sDate);
	}
	if (iM < 1 || iM > 12) {
		throw std::invalid_argument("Month value is invalid: " + std::to_string(iM));
	}
	else if (iD < 1 || iD > 31) {
		throw std::invalid_argument("Day value is invalid: " + std::to_string(iD));
	}


	iYear = iY;
	iMonth = iM;
	iDay = iD;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear()) {
		return true;
	}
	else if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() < rhs.GetMonth()) {
		return true;
	}
	else if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() < rhs.GetDay()) {
		return true;
	}
	else {
		return false;
	}
}

std::ostream& operator << (std::ostream& stream, const Date& date) {
	stream << std::setfill('0') << std::setw(4) << date.GetYear()
		<< '-'
		<< std::setfill('0') << std::setw(2) << date.GetMonth()
		<< '-'
		<< std::setfill('0') << std::setw(2) << date.GetDay();
	return stream;
}

Date ParseDate(std::istringstream& is) {
	Date date;
	date.ReadFromStream(is);
	return date;
}