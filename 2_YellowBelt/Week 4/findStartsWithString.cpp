template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end,
	const string& prefix) {
	RandomIt itLow = std::lower_bound(range_begin, range_end, prefix, [](const std::string& str, const std::string& prefix) { return str.substr(0, prefix.size()) < prefix; });
	RandomIt itUp = std::upper_bound(range_begin, range_end, prefix, [](const std::string& prefix, const std::string& str) { return prefix < str.substr(0, prefix.size()); });
	return std::pair<RandomIt, RandomIt>(itLow, itUp);	
}