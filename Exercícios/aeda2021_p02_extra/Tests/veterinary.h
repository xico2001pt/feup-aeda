#ifndef SRC_VETERINARY_H_
#define SRC_VETERINARY_H_

#include <string>
using namespace std;

class Veterinary {
    string name;
    long codOrder;
public:
    Veterinary(string nome, int cod);
    string getName() const;
    string getInfo() const;
};


#endif /* SRC_VETERINARY_H_ */
