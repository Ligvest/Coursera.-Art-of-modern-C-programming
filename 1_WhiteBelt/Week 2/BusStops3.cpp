#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

int main() {
	int iCmdCnt, iStopsCnt, iBusNum = 1;
	std::string sStop;
	std::map <std::set <std::string>, int> mapStops;
	std::set<std::string> setStops;
	std::cin >> iCmdCnt;
	for (int i = 0; i < iCmdCnt; ++i) {
		std::cin >> iStopsCnt;
		for (int i = 0; i < iStopsCnt; ++i) {
			std::cin >> sStop;
			setStops.insert(sStop);
		}
		if (mapStops.count(setStops) == 0) {
			mapStops[setStops] = iBusNum;
			std::cout << "New bus " << iBusNum++ << std::endl;
		}
		else {
			std::cout << "Already exists for " << mapStops[setStops] << std::endl;
		}
		setStops.clear();
	}
	return 0;
}

