#ifndef COUNTER_H_
#define COUNTER_H_

#include <iostream>
#include <queue>
using namespace std;

class Client {
    unsigned numGifts;
public:
    Client();
    unsigned getNumGifts() const;
};


class Counter {
    queue<Client> clients;
    const unsigned wrappingTime;
    unsigned nextEnter, nextLeave;
    unsigned actualTime;
    unsigned numAttendedClients;
public:
    Counter(unsigned wt=2);
    unsigned getActualTime() const;
    unsigned getNextEnter() const;
    unsigned getNumAttendedClients() const;
    unsigned getWrappingTime() const;
    unsigned getNextLeave() const;
    Client & getNextClient();
    void enter();
    void leave();
    void nextEvent();
    friend ostream & operator << (ostream & out, const Counter & c2);
};

#endif
