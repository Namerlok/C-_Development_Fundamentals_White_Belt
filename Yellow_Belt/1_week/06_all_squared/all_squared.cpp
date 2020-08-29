#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

template<typename T> T Sqr(T val);
template<typename All> vector<All> Sqr(vector<All> v);
template<typename Key, typename Value> map<Key, Value> Sqr(map<Key, Value> m);
template<typename First, typename Second> pair<First, Second> Sqr(pair<First, Second> p);

template<typename T>
T Sqr(T val) {
	return val * val;
}

template<typename All>
vector<All> Sqr(vector<All> v) {
	for (auto& i: v)
		i = Sqr(i);
	return v;
}

template<typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> m) {
	for(auto& i: m)
		i.second = Sqr(i.second);
	return m;
}

template<typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> p) {
	p.first = Sqr(p.first);
	p.second = Sqr(p.second);
	return p;
}

int main() {
	// Пример вызова функции
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
	  cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}

/* образцовое решение
// Объявим функции без тела,
// чтобы их можно было использовать в произвольном порядке

// Для простых типов
template<typename T>
T Sqr(T value);

// Для вектора
template<typename T>
vector<T> Sqr(const vector<T>& value);

// Для словаря
template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value);

// Для пары
template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value);

// Теперь реализуем их в соответствии с заданием
template<typename T>
T Sqr(T value) {
  return value * value;
}

template<typename T>
vector<T> Sqr(const vector<T>& value) {
  vector<T> result;
  for (const T& x : value) {
    // Здесь важно, что вместо x * x вызывается функция Sqr:
    // это позволяет возводить в квадрат составные объекты
    result.push_back(Sqr(x));
  }

  return result;
}

template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value) {
  map<K, V> result;
  for (const auto& element : value) {
    result[element.first] = Sqr(element.second);
  }
  return result;
}

template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value) {
  return {Sqr(value.first), Sqr(value.second)};
}
 */
