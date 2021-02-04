#include "box.h"
#include <sstream>

Object::Object(unsigned i, unsigned w): id(i), weight(w) {}

unsigned Object::getID() const {
    return id;
}

unsigned Object::getWeight() const {
    return weight;
}

Box::Box(unsigned cap): id(lastId++), capacity(cap), free(cap) {}

unsigned Box::getID() const {
    return id;
}

unsigned Box::getFree() const {
    return free;
}

void Box::addObject(Object& obj) {
    free -= obj.getWeight();
    objects.push(obj);
}

void Box::resetID(){
    lastId = 1;
}

unsigned Box::getSize() const {
    return objects.size();
}

ostream& operator<<(ostream& os, Object obj) {
    os << "O" << obj.id << ":" << obj.weight;
    return os;
}

unsigned Box::lastId = 1;

bool Object::operator<(const Object& o1) const {
	return this->getWeight() < o1.getWeight();
}

bool Box::operator<(const Box& b1) const {
	return !(this->getFree() < b1.getFree());
}

string Box::printContent() const {
    string str = "Box " + to_string(getID()) + " ";
    if (objects.empty()) return str + + "empty!\n";

    str += "[ ";
    stringstream ss;
    StackObj objects_cpy = objects;
    while (!objects_cpy.empty()) {
        ss << objects_cpy.top() << " ";
        objects_cpy.pop();
    }
    str += ss.str() + "]";
    return str;
}