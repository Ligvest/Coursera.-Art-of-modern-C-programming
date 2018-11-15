#include "database.h"

void Database::Add(const Date& new_date, const std::string& new_event) {
	if (getEventByDate.count(new_date) > 0) {
		for (auto ev : getEventByDate[new_date]) {
			if (ev == new_event) {
				return;
			}
		}
	}
	getEventByDate[new_date].insert(new_event);
	getVecEventsByDate[new_date].push_back(new_event);
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

int Database::RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate) {
	int iCount = 0;
	for (auto it = getVecEventsByDate.begin(); it != getVecEventsByDate.end(); ++it) {
				
		auto itToRem = std::remove_if(it->second.begin(), it->second.end(), [&it, &predicate] (std::string sEvent)
		{
			return predicate(it->first, sEvent);
		});
		iCount += std::distance(itToRem, it->second.end());
		if (itToRem != it->second.end()) {
			for (auto iter = itToRem; iter != it->second.end(); ++iter) {
				getEventByDate[it->first].erase(*iter);
			}
			it->second.erase(itToRem, it->second.end());
		}
	}
	return iCount;
}

std::vector<std::string> Database::FindIf(std::function<bool(const Date& date, const std::string& event)> predicate) const {
	std::vector<std::string> vecEvents;	
	
	for (auto it = getVecEventsByDate.begin(); it != getVecEventsByDate.end(); ++it) {
		auto itToRem = it->second.begin();
		while (itToRem != it->second.end()) {
			itToRem = std::find_if(itToRem, it->second.end(), [&it, &predicate](std::string sEvent)
			{
				return predicate(it->first, sEvent);
			});

			if (itToRem != it->second.end()) {
				std::ostringstream oss;
				oss << it->first << " " << *itToRem;
				vecEvents.push_back(oss.str());
				++itToRem;
			}
		}		
	}

	return vecEvents;	
}


std::string Database::Last(Date date) const {		
	for (auto it = getVecEventsByDate.rbegin(); it != getVecEventsByDate.rend(); ++it) {
		if (it->first <= date) { 	
			std::ostringstream oss;
			oss << it->first << " " << it->second.back();			
			return oss.str();
		}		
	}
	return "No entries";
}