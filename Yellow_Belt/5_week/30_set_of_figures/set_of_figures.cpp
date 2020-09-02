//============================================================================
// Name        : set_of_figures
// Author      : Namerlok
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
protected:
	virtual ~Figure() {}
};

class Rect : public Figure {
public:
	Rect(int w, int h) : width(w), height(h) {}

	virtual string Name() const override {
		return "RECT";
	}

	virtual double Perimeter() const override {
		return static_cast<double>(2 * width + 2 * height);
	}

	virtual double Area() const override {
		return static_cast<double>(width * height);
	}

private:
	const int width;
	const int height;
};

class Triangle : public Figure {
public:
	Triangle(int a_, int b_, int c_) : a(a_), b(b_), c(c_) {}

	virtual string Name() const override {
		return "TRIANGLE";
	}

	virtual double Perimeter() const override {
		return static_cast<double>(a + b + c);
	}

	virtual double Area() const override {
		double pol_per = Perimeter() / 2;
		return sqrt(pol_per *
				(pol_per - static_cast<double>(a)) *
				(pol_per - static_cast<double>(b)) *
				(pol_per - static_cast<double>(c)));
	}

private:
	const int a, b, c;
};

class Circle : public Figure {
public:
	Circle(int R) : r(R) {}

	virtual string Name() const override {
		return "CIRCLE";
	}

	virtual double Perimeter() const override {
		return pi * static_cast<double>(2 * r);
	}

	virtual double Area() const override {
		return pi * static_cast<double>(r * r);
	}

private:
	const int r;
	const double pi = 3.14;
};

shared_ptr<Figure> CreateFigure(istream& is) {
	string is_figure = "";
	shared_ptr<Figure> figure;
	is >> is_figure;

	if (is_figure == "RECT") {
		int w = 0, h = 0;
		is >> w >> h;
		figure = make_shared<Rect>(w, h);
	} else if (is_figure == "TRIANGLE") {
		int a = 0, b = 0, c = 0;
		is >> a >> b >> c;
		figure = make_shared<Triangle>(a, b, c);
	} else if (is_figure == "CIRCLE") {
		int R = 0;
		is >> R;
		figure = make_shared<Circle>(R);
	} else {
		cerr << "undefined figure: " << is_figure << endl;
	}
	return figure;
}

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			// Пропускаем "лишние" ведущие пробелы.
			// Подробнее об std::ws можно узнать здесь:
			// https://en.cppreference.com/w/cpp/io/manip/ws
			is >> ws;
			figures.push_back(CreateFigure(is));
		} else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	return 0;
}

/* авторское решение
#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const float pi = 3.14;

class Figure {
public:
  Figure(const string& type)
      : Type(type) {}

  virtual string Name() = 0;
  virtual float Perimeter() = 0;
  virtual long double Area() = 0;

  // Виртуальный деструктор.
  // При отсутствии проблем компиляции данного решения строка не является
  // необходимой и может быть опущена.
  // А вот что такое виртуальный деструктор - Вы узнаете уже на черном поясе.
  virtual ~Figure() = default;

  const string Type;
};

class Rect : public Figure {
public:
  Rect(int& w, int& h)
      : Figure("RECT")
      , P(2 * w + 2 * h)
      , S(w * h) {
  }

  float Perimeter() override {
    return P;
  }
  long double Area() override {
    return S;
  }
  string Name() override {
    return Type;
  }
private:
  int P;
  double S;
};

class Circle : public Figure {
public:
  Circle (int& r)
      : Figure("CIRCLE")
      , P(2 * pi * r)
      , S(pi * r * r) {}

  float Perimeter() override {
    return P;
  }
  long double Area() override {
    return S;
  }
  string Name() override {
    return Type;
  }
private:
  float P;
  double S;
};

class Triangle : public Figure {
public:
  Triangle(int& a, int& b, int& c)
      : Figure("TRIANGLE") {
    P = a + b + c;
    S = sqrtl((P/2)*(P/2 - a)*(P/2 - b)*(P/2 - c));
  }

  float Perimeter() override {
    return P;
  }
  long double Area() override {
    return S;
  }
  string Name() override {
    return Type;
  }
private:
  float P;
  long double S;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
  shared_ptr<Figure> fig;

  string figure_name;
  is >> figure_name;
  if(figure_name == "RECT") {
    int a, b;
    is >> a >> b;
    fig = make_shared<Rect>(a, b);
    return fig;
  }
  if (figure_name == "TRIANGLE") {
    int a, b, c;
    is >> a >> b >> c;
    fig = make_shared<Triangle>(a, b, c);
    return fig;
  }
  if (figure_name == "CIRCLE") {
    int r;
    is >> r;
    fig = make_shared<Circle>(r);
    return fig;
  }
  throw std::invalid_argument("invalid figure name was specified");
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
*/

