#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
	Date(int new_year = 0, int new_month = 0, int new_day = 0) {
		iYear = new_year;
		iMonth = new_month;
		iDay = new_day;
	}

	int GetYear() const { return iYear; }
	int GetMonth() const { return iMonth; }
	int GetDay() const { return iDay; }

	void ReadFromStream(std::istream& stream) {
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

private:
	int iYear;
	int iMonth;
	int iDay;
};

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

ostream& operator << (ostream& stream, const Date& date) {
	stream << std::setfill('0') << std::setw(4) << date.GetYear()
		<< '-'
		<< std::setfill('0') << std::setw(2) << date.GetMonth()
		<< '-'
		<< std::setfill('0') << std::setw(2) << date.GetDay();
	return stream;
}

class Database {
public:
	void AddEvent(const Date& new_date, const string& new_event = "") {
		if (getEventByDate.count(new_date) > 0) {
			for (auto ev : getEventByDate[new_date]) {
				if (ev == new_event) {
					return;
				}
			}
		}
		getEventByDate[new_date].insert(new_event);
	}

	bool DeleteEvent(const Date& date, const string& event) {
		if (getEventByDate.count(date) > 0) {
			auto it = std::begin(getEventByDate[date]);
			for (auto ev : getEventByDate[date]) {				
				if (ev == event) {
					getEventByDate[date].erase(it);
					std::cout << "Deleted successfully" << std::endl;
					return true;
				}
				++it;
			}
		}
		std::cout << "Event not found" << std::endl;
		return false; 
	}


	int  DeleteDate(const Date& date) { 
		int iSize = 0;
		if (getEventByDate.count(date) > 0) {
			int iSize = getEventByDate[date].size();
			getEventByDate.erase(date);
			std::cout << "Deleted " << iSize << " events" << std::endl; 
			return iSize;
		}
		std::cout << "Deleted " << iSize << " events" << std::endl;
		return iSize;
	}
	
	bool Find(const Date& date) const {
		if (getEventByDate.count(date) > 0 && getEventByDate.at(date).size() > 0) {
			for (auto ev : getEventByDate.at(date)) {
				std::cout << ev << std::endl;
			}
			return true;
		}

		return false;
	}

	void Print() const {
		for (auto el : getEventByDate) {
			for (auto sEvent : el.second) {
				std::cout << el.first << " " << sEvent << std::endl;
			}
		}
	}
private:
	std::map < Date, std::set<std::string> > getEventByDate;
};


int main() {
	Database db;

	string command;
	
	try {
		while (getline(cin, command)) {
			Date date;
			std::stringstream ss(command);
			std::string sCmd, sEvent;
			ss >> sCmd;
			if (sCmd == "Add") {
				try {
					date.ReadFromStream(ss);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					return 1;
				}

				ss >> sEvent;
				db.AddEvent(date, sEvent); //Processing Add Date Event			
			}
			else if (sCmd == "Del") {
				date.ReadFromStream(ss);
				if (!ss.eof()) {
					ss >> sEvent;
					db.DeleteEvent(date, sEvent); //Processing Del Date Event
					continue;
				}
				db.DeleteDate(date); //Processing Del Date
			}
			else if (sCmd == "Find") {
				date.ReadFromStream(ss);
				db.Find(date); //Processing Find Date
			}
			else if (sCmd == "Print") {
				db.Print(); //Processing Print
			}
			else if (sCmd == "") {
				continue;
			}
			else {
				std::cout << "Unknown command: " << sCmd << std::endl;
				return 1;
			}
		}
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}

	return 0;
}