/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

unsigned int BankOfficer::idCounter = 1;

BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

// a alterar
BankOfficer::BankOfficer(string name) : id(idCounter), name(name) {
    idCounter++;
}

bool BankOfficer::operator>(const BankOfficer &bc) const {
    if (this->getAccounts().size() == bc.getAccounts().size()) {
        return this->getName() > bc.getName();
    }
    return this->getAccounts().size() > bc.getAccounts().size();
}



