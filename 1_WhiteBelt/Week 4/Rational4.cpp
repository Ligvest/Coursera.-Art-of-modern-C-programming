#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

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

	void SetNumerator(int iNewNum) {
		iNumerator = iNewNum;
	}

	void SetDenominator(int iNewDen) {
		iDenominator = iNewDen;
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

ostream& operator << (ostream& stream, const Rational& ratNum) {
	stream << ratNum.Numerator() << "/" << ratNum.Denominator();
	return stream;
}

istream& operator >> (istream& stream, Rational& ratNum) {
	std::string sTemp;
	stream >> sTemp;
	if (!sTemp.empty()) {
		std::stringstream ssStream(sTemp);
		int iNum, iDen;
		ssStream >> iNum;
		ssStream.ignore(1);
		ssStream >> iDen;
		ratNum.SetNumerator(iNum);
		ratNum.SetDenominator(iDen);
		ratNum.Cut();
	}
	return stream;
}



// Реализуйте для класса Rational операторы ==, + и -

int main() {
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 3;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 4;
		}
	}

	cout << "OK" << endl;
	return 0;
}