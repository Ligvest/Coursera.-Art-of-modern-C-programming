#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctype.h>

int main() {
	int iCmdCnt, iNum;
	std::string sWord;
	std::vector < std::string > vecNums;

	std::cin >> iCmdCnt;
	for (int i = 0; i < iCmdCnt; ++i) {
		std::cin >> sWord;
		vecNums.push_back(sWord);
	}
	std::sort(std::begin(vecNums), std::end(vecNums), 
		[](std::string a, std::string b) { 
		for (auto& ia : a) {
			ia = tolower(ia);
		}
		for (auto& ib : b) {
			ib = tolower(ib);
		}
		return a < b; });

	for (auto i : vecNums) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	return 0;
}