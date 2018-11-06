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

	Rational operator + (const Rational& rhs) const {		
		return Rational(rhs.iNumerator*this->iDenominator + rhs.iDenominator*this->iNumerator, this->iDenominator * rhs.iDenominator);
	}

	Rational operator - (const Rational& rhs) const {
		return Rational(rhs.iNumerator*this->iDenominator - rhs.iDenominator*this->iNumerator, this->iDenominator * rhs.iDenominator);
	}

	Rational operator * (const Rational& rhs) const {
		return Rational(this->iNumerator * rhs.iNumerator, this->iDenominator * rhs.iDenominator);
	}

	Rational operator / (const Rational& rhs) const {
		return Rational(this->iNumerator * rhs.iDenominator, this->iDenominator * rhs.iNumerator);
	}


private:
	int iNumerator, iDenominator;
};




// Реализуйте для класса Rational операторы ==, + и -

int main() {
	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a * b;
		bool equal = c == Rational(8, 9);
		if (!equal) {
			cout << "2/3 * 4/3 != 8/9" << endl;
			return 1;
		}
	}

	{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		if (!equal) {
			cout << "5/4 / 15/8 != 2/3" << endl;
			return 2;
		}
	}

	cout << "OK" << endl;
	return 0;
}