#ifndef KID_H_
#define KID_H_

#include <string>
#include <sstream>
using namespace std;

class Kid {
    string name;
    int age;
public:
    Kid();
    Kid(string nm, unsigned a);
    Kid(const Kid& k1);
    string getName() const;
    unsigned getAge() const;
    bool operator==(const Kid& k2) const;
    string write() const;
    friend ostream & operator<<(ostream & o, const Kid & d);
};

#endif /* KID_H_ */
