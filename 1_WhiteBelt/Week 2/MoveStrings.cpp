void MoveStrings(std::vector<std::string>& src, std::vector<std::string>& dst) {
	for (auto it = std::begin(src); it != std::end(src); ++it) {
		dst.push_back(*it);
	}
	src.clear();
}