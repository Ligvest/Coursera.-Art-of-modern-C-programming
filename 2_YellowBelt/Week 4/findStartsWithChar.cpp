
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end,
	char prefix) {
	RandomIt itLow = std::lower_bound(range_begin, range_end, prefix, [](const std::string& str, const char& prefix) {return str[0] < prefix; });
	RandomIt itUp = std::upper_bound(range_begin, range_end, prefix, [](const char& prefix, const std::string& str) {return prefix < str[0]; });	
	return std::pair<RandomIt, RandomIt>(itLow, itUp);	
}
