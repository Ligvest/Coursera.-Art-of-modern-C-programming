int Factorial(int f) {
	int res = 1;	
	if (f < 0) {		
		return 1;
	}
	for (int i = f; i > 0; --i) {
		res *= i;
	}
	return res;
}