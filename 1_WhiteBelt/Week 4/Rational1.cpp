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

		if (iNumerator*iDenominator > 0) {
			iNumerator = abs(iNumerator);
			iDenominator = abs(iDenominator);
		}
		else if (iNumerator*iDenominator < 0) {
			iNumerator = abs(iNumerator) * (-1);
			iDenominator = abs(iDenominator);
		}
		else if (iNumerator == 0) {
			iDenominator = 1;
		}

	}

	int Numerator() const {
		return iNumerator;
	}

	int Denominator() const {
		return iDenominator;
	}

	bool operator == (const Rational& lhs) {
		if (lhs.Denominator() == this->iDenominator && lhs.Numerator() == this->iNumerator) {
			return true;
		}
		else {
			return false;
		}
	}

	Rational operator + (const Rational& lhs) {
		Rational res;
		if (lhs.iDenominator != this->iDenominator) {
			res.iDenominator = lhs.iDenominator * this->iDenominator;
			res.iNumerator = lhs.iDenominator*this->iNumerator + lhs.iNumerator*this->iDenominator;
			return res;
		}
		else {
			res.iDenominator = lhs.iDenominator;
			res.iNumerator = this->iNumerator + lhs.iNumerator;
			res.Cut();
			return res;
		}
	}


private:
	int iNumerator, iDenominator;
};

int main() {
	{
		const Rational r(3, 10);
		if (r.Numerator() != 3 || r.Denominator() != 10) {
			cout << "Rational(3, 10) != 3/10" << endl;
			return 1;
		}
	}

	{
		const Rational r(8, 12);
		if (r.Numerator() != 2 || r.Denominator() != 3) {
			cout << "Rational(8, 12) != 2/3" << endl;
			return 2;
		}
	}

	{
		const Rational r(-4, 6);
		if (r.Numerator() != -2 || r.Denominator() != 3) {
			cout << "Rational(-4, 6) != -2/3" << endl;
			return 3;
		}
	}

	{
		const Rational r(4, -6);
		if (r.Numerator() != -2 || r.Denominator() != 3) {
			cout << "Rational(4, -6) != -2/3" << endl;
			return 3;
		}
	}

	{
		const Rational r(4, -8);
		if (r.Numerator() != -1 || r.Denominator() != 2) {
			cout << "Rational(4, -8) != -1/2" << endl;
			return 3;
		}
	}

	{
		const Rational r(0, 15);
		if (r.Numerator() != 0 || r.Denominator() != 1) {
			cout << "Rational(0, 15) != 0/1" << endl;
			return 4;
		}
	}

	{
		const Rational defaultConstructed;
		if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
			cout << "Rational() != 0/1" << endl;
			return 5;
		}
	}

	{
		const Rational r(-1, 2);
		if (r.Numerator() != -1 || r.Denominator() != 2) {
			cout << "Rational() != -1/2" << endl;
			return 5;
		}
	}

	{
		const Rational r(1, -2);
		if (r.Numerator() != -1 || r.Denominator() != 2) {
			cout << "Rational() != -1/2" << endl;
			return 5;
		}
	}

	{
		const Rational r(-1, -2);
		if (r.Numerator() != 1 || r.Denominator() != 2) {
			cout << "Rational() != 1/2" << endl;
			return 5;
		}
	}

	{
		const Rational r(-1, 2);
		if (r.Numerator() != -1 || r.Denominator() != 2) {
			cout << "Rational() != -1/2" << endl;
			return 5;
		}
	}

	cout << "OK" << endl;
	return 0;
}
