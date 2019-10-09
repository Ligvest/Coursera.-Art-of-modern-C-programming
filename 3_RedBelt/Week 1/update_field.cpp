#include <map>
#include <sstream>
#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values)        \
    if (values.count(#field)) {                    \
        setValue(ticket.field, values.at(#field)); \
    }

template <typename typevalue>
void setValue(typevalue& destination, const std::string& source) {
    destination = source;
}

template <>
void setValue(Date& destination, const std::string& source) {
    std::istringstream inStream(source);
    inStream >> destination.year;
    inStream.ignore(1);
    inStream >> destination.month;
    inStream.ignore(1);
    inStream >> destination.day;
}

template <>
void setValue(Time& destination, const std::string& source) {
    std::istringstream inStream(source);
    inStream >> destination.hours;
    inStream.ignore(1);
    inStream >> destination.minutes;
}

template <>
void setValue(int& destiantion, const std::string& source) {
    destiantion = std::atoi(source.c_str());
}

bool operator<(const Date& lhsDate, const Date& rhsDate) {
    return std::tie(lhsDate.year, lhsDate.month, lhsDate.day) <
           std::tie(rhsDate.year, rhsDate.month, rhsDate.day);
}

bool operator==(const Date& lhsDate, const Date& rhsDate) {
    return std::tie(lhsDate.year, lhsDate.month, lhsDate.day) ==
           std::tie(rhsDate.year, rhsDate.month, rhsDate.day);
}

bool operator<(const Time& lhsTime, const Time& rhsTime) {
    return std::tie(lhsTime.hours, lhsTime.minutes) < std::tie(rhsTime.hours, rhsTime.minutes);
}

bool operator==(const Time& lhsTime, const Time& rhsTime) {
    return std::tie(lhsTime.hours, lhsTime.minutes) == std::tie(rhsTime.hours, rhsTime.minutes);
}

std::ostream& operator<<(std::ostream& sout, const Date& d) {
    sout << d.year << ", " << d.month << ", " << d.day << ", " << std::endl;
    return sout;
}
std::ostream& operator<<(std::ostream& sout, const Time& t) {
    sout << t.hours << ", " << t.minutes << std::endl;
    return sout;
}

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
        {"departure_date", "2018-2-28"},
        {"departure_time", "17:40"},
    };

    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
        {"price", "12550"},
        {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
