#include "vehicle.h"
#include <iostream>

using namespace std;

// Class Vehicle
Vehicle::Vehicle(string b, int m, int y) : brand(b), month(m), year(y) {
}

int Vehicle::getYear() const {
    return year;
}

int Vehicle::getMonth() const {
    return month;
}

string Vehicle::getBrand() const {
    return brand;
}

int Vehicle::info() const {
    return info(cout);
}

int Vehicle::info(ostream &o) const {
    o << "Brand: " << brand << endl << "Year: " << year << endl << "Month: " << month << endl;
    return 3;
}

bool Vehicle::operator < (const Vehicle & v) const {
    if (year < v.getYear())
        return true;
    else if (year == v.getYear())
        return month < v.getMonth();
    else
        return false;
}

// Class MotorVehicle
MotorVehicle::MotorVehicle(string b, int m, int y,string f,int cyl) : Vehicle(b, m, y), fuel(f), cylinder(cyl) {
}

string MotorVehicle::getFuel() const {
    return fuel;
}

int MotorVehicle::info() const {
    return info(cout);
}

int MotorVehicle::info(ostream &o) const {
    o << "Fuel: " << fuel << endl << "Cylinder: " << cylinder << endl;
    return Vehicle::info(o) + 2;
}

float MotorVehicle::calculateTax() const {
    float prices[2][6] = {{8.10, 14.56, 22.65, 54.89, 87.13, 148.37}, {14.56, 29.06, 45.15, 113.98, 181.17, 320.89}};
    bool greaterThan1995 = year > 1995;
    int index;
    if (fuel == "gas") {
        if (cylinder <= 1000) index = 0;
        else if (cylinder <= 1300) index = 1;
        else if (cylinder <= 1750) index = 2;
        else if (cylinder <= 2600) index = 3;
        else if (cylinder <= 3500) index = 4;
        else index = 5;
    }
    else {
        if (cylinder <= 1500) index = 0;
        else if (cylinder <= 2000) index = 1;
        else if (cylinder <= 3000) index = 2;
        else index = 3;
    }
    return prices[greaterThan1995][index];
}

// Class Car
Car::Car(string b, int m, int y, string f, int cyl) : MotorVehicle(b, m, y, f, cyl) {
}

int Car::info() const {
    return info(cout);
}

int Car::info(ostream &o) const {
    return MotorVehicle::info(o);
}

// Class Truck
Truck::Truck(string b, int m, int y,string f, int cyl,int ml) : MotorVehicle(b, m, y, f, cyl), maximumLoad(ml) {
}

int Truck::info() const {
    return info(cout);
}

int Truck::info(ostream &o) const {
    o << "Maximum load: " << maximumLoad << endl;
    return MotorVehicle::info(o) + 1;
}

// Class Bicycle
Bicycle::Bicycle(string b, int m, int y, string t) : Vehicle(b, m, y), type(t) {
}

int Bicycle::info() const {
    return info(cout);
}

int Bicycle::info(ostream &o) const {
    o << "Type: " << type << endl;
    return Vehicle::info(o) + 1;
}

float Bicycle::calculateTax() const {
    return 0;
}