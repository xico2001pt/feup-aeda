#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;

// TODO
bool InfoCard::operator == (const InfoCard &ic1) const
{
    if (name==ic1.name) return true;
    return false;
}

// TODO
bool InfoCard::operator < (const InfoCard &ic1) const
{
    if (frequency > ic1.frequency)
        return true;
    else if (frequency < ic1.frequency)
        return false;
    else
        return (name<ic1.name);
}

// TODO
bool compName(const InfoCard &c1, const InfoCard &c2)
{
    return c1.name < c2.name;
}


CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}


// TODO
int CarPark::clientPosition(const string & name) const
{
    InfoCard ic1;
    ic1.name=name;
    int p = sequentialSearch(clients, ic1);
    return p;
}

// TODO
unsigned CarPark::getFrequency(const string &name) const
{
    int pos = clientPosition(name);
    if (pos == -1) throw ClientDoesNotExist(name);
    return clients[pos].frequency;
}

bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    info.frequency = 0;  // TODO
    clients.push_back(info);
    return true;
}

bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    clients[pos].frequency++;   // TODO
    freePlaces--;
    return true;
}

bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}


// TODO
ostream & operator<<(ostream & os, const CarPark & cp)
{
    for (unsigned i= 0; i < cp.clients.size(); i++) {
        os << "Name: " << cp.clients[i].name;
        if (cp.clients[i].present == true) os << " (is present)" ;
        os << " ; frequency = " << cp.clients[i].frequency << endl;
    }
    return os;

}

// TODO
InfoCard CarPark::getClientAtPos(unsigned p) const
{
    if (p >= clients.size()) throw PositionDoesNotExist(p);
    return clients[p];
}

// TODO
void CarPark::sortClientsByFrequency()
{
    insertionSort(clients);
}

// TODO
void CarPark::sortClientsByName()
{
    sort(clients.begin(),clients.end(),compName);
}

// TODO
vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    sortClientsByFrequency();
    vector<string> names;
    for (unsigned i=0; i<clients.size(); i++)
    {
        if (clients[i].frequency < f1)
            break;
        if (clients[i].frequency <= f2)
            names.push_back(clients[i].name);
    }
    return names;
}









 


  




