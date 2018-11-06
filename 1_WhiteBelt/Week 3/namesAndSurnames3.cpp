#include <vector>
#include <map>

using namespace std;



class Person {
public:

	Person(std::string new_name, std::string new_surname, int new_birthyear) {
		iBirthYear = new_birthyear;
		mapFname[iBirthYear] = new_name;
		mapLname[iBirthYear] = new_surname;
	}

	void ChangeFirstName(int year, const string& first_name) {
		if (year >= iBirthYear) {
			mapFname[year] = first_name;
		}
	}
	void ChangeLastName(int year, const string& last_name) {
		if (year >= iBirthYear) {
			mapLname[year] = last_name;
		}
	}

	string GetFullName(int year) const {
		if (year < iBirthYear) {
			return "No person";
		}

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



	string GetFullNameWithHistory(int year) const {
		if (year < iBirthYear) {
			return "No person";
		}
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
	int iBirthYear;


	std::string findNameByYear(const std::map<int, std::string>& mapNames, const int& year, std::vector<std::string>& vecPrevNames) const {
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