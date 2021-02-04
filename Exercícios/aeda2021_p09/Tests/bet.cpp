#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;

bool Bet::contains(unsigned num) const {
    return numbers.find(num) != numbers.end();
}

void Bet::generateBet(const vector<unsigned>& values, unsigned n) {
    for (int i = 0; i < values.size(); ++i) {
        if (n == 0) break;
        if (numbers.insert(values.at(i)).second) --n;
    }
}

unsigned Bet::countRights(const tabHInt& draw) const {
    tabHInt::const_iterator it = draw.begin();
    unsigned counter = 0;

    while (it != draw.end()) {
        if (numbers.find(*it) != numbers.end()) ++counter;
        ++it;
    }
	return counter;
}
