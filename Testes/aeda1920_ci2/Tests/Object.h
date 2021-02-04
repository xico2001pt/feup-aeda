#ifndef SRC_OBJECT_H_
#define SRC_OBJECT_H_

#include <iostream>
#include <string>

using namespace std;

class Object {
	string name;
	double size;
public:
	Object() {};
	Object(string name, double size);
	string getName() const;
	double getSize() const;
    void setName(string nm);
    void setSize(double s);
	bool operator ==(const Object& obj) const;
	bool operator <(const Object& obj) const;
    friend ostream & operator << (ostream & out, const Object & o1);
};

#endif /* SRC_OBJECT_H_ */
