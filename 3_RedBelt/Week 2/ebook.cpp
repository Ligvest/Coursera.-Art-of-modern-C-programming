//#define TEST
#ifdef TEST
#include <sstream>
#include "profiler.h"
#include "test_runner.h"
#endif
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;

class ReadingManager {
    int maxPages = 1000 + 1;
    std::map<int, int> users;          //<user id, pages>
    std::vector<int> lessUsersByPage;  //[pages], <count of users that less>

   public:
    ReadingManager() : lessUsersByPage(maxPages, 0) {}

    void incrementPages(int pages) {
        for (int i = pages + 1; i < lessUsersByPage.size(); ++i) {
            ++lessUsersByPage[i];
        }
    }

    void decrementPages(int pages) {
        for (int i = pages + 1; i < lessUsersByPage.size(); ++i) {
            --lessUsersByPage[i];
        }
    }

    void Read(int user_id, int page_count) {
        // remove prev readPages for the user_id
        if (users.count(user_id) > 0) {
            decrementPages(users.at(user_id));
        }

        // add new readPages for user_id
        users[user_id] = page_count;
        incrementPages(page_count);
    }

    double Cheer(int user_id) const {
        // if there is no such user
        if (users.count(user_id) == 0) {
            return 0;
        }

        // if there is only one user
        if (users.size() == 1) {
            return 1;
        }

        int pages = users.at(user_id);
        int lessUsers = lessUsersByPage[pages];
        int usersCount = users.size() - 1;
        return lessUsers * 1.0 / usersCount;
    }
};

#ifdef TEST
void TestReadPage() {
    {  // add user
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
        manager.Read(2, 2);
        ASSERT_EQUAL(manager.Cheer(2), 1.0);
        manager.Read(1, 2);
        ASSERT_EQUAL(manager.Cheer(2), 0);
        manager.Read(3, 1);
        ASSERT_EQUAL(manager.Cheer(3), 0);
        manager.Read(3, 3);
        ASSERT_EQUAL(manager.Cheer(3), 1);
    }
    {  // add user but cheer not existed
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
    }
    {  // read twice
        ReadingManager manager;
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        manager.Read(1, 2);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }
    {  // better than third
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        ASSERT_EQUAL(manager.Cheer(2), 0.5);
        manager.Read(4, 4);
        ASSERT_EQUAL(manager.Cheer(2), 1.0 / 3.0);
    }
    {  // better than 2 third
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        ASSERT_EQUAL(manager.Cheer(2), 0.5);
        manager.Read(4, 4);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }
    {  // read zero
        ReadingManager manager;
        manager.Read(1, 0);
        manager.Read(2, 0);
        manager.Read(3, 1);
        manager.Read(4, 2);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }
    {  // all read the same
        ReadingManager manager;
        manager.Read(1, 5);
        manager.Read(2, 5);
        manager.Read(3, 5);
        manager.Read(4, 5);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
    }
    {  // reverse order
        ReadingManager manager;
        manager.Read(4, 5);
        manager.Read(3, 4);
        manager.Read(2, 3);
        manager.Read(1, 2);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }
    {  // two users read two times
        ReadingManager manager;
        manager.Read(4, 5);
        manager.Read(3, 4);
        manager.Read(4, 6);
        manager.Read(3, 5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
        manager.Read(10, 2);
        ASSERT_EQUAL(manager.Cheer(3), 0.5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
    }
    {  // only one user
        ReadingManager manager;
        manager.Read(4, 5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        manager.Read(4, 6);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        manager.Read(4, 100);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
        ASSERT_EQUAL(manager.Cheer(5), 0.0);
    }
    {  // ten users
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        manager.Read(4, 4);
        manager.Read(5, 5);
        manager.Read(6, 6);
        manager.Read(7, 7);
        manager.Read(8, 8);
        manager.Read(9, 9);
        manager.Read(100, 10);
        manager.Read(111, 11);

        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.1);
        ASSERT_EQUAL(manager.Cheer(3), 0.2);
        ASSERT_EQUAL(manager.Cheer(4), 0.3);
        ASSERT_EQUAL(manager.Cheer(5), 0.4);
        ASSERT_EQUAL(manager.Cheer(6), 0.5);
        ASSERT_EQUAL(manager.Cheer(7), 0.6);
        ASSERT_EQUAL(manager.Cheer(8), 0.7);
        ASSERT_EQUAL(manager.Cheer(9), 0.8);
        ASSERT_EQUAL(manager.Cheer(100), 0.9);
        ASSERT_EQUAL(manager.Cheer(111), 1.0);
        ASSERT_EQUAL(manager.Cheer(12), 0.0);
    }
    {  // cheer twice
        ReadingManager manager;

        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);

        ASSERT_EQUAL(manager.Cheer(2), 0);
    }
    {  // max ID
        const int MAX_USER_COUNT = 100'000;
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0);
        manager.Read(MAX_USER_COUNT, 1);
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0);
    }
    {  // max page
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1000);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }
    {  // max ID and max page
        const int MAX_USER_COUNT = 100'000;
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0);
        manager.Read(MAX_USER_COUNT, 1000);
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0);
    }
    {  // zero ID
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(0), 0.0);
        manager.Read(0, 1000);
        ASSERT_EQUAL(manager.Cheer(0), 1.0);
    }
    {  // from coursera
       //
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(1, 3);
        manager.Read(2, 2);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
    }
}
#endif

int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ReadingManager manager;
#ifdef TEST
    TestRunner tr;
    tr.RunTest(TestReadPage, "Main test");

    std::istringstream is(

        "3\n"
        "READ 1 10\n"
        "READ 2 20\n"
        "CHEER 2");

    int query_count;
    is >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        is >> query_type;
        int user_id;
        is >> user_id;

        if (query_type == "READ") {
            int page_count;
            is >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    //    {
    //        std::map<int, int> test;
    //        for (int i = 0; i < 1000; ++i) {
    //            test[i] = i;
    //        }
    //        int pages = 1000;
    //        LOG_DURATION("1000 set")
    //        for (int i = 0; i < 100000; ++i) {
    //            for (auto pos = test.begin(); pos->first < 1000; ++pos) {
    //                pos->second = pos->first;
    //            }
    //        }
    //    }

    {
        LOG_DURATION("Cheer")
        for (int i = 0; i < 1000000; ++i) {
            manager.Cheer(1);
        }
    }

    {
        LOG_DURATION("Read")
        for (int i = 0; i < 10000; ++i) {
            manager.Read(i, i);
        }
    }
#else
    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
#endif

    return 0;
}
