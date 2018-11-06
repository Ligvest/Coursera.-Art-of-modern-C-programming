#include <iostream>
#include <fstream>
#include <string>


int main() {
	std::ifstream fin("input.txt");

	if (fin.is_open()) {
		std::string sLine;
		while (std::getline(fin, sLine)) {
			std::cout << sLine << std::endl;
		}
	}
	return 0;
}