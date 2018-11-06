template <typename F, typename S>
std::map<F, S> operator*(const std::map<F, S>& lmap, const std::map<F, S>& rmap) {
	std::map<F, S> mapRes;
	for (auto item : lmap) {
		mapRes[item.first] = lmap.at(item.first) * rmap.at(item.first);
	}
	return mapRes;
}

template <typename F, typename S>
std::pair<F, S> operator*(const std::pair<F, S>& lpair, const std::pair<F, S>& rpair) {
	std::pair<F, S> pairRes;
	pairRes.first = lpair.first * rpair.first;
	pairRes.second = lpair.second * rpair.second;
	return pairRes;
}

template <typename T>
std::vector<T> operator*(const std::vector<T>& lvec, const std::vector<T>& rvec) {
	std::vector<T> vecRes;
	for (size_t i = 0; i < lvec.size(); ++i) {
		vecRes.push_back(lvec[i] * rvec[i]);
	}
	return vecRes;
}

template <typename T>
T Sqr(const T& container) {
	return container*container;
}