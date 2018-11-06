template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	size_t uSize = range_end - range_begin;
	if (uSize < 2) { return; }
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto it1Beg = std::begin(elements);
	auto it1End = std::end(elements) - (uSize / 2);
	auto it2Beg = std::end(elements) - (uSize / 2);
	auto it2End = std::end(elements);

	MergeSort(it1Beg, it1End);
	MergeSort(it1End, it2End);
	std::merge(it1Beg, it1End, it2Beg, it2End, range_begin);	
}