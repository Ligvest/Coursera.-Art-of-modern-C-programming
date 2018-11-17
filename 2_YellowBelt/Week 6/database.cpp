#include "database.h"

using namespace std;

void Database::Add(const Date& new_date, const std::string& new_event) {
	if (getSetEventsByDate[new_date].count(new_event) > 0) {
		return;
	}
	else {
		getSetEventsByDate[new_date].insert(new_event);
		getVecEventsByDate[new_date].push_back(new_event);
	}
}

void Database::Print(std::ostream& os) const {	
	for (auto el : getVecEventsByDate) {
		for (auto sEvent : el.second) {
			os << el.first << " " << sEvent << std::endl;
		}
	}
}



int Database::RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate) {
	int iCount = 0;
	auto it = getVecEventsByDate.begin(); 
	while(it != getVecEventsByDate.end()) {
		auto itToRem = std::stable_partition(it->second.begin(), it->second.end(), [&iCount, &it, &predicate](std::string sEvent)
		{
			if (predicate(it->first, sEvent)) {
				++iCount; 
				return false; 
			}
			else {
				return true;
			}
		});

		if (itToRem != it->second.end()) {
			for (auto iter = itToRem; iter != it->second.end(); ++iter) {
				getSetEventsByDate[it->first].erase(*iter);
			}
			it->second.erase(itToRem, it->second.end());
		}

		//If date is empty then delete this date from map
		if (getSetEventsByDate[it->first].size() == 0) {
			++it;
			getSetEventsByDate.erase(std::prev(it)->first);
			getVecEventsByDate.erase(std::prev(it)->first);			
		}
		else {
			++it; 
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
	auto it = getVecEventsByDate.upper_bound(date);	
	//auto iDist = std::distance(it, getVecEventsByDate.end());

	std::ostringstream oss;	
	
	if ((getVecEventsByDate.size() > 0 && it != getVecEventsByDate.begin())) {// || (iDist == 0 && getVecEventsByDate.size() > 0)) {
		oss << std::prev(it)->first << " " << std::prev(it)->second.back();
		return oss.str();		
	}
	else {
		return "No entries";
	}		
}
