bool operator < (const Region& lhs, const Region& rhs) {
	return std::tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
			std::tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}
 
int FindMaxRepetitionCount(std::vector<Region> regions) {
	
	int iResult = 0;
	std::map<Region, int> mapRepeats;

	for (auto region : regions) {
		iResult = std::max(iResult, ++mapRepeats[region]);
	}

	
	
	return iResult;		
}