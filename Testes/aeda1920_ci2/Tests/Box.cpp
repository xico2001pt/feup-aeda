#include "Box.h"

Box::Box(double c) : capacity(c) {
	content_size = 0;
	days_to_send = rand()%4+2; //
}

const double Box::getCapacity() const {
	return capacity;
}

double Box::getContentSize() const {
	return content_size;
}

int Box::getDays() const {
    return days_to_send;
}

void Box::setContentSize(double contentSize) {
	content_size = contentSize;
}

void Box::setDaysToSend(int d) {
    days_to_send = d;
}

bool Box::empty() const {
	return content_size == 0;
}

bool Box::full() const {
    return capacity == content_size;
}


Object Box::removeNext() {
	if (empty()) throw InaccessibleObjectException();
	Object ob = next();
	remove(ob);
    return ob;
}
