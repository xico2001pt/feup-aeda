#include "Donation.h"

Donation::Donation(string s, unsigned v, unsigned e) : streamer(s), value(v), evaluation(e) {
    counter = 1;
}

string Donation::getStreamer() const {
    return streamer;
}

unsigned Donation::getValue() const {
    return value;
}

unsigned Donation::getEvaluation() const {
    return evaluation;
}

unsigned Donation::getCounter() const {
    return counter;
}

void Donation::setCounter(unsigned int c) {
    counter = c;
}

bool Donation::operator<(const Donation &d) const {
    if (this->getValue() == d.getValue())
        return (this->getEvaluation() > d.getEvaluation());
    return this->getValue() > d.getValue();
}

bool Donation::operator==(const Donation &d) const {
    return this->getStreamer() == d.getStreamer() && this->getValue() == d.getValue() && this->getEvaluation() == d.getEvaluation();
}

std::ostream& operator <<(std::ostream& os, const Donation &d){
    os << d.getStreamer() << "  " << d.getValue() << "€  " << d.getEvaluation() << "  " << d.getCounter() << std::endl;
    return os;
}
