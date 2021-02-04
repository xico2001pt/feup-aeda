#ifndef SRC_EXCEPTIONS_H_
#define SRC_EXCEPTIONS_H_

#include <string>
using namespace std;

class EmptyQueue {
	string msg;
public:
	EmptyQueue() {msg = "Empty Queue";}
	string getMsg() const {return msg;}
};

#endif /* SRC_EXCEPTIONS_H_ */
