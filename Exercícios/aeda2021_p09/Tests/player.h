#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
using namespace std;

struct betHash {
	int operator() (const Bet& b) const {
	    int v = 0;
	    for (unsigned num : b.getNumbers()) {
	        v += 37 * v + num;
	    }
        return v;
	}
	
	bool operator() (const Bet& b1, const Bet& b2) const {
		return (b1.getNumbers().size() == b1.getNumbers().size()) && (b1.countRights(b2.getNumbers()));
	}
};


typedef unordered_set<Bet, betHash, betHash> tabHBet;

class Player
{
	tabHBet bets;
	string name;
public:
	Player(string nm="anonymous") { name=nm; }
	void addBet(const Bet & ap);
	unsigned betsInNumber(unsigned num) const;
	tabHBet drawnBets(const tabHInt& draw) const;
	unsigned getNumBets() const { return bets.size(); }
};

#endif 
