//#define TEST
#ifdef TEST
#include "test_runner.h"
#endif
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>

struct HotelClientRooms {
    HotelClientRooms(std::string hotelName, int clientId, int roomsCount)
        : hotelName_(hotelName), clientId_(clientId), roomsCount_(roomsCount) {}
    std::string hotelName_;
    int clientId_;
    int roomsCount_;
};

class BookingManager {
   public:
    void book(int64_t time, const std::string& hotelName, int clientId,
              int roomsCount);                        // O(2LogN) + O(cleanOldData)
    int clients(const std::string& hotelName) const;  // O(1)
    int rooms(const std::string& hotelName) const;    // O(1)
    BookingManager() : dayBegin_(0), oldestTime_(0) {}

   private:
    void cleanOldData();  // O(N) amortizated

   private:
    std::list<int64_t> times_;
    std::list<HotelClientRooms> reservations_;
    std::map<std::string, int> hotelsRoomsCount_;
    std::map<std::string, std::map<int, int>> hotelsClientsCount_;

    int64_t dayBegin_;
    int64_t oldestTime_;
};

void BookingManager::cleanOldData() {
    auto timesPos = times_.begin();
    auto curReservation = reservations_.begin();

    while (*timesPos <= dayBegin_ && timesPos != times_.end()) {
        std::string& hotelName = curReservation->hotelName_;
        int clientId = curReservation->clientId_;
        int roomsCount = curReservation->roomsCount_;

        hotelsRoomsCount_[hotelName] -= roomsCount;

        auto& curHotelClients = hotelsClientsCount_[hotelName];
        auto clientPos = curHotelClients.find(clientId);
        int clientPosVal = clientPos->second;
        --clientPos->second;
        if (clientPos->second == 0) {
            curHotelClients.erase(clientPos);
        }

        times_.erase(timesPos++);
        reservations_.erase(curReservation++);
    }
}

void BookingManager::book(int64_t time, const std::string& hotelName, int clientId,
                          int roomsCount) {
    dayBegin_ = time - 86400;
    if (oldestTime_ <= dayBegin_) {
        cleanOldData();
    }

    times_.emplace_back(time);
    oldestTime_ = times_.front();
    reservations_.emplace_back(hotelName, clientId, roomsCount);
    hotelsRoomsCount_[hotelName] += roomsCount;
    ++hotelsClientsCount_[hotelName][clientId];
}

int BookingManager::rooms(const std::string& hotelName) const {
    if (hotelsRoomsCount_.count(hotelName) == 0) {
        return 0;
    }

    int roomsCount = 0;
    roomsCount = hotelsRoomsCount_.at(hotelName);

    return roomsCount;
}

int BookingManager::clients(const std::string& hotelName) const {
    if (hotelsClientsCount_.count(hotelName) == 0) {
        return 0;
    }

    int clientsCount = 0;
    clientsCount = hotelsClientsCount_.at(hotelName).size();

    return clientsCount;
}

void testAll();

int main() {
    std::list<int> sortedList;
    sortedList.sort();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    BookingManager manager;

#ifdef TEST
    TestRunner tr;
    tr.RunTest(testAll, "basic tests");
#else

    int queriesCount;
    std::cin >> queriesCount;

    for (int i = 0; i < queriesCount; ++i) {
        std::string query;
        std::cin >> query;
        std::string hotelName;

        if (query == "BOOK") {
            int64_t time;
            int clientId;
            int roomsCount;

            std::cin >> time >> hotelName >> clientId >> roomsCount;
            manager.book(time, hotelName, clientId, roomsCount);
        } else if (query == "CLIENTS") {
            std::cin >> hotelName;
            std::cout << manager.clients(hotelName) << "\n";
        } else if (query == "ROOMS") {
            std::cin >> hotelName;
            std::cout << manager.rooms(hotelName) << "\n";
        }
    }

#endif

    return 0;
}
#ifdef TEST
void testAll() {
    // border values
    {
        BookingManager bm;
        ASSERT_EQUAL(bm.clients("Marriott"), 0);
        ASSERT_EQUAL(bm.rooms("Marriott"), 0);
        bm.book(-1'000'000'000'000'000'000, "Marriott", 1'000'000'000, 1000);
        bm.book(-1'000'000'000'000'000'000, "Marriott", 1'000'000'000, 1000);
        bm.book(-1'000'000'000'000'000'000, "Marriott", 1'00'000'000, 1000);
        ASSERT_EQUAL(bm.clients("Marriott"), 2);
        ASSERT_EQUAL(bm.rooms("Marriott"), 3000);
        bm.book(1'000'000'000'000'000'000, "Marriott", 1'00'000'000, 1000);
        ASSERT_EQUAL(bm.clients("Marriott"), 1);
        ASSERT_EQUAL(bm.rooms("Marriott"), 1000);
        ASSERT_EQUAL(bm.clients("F"), 0);
        ASSERT_EQUAL(bm.rooms("F"), 0);
    }

    // first test
    {
        BookingManager bm;
        ASSERT_EQUAL(bm.clients("Marriott"), 0);
        ASSERT_EQUAL(bm.rooms("Marriott"), 0);
        bm.book(10, "FourSeasons", 1, 2);
        bm.book(10, "Marriott", 1, 1);
        bm.book(86409, "FourSeasons", 2, 1);
        ASSERT_EQUAL(bm.clients("FourSeasons"), 2);
        ASSERT_EQUAL(bm.rooms("FourSeasons"), 3);
        ASSERT_EQUAL(bm.clients("Marriott"), 1);
        bm.book(86410, "Marriott", 2, 10);
        ASSERT_EQUAL(bm.rooms("FourSeasons"), 1);
        ASSERT_EQUAL(bm.rooms("Marriott"), 10);
    }

    {
        BookingManager bm;
        ASSERT_EQUAL(bm.clients("Marriott"), 0);
        ASSERT_EQUAL(bm.rooms("Marriott"), 0);
        bm.book(-86400, "FourSeasons", 1, 2);
        ASSERT_EQUAL(bm.clients("FourSeasons"), 1);
        ASSERT_EQUAL(bm.rooms("FourSeasons"), 2);
        bm.book(-86400, "Marriott", 1, 1);
        bm.book(1234, "Marriott", 3, 2);
        bm.book(2222, "Marriott", 3, 3);
        bm.book(3333, "Marriott", 2, 2);
        bm.book(4567, "Marriott", 2, 3);
        ASSERT_EQUAL(bm.clients("Marriott"), 2);
        ASSERT_EQUAL(bm.rooms("Marriott"), 10);
        bm.book(86410, "Marriott", 1, 3);
        ASSERT_EQUAL(bm.clients("Marriott"), 3);
        ASSERT_EQUAL(bm.rooms("Marriott"), 13);
    }
    {
        BookingManager bm;
        ASSERT_EQUAL(bm.clients("Marriott"), 0);
        ASSERT_EQUAL(bm.rooms("Marriott"), 0);
        bm.book(0, "FourSeasons", 0, 1);
        ASSERT_EQUAL(bm.clients("FourSeasons"), 1);
        ASSERT_EQUAL(bm.rooms("FourSeasons"), 1);
    }

    {
        BookingManager bm;
        bm.book(0, "q", 0, 0);
        ASSERT_EQUAL(bm.clients("q"), 1);
        ASSERT_EQUAL(bm.rooms("q"), 0);
        bm.book(0, "q", 1, 0);
        ASSERT_EQUAL(bm.clients("q"), 2);
        ASSERT_EQUAL(bm.rooms("q"), 0);
        bm.book(0, "q", 0, 4);
        ASSERT_EQUAL(bm.clients("q"), 2);
        ASSERT_EQUAL(bm.rooms("q"), 4);
    }
    {
        BookingManager bm;

        // Test empty bookings
        ASSERT_EQUAL(bm.clients("mariott"), 0);
        ASSERT_EQUAL(bm.rooms("mariott"), 0);

        bm.book(0, "mariott", 1, 10);
        bm.book(0, "mariott", 2, 1);
        bm.book(0, "mariott", 3, 1);
        bm.book(0, "mariott", 4, 1);
        bm.book(0, "hilton", 1, 1);
        bm.book(1, "hilton", 2, 1);

        // Test correctness
        ASSERT_EQUAL(bm.clients("mariott"), 4);
        ASSERT_EQUAL(bm.rooms("mariott"), 13);
        ASSERT_EQUAL(bm.clients("hilton"), 2);
        ASSERT_EQUAL(bm.rooms("hilton"), 2);

        // Test event past 1 day resets statics
        bm.book(86400, "mariott", 1, 1);
        ASSERT_EQUAL(bm.clients("mariott"), 1);
        ASSERT_EQUAL(bm.rooms("mariott"), 1);
        ASSERT_EQUAL(bm.clients("hilton"), 1);
        ASSERT_EQUAL(bm.rooms("hilton"), 1);

        // Test no clients and room for the last day
        bm.book(86401, "mariott", 5, 1);
        ASSERT_EQUAL(bm.clients("mariott"), 2);
        ASSERT_EQUAL(bm.rooms("mariott"), 2);
        ASSERT_EQUAL(bm.clients("hilton"), 0);
        ASSERT_EQUAL(bm.rooms("hilton"), 0);
    }
}
#endif
