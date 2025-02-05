#include <iostream>
#include <vector>
using namespace std;

class Animal {
protected:
    string name;
    int age;
public:
    virtual ~Animal() = default;

    Animal(string& name, int age) {
        this->name = name;
        this->age = age;
    }

    const int getAge() { return age; }
    string getName() { return name; }
    void setAge(int age) { this->age = age; }
    void setName(string& name) { this->name = name; }

    virtual void makeSound() = 0;
};

class LandAnimal : virtual public Animal {
public:
    LandAnimal(string name, int age) : Animal(name, age) {}
    void makeSound() override {
        cout << "Land sounds" << endl;
    }
    virtual void walk() {
        cout << "Walk" << endl;
    }
};

class WaterAnimal : virtual public Animal {
public:
    WaterAnimal(string name, int age) : Animal(name, age) {}
    void makeSound() override {
        cout << "Water sounds" << endl;
    }
    virtual void swim() {
        cout << "Swim" << endl;
    }
};

class Lion : public LandAnimal {
public:
    Lion(string name, int age) : Animal(name, age), LandAnimal(name, age) {}
    void makeSound() override {
        cout << "Roar" << endl;
    }
    void walk() override {
        cout << "Lion walks" << endl;
    }
};

class Dolphin : public WaterAnimal {
public:
    Dolphin(string name, int age) : Animal(name, age), WaterAnimal(name, age) {}
    void makeSound() override {
        cout << "Dolphin sounds" << endl;
    }
    void swim() override {
        cout << "Dolphin swims" << endl;
    }
};

class Frog : public LandAnimal, public WaterAnimal {
public:
    Frog(string name, int age) : Animal(name, age), LandAnimal(name, age), WaterAnimal(name, age) {}

    void makeSound() override {
        cout << "Frog croaks" << endl;
    }
    void swim() override {
        cout << "Frog swims" << endl;
    }
    void walk() override {
        cout << "Frog hops" << endl;
    }
};

int main() {
    vector<Animal*> animals;
    animals.push_back(new Lion("Lion", 20));
    animals.push_back(new Dolphin("Dolphin", 21));
    animals.push_back(new Frog("Frog", 1));

    for (Animal* animal : animals) {
        animal->makeSound();
    }

    for (Animal* animal : animals) {
        delete animal;
    }
}
