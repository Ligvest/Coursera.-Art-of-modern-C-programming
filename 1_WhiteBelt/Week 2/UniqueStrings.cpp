#include <iostream>
#include <string>
#include <set>

int main() {
	int iCmdCnt, iStopsCnt, iBusNum = 1;	
	std::string sWord;	
	std::set<std::string> setWords;
	std::cin >> iCmdCnt;
	for (int i = 0; i < iCmdCnt; ++i) {
		std::cin >> sWord;
		setWords.insert(sWord);
	}
	std::cout << setWords.size() << std::endl;
	return 0;
}

