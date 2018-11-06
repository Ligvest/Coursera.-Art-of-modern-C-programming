void Reverse(std::vector<int>& v) {
	std::vector<int> temp;
	for (auto it = v.rbegin(); it != v.rend(); ++it) {
		temp.push_back(*it);
	}
	v = temp;
}
