#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <string>
using namespace std;

class  Vehicle {
protected:
   string brand;
   int month, year;
public:
   Vehicle(string b, int m, int y);
   virtual ~Vehicle(){};
   int getYear() const;
   int getMonth() const;
   string getBrand() const;
   virtual int info() const;
   virtual int info(ostream &o) const;
   bool operator < (const Vehicle & v) const;
   virtual float calculateTax() const = 0;
};

class MotorVehicle: public Vehicle {
    string fuel; int cylinder;
public:
    MotorVehicle(string b, int m, int y,string f,int cyl);

    string getFuel() const;
    virtual int info() const;
    virtual int info(ostream &o) const;
    float calculateTax() const;
};


class Car: public MotorVehicle {
public:
    Car(string b, int m, int y, string f, int cyl);
    int info() const;
    int info(ostream &o) const;
};


class Truck: public MotorVehicle {
    int maximumLoad;
public:
    Truck(string b, int m, int y,string f, int cyl,int ml);
    int info() const;
    int info(ostream &o) const;
};


class Bicycle: public Vehicle {
    string type;
public:
    Bicycle(string b, int m, int y, string t);
    int info() const;
    int info(ostream &o) const;
    float calculateTax() const;
};

#endif /* VEHICLE_H_ */
