#include <algorithm>
#include <numeric>
#include <tuple>
#include "airline_ticket.h"
#include "test_runner.h"
using namespace std;

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

#define SORT_BY(field)                                                   \
    [](const AirlineTicket& lhsTicket, const AirlineTicket& rhsTicket) { \
        return lhsTicket.field < rhsTicket.field;                        \
    }

void TestSortBy() {
    vector<AirlineTicket> tixs = {
        {"VKO", "AER", "Utair", {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20, 0}, 1200},
        {"AER", "VKO", "Utair", {2018, 3, 5}, {14, 15}, {2018, 3, 5}, {16, 30}, 1700},
        {"AER", "SVO", "Aeroflot", {2018, 3, 5}, {18, 30}, {2018, 3, 5}, {20, 30}, 2300},
        {"PMI", "DME", "Iberia", {2018, 2, 8}, {23, 00}, {2018, 2, 9}, {3, 30}, 9000},
        {"CDG", "SVO", "AirFrance", {2018, 3, 1}, {13, 00}, {2018, 3, 1}, {17, 30}, 8000},
    };

    sort(begin(tixs), end(tixs), SORT_BY(price));
    ASSERT_EQUAL(tixs.front().price, 1200);
    ASSERT_EQUAL(tixs.back().price, 9000);

    sort(begin(tixs), end(tixs), SORT_BY(from));
    ASSERT_EQUAL(tixs.front().from, "AER");
    ASSERT_EQUAL(tixs.back().from, "VKO");

    sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
    ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
    ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSortBy);
}
