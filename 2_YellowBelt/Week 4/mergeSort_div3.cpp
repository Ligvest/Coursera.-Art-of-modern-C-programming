template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	size_t uSize = range_end - range_begin;
	if (uSize < 3) { return; }
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	vector<typename RandomIt::value_type> vecTemp;
	auto it1Beg = std::begin(elements);
	auto it1End = std::end(elements) - ((uSize / 3) * 2);
	auto it2Beg = std::end(elements) - ((uSize / 3) * 2);
	auto it2End = std::end(elements) - (uSize / 3);
	auto it3Beg = std::end(elements) - (uSize / 3);
	auto it3End = std::end(elements);

	MergeSort(it1Beg, it1End);
	MergeSort(it2Beg, it2End);
	MergeSort(it3Beg, it3End);

	std::merge(it1Beg, it1End, it2Beg, it2End, std::back_inserter(vecTemp));	
	std::merge(std::begin(vecTemp), std::end(vecTemp), it3Beg, it3End, range_begin);
}