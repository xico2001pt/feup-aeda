#include "fleet.h"
#include <string>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

int Fleet::numVehicles() const {
    return vehicles.size();
}

int Fleet::lowestYear() const {
    int size = vehicles.size();
    if (size == 0) return 0;
    int lowestIndex = 0;
    for (int index = 1; index < size; index++)
        if (vehicles.at(index)->getYear() < vehicles.at(lowestIndex)->getYear())
            lowestIndex = index;
    return vehicles.at(lowestIndex)->getYear();
}

void Fleet::addVehicle(Vehicle *vl) {
    vehicles.push_back(vl);
}

unsigned Fleet::removeOldVehicles(int y1) {
    auto it = vehicles.begin();
    unsigned counter = 0;
    while (it != vehicles.end()) {
        if ((*it)->getYear() <= y1) {
            vehicles.erase(it);
            ++counter;
        }
        else
            ++it;
    }
    return counter;
}

ostream & operator<<(ostream & o, const Fleet & f) {
    string bar = "*-----------------------------*\n";
    for (Vehicle *vc : f.getVehicles()) {
        o << bar;
        vc->info(o);
        o << bar;
    }
    return o;
}

vector<Vehicle *> Fleet::operator () (int yearM) const {
    vector<Vehicle *> result;
    for (Vehicle * vc : vehicles)
        if (vc->getYear() == yearM)
            result.push_back(vc);
    return result;
}

float Fleet::totalTax() const {
    float sum = 0;
    for (Vehicle * vc : vehicles)
        sum += vc->calculateTax();
    return sum;
}