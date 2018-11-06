#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;



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
		std::vector < std::string > vecPrevFnames;
		std::vector < std::string > vecPrevLnames;


		sFirst = findNameByYear(mapFname, year, vecPrevFnames);
		sLast = findNameByYear(mapLname, year, vecPrevLnames);

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



	string GetFullNameWithHistory(int year) {
		string sFirst = "";
		string sLast = "";
		std::vector < std::string > vecPrevFnames;
		std::vector < std::string > vecPrevLnames;

		sFirst = findNameByYear(mapFname, year, vecPrevFnames);
		sLast = findNameByYear(mapLname, year, vecPrevLnames);

		bool bFirstIt = true;
		std::string sPrevFirst = " (";
		for (auto name : vecPrevFnames) {
			if (bFirstIt == true) {
				sPrevFirst += name;
				bFirstIt = false;
			}
			else {
				sPrevFirst += ", " + name;
			}
		}
		sPrevFirst += ")";
		sPrevFirst = (sPrevFirst == " ()") ? "" : sPrevFirst;


		bFirstIt = true;
		std::string sPrevLast = " (";
		for (auto name : vecPrevLnames) {
			if (bFirstIt == true) {
				sPrevLast += name;
				bFirstIt = false;
			}
			else {
				sPrevLast += ", " + name;
			}
		}
		sPrevLast += ")";
		sPrevLast = (sPrevLast == " ()") ? "" : sPrevLast;




		if (sFirst == ""  && sLast == "") {
			return "Incognito";
		}
		else if (sFirst == "") {
			return sLast + sPrevLast + " with unknown first name";	
		}
		else if (sLast == "") {
			return sFirst + sPrevFirst + " with unknown last name";
		}
		else {
			return sFirst + sPrevFirst + " " + sLast + sPrevLast;
		}
	}
private:
	map<int, string> mapFname, mapLname;


	std::string findNameByYear(const std::map<int, std::string>& mapNames, const int& year, std::vector<std::string>& vecPrevNames) {
		std::string sName = "";
		std::string sPrevTemp = "";
		vecPrevNames.clear();
		std::vector<std::string> vecTemp;


		for (const auto& item : mapNames) {
			if (item.first <= year) {
				sName = item.second;
				if (sPrevTemp != item.second) {
					vecTemp.push_back(item.second);
				}
				sPrevTemp = item.second;
			}
			else {
				break;
			}
		}

		if (vecTemp.size() > 0) { vecTemp.pop_back(); }

		//reverse
		for (int i = vecTemp.size(); i > 0; --i) {
			vecPrevNames.push_back(vecTemp[i - 1]);
		}

		return sName;
	}
};

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	cout << person.GetFullNameWithHistory(1990) << endl;

	person.ChangeFirstName(1966, "Pauline");
	cout << person.GetFullNameWithHistory(1966) << endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	cout << person.GetFullNameWithHistory(1967) << endl;

	system("pause");

	return 0;
}