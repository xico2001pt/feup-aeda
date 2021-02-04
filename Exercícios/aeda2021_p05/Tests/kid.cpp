#include "kid.h"

Kid::Kid(): name(""), age(0)
{}

Kid::Kid(string nm, unsigned a): name(nm), age(a)
{}

Kid::Kid(const Kid& k1)
{
    this->name = k1.name;
    this->age = k1.age;
}

string Kid::getName() const
{
    return this->name;
}

unsigned Kid::getAge() const
{
    return this->age;
}

bool Kid::operator==(const Kid& k2) const
{
    return( this->name == k2.name && this->age == k2.age);
}


string Kid::write() const
{
    stringstream oss;
    oss << name << " : " << age;
    return oss.str();
}



