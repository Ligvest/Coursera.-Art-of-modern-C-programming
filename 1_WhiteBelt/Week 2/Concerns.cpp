#include <iostream>
#include <string>
#include <vector>

void moveToTheEnd(std::vector<std::vector<std::string>>& vec, int pos) {
	size_t size = vec.size();
	for (int i = pos+1; i < size; ++i) {
		for (auto el : vec[i]) {
			vec[pos].push_back(el);
		}
	}
}

int main() {
	int iCmdNum, iArg, iCurMon = 1;
	std::cin >> iCmdNum;
	std::vector<std::vector<std::string>> months(31+1);
	std::string sCmd, sArg;
	for (int i = 0; i < iCmdNum; ++i) {
		std::cin >> sCmd;
		if (sCmd == "ADD") {
			std::cin >> iArg;
			std::cin >> sArg;
			months[iArg].push_back(sArg);

		} else if (sCmd == "NEXT") {
			if (++iCurMon > 12) {
				iCurMon = 1;
			}
			switch (iCurMon) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				months.resize(31+1);
				break;
			case 2:
				moveToTheEnd(months, 28);
				months.resize(28+1);
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				moveToTheEnd(months, 30);
				months.resize(30+1);
				break;
			default:
				break;
			}
		} else if (sCmd == "DUMP") {
			std::cin >> iArg;
			std::cout << months[iArg].size() << " ";
			for (auto el : months[iArg]) {
				std::cout << el << " ";
			}
			std::cout << std::endl;
		}

	}


	return 0;
}