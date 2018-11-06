#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
	int iCmdCnt, iNum;
	std::vector<int> vecNums;

	std::cin >> iCmdCnt;
	for (int i = 0; i < iCmdCnt; ++i) {
		std::cin >> iNum;
		vecNums.push_back(iNum);
	}
	std::sort(std::begin(vecNums), std::end(vecNums), [](int a, int b) { return std::abs(a) < std::abs(b); });

	for (auto i : vecNums) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	return 0;
}