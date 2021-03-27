#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <tuple>
#include <set>
#include <unordered_set>
#include <deque>
#include <exception>

#include "test_runner.h"

class Booking {
public:
    Booking() {}

    void Book(const int64_t& time,const std::string& hotel_name,
              const int& client_id, const int& room_count) {
        current_time = time;
        if (!events.empty()) {
//            EraseOldTime();
        }

        events.push_back(Event(time, hotel_name, client_id, room_count));
        ++(clients_booking[hotel_name][client_id]);
        booking_rooms[hotel_name] += room_count;
        EraseOldTime();
    }

    int64_t Clients(const std::string& hotel_name) const {
        try {
            return clients_booking.at(hotel_name).size();
        }  catch (...) {
            return 0;
        }
    }

    int64_t Rooms(const std::string& hotel_name) const {
        try {
            return booking_rooms.at(hotel_name);
        }  catch (...) {
            return 0;
        }
    }

    struct Event{
        Event(const int64_t& time, const std::string& hotel_name,
              const int& client_id, const int& room_count):
              time(time), hotel_name(hotel_name),
              client_id(client_id), room_count(room_count) {}

        int64_t time = 0;
        std::string hotel_name;
        int client_id = 0;
        int room_count = 0;
    };

    const int SECOND_PER_DAY = 86'400;
    int64_t current_time = 0;
    std::deque<Event> events;
    std::unordered_map<std::string, int> booking_rooms;
    std::unordered_map<std::string, std::unordered_map<int, int>> clients_booking;

    void EraseOldTime() {
        while (!events.empty() && events.front().time <= current_time - SECOND_PER_DAY) {
            booking_rooms[events.front().hotel_name] -= events.front().room_count;
            --clients_booking[events.front().hotel_name][events.front().client_id];
            if ( clients_booking[events.front().hotel_name][events.front().client_id] == 0) {
                clients_booking.at(events.front().hotel_name).erase(events.front().client_id);
            } else if (clients_booking[events.front().hotel_name][events.front().client_id] < 0) {
                throw std::logic_error("out_of_range");
            }
            events.pop_front();
        }
    }
};

void TestBegin();
void TestBooking();
void TotalTest();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    TestRunner tr;

    tr.RunTest(TestBegin, "Test from condition");
    tr.RunTest(TestBooking, "Test class Booking");
    tr.RunTest(TotalTest, "Total test class Booking");

    Booking booking;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        std::string query_type;
        std::cin >> query_type;

        if (query_type == "BOOK") {
            long int time;
            std::string hotel_name;
            int client_id;
            int room_count;
            std::cin >> time >> hotel_name >> client_id >> room_count;
            booking.Book(time, hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS") {
            std::string hotel_name;
            std::cin >> hotel_name;
            std::cout << booking.Clients(hotel_name) << "\n";
        } else if (query_type == "ROOMS") {
            std::string hotel_name;
            std::cin >> hotel_name;
            std::cout << booking.Rooms(hotel_name) << "\n";
        }
    }

    return 0;
}

void TestBegin() {
    {
        Booking booking;
        ASSERT_EQUAL(booking.Clients("Marriott"), 0);
        ASSERT_EQUAL(booking.Rooms("Marriott"), 0);
        booking.Book(10, "FourSeasons", 1, 2);
        booking.Book(10, "Marriott", 1, 1);
        booking.Book(86409, "FourSeasons", 2, 1);
        ASSERT_EQUAL(booking.Clients("FourSeasons"), 2);
        ASSERT_EQUAL(booking.Rooms("FourSeasons"), 3);
        ASSERT_EQUAL(booking.Clients("Marriott"), 1);
        booking.Book(86410, "Marriott", 2, 10);
        ASSERT_EQUAL(booking.Rooms("FourSeasons"), 1);
        ASSERT_EQUAL(booking.Rooms("Marriott"), 10);
    }
}

void TestBooking() {
    {
        Booking booking;
        booking.Book(10, "FourSeasons", 1, 2);
        booking.Book(10, "Marriott", 1, 1);
        booking.Book(86409, "FourSeasons", 2, 1);
        booking.Book(86410, "Marriott", 2, 10);
        ASSERT_EQUAL(booking.Rooms("FourSeasons"), 1);
        ASSERT_EQUAL(booking.Rooms("Marriott"), 10);
        booking.Book(86411, "Marriott", 2, 2);
        booking.Book(86412, "Marriott", 2, 2);
        ASSERT_EQUAL(booking.Rooms("Marriott"), 14);
        ASSERT_EQUAL(booking.Clients("Marriott"), 1);
    }
    {
        Booking booking;
        booking.Book(1, "FourSeasons", 1, 2);
        booking.Book(2, "FourSeasons", 1, 2);
        booking.Book(3, "FourSeasons", 1, 2);
        booking.Book(864120, "FourSeasons", 2, 2);
        ASSERT_EQUAL(booking.Rooms("FourSeasons"), 2);
        ASSERT_EQUAL(booking.Clients("FourSeasons"), 1);
    }
}

void TotalTest() {
    {
        Booking manager;

        // Test empty bookings
        ASSERT_EQUAL(manager.Clients("Marriott"), 0);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 0);

        manager.Book(0, "Marriott", 1, 10);
        manager.Book(0, "Marriott", 2, 1);
        manager.Book(0, "Marriott", 3, 1);
        manager.Book(0, "Marriott", 4, 1);
        manager.Book(0, "FourSeasons", 1, 1);
        manager.Book(1, "FourSeasons", 2, 1);

        // Test correctness
        ASSERT_EQUAL(manager.Clients("Marriott"), 4);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 13);
        ASSERT_EQUAL(manager.Clients("FourSeasons"), 2);
        ASSERT_EQUAL(manager.Rooms("FourSeasons"), 2);

        // Test event past 1 day resets statics
        manager.Book(86400, "Marriott", 1, 1);
        ASSERT_EQUAL(manager.Clients("Marriott"), 1);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 1);
        ASSERT_EQUAL(manager.Clients("FourSeasons"), 1);
        ASSERT_EQUAL(manager.Rooms("FourSeasons"), 1);

        // Test no clients and room for the last day
        manager.Book(86401, "Marriott", 5, 1);
        ASSERT_EQUAL(manager.Clients("Marriott"), 2);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 2);
        ASSERT_EQUAL(manager.Clients("FourSeasons"), 0);
        ASSERT_EQUAL(manager.Rooms("FourSeasons"), 0);
    }

    {
        Booking manager;

        manager.Book(1, "Marriott", 1, 1);
        manager.Book(2, "Marriott", 1, 1);
        manager.Book(3, "Marriott", 1, 1);
        ASSERT_EQUAL(manager.Clients("Marriott"), 1);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 3);
    }

    {
        Booking manager;

        // Test from example
        ASSERT_EQUAL(manager.Clients("Marriott"), 0);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 0);
        manager.Book(10, "FourSeasons", 1, 2);
        manager.Book(10, "Marriott", 1, 1);
        manager.Book(86409, "FourSeasons", 2, 1);
        ASSERT_EQUAL(manager.Clients("FourSeasons"), 2);
        ASSERT_EQUAL(manager.Rooms("FourSeasons"), 3);
        ASSERT_EQUAL(manager.Clients("Marriott"), 1);
        manager.Book(86410, "Marriott", 2, 10);
        ASSERT_EQUAL(manager.Rooms("FourSeasons"), 1);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 10);
    }
}

/*
#include <cstdint>
#include <iostream>
#include <map>
#include <queue>

using namespace std;


class HotelManager {
public:
  void Book(int64_t time, const string& hotel_name,
            int client_id, int room_count) {
    current_time_ = time;
    hotels_[hotel_name].Book({time, client_id, room_count});
  }
  int ComputeClientCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeClientCount(current_time_);
  }
  int ComputeRoomCount(const string& hotel_name) {
    return hotels_[hotel_name].ComputeRoomCount(current_time_);
  }

private:
  struct Booking {
    int64_t time;
    int client_id;
    int room_count;
  };

  class HotelInfo {
  public:
    void Book(const Booking& booking) {
      last_bookings_.push(booking);
      room_count_ += booking.room_count;
      ++client_booking_counts_[booking.client_id];
    }
    int ComputeClientCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return client_booking_counts_.size();
    }
    int ComputeRoomCount(int64_t current_time) {
      RemoveOldBookings(current_time);
      return room_count_;
    }
  private:
    static const int TIME_WINDOW_SIZE = 86400;
    queue<Booking> last_bookings_;
    int room_count_ = 0;
    map<int, int> client_booking_counts_;

    void PopBooking() {
      const Booking& booking = last_bookings_.front();
      room_count_ -= booking.room_count;
      const auto client_stat_it =
          client_booking_counts_.find(booking.client_id);
      if (--client_stat_it->second == 0) {
        client_booking_counts_.erase(client_stat_it);
      }
      last_bookings_.pop();
    }
    void RemoveOldBookings(int64_t current_time) {
      while (
          !last_bookings_.empty()
          && last_bookings_.front().time <= current_time - TIME_WINDOW_SIZE
      ) {
        PopBooking();
      }
    }
  };

  int64_t current_time_ = 0;
  map<string, HotelInfo> hotels_;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  HotelManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      int64_t time;
      cin >> time;
      string hotel_name;
      cin >> hotel_name;
      int client_id, room_count;
      cin >> client_id >> room_count;
      manager.Book(time, hotel_name, client_id, room_count);
    } else {
      string hotel_name;
      cin >> hotel_name;
      if (query_type == "CLIENTS") {
        cout << manager.ComputeClientCount(hotel_name) << "\n";
      } else if (query_type == "ROOMS") {
        cout << manager.ComputeRoomCount(hotel_name) << "\n";
      }
    }
  }

  return 0;
}
*/
