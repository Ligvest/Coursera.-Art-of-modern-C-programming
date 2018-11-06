#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
	std::ifstream fin("input.txt");
	std::cout << std::fixed;
	std::cout << std::setprecision(3);
	if (fin.is_open()) {
		double dNum;
		while (!fin.eof()) {
			fin >> dNum;
			std::cout << dNum << std::endl;
		}
	}
	return 0;
}