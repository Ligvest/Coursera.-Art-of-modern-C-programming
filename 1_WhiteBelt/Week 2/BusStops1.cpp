#include <iostream>
#include <string>
#include <map>
#include <vector>

int main() {
	int iCmdCnt, iStopCnt;
	std::string sCmd, sBus, sStop;
	bool bExists = false;
	bool bIsFirst = true;
	std::cin >> iCmdCnt;
	std::vector<std::string> vBusesOrder;
	std::map<std::string, std::vector<std::string>> mBuses;
	for (int i = 0; i < iCmdCnt; ++i) {
		std::cin >> sCmd;
		if (sCmd == "NEW_BUS") {
			std::cin >> sBus >> iStopCnt;
			vBusesOrder.push_back(sBus);
			for (int i = 0; i < iStopCnt; ++i) {
				std::cin >> sStop;
				mBuses[sBus].push_back(sStop);
			}
		} 
		else
		if (sCmd == "BUSES_FOR_STOP") {
			std::cin >> sStop;
			for (std::string bus : vBusesOrder) {
				for (std::string stop : mBuses[bus]) {
					if (stop == sStop) {
						bExists = true;
						if (bIsFirst == true) {
							std::cout << bus;
							bIsFirst = false;
						}
						else {
							std::cout << " " << bus;
						}						
					}
				}
			}
			if (bExists == false) {
				std::cout << "No stop";
			}
			bExists = false;
			std::cout << std::endl;
			bIsFirst = true;
		}
		else 
		if (sCmd == "STOPS_FOR_BUS") {
			std::cin >> sBus;
			if (mBuses.count(sBus) == 0) {
				std::cout << "No bus" << std::endl;				
			}
			else {
				for (auto stop : mBuses[sBus]) {
					std::cout << "Stop " << stop << ":";
					for (std::string bus : vBusesOrder) {
						if (bus == sBus) { continue; }
						for (std::string st : mBuses[bus]) {
							if (st == stop) {
								bExists = true;
								std::cout << " " << bus;
							}
						}
					}
					if (bExists == false) {
						std::cout << " no interchange";
					}
					std::cout << std::endl;
					bExists = false;
				}
			}
		}
		else
		if (sCmd == "ALL_BUSES") {
			if (mBuses.size() == 0) {
				std::cout << "No buses" << std::endl;
			}
			else
			{
				for (auto bus : mBuses) {
					std::cout << "Bus " << bus.first << ":";
					for (auto stop : bus.second) {
						std::cout << " " << stop;
					}
					std::cout << std::endl;
				}
			}
		}
	}
	return 0;
}