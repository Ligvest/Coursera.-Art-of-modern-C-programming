#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
	Animal(std::string str) : Name(str) {}

	const string Name;
};


class Dog : public Animal {
public:

	Dog(std::string str) : Animal(str) {}

	void Bark() {
		cout << Name << " barks: woof!" << endl;
	}
};