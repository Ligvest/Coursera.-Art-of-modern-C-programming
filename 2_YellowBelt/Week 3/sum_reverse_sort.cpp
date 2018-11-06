#include "sum_reverse_sort.h"
#include <algorithm>

int Sum(int x, int y) {
	return x + y;
}

void Sort(vector<int>& nums) {
	std::sort(std::begin(nums), std::end(nums));
}

std::string Reverse(string v) {
	std::string temp;
	for (auto it = v.rbegin(); it != v.rend(); ++it) {
		temp.push_back(*it);		
	}
	return temp;
}
