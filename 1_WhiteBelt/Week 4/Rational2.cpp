#include <iostream>
#include <cmath>

using namespace std;


int NOD(int a, int b)
{
	a = abs(a);
	b = abs(b);
	while (a > 0 && b > 0)
		if (a > b) {
			a %= b;
		}
		else {
			b %= a;
		}
		return a + b;
}

class Rational {
public:
	Rational() {
		iNumerator = 0;
		iDenominator = 1;
	}

	Rational(int numerator, int denominator) {
		iNumerator = numerator;
		iDenominator = denominator;
		this->Cut();
	}

	void Cut() {

		int nod = NOD(iNumerator, iDenominator);

		iNumerator = iNumerator / nod;
		iDenominator = iDenominator / nod;

		if ( (iNumerator > 0 && iDenominator > 0) || ((iNumerator < 0 && iDenominator < 0))) {
			iNumerator = abs(iNumerator);
			iDenominator = abs(iDenominator);
		}
		else if (iNumerator == 0) {
			iDenominator = 1;
		}
		else {
			iNumerator = abs(iNumerator) * (-1);
			iDenominator = abs(iDenominator);
		}


	}

	int Numerator() const {
		return iNumerator;
	}

	int Denominator() const {
		return iDenominator;
	}

	bool operator == (const Rational& lhs) const {
		if (lhs.Denominator() == this->iDenominator && lhs.Numerator() == this->iNumerator) {
			return true;
		}
		else {
			return false;
		}
	}

	Rational operator + (const Rational& lhs) const {		
		return Rational(lhs.iDenominator*this->iNumerator + lhs.iNumerator*this->iDenominator, lhs.iDenominator * this->iDenominator);
	}

	Rational operator - (const Rational& lhs) const {
		return Rational(lhs.iDenominator*this->iNumerator - lhs.iNumerator*this->iDenominator, lhs.iDenominator * this->iDenominator);
	}


private:
	int iNumerator, iDenominator;
};




// Реализуйте для класса Rational операторы ==, + и -

int main() {
	{
		Rational r1(4, 6);
		Rational r2(2, 3);
		bool equal = r1 == r2;
		if (!equal) {
			cout << "4/6 != 2/3" << endl;
			return 1;
		}
	}

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a + b;
		bool equal = c == Rational(2, 1);
		if (!equal) {
			cout << "2/3 + 4/3 != 2" << endl;
			return 2;
		}
	}

	{
		Rational a(0, 1);
		Rational b(0, 1);
		Rational c = a + b;
		bool equal = c == Rational(0, 1);
		if (!equal) {
			cout << "3" << endl;
			return 2;
		}
	}

	{
		Rational a(0, 1);
		Rational b(5, 2);
		Rational c = a + b;
		bool equal = c == Rational(5, 2);
		if (!equal) {
			cout << "4" << endl;
			return 2;
		}
	}

	{
		Rational a(4, 6);
		Rational b(3, 5);
		Rational c = a + b;
		bool equal = c == Rational(19, 15);
		if (!equal) {
			cout << "5" << endl;
			return 2;
		}
	}

	{
		Rational a(-4, 6);
		Rational b(-3, 6);
		Rational c = a + b;
		bool equal = c == Rational(-7, 6);
		if (!equal) {
			cout << "6" << endl;
			return 2;
		}
	}

	{
		Rational a(-4000, 6000);
		Rational b(3000, 6000);
		Rational c = a + b;
		bool equal = c == Rational(-1, 6);
		if (!equal) {
			cout << "7" << endl;
			return 2;
		}
	}

	{
		Rational a(5, 7);
		Rational b(2, 9);
		Rational c = a - b;
		bool equal = c == Rational(31, 63);
		if (!equal) {
			cout << "5/7 - 2/9 != 31/63" << endl;
			return 3;
		}
	}

	cout << "OK" << endl;
	return 0;
}