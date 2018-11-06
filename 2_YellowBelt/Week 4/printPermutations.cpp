#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> GetPermutations(const std::vector<int>& vecContainer) {
	std::vector<int> vecTemp = vecContainer;
	std::vector<std::vector<int>> vecVecResult;
	vecVecResult.push_back(vecContainer);
	std::next_permutation(std::begin(vecTemp), std::end(vecTemp));
	while (vecContainer != vecTemp) {
		vecVecResult.push_back(vecTemp);
		std::next_permutation(std::begin(vecTemp), std::end(vecTemp));
	}

	return vecVecResult;	
}

int main() {
	std::vector<int> vecSeq;
	size_t uSeqSize;
	std::cin >> uSeqSize;
	while (uSeqSize >= 1) {
		vecSeq.push_back(uSeqSize);
		--uSeqSize;
	}
	auto res = GetPermutations(vecSeq);
	std::sort(std::rbegin(res), std::rend(res));
	for (auto vec : res) {
		for (int val : vec) {
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
