#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
	std::string sTemp("");
	std::vector<string> vecRes;
	auto itNext = std::begin(s);
	auto itPrev = std::begin(s);
	
	while (itNext != std::end(s)) {
		itNext = std::find_if(itPrev, std::end(s), [](char a) {return a == ' '; });
		
		for (auto it = itPrev;
			it != itNext; ++it) {
			sTemp += *it;
		}		
		
		vecRes.push_back(sTemp);
		sTemp.clear();
		itPrev = itNext;
		if (itPrev != std::end(s)) {
			++itPrev;
		}
	}

	return vecRes;
}