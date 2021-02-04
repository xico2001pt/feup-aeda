#include "ThinTallBox.h"
#include "WideFlatBox.h"
#include <algorithm>

ThinTallBox::ThinTallBox(double capacity) : Box(capacity) {
}

ThinTallBox::ThinTallBox(double capacity, stack<Object> objects, double content_size) : Box(capacity) {
	this->objects = objects;
	this->setContentSize(content_size);
}

stack<Object> ThinTallBox::getObjects() const {
    return objects;
}

void ThinTallBox::remove(Object object) {
	Object next_object = next();
	if(!(next_object == object)) {
		throw InaccessibleObjectException(object);
	} else {
		setContentSize(getContentSize()-next_object.getSize());
		objects.pop();
	}
}

const Object& ThinTallBox::next() const {
	return objects.top();
}


void ThinTallBox::insert(Object object) {
    if (object.getSize() + getContentSize() > getCapacity())
        throw ObjectDoesNotFitException();
    objects.push(object);
    setContentSize(getContentSize() + object.getSize());
}

void ThinTallBox::sortObjects() {
	vector<Object> aux;
	while (!objects.empty()) {
	    aux.push_back(objects.top());
	    objects.pop();
	}
	sort(aux.begin(), aux.end(), sortFunc);
	for (Object &ob : aux) {
	    objects.push(ob);
	}
}

bool sortFunc(const Object &ob1, const Object &ob2) {
    return ob1.getSize() > ob2.getSize();
}
