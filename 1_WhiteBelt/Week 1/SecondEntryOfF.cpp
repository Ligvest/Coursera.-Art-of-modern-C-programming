int main() {
	/* Второе вхождение буквы f
	std::string sWord;
	std::cin >> sWord;
	int nCounter = 0;
	for (int i = 0; i < sWord.size(); ++i) {
		if (sWord[i] == 'f') {
			++nCounter;
		}
		if (nCounter == 2) {
			std::cout << i;
			return 0;
		}
	}

	if (nCounter == 1) {
		std::cout << -1;
		return 0;
	} else if (nCounter == 0) {
		std::cout << -2;
		return 0;
	}
	return 0;
}