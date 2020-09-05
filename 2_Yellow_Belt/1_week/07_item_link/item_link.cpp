#include <stdexcept>
#include <iostream>
#include <string>
#include <map>

using namespace std;

template<typename Key, typename Value> Value& GetRefStrict(map<Key, Value>& m, Key k);

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key k) {
	if (!m.count(k))
		throw runtime_error("Runtime error: template<typename Key, typename Value> Value& GetRefStrict(map<Key, Value>& m, Key k)");
	return m[k];
}

int main () {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
	return 0;
}

/* авторское решение
#include <map>
#include <stdexcept>

template<typename KeyType, typename ValueType>
ValueType& GetRefStrict(map<KeyType, ValueType>& input_map, KeyType key) {
    if (input_map.count(key) == 0) {
        throw runtime_error("no such key in dictionary");
    }
    return input_map[key];
}
 */

