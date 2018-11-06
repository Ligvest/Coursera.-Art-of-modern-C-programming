#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
	std::sort(std::begin(elements), std::end(elements));
	auto it = std::unique(std::begin(elements), std::end(elements));
	elements.erase(it, std::end(elements));
}