#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
	Person(const string& name, const string& profession) :
		Name(name), Profession(profession) {}

	virtual void Walk(const string& destination) const {
		cout << Intriduce() << " walks to: " << destination << endl;
	}

	const string Name;
	const string Profession;

protected:
	string Intriduce() const {
		return Profession + ": " + Name;
	}

	virtual ~Person() = default;
};

class Student : public Person {
public:
	Student(const string& name, const string& favouriteSong) :
		Person(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() const {
        cout << Intriduce() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
    	Person::Walk(destination);
    	SingSong();
    }

    void SingSong() const {
        cout << Intriduce() << " sings a song: " << FavouriteSong << endl;
    }

private:
    const string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject) :
    	Person(name, "Teacher"), Subject(subject) {}

    void Teach() const {
        cout << Intriduce() << " teaches: " << Subject << endl;
    }

private:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name) :
    	Person(name, "Policeman") {}

    void Check(const Person& people) const {
        cout << Intriduce() << " checks " << people.Profession <<
        		". " << people.Profession << "'s name is: " << people.Name << endl;
    }

};


void VisitPlaces(const Person& person, const vector<string>& places) {
    for (const string& place : places) {
    	person.Walk(place);
    }
}

int main() {
    Teacher teacher("Jim", "Math");
    Student student("Ann", "We will rock you");
    Policeman policeman("Bob");

    vector<string> city = {"Moscow", "London"};

    VisitPlaces(teacher, city);
    policeman.Check(student);
    VisitPlaces(student, city);

    return 0;
}

