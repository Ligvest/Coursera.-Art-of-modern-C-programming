#include "database.h"

void Database::Add(const Date& new_date, const std::string& new_event) {
	if (getEventByDate.count(new_date) > 0) {
		if (getEventByDate[new_date].find(new_event) != getEventByDate[new_date].end()) { return; }
	} 
	else {
		getEventByDate[new_date].insert(new_event);
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

using namespace std;

int Database::RemoveIf(std::function<bool(const Date& date, const std::string& event)> predicate) {
	int N = 0;		
	map<Date, vector<string> > db_vec_copy(getVecEventsByDate);
	map<Date, set<string>> db_set_copy(getEventByDate);

	for (auto& item : db_vec_copy)
	{
		auto func = [&](string str) { if (predicate(item.first, str)) { ++N; }
		return predicate(item.first, str); };

		auto iter_rem = remove_if(begin(item.second), end(item.second), func);

		item.second.erase(iter_rem, end(item.second));
	}

	for (const auto& item : getEventByDate)
	{
		for (const auto& item2 : item.second)
		{
			if (predicate(item.first, item2))
				db_set_copy[item.first].erase(item2);
		}
	}

	// теперь надо удалить элементы с нулями
	for (auto it_map = db_vec_copy.begin(); it_map != db_vec_copy.end(); )
	{
		if (it_map->second.size() == 0)
		{
			it_map = db_vec_copy.erase(it_map);
		}
		else it_map++;
	}

	for (auto it_map_set = db_set_copy.begin(); it_map_set != db_set_copy.end(); )
	{
		if (it_map_set->second.size() == 0)
		{
			it_map_set = db_set_copy.erase(it_map_set);
		}
		else it_map_set++;
	}

	getVecEventsByDate = move(db_vec_copy);
	getEventByDate = move(db_set_copy);
	return N;

	//int iCount = 0;
	//std::vector<Date> vecDatesToRem;
	//for (auto it = getVecEventsByDate.begin(); it != getVecEventsByDate.end(); ++it) {

	//	auto itToRem = std::remove_if(it->second.begin(), it->second.end(), [&it, &predicate](std::string sEvent)
	//	{
	//		return predicate(it->first, sEvent);
	//	});
	//	iCount += std::distance(itToRem, it->second.end());
	//	if (itToRem != it->second.end()) {
	//		for (auto iter = itToRem; iter != it->second.end(); ++iter) {
	//			getEventByDate[it->first].erase(*iter);
	//		}
	//		it->second.erase(itToRem, it->second.end());
	//	}

	//	//If date is empty then delete this date from map
	//	if (getEventByDate[it->first].size() == 0) {
	//		vecDatesToRem.push_back(it->first);
	//	}
	//}

	//for (auto dateToRem : vecDatesToRem) {
	//	getEventByDate.erase(dateToRem);
	//	getVecEventsByDate.erase(dateToRem);
	//}


	//return iCount;
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
	auto iDist = std::distance(it, getVecEventsByDate.end());

	std::ostringstream oss;	
	
	if ((iDist > 0 && it != getVecEventsByDate.begin()) || (iDist == 0 && getVecEventsByDate.size() > 0)) {
		oss << std::prev(it)->first << " " << std::prev(it)->second.back();
		return oss.str();		
	}
	else {
		return "No entries";
	}		
}
