//#define TEST
#ifdef TEST
#include <profiler.h>
#include <sstream>
#endif

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class RouteManager {
   public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }
    int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);
        if (reachable_lists_.count(start) < 1) {
            return result;
        }
        const set<int>& reachable_stations = reachable_lists_.at(start);
        if (reachable_stations.size() == 1) {
            result = min(result, abs(*reachable_stations.begin() - finish));
        } else if (reachable_stations.size() > 1) {
            int minDistance;
            auto low = reachable_stations.lower_bound(finish);
            if (low == reachable_stations.end()) {
                minDistance = abs(*std::prev(low) - finish);
            } else if (low == reachable_stations.begin()) {
                minDistance = abs(*low - finish);
            } else {
                minDistance = std::min(std::abs(*low - finish), abs(*std::prev(low) - finish));
            }

            result = min(result, minDistance);
        }
        return result;
    }

   private:
    map<int, set<int>> reachable_lists_;
};

int main() {
    RouteManager routes;
#ifdef TEST
    std::istringstream is(
        "7\n"
        "ADD -2 5\n"
        "ADD 10 4\n"
        "ADD 5 8\n"
        "GO 4 10\n"
        "GO 4 -2\n"
        "GO 5 0\n"
        "GO 5 100");

    int query_count;
    is >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        is >> query_type;
        int start, finish;
        is >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    {
        LOG_DURATION("Main loop")
        for (int i = 0; i < 1000000; ++i) {
            routes.FindNearestFinish(5, 4);
        }
    }
#else
    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }
#endif

    return 0;
}
