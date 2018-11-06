#include <iostream>
#include <algorithm>
#include <vector>

void PrintVectorPart(const std::vector<int>& numbers) {
	auto border = std::find_if(std::begin(numbers), std::end(numbers), [](int a) { return a < 0; });
	auto it = border;
	
	if (border == std::end(numbers)) {
		it = std::end(numbers);
	}

	while (it != (std::begin(numbers))) {
		--it;
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}