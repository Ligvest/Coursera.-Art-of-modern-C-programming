#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>

int main() {
	std::map<std::string, int> mapSynonymsCnt;
	std::set<std::set<std::string>> setSynonyms;
	std::set<std::string> setTemp;
	int iCmdCnt;
	std::cin >> iCmdCnt;
	std::string sCmd, sWord1, sWord2;
	for (int i = 0; i < iCmdCnt; ++i) {
		std::cin >> sCmd;
		if (sCmd == "ADD") {
			std::cin >> sWord1 >> sWord2;			
			setTemp.insert(sWord1);
			setTemp.insert(sWord2);
			if (setSynonyms.count(setTemp) == 0) {
				setSynonyms.insert(setTemp);
				++mapSynonymsCnt[sWord1];
				++mapSynonymsCnt[sWord2];
			}
			setTemp.clear();

		} 
		else if (sCmd == "COUNT") {
			std::cin >> sWord1;
			std::cout << mapSynonymsCnt[sWord1] << std::endl;			
		}
		else if (sCmd == "CHECK") {
			std::cin >> sWord1 >> sWord2;
			setTemp.insert(sWord1);
			setTemp.insert(sWord2);
			if (setSynonyms.count(setTemp) == 0) {
				std::cout << "NO" << std::endl; 
			}
			else {
				std::cout << "YES" << std::endl;
			}
			setTemp.clear();			
		}
	}

	return 0;
}