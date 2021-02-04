#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

Zoo::~Zoo() {
    for (int index = 0; index < veterinarians.size(); index++)
        delete veterinarians.at(index);
}

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

string Zoo::getInfo() const {
    string result = "";
    for (Animal * an : animals) {
        result += an->getInfo() + ", ";
    }
    return result;
}

bool Zoo::isYoung(string nameA) {
    for (Animal * an : animals)
        if (an->getName() == nameA && an->isYoung())
            return true;
    return false;
}

void Zoo::allocateVeterinarians(istream &isV) {
    string name, codStr;
    int numVet = 0;
    while (!isV.eof()) {
        getline(isV, name);
        getline(isV, codStr);
        Veterinary * vt = new Veterinary(name, stoi(codStr));
        veterinarians.push_back(vt);
        ++numVet;
    }
    for (int index = 0; index < animals.size(); index++)
        animals.at(index)->setVeterinary(veterinarians.at(index % numVet));
}

bool Zoo::removeVeterinary(string nameV) {
    Veterinary * vt;
    int index;
    for (index = 0; index < veterinarians.size(); index++)
        if (veterinarians.at(index)->getName() == nameV) {
            vt = veterinarians.at(index);
            break;
        }
    if (index == veterinarians.size())
        return false;
    for (Animal * an : animals)
        if (an->getVeterinary() == vt)
            an->setVeterinary(veterinarians.at((index + 1) % veterinarians.size()));
    veterinarians.erase(veterinarians.begin() + index);
    return true;
}

bool Zoo::operator < (Zoo& zoo2) const {
    int ages1 = 0, ages2 = 0;
    for (Animal * an : animals)
        ages1 += an->getAge();
    for (Animal * an : zoo2.animals)
        ages2 += an->getAge();
    return ages1 < ages2;
}