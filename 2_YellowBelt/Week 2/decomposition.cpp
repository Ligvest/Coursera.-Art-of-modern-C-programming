#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	std::string sType;
	is >> sType;
	if (sType == "NEW_BUS") {
		int iStopCount;
		q.type = QueryType::NewBus;
		is >> q.bus;
		is >> iStopCount;
		q.stops.clear();
		for (int i = 0; i < iStopCount; ++i) {
			is >> q.stop;
			q.stops.push_back(q.stop);
		}
	}
	else if (sType == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (sType == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (sType == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	
	return is;
}

struct BusesForStopResponse {
	std::string stop;
	map<string, vector<string>> stops_to_buses;
	BusesForStopResponse(map<string, vector<string>> new_stb, std::string new_stop) {
		stops_to_buses = new_stb;
		stop = new_stop;
	}
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.stops_to_buses.count(r.stop) == 0) {
		cout << "No stop";
	}
	else {
		for (const string& bus : r.stops_to_buses.at(r.stop)) {
			cout << bus << " ";
		}		
	}

	return os;
}

struct StopsForBusResponse {
	std::string bus;
	map<string, vector<string>> buses_to_stops;
	map<string, vector<string>> stops_to_buses;
	StopsForBusResponse(map<string, vector<string>> new_stb, map<string, vector<string>> new_bts,  std::string new_bus) {
		bus = new_bus;
		buses_to_stops = new_bts;
		stops_to_buses = new_stb;
	}
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.buses_to_stops.count(r.bus) == 0) {
		cout << "No bus";
	}
	else {
		for (const string& stop : r.buses_to_stops.at(r.bus)) {
			cout << "Stop " << stop << ": ";
			if (r.stops_to_buses.at(stop).size() == 1) {
				cout << "no interchange";
			}
			else {
				for (const string& other_bus : r.stops_to_buses.at(stop)) {
					if (r.bus != other_bus) {
						cout << other_bus << " ";
					}
				}
			}
			std::cout << std::endl;
		}
	}

	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> buses_to_stops;	
	AllBusesResponse(map<string, vector<string>> new_bts) {
		buses_to_stops = new_bts;		
	}
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.buses_to_stops.empty()) {
		cout << "No buses";
	}
	else {
		for (const auto& bus_item : r.buses_to_stops) {
			cout << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				cout << stop << " ";
			}	
			std::cout << std::endl;
		}
	}

	return os;
}

class BusManager {
public:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
public:
	void AddBus(const string& bus, const vector<string>& stops) {				
		for (const string& stop : stops) {
			stops_to_buses[stop].push_back(bus);
		}
		buses_to_stops[bus] = stops;
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {		
		return BusesForStopResponse(stops_to_buses, stop);		
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {		
		return StopsForBusResponse(stops_to_buses, buses_to_stops, bus);
	}

	AllBusesResponse GetAllBuses() const {
		return AllBusesResponse(buses_to_stops);
	}
};


// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);			
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}