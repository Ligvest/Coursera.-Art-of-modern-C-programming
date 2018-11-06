#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Person
class Person {
public:
	Person(const std::string& sName, const std::string& sProfession) : sName_(sName), sProfession_(sProfession) {}

	std::string who() const {
		return sProfession_ + ": " + sName_;
	}

	virtual void Walk(const std::string& destination) const {
		cout << who() << " walks to: " << destination << endl;
	}

	void SingSong(const std::string& sSong) const {
		cout << who() << " sings a song: " << sSong << endl;
	}

public:
	const std::string sName_;
	const std::string sProfession_;
};


//Student
class Student : public Person {
public:

	Student(const string& name, const string& favouriteSong) : Person(name, "Student"), FavouriteSong(favouriteSong) {}

	void Learn() const {
		cout << who() << " learns" << endl;
	}

	void Walk(const string& destination) const override {
		Person::Walk(destination);
		SingSong(FavouriteSong);
	}

public:
	const string FavouriteSong;
};


//Teacher
class Teacher : public Person {
public:
	Teacher(const string& name, const string& subject) : Person(name, "Teacher"), Subject(subject) {}

	void Teach() const {
		cout << who() << " teaches: " << Subject << endl;
	}

public:
	const string Subject;
};


//Policeman
class Policeman : public Person {
public:
	Policeman(string name) : Person(name, "Policeman") {}

	void Check(const Person& p) const {
		cout << who() << " checks " << p.sProfession_ << ". "
			<< p.sProfession_ << "'s name is: " << p.sName_ << endl;
	}
};


void VisitPlaces(const Person& p, vector<string> places) {
	for (auto place : places) {
		p.Walk(place);
	}
}


int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}
