#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap) {}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}

unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
	unsigned counter = 0;
	vector<Object>::iterator it = objs.begin();
	while (it != objs.end()) {
	    if (it->getWeight() <= boxCapacity) {
	        objects.push(*it);
	        ++counter;
            it = objs.erase(it);
	    }
	    else {
	        ++it;
	    }
	}
    return counter;
}

Box PackagingMachine::searchBox(Object& obj) {
    vector<Box> aux;
	while (!boxes.empty()) {
	    Box b = boxes.top();
        boxes.pop();
	    if (b.getFree() >= obj.getWeight()) {
            for (Box &box : aux) {
                boxes.push(box);
            }
            return b;
	    }
	    else {
	        aux.push_back(b);
	    }
	}
	for (Box &box : aux) {
	    boxes.push(box);
	}
	return Box();
}

unsigned PackagingMachine::packObjects() {
    while (!objects.empty()) {
        Object o = objects.top();
        objects.pop();
        Box b = searchBox(o);
        b.addObject(o);
        boxes.push(b);
    }
    return boxes.size();
}

string PackagingMachine::printObjectsNotPacked() const {
    if (objects.empty()) return "No objects!\n";
    stringstream ss;
    HeapObj objects_cpy = objects;
    while (!objects_cpy.empty()) {
        ss << objects_cpy.top() << endl;
        objects_cpy.pop();
    }
    return ss.str();
}

Box PackagingMachine::boxWithMoreObjects() const {
    if (boxes.empty()) throw MachineWithoutBoxes();

    Box b;
    HeapBox boxes_cpy = boxes;
    while (!boxes_cpy.empty()) {
        Box aux = boxes_cpy.top();
        if (aux.getSize() > b.getSize()) {
            b = aux;
        }
        boxes_cpy.pop();
    }
	return b;
}