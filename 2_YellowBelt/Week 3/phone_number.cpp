#include "phone_number.h"
#include <sstream>

PhoneNumber::PhoneNumber(const std::string& sInternationalNumber) {
	std::stringstream ss(sInternationalNumber);
	if (ss.peek() != '+') { throw std::invalid_argument("Wrong format of phone number (+) "); }
	ss.ignore(1);
	if (ss.peek() == ' ' || ss.peek() == '-' || ss.peek() == '+') { throw std::invalid_argument("Wrong format of phone number (space) 1 "); }
	std::getline(ss, country_code_, '-');
	ss.unget();
	if (ss.peek() != '-') { throw std::invalid_argument("Wrong format of phone number (-) 1 "); }
	ss.ignore(1);
	if (ss.peek() == ' ' || ss.peek() == '-' || ss.peek() == '+') { throw std::invalid_argument("Wrong format of phone number (space) 2 "); }
	std::getline(ss, city_code_, '-');	
	ss.unget();
	if (ss.peek() != '-') { throw std::invalid_argument("Wrong format of phone number (-) 2"); }
	ss.ignore(1);
	if (ss.peek() == ' ' || ss.peek() == '-' || ss.peek() == '+') { throw std::invalid_argument("Wrong format of phone number (space) 3 "); }
	ss >> local_number_;
}

std::string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

std::string PhoneNumber::GetCityCode() const {
	return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const {
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}