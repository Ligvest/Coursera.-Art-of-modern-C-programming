class ReversibleString {
public:
	ReversibleString(std::string new_string) {
		sString = new_string;
	}

	ReversibleString() {
		sString = "";
	}

	void Reverse() {
		std::string sTemp = sString;
		sString.clear();

		for (int i = sTemp.size(); i > 0; --i) {
			sString += sTemp[i - 1];
		}
	}

	std::string ToString() const {
		return sString;
	}

private:
	std::string sString;
};