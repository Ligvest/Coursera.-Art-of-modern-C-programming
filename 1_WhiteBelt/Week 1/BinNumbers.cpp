int main() {
	std::stack<int> st;
	int nNum, nRest;
	std::cin >> nNum;
	while (true) {
		nRest = nNum % 2;
		st.push(nRest);
		nNum /= 2;
		if (nNum == 0) {
			break;
		}		
	}

	while(st.size() > 0) {
		std::cout << st.top();
		st.pop();		
	}
}