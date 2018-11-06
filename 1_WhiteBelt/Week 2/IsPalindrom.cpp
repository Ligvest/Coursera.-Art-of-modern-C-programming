bool IsPalindrom(std::string sWord) {
	std::string sTemp = sWord;
	size_t iLast = sWord.size()-1;
	for (int i = 0; i < sWord.size()/2; ++i) {		
		if (sWord[i] != sWord[iLast - i]) {
			return false;
		}
	}
	return true;	
}