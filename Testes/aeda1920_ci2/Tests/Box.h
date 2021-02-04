#ifndef SRC_BOX_H_
#define SRC_BOX_H_

#include "Object.h"

class Box {
	const double capacity;
	double content_size;
	int days_to_send;

public:
	Box(double capacity);
	virtual void insert(Object object) = 0;
	virtual void remove(Object object) = 0;
	const double getCapacity() const;
	double getContentSize() const;
    int getDays() const;
	void setContentSize(double contentSize);
    void setDaysToSend(int d);
	bool empty() const;
    bool full() const;
	virtual const Object& next() const = 0;
	virtual void sortObjects() = 0;
	Object removeNext();
};

class ObjectDoesNotFitException {
public:
	ObjectDoesNotFitException() {}
};

class InaccessibleObjectException {
	Object object;
public:
	InaccessibleObjectException() {}
	InaccessibleObjectException(Object object) { this->object = object; }
	Object getObject() {
		return object;
	}
};

#endif /* SRC_BOX_H_ */
