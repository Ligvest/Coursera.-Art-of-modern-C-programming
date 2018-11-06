#include <iostream>
#include <string>
#include <deque>

int main() {
	int x;
	std::cin >> x;
	
	size_t uOps;
	std::cin >> uOps;

	std::deque<std::string> deqExpression;		
	deqExpression.push_back(std::to_string(x));	

	int iValue;
	char cOp;	
	for (int i = 0; i < uOps; ++i) {
		std::cin >> cOp;
		std::cin >> iValue;
		
		deqExpression.push_front("(");
		deqExpression.push_back(") ");
		deqExpression.push_back(std::string(1, cOp) + " " + std::to_string(iValue));
	}
	
	for (auto el : deqExpression) {
		std::cout << el;
	}
	std::cout << std::endl;

	return 0;
}