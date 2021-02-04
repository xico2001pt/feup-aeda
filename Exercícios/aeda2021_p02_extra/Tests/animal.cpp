#include "animal.h"
#include <sstream>
using namespace std;

// Class Animal
int Animal::youngest = 99999;

Animal::Animal(string name, int age) : name(name), age(age), vet(NULL) {
    if (age < youngest)
        youngest = age;
}

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

int Animal::getYoungest() {
    return youngest;
}

string Animal::getInfo() const {
    string vetInfo = "";
    if (vet)
        vetInfo = ", " + vet->getInfo();
    return name + ", " + to_string(age) + vetInfo;
}

// Class Dog
Dog::Dog(string name, int age, string breed) : Animal(name, age), breed(breed){
}

bool Dog::isYoung() const {
    return age < 5;
}

string Dog::getInfo() const {
    return Animal::getInfo() + ", " + breed;
}

// Class Flying
Flying::Flying(int maxv, int maxa) : maxVelocity(maxv), maxAltitude(maxa) {
}

string Flying::getInfo() const {
    return to_string(maxVelocity) + ", " + to_string(maxAltitude);
}

// Class Bat
Bat::Bat(string name, int age, int maxv, int maxa) : Animal(name, age), Flying(maxv, maxa){
}

bool Bat::isYoung() const {
    return age < 4;
}

string Bat::getInfo() const {
    return Animal::getInfo() + ", " + Flying::getInfo();
}