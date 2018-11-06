#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

bool operator == (const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator() && lhs.Numerator() == rhs.Numerator()) {
		return true;
	}
	else {
		return false;
	}
}

bool operator != (const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() != rhs.Denominator() || lhs.Numerator() != rhs.Numerator()) {
		return true;
	}
	else {
		return false;
	}
}

ostream& operator << (ostream& stream, const Rational& ratNum) {
	stream << ratNum.Numerator() << "/" << ratNum.Denominator();
	return stream;
}


void TestRational() {
	Rational r1;	
	AssertEqual(r1.Numerator(), 0, "1");
	AssertEqual(r1.Denominator(), 1, "1");

	Rational r2(5,10);
	AssertEqual(r2.Numerator(), 1, "2");
	AssertEqual(r2.Denominator(), 2, "2");	

	Rational r3(10,5);
	AssertEqual(r3.Numerator(), 2, "3");
	AssertEqual(r3.Denominator(), 1, "3");	

	Rational r4(10,-5);
	AssertEqual(r4.Numerator(), -2, "4");
	AssertEqual(r4.Denominator(), 1, "4");	

	Rational r5(-10,5);
	AssertEqual(r5.Numerator(), -2, "5");
	AssertEqual(r5.Denominator(), 1, "5");

	Rational r6(0,3);
	AssertEqual(r6.Numerator(), 0, "6");
	AssertEqual(r6.Denominator(), 1, "6");
	
	Rational r7(0,-3);
	AssertEqual(r7.Numerator(), 0, "7");
	AssertEqual(r7.Denominator(), 1, "7");

	Rational r8(-2,-3);
	AssertEqual(r8.Numerator(), 2, "8");
	AssertEqual(r8.Denominator(), 3, "8");

	Rational r9(-20,-30);
	AssertEqual(r9.Numerator(), 2, "9");
	AssertEqual(r9.Denominator(), 3, "9");
}

class Rational {
public:
	// Вы можете вставлять сюда различные реализации,
	// чтобы проверить, что ваши тесты пропускают корректный код
	// и ловят некорректный

	Rational();
	Rational(int numerator, int denominator) {
	}

	int Numerator() const {
	}

	int Denominator() const {
	}
};

int main() {
	TestRunner runner;	
	
	// добавьте сюда свои тесты
	return 0;
}