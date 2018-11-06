int NOD(int a, int b)
{
	while (a > 0 && b > 0)
		if (a > b) {
			a %= b;
		}
		else {
			b %= a;
		}
		return a + b;
}

int main() {
	int a, b, c;
	std::cin >> a >> b;
	c = NOD(a, b);
	std::cout << c;
}