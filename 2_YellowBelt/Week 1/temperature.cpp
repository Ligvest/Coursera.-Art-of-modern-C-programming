#include <iostream>
#include <vector>

int main() {
	int64_t iDaysCnt, iValue, iMedium = 0;

	std::vector<int64_t> vecDaysTemperature, vecTemp;
	std::cin >> iDaysCnt;

	for (size_t i = 0; i < iDaysCnt; ++i) {
		std::cin >> iValue;
		iMedium += iValue;
		vecTemp.push_back(iValue);
	}

	iMedium /= iDaysCnt;
	
	for (size_t i = 0; i < vecTemp.size(); ++i) {		
		if (vecTemp[i] > iMedium) {
			vecDaysTemperature.push_back(static_cast<int>(i));
		}
	}

	std::cout << vecDaysTemperature.size() << std::endl;

	for (auto val : vecDaysTemperature) {
		std::cout << val << " ";
	}

	std::cout << std::endl;
	

	return 0;
}