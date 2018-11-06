#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure {
public:	
	virtual std::string Name() = 0;
	virtual double Perimeter() = 0;
	virtual double Area() = 0;
};

class Triangle : public Figure {
public:
	Triangle(int a, int b, int c) : a_(a), b_(b), c_(c) {}
	
	double Area() override {
		double dHalfMeter = Perimeter() / 2;
		return std::sqrt(dHalfMeter * (dHalfMeter - a_) * (dHalfMeter - b_) * (dHalfMeter - c_));
	}

	std::string Name() override {
		return "TRIANGLE";
	}

	double Perimeter() override {
		return a_ + b_ + c_;
	}

private:
	double a_, b_, c_;	
};

class Rect : public Figure {
public:
	Rect(int x, int y) : x_(x), y_(y) {}
	
	double Area() override {		
		return x_*y_;
	}

	std::string Name() override {
		return "RECT";
	}

	double Perimeter() override {
		return x_*2 + y_*2;
	}

private:
	int x_, y_;

};

class Circle : public Figure {
public:
	Circle(int r) : r_(r) {}

	double Area() override {
		return 3.14*pow(r_, 2);
	}

	std::string Name() override {
		return "CIRCLE";
	}

	double Perimeter() override {
		return r_ * 2 * 3.14;
	}
private:
	int r_;
};


std::shared_ptr<Figure> CreateFigure(std::istringstream& is) {
	std::string sType;
	is >> sType;
	if (sType == "TRIANGLE") {
		int a, b, c;
		is >> a >> b >> c;
		return std::make_shared<Triangle>(Triangle(a, b, c));
	}
	else if (sType == "RECT") {
		int x, y;
		is >> x >> y;
		return std::make_shared<Rect>(Rect(x, y));
	}
	else if (sType == "CIRCLE") {
		int r;
		is >> r;
		return std::make_shared<Circle>(Circle(r));
	}
}