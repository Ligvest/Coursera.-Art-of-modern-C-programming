#include <string>

void EnsureEqual(const std::string& left, const std::string& right) {
	if (left != right) {		
		std::string sMsg(left + " != " + right);
		throw std::runtime_error(sMsg);
	}
}