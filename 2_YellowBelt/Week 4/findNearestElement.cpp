set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
	set<int>::const_iterator it = numbers.lower_bound(border);	
	
	if (it == numbers.begin()) {
		return it;
	}

	auto prev = std::prev(it);
	if (it == numbers.end()) {
		return prev;
	}

	const bool is_left = (border - *prev <= *it - border);
	return is_left ? prev : it;
	
	if (*it - border >= border - *prev ) {
		return prev;
	} else {
		return it;
	}
}