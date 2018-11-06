bool IsPalindrom(std::string sWord) {
	std::string sTemp = sWord;
	size_t iLast = sWord.size() - 1;
	for (int i = 0; i < sWord.size() / 2; ++i) {
		if (sWord[i] != sWord[iLast - i]) {
			return false;
		}
	}
	return true;
}


std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength) {
	std::vector<std::string> Temp;
	for (auto it = std::begin(words); it != std::end(words); ++it) {
		if (it->size() >= minLength && IsPalindrom(*it)) { Temp.push_back(*it); }
	}
	return Temp;
}
