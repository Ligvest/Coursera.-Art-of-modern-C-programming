class SortedStrings {
public:
	void AddString(const std::string& s) {
		vecStrings.push_back(s);
	}
	std::vector<std::string> GetSortedStrings() {
		std::sort(std::begin(vecStrings), std::end(vecStrings));
		return vecStrings;
	}
private:
	std::vector<std::string> vecStrings;
};