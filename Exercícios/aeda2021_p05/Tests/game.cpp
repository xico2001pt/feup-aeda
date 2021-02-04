#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

Game::Game() {
    kids.clear();
}

Game::Game(list<Kid>& l2) : kids(l2) {
}

void Game::addKid(const Kid &k1) {
    kids.push_back(k1);
}

list<Kid> Game::getKids() const {
    return kids;
}

string Game::write() const {
    string res;
    for (const Kid &kid : kids)
        res += kid.write() + "\n";
    return res;
}

Kid& Game::loseGame(string phrase) {
    int numWords = numberOfWords(phrase);
    list<Kid>::iterator it = kids.begin();
    while (kids.size() > 1) {
        for (int i = 1; i < numWords; i++) {
            it++;
            if (it == kids.end()) it = kids.begin();
        }
        it = kids.erase(it);
        if (it == kids.end()) it = kids.begin();
    }
    return kids.front();
}

list<Kid>& Game::reverse()
{
    list<Kid> reverseKids;
    list<Kid>::reverse_iterator rit = kids.rbegin();
    while (rit != kids.rend()) {
        reverseKids.push_back(*rit);
        rit++;
    }
    kids = reverseKids;
    return kids;
}

list<Kid> Game::removeOlder(unsigned id) {
    list<Kid> res;
    list<Kid>::iterator it = kids.begin();
    while (it != kids.end()) {
        if (it->getAge() > id) {
            res.push_back(*it);
            it = kids.erase(it);
        }
        else
            it++;
    }
    return res;
}

void Game::setKids(const list<Kid>& l1) {
    for (const Kid &kid : l1)
        kids.push_back(kid);
}

bool Game::operator==(Game& g2) {
	return kids == g2.getKids();
}

list<Kid> Game::shuffle() const {
    list<Kid> res = kids;
    res.reverse();
    return res;
}
