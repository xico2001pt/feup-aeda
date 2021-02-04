#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;

Client::Client() : numGifts(rand() % 5 + 1) {
}

unsigned Client::getNumGifts() const {
    return numGifts;
}



Counter::Counter(unsigned wt): wrappingTime(wt), actualTime(0), nextEnter(rand() % 20 + 1), nextLeave(0), numAttendedClients(0) {
}

unsigned Counter::getActualTime() const {
    return actualTime;
}

unsigned Counter::getNextEnter() const {
    return nextEnter;
}

unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}

unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

unsigned Counter::getNextLeave() const {
    return nextLeave;
}

Client & Counter::getNextClient() {
    if (clients.empty()) throw EmptyQueue();
    return clients.front();
}

void Counter::enter() {
    Client cl;
    if (clients.empty()) nextLeave = actualTime + cl.getNumGifts() * wrappingTime;
    clients.push(cl);
    nextEnter = rand() % 20 + 1;
    cout << "time = " << actualTime << endl << "new customer arrived with " << cl.getNumGifts() << " gifts" << endl;
}

void Counter::leave() {
    Client cl;
    try {
        cl = getNextClient();
    }
    catch (EmptyQueue &e) {
        throw EmptyQueue();
    }
    clients.pop();
    if (!clients.empty()) nextLeave = actualTime + clients.front().getNumGifts() * wrappingTime;
    else nextLeave = 0;
    cout << "time = " << actualTime << endl << "new customer left with " << cl.getNumGifts() << " gifts" << endl;
}

void Counter:: nextEvent() {
    if (actualTime + nextEnter < nextLeave || nextLeave == 0) {
        actualTime = actualTime + nextEnter;
        enter();
    }
    else {
        actualTime = nextLeave;
        try {
            leave();
            numAttendedClients++;
        }
        catch (EmptyQueue &e) {}
    }
}

ostream & operator << (ostream & out, const Counter & c2) {
    out << c2.getNumAttendedClients() << " " << c2.clients.size();
    return out;
}


