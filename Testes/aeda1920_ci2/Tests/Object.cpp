#include "Object.h"

Object::Object(string name, double size) {
	this->name = name;
	this->size = size;
}

string Object::getName() const {
	return name;
}

double Object::getSize() const {
    return size;
}

void Object::setName(string nm) {
    name =nm;
}
void Object::setSize(double s) {
    size = s;
}

bool Object::operator ==(const Object& obj) const {
	return this->name == obj.name;
}

bool Object::operator <(const Object& obj) const {
	return this->size > obj.size;
}

ostream & operator << (ostream & out, const Object & o1) {
     out << o1.getName() << "(" << o1.getSize() << ")" << endl;
     return out;
}
