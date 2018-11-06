#include <iostream>
#include <string>
#include <vector>
#include <map>

auto buildCharCounter(std::string w) {
	std::map<char, int> wCounter;
	for (char c : w) {
		++wCounter[c];
	}
	return wCounter;
}

int main() {
	int iCmdNum;
	std::cin >> iCmdNum;	
	std::string sArg1, sArg2;
	for (int i = 0; i < iCmdNum; ++i) {
		std::cin >> sArg1 >> sArg2;
		if (buildCharCounter(sArg1) == buildCharCounter(sArg2)) {
			std::cout << "YES" << std::endl;
		}
		else {
			std::cout << "NO" << std::endl;
		}
		
	}


	return 0;
}