template <typename Key, typename Value>
Value& GetRefStrict(std::map<Key, Value>& mapCol, const Key& key) {
	if (mapCol.count(key) > 0) {
		return mapCol.at(key);
	}
	else
	{
		throw std::runtime_error("Key doesn't exist.");
	}
}
