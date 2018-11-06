#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
	auto itBorder = std::find_if(std::begin(elements),
		std::end(elements),
		[&border](T a) {return a > border; });

	std::vector<T> vecTemp;

	for (auto it = itBorder; it != std::end(elements); ++it) {
		vecTemp.push_back(*it);
	}

	return vecTemp;
}

int main() {
	for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
		cout << x << " ";
	}
	cout << endl;

	string to_find = "Python";
	cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
	return 0;
}
