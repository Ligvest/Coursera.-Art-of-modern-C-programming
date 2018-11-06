#include <iostream>
#include <numeric>
#include <vector>

int main() {
	int iDensity = 0,
		iWidth = 0,
		iHeight = 0,
		iLong = 0,
		iBlocksCnt = 0;
	uint64_t iSum = 0;

	std::cin >> iBlocksCnt >> iDensity;

	for (size_t i = 0; i < iBlocksCnt; ++i) {
		std::cin >> iLong >> iWidth >> iHeight;
		iSum += static_cast<uint64_t>(iLong)*iWidth*iHeight*iDensity;
	}

	std::cout << iSum << std::endl;

	return 0;
}