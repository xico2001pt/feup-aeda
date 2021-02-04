#ifndef SRC_WIDEFLATBOX_H_
#define SRC_WIDEFLATBOX_H_

#include <vector>
#include "Box.h"

using namespace std;

class WideFlatBox : public Box {
	vector<Object> objects;
public:
	WideFlatBox(double capacity);
	void insert(Object object);
	void remove(Object object);
	const Object& next() const;
	void sortObjects();
};

#endif /* SRC_WIDEFLATBOX_H_ */
