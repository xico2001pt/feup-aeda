#include "player.h"

void Player::addBet(const Bet& b) {
    bets.insert(b);
}

unsigned Player::betsInNumber(unsigned num) const {
    unsigned counter = 0;
    for (const Bet &bet : bets) {
        if (bet.contains(num)) ++counter;
    }
    return counter;
}

tabHBet Player::drawnBets(const tabHInt& draw) const {
	tabHBet res;
    for (const Bet &bet : bets) {
        if (bet.countRights(draw) > 3) res.insert(bet);
    }
	return res;
}
