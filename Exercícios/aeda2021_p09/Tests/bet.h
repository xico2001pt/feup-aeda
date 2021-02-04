#ifndef BET_H_
#define BET_H_

#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

typedef unordered_set<unsigned> tabHInt;

class Bet
{
	tabHInt numbers;
public:
	Bet() {};
	void generateBet(const vector<unsigned>& values, unsigned n=6);
	bool contains(unsigned num) const;
	unsigned countRights(const tabHInt& draw) const;
	tabHInt getNumbers() const { return numbers; }
};

#endif 
