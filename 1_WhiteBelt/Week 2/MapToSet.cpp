std::set<std::string> BuildMapValuesSet(const std::map<int, std::string>& m) {
	std::set<std::string> s;
	for (auto el : m) {
		s.insert(el.second);
	}

	return s;
}