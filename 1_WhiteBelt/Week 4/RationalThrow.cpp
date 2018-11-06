#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>

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
		if (denominator == 0) {
			throw std::invalid_argument("invalid argument");
		}

		iNumerator = numerator;
		iDenominator = denominator;
		this->Cut();
	}

	void Cut() {

		int nod = NOD(iNumerator, iDenominator);

		iNumerator = iNumerator / nod;
		iDenominator = iDenominator / nod;

		if ((iNumerator > 0 && iDenominator > 0) || ((iNumerator < 0 && iDenominator < 0))) {
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
		if (rhs.iNumerator == 0) {
			throw std::domain_error("zero division");
		}

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

bool operator < (const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator()*rhs.Denominator()) < (rhs.Numerator()*lhs.Denominator());
}


// Вставьте сюда реализацию operator == для класса Rational из второй части

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а


int main() {
	try {
		Rational r(1, 0);
		cout << "Doesn't throw in case of zero denominator" << endl;
		return 1;
	}
	catch (invalid_argument&) {
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		cout << "Doesn't throw in case of division by zero" << endl;
		return 2;
	}
	catch (domain_error&) {
	}

	cout << "OK" << endl;
	return 0;
}