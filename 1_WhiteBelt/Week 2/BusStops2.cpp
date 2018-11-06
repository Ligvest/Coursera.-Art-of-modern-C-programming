#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
	int iCmdCnt, iStopsCnt, iBusNum = 1;	
	std::string sStop;
	std::map <std::vector <std::string>, int> mapStops;	
	std::vector<std::string> vecStops;
	std::cin >> iCmdCnt;
	for (int i = 0; i < iCmdCnt; ++i) {
		std::cin >> iStopsCnt;
		for (int i = 0; i < iStopsCnt; ++i) {
			std::cin >> sStop;
			vecStops.push_back(sStop);
		}
		if (mapStops.count(vecStops) == 0) {
			mapStops[vecStops] = iBusNum;
			std::cout << "New bus " << iBusNum++ << std::endl;
		}
		else {
			std::cout << "Already exists for " << mapStops[vecStops] << std::endl;
		}		
		vecStops.clear();
	}
	return 0;
}

