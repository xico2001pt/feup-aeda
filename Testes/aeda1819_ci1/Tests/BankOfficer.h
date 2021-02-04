/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>

class BankOfficer {
    static unsigned int idCounter;
	unsigned int id;
	string name;
	vector<Account *> myAccounts;
public:
	BankOfficer();
	void setName(string nm);
	void addAccount(Account *a);
	void addAccount(vector<Account *> accounts);
	string getName() const;
	vector<Account *> getAccounts() const;
	unsigned int getID() const;

	//-------
	BankOfficer(string nm);
	vector<Account *> removeBankOfficer(string name);
	bool operator>(const BankOfficer &bc) const;
};

template<typename T>
unsigned int numberDifferent(const vector<T> &v1) {
    vector<T> different;
    for (T elem1 : v1) {
        bool found = false;
        for (T elem2 : different) {
            if (elem1 == elem2)
                found = true;
        }
        if (!found) {
            different.push_back(elem1);
        }
    }
    return different.size();
}

#endif /* SRC_BANKOFFICER_H_ */
