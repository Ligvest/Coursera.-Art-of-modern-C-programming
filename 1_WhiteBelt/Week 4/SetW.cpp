#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
	std::ifstream fin("input.txt");
	if (fin.is_open()) {
		int n, m, iNum;
		fin >> n;
		fin.ignore(1);
		fin >> m;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				fin >> iNum;
				std::cout << std::setw(10) << iNum;
				if (j < m - 1) {
					fin.ignore(1);
					std::cout << " ";
				}
			}

			if (i < n - 1) {
				std::cout << std::endl;
			}			
		}
	}
	return 0;
}