//============================================================================
// Name        : inheritance
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include <iostream>

using namespace std;

#include <iostream>

using namespace std;

class Animal {
public:
	Animal(const string str) : Name(str) { }

    const string Name;
};

class Dog : public Animal {
public:
    Dog(const string str) : Animal(str) {}

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main() {
	Dog d("Ralf");
	d.Bark();
	return 0;
}

/* Авторское решение
#include <string>
#include <iostream>

using namespace std;

class Animal {
public:
  Animal(const string& name)
    : Name(name)
  {}

  const string Name;
};


class Dog : public Animal {
public:
  Dog(const string& name)
    : Animal(name)
  {}

  void Bark() {
        cout << Name << " barks: woof!" << endl;
  }
};
 */

