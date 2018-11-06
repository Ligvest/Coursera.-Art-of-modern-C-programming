std::string findNameByYear(map<int, std::string> mapNames, int year) {
	std::string sName = "";
	for (auto item : mapNames) {
		if (item.first <= year) {
			sName = item.second;
		}
		else {
			break;
		}
	}
	return sName;
}

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		mapFname[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		mapLname[year] = last_name;
	}
	string GetFullName(int year) {
		string sFirst = "";
		string sLast = "";

		sFirst = findNameByYear(mapFname, year);
		sLast = findNameByYear(mapLname, year);

		if (sFirst == ""  && sLast == "") {
			return "Incognito";
		}
		else if (sFirst == "") {
			return sLast + " with unknown first name";
		}
		else if (sLast == "") {
			return sFirst + " with unknown last name";
		}
		else {
			return sFirst + " " + sLast;
		}
	}
private:
	map<int, string> mapFname, mapLname;
};