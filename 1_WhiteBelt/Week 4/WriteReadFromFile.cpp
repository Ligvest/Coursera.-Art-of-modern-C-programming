#include <iostream>
#include <fstream>
#include <string>


int main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt", std::ios::trunc);
	fout.close();
	fout.open("output.txt", std::ios::app);


	if (fin.is_open()) {
		if (fout.is_open()) {
			std::string sLine;
			while (std::getline(fin, sLine)) {
				fout << sLine << std::endl;
			}
		}		
	}

	fin.close();
	fout.close();
	return 0;
}