# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> allStack;
    stack<T> minStack;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

template <class T> 
bool StackExt<T>::empty() const {
	return allStack.empty();
}

template <class T> 
T& StackExt<T>::top() {
    return allStack.top();
}

template <class T> 
void StackExt<T>::pop() {
    if (allStack.top() == minStack.top()) minStack.pop();
    allStack.pop();
}

template <class T> 
void StackExt<T>::push(const T & val) {
    if (minStack.empty() || val <= minStack.top()) minStack.push(val);
    allStack.push(val);
}

template <class T> 
T& StackExt<T>::findMin() {
    return minStack.top();
}

