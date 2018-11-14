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
	for (auto it = getEventByDate.begin(); it != getEventByDate.end(); ++it) {
		std::vector<std::string> setStr;
		return 0;
		auto itToRem = std::remove_if(setStr.begin(), setStr.end(), [](const std::string& sEvent)
		{
			return true;
		});
		
		
		//auto itToRem = std::remove_if(setStr.begin(), setStr.end(), [it, predicate](const std::string sEvent)
		//{
		//	return predicate(it->first, sEvent);
		//});



		/*auto itToRem = std::remove_if(it->second.begin(), it->second.end(), [it, predicate] (std::string sEvent)
		{
			return predicate(it->first, sEvent);
		});
		int iCount = std::distance(itToRem, it->second.end());
		if (itToRem != it->second.end()) {
			it->second.erase(itToRem);
		}	*/	
	}
}

std::vector<std::string> Database::FindIf(std::function<bool(const Date& date, const std::string& event)> predicate) const {
	std::vector<std::string> vecEvents;
	return vecEvents;
	////All sets in getEventByDate
	//for (auto it = getEventByDate.begin(); it != getEventByDate.end(); ++it) {
	//	//Find events in each set
	//	auto itFound = (*it).second.begin();
	//	while (true) {
	//		itFound = std::find_if(itFound, (*it).second.end(), predicate);
	//		if (itFound == (*it).second.end()) {
	//			break;
	//		}
	//		else {
	//			vecEvents.push_back(*itFound);
	//		}
	//	}
	//}
}


std::string Database::Last(Date date) const {
	bool isPrevWasLess = false;
	std::string sRes = "No entries";
	for (auto el : getEventByDate) {		
	}
	for (auto it = getVecEventsByDate.rbegin(); it != getVecEventsByDate.rend(); ++it) {
		if (it->first <= date) { 
			isPrevWasLess = true; 
			sRes = it->second.back();
		}
		else if (it->first > date && isPrevWasLess) {
			break;
		}
	}
	return sRes;
}