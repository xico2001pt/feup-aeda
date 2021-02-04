#ifndef PACKAGINGMACHINE_H_
#define PACKAGINGMACHINE_H_

#include <queue>
#include <vector>
#include <stack>
#include <iostream>
#include "box.h"
using namespace std;

typedef priority_queue<Object> HeapObj;
typedef priority_queue<Box> HeapBox;

class PackagingMachine {
    HeapObj objects;
    HeapBox boxes;
    unsigned boxCapacity;
public:
    PackagingMachine(int boxCap = 10);
    unsigned numberOfBoxes();
    unsigned addBox(Box& b1);
    HeapObj getObjects() const;
    HeapBox getBoxes() const;

    unsigned loadObjects(vector<Object> &objs);
    Box searchBox(Object& obj);
    unsigned packObjects();
    string printObjectsNotPacked() const;
    Box boxWithMoreObjects() const;

    class MachineWithoutBoxes{};
};

#endif