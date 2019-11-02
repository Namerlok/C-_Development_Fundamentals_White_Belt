#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <set>

using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
	Date (const int& new_year, const int& new_month, const int& new_day) {
		year = new_year;
		if (new_month >= 1 && new_month <= 12) {
			month = new_month;
		} else {
			cout << "Month value is invalid: " << new_month << endl;
			throw runtime_error("EROOR: Month value is invalid");
		}
		if (new_day >= 1 && new_day <= 31) {
			day = new_day;
		} else {
			cout << "Day value is invalid: " << new_day << endl;
			throw runtime_error("EROOR: Day value is invalid");
		}
	}
	int GetYear () const {
		return year;
	}
	int GetMonth () const {
		return month;
	}
	int GetDay () const {
		return day;
	}
private:
	int year = 0;
	int month = 0;
	int day = 0;
};

bool operator< (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear())
		return true;
	else if (lhs.GetYear() > rhs.GetYear())
		return false;

	if (lhs.GetMonth() < rhs.GetMonth())
		return true;
	else if (lhs.GetMonth() > rhs.GetMonth())
		return false;

	if (lhs.GetDay() < rhs.GetDay())
		return true;
	else
		return false;
}

ostream& operator << (ostream& out, const Date& date) {

	out << setfill('0');
	out << setw(4) << date.GetYear() << '-' <<
		   setw(2) << date.GetMonth() << '-' <<
		   setw(2) << date.GetDay();
	return out;
}

class Database {
public:
	void AddEvent (const Date& date, const string& event) {
		data_base[date].insert(event);
	}
	bool DeleteEvent (const Date& date, const string& event) {
/*
		if (data_base.count(date)) {
			if (data_base.at(date).find(event) != data_base.at(date).end()) {
				data_base.at(date).erase(event);
				return true;
			} else
				return false;
		} else {
			return true;
		}
*/
		if(data_base.count(date) > 0 && data_base[date].count(event) > 0) {
			data_base[date].erase(event);
			return true;
		} else {
			return false;
		}
	}
	int  DeleteDate (const Date& date) {
		int size = 0;

		try {
			size = data_base.at(date).size();
		} catch (out_of_range &) {
			return 0;
		}
		data_base.erase(date);
		return size;
	}
	string Find (const Date& date) const {
		if (data_base.count(date)) {
			string strout;
			set<string> event = data_base.at(date);

			for (const auto& iter : event) {
				strout += iter + '\n';
			}
			return strout;
		}
		return "";
	}

	void Print () const {
		for (const auto& itermap : data_base) {
			for (const auto& iterset : itermap.second) {
				cout << itermap.first << " " << iterset << endl;
			}
		}
	}
private:
	map<Date, set<string>> data_base;
};

void skip (const string& command, int s ) {
	cout << "Wrong date format: ";
	while (!isspace(command[s]) && command[s] != '\0') {
		cout << command[s++];
	}
	cout << endl;
	throw runtime_error("Wrong date format");
}

void scanf_data (const string& command, int& year, int& month, int& day, int& i) {
	while (isspace(command[i]))
		i++;
	int s = i, sign = (command[i] == '-') ? -1 : 1;

	if (command[i] == '-' || command[i] == '+') i++;
	if (!isdigit(command[i]))
		skip (command, s);
	for ( ; isdigit(command[i]); i++)
		year = year * 10 + command[i] - '0';
	year *= sign;
	if (command[i] != '-')
		skip (command, s);
	else
		i++;

	sign = (command[i] == '-') ? -1 : 1;
	if (command[i] == '-' || command[i] == '+') i++;
	if (!isdigit(command[i]))
		skip (command, s);
	for ( ; isdigit(command[i]); i++)
		month = month * 10 + command[i] - '0';
	month *= sign;
	if (command[i] != '-')
		skip (command, s);
	else
		i++;

	sign = (command[i] == '-') ? -1 : 1;
	if (command[i] == '-' || command[i] == '+') i++;
	if (!isdigit(command[i]))
		skip (command, s);
	for ( ; isdigit(command[i]); i++)
		day = day * 10 + command[i] - '0';
	day *= sign;
	if (command[i] != ' ' && command[i] != '\0' && command[i] != '\n')
		skip (command, s);

	while (isspace(command[i]))
		i++;
}

int main () {
	Database db;

	string command;
	while (getline (cin, command)) {
		// Считайте команды с потока ввода и обработайте каждую
		try {
			int i = 0;
			string com;

			while (isspace(command[i]))
				i++;
			if (command[i] != '\0') {
				for ( ; !isspace(command[i]) && command[i] != '\0'; i++)
					com += command[i];

				if (com == "Add") {
					int year = 0, month = 0, day = 0;
					scanf_data (command, year, month, day, i);

					string event = &(command[i]);

					db.AddEvent (Date(year, month, day), event);

				} else if (com == "Del") {
					int year = 0, month = 0, day = 0;
					scanf_data (command, year, month, day, i);

					if (command[i] == '\0') {
						int i = db.DeleteDate (Date(year, month, day));
						cout << "Deleted " << i << " events\n";
					} else {
						string event = &(command[i]);

						if (db.DeleteEvent (Date(year, month, day), event))
							cout << "Deleted successfully\n";
						else
							cout << "Event not found\n";
					}
				} else if (com == "Find") {
					int year = 0, month = 0, day = 0;
					scanf_data (command, year, month, day, i);

					string y = db.Find(Date(year, month, day));
					cout << y;
				} else if (com == "Print") {
					db.Print();
				} else {
					cout << "Unknown command: " << com << endl;
					return 1;
				}
			}
		} catch (exception&) {
			return 2;
		}
	}

	return 0;
}

/*
Add 0-1-2 event1
Add 0-1-2 event2
Add 1-1-2 event1
Add 1-1-2 event2
Add 1-1-2aa event2
Add 1--1-2 event2
Add 1---1-2 event2
 */

/* expert answer

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class Date {
public:
  // конструктор выбрасывает исключение, если его аргументы некорректны
  Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
      throw logic_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
      throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
  }

  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const {
    return day;
  }

private:
  int year;
  int month;
  int day;
};

// определить сравнение для дат необходимо для использования их в качестве ключей словаря
bool operator<(const Date& lhs, const Date& rhs) {
  // воспользуемся тем фактом, что векторы уже можно сравнивать на <:
  // создадим вектор из года, месяца и дня для каждой даты и сравним их
  return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

// даты будут по умолчанию выводиться в нужном формате
ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    storage[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event) {
    if (storage.count(date) > 0 && storage[date].count(event) > 0) {
      storage[date].erase(event);
      return true;
    }
    return false;
  }

  int DeleteDate(const Date& date) {
    if (storage.count(date) == 0) {
      return 0;
    } else {
      const int event_count = storage[date].size();
      storage.erase(date);
      return event_count;
    }
  }

  set<string> Find(const Date& date) const {
    if (storage.count(date) > 0) {
      return storage.at(date);
    } else {
      return {};
    }
  }

  void Print() const {
    for (const auto& item : storage) {
      for (const string& event : item.second) {
        cout << item.first << " " << event << endl;
      }
    }
  }

private:
  map<Date, set<string>> storage;
};

Date ParseDate(const string& date) {
  istringstream date_stream(date);
  bool ok = true;

  int year;
  ok = ok && (date_stream >> year);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int month;
  ok = ok && (date_stream >> month);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int day;
  ok = ok && (date_stream >> day);
  ok = ok && date_stream.eof();

  if (!ok) {
    throw logic_error("Wrong date format: " + date);
  }
  return Date(year, month, day);
}

int main() {
  try {
    Database db;

    string command_line;
    while (getline(cin, command_line)) {
      stringstream ss(command_line);

      string command;
      ss >> command;

      if (command == "Add") {

        string date_str, event;
        ss >> date_str >> event;
        const Date date = ParseDate(date_str);
        db.AddEvent(date, event);

      } else if (command == "Del") {

        string date_str;
        ss >> date_str;
        string event;
        if (!ss.eof()) {
          ss >> event;
        }
        const Date date = ParseDate(date_str);
        if (event.empty()) {
          const int count = db.DeleteDate(date);
          cout << "Deleted " << count << " events" << endl;
        } else {
          if (db.DeleteEvent(date, event)) {
            cout << "Deleted successfully" << endl;
          } else {
            cout << "Event not found" << endl;
          }
        }

      } else if (command == "Find") {

        string date_str;
        ss >> date_str;
        const Date date = ParseDate(date_str);
        for (const string& event : db.Find(date)) {
          cout << event << endl;
        }

      } else if (command == "Print") {

        db.Print();

      } else if (!command.empty()) {

        throw logic_error("Unknown command: " + command);

      }
    }
  } catch (const exception& e) {
    cout << e.what() << endl;
  }

  return 0;
}


 */
