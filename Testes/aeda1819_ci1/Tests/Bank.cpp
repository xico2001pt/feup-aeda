/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
    double result = 0;
    for (const Account *ac : accounts)
        if (ac->getCodH() == cod1)
            result += ac->getWithdraw();
	return result;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	vector<BankOfficer>::iterator it = bankOfficers.begin();
	while (it != bankOfficers.end()) {
	    if (it->getName() == name) {
	        res = it->getAccounts();
	        bankOfficers.erase(it);
            break;
	    }
	    it++;
	}
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    vector<BankOfficer>::iterator it = bankOfficers.begin();
    while (it != bankOfficers.end()) {
        if (it->getName() == name) {
            it->addAccount(ac);
            return *it;
        }
        it++;
    }
    throw NoBankOfficerException(name);
}


// a alterar
void Bank::sortAccounts() {
    sort(accounts.begin(), accounts.end(), accountsSort);
}

NoBankOfficerException::NoBankOfficerException(const string &name) : name(name) { }
string NoBankOfficerException::getName() const {
    return name;
}

bool accountsSort(const Account *ac1, const Account* ac2) {
    if (ac1->getBalance() == ac2->getBalance())
        return ac1->getCodIBAN() < ac2->getCodIBAN();
    return ac1->getBalance() < ac2->getBalance();
}
