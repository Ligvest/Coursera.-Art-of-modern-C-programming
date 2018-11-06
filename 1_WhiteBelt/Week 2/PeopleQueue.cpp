#include <iostream>
#include <string>
#include <vector>

int main() {
	int iNumOfOps;
	std::cin >> iNumOfOps;

	std::string cmd;
	int cmdArg, worry = 0;
	std::vector<bool> people(0, false);
	for (int i = 0; i < iNumOfOps; ++i) {
		std::cin >> cmd;		
		if (cmd == "COME") {
			std::cin >> cmdArg;
			people.resize(people.size() + cmdArg);
		} else if (cmd == "WORRY") {
			std::cin >> cmdArg;
			people[cmdArg] = true;
		} else if (cmd == "QUIET") {
			std::cin >> cmdArg;
			people[cmdArg] = false;
		} else if (cmd == "WORRY_COUNT") {
			for (auto el : people) {
				if (el) { ++worry; }
			}
			std::cout << worry << std::endl;
			worry = 0;
		}
	}

	return 0;
}

