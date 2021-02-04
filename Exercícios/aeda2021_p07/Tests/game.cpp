#include "game.h"
#include <sstream>


ostream &operator << (ostream &os, Circle &c1)
{
    os << c1.getPoints() << "-" << (c1.getState() ? "true" : "false") << "-" << c1.getNVisits() << endl;
	return os;
}

Game::Game(int h, vector<int> &points, vector<bool> &states) {
    game = initGame(0, h, points, states);
}

BinaryTree<Circle> Game::initGame(unsigned int pos, int h, vector<int> &points, vector<bool> &states) {
    Circle root(points.at(pos), states.at(pos));
    if (h == 0) return BinaryTree<Circle>(root);
    BinaryTree<Circle> left = initGame(2 * pos + 1, h - 1, points, states);
    BinaryTree<Circle> right = initGame(2 * pos + 2, h - 1, points, states);
    return BinaryTree<Circle>(root, left, right);
}

string Game::writeGame() {
    stringstream ss;
	BTItrLevel<Circle> it(game);
	while (!it.isAtEnd()) {
	    ss << it.retrieve();
	    it.advance();
	}
    return ss.str();
}

int Game::move() {
    int points, i = 0, pos = 0;
    bool state;
    BTItrLevel<Circle> it(game);
    while (!it.isAtEnd()) {
        Circle &c = it.retrieve();
        points = c.getPoints();
        it.retrieve().incVisits();
        state = c.getState();
        it.retrieve().changeState();
        for (i; i < 2 * pos + 1 + (state); i++) {
            it.advance();
            if (it.isAtEnd()) break;
        }
        pos = i;
        if (it.isAtEnd()) break;
    }
    return points;
}

int Game::mostVisited() {
    BTItrLevel<Circle> it(game);
    int result = 0;
    it.advance();
    while (!it.isAtEnd()) {
        Circle c = it.retrieve();
        if (c.getNVisits() > result) result = c.getNVisits();
        it.advance();
    }
    return result;
}
