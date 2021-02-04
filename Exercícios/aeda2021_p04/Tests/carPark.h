#ifndef CARPARK_H_
#define CARPARK_H_
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class InfoCard {
public:
	string name;
	bool present;
    int frequency;
    bool operator == (const InfoCard &ic1) const;
    bool operator < (const InfoCard &ic1) const;
};


class CarPark {
	unsigned freePlaces;
	const unsigned  capacity;
	vector<InfoCard> clients;
	const unsigned numMaxClients;
public:
	CarPark(unsigned cap, unsigned nMaxCli);
    unsigned getNumPlaces() const;
    unsigned getNumMaxClients() const;
    unsigned getNumOccupiedPlaces() const;
    unsigned getNumClients() const;
    vector<InfoCard> getClients() const;
	bool addClient(const string & name);
	bool removeClient(const string & name);
	bool enter(const string & name);
	bool leave(const string & name);
	int clientPosition(const string & name) const;
    friend ostream & operator<<(ostream & os, const CarPark & cp);
    unsigned getFrequency(const string &name) const;
    InfoCard getClientAtPos(unsigned p) const;
    void sortClientsByFrequency();
    void sortClientsByName();
    vector<string> clientsBetween(unsigned f1, unsigned f2);
};



// TODO
class ClientDoesNotExist{
    string name;
public:
    ClientDoesNotExist(string nm): name(nm) {}
    string getName() const { return name; }
};

// TODO
class PositionDoesNotExist{
    int position;
public:
    PositionDoesNotExist(int p): position(p) {}
    int getPosition() const { return position; }
};

#endif /*CARPARK_H_*/