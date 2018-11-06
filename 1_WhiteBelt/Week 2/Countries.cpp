#include <iostream>
#include <string>
#include <vector>
#include <map>

auto buildCharCounter(std::string w){
	std::map<char, int> wCounter;
	for (char c : w) {
		wCounter[c] = 0;
	}
	return wCounter;
}

int main() {
	int iCmdNum;
	std::cin >> iCmdNum;
	std::map<std::string, std::string> capitals;
	std::string sCmd, sArg1, sArg2;
	for (int i = 0; i < iCmdNum; ++i) {
		std::cin >> sCmd;
		if (sCmd == "CHANGE_CAPITAL") {
			std::cin >> sArg1 >> sArg2;
			if (capitals.count(sArg1) == 0) {
				std::cout << "Introduce new country " << sArg1 << " with capital " << sArg2 << std::endl;
			}
			else if (capitals[sArg1] == sArg2) {
				std::cout << "Country " << sArg1 << " hasn't changed its capital" << std::endl;
			}
			else {
				std::cout << "Country " << sArg1 << " has changed its capital from " << capitals[sArg1] << " to " << sArg2 << std::endl;
			}
			capitals[sArg1] = sArg2;
		} else if (sCmd == "RENAME") {
			std::cin >> sArg1 >> sArg2;
			if (sArg1 == sArg2 || capitals.count(sArg1) == 0 || capitals.count(sArg2) == 1) {
				std::cout << "Incorrect rename, skip" << std::endl;
			} else if (capitals.count(sArg1) == 1) {
				std::cout << "Country " << sArg1 << " with capital " << capitals[sArg1] << " has been renamed to " << sArg2 << std::endl;
				capitals[sArg2] = capitals[sArg1];
				capitals.erase(sArg1);
			}
		} else if (sCmd == "ABOUT") {
			std::cin >> sArg1;
			if (capitals.count(sArg1) == 0) {
				std::cout << "Country " << sArg1 << " doesn't exist" << std::endl;
			} else {
				std::cout << "Country " << sArg1 << " has capital " << capitals[sArg1] << std::endl;
			}
		} else if (sCmd == "DUMP") {
			if (capitals.size() == 0) {
				std::cout << "There are no countries in the world" << std::endl;
			}
			else {
				for (auto item : capitals) {
					std::cout << item.first << "/" << item.second << " ";
				}
			}
			
		}
	}


	return 0;
}