#include "database.h"

void Database::Add(const Date& new_date, const std::string& new_event = "") {
	if (getEventByDate.count(new_date) > 0) {
		for (auto ev : getEventByDate[new_date]) {
			if (ev == new_event) {
				return;
			}
		}
	}
	getEventByDate[new_date].insert(new_event);
}

bool Database::DeleteEvent(const Date& date, const std::string& event) {
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


int  Database::DeleteDate(const Date& date) {
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

void Database::Print(std::ostream& os) const {
	for (auto el : getEventByDate) {
		for (auto sEvent : el.second) {
			os << el.first << " " << sEvent << std::endl;
		}
	}
}

template <typename _Pred>
int Database::RemoveIf(_Pred predicate) {
	auto itToRem = std::remove_if(getEventByDate.begin(), getEventByDate.end(), predicate);
	int iCount = std::distance(itToRem, getEventByDate.end());
	getEventByDate.erase(itToRem, getEventByDate.end());
}

template <typename _Pred>
std::vector<std::string> Database::FindIf(_Pred predicate) const {
	std::vector<std::string> vecEvents;
	
	//All sets in getEventByDate
	for (auto it = getEventByDate.begin(); it != getEventByDate.end(); ++it) {
		//Find events in each set
		auto itFound = (*it).second.begin();
		while (true) {
			itFound = std::find_if(itFound, (*it).second.end(), predicate);
			if (itFound == (*it).second.end()) {
				break;
			}
			else {
				vecEvents.push_back(*itFound);
			}
		}
	}
}