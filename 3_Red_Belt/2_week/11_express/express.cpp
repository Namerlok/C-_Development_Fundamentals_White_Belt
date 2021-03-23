#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "profile.h"
#include "test_runner.h"

class RouteManager {
public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }

    int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);

        if (reachable_lists_.count(start) < 1)
            return result;

        const std::set<int>& reachable_stations = reachable_lists_.at(start);
        if (!reachable_stations.empty()) {
            auto lower_bound_finish = reachable_stations.lower_bound(finish);
            if(lower_bound_finish != reachable_stations.end())
                result = std::min(abs(finish - *lower_bound_finish), abs(finish - start));
            if (lower_bound_finish != reachable_stations.begin())
                result = std::min(result, abs(finish - *prev(lower_bound_finish)));
//            result = std::min( result,
//                abs(finish - *min_element( begin(reachable_stations), end(reachable_stations),
//                [finish](int lhs, int rhs) { return abs(lhs - finish) < abs(rhs - finish); } )));
        }
        return result;
    }

private:
    std::map<int, std::set<int>> reachable_lists_;
};


void TestGO() {
    {
        RouteManager routes;
        routes.AddRoute(-2, 5);
        routes.AddRoute(10, 4);
        routes.AddRoute(5, 8);
        ASSERT_EQUAL(routes.FindNearestFinish(4, 10), 0);
        ASSERT_EQUAL(routes.FindNearestFinish(4, -2), 6);
        ASSERT_EQUAL(routes.FindNearestFinish(5, 0), 2);
        ASSERT_EQUAL(routes.FindNearestFinish(5, 100), 92);
    }
    {
        RouteManager routes;
        routes.AddRoute(-2, 4);
        ASSERT_EQUAL(routes.FindNearestFinish(-2, 0), 2);
        ASSERT_EQUAL(routes.FindNearestFinish(-2, -4), 2);
        ASSERT_EQUAL(routes.FindNearestFinish(-2, 3), 1);
        ASSERT_EQUAL(routes.FindNearestFinish(-2, 4), 0);
        ASSERT_EQUAL(routes.FindNearestFinish(-2, 1), 3);
        ASSERT_EQUAL(routes.FindNearestFinish(-2, -8), 6);
    }

}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestGO);


    RouteManager routes;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        std::string query_type;
        std::cin >> query_type;
        int start, finish;
        std::cin >> start >> finish;
        if (query_type == "ADD") {
            {
                //LOG_DURATION("test AddRoute");
                routes.AddRoute(start, finish);
            }
        } else if (query_type == "GO") {
            {
                //LOG_DURATION("test FindNearestFinish");
                std::cout << routes.FindNearestFinish(start, finish) << "\n";
            }
        }
    }

    return 0;
}
