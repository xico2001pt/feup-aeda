#ifndef GAME_H_
#define GAME_H_

#include "binaryTree.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


class Circle {
    int points;
    bool state;
    int nVisits;
public:
    Circle(int p=0, bool s=false): points(p), state(s), nVisits(0) {}
    int getPoints() const { return points; }
    bool getState() const { return state; }
    void changeState() { if (state==false) state=true; else state=false; }
    int getNVisits() const { return nVisits; }
    void incVisits() {nVisits++;}
    friend ostream &operator << (ostream &os, Circle &c1);
};


class Game {
    BinaryTree<Circle> game;
public:
    Game(int h, vector<int> &points, vector<bool> &states);
    BinaryTree<Circle> initGame(unsigned int pos, int h, vector<int> &points, vector<bool> &states);
    string writeGame();
    int move();
    int mostVisited();
    BinaryTree<Circle> &getGame() { return game; }
};

#endif
