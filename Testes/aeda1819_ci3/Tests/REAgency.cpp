#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

void REAgency::generateCatalog() {
    vector<Property*> similar = {properties[0]};
    Property* aux = properties[0];
    int maxPrice = aux->getPrice();
    for(int i = 1; i < properties.size(); i++)
    {
        Property* property = properties[i];
        if(aux->getTypology() != property->getTypology() ||
           aux->getPostalCode() != property->getPostalCode() ||
           aux->getAddress() != property->getAddress())
        {
            PropertyTypeItem pti(aux->getAddress(), aux->getPostalCode(), aux->getTypology(), maxPrice);
            pti.setItems(similar);
            catalogItems.insert(pti);
            similar = {property};
            aux = property;
            maxPrice = property->getPrice();
        }
        else{
            if(maxPrice < property->getPrice()){
                maxPrice = property->getPrice();
            }
            similar.push_back(property);
        }
    }
    free(aux);
    similar.clear();
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
    vector<Property*> temp;
    BSTItrIn<PropertyTypeItem> it(catalogItems);
    while(!it.isAtEnd())
    {
        if(it.retrieve().getTypology() == property->getTypology() &&
           it.retrieve().getPostalCode() == property->getPostalCode() &&
           it.retrieve().getAddress() == property->getAddress())
        {
            for(auto&p : it.retrieve().getItems())
            {
                tuple<Client*,int> aux = p->getReservation();
                if(get<0>(aux) == NULL)
                    temp.push_back(p);
            }
        }
        it.advance();
    }
    return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
    PropertyTypeItem itemNotFound("", "","", 0);
    PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
    PropertyTypeItem ptiX = catalogItems.find(pti);
    if(ptiX == itemNotFound) {
        return false;
    }
    for (Property *p : ptiX.getItems()) {
        if (get<0>(p->getReservation()) == NULL) {
            this->catalogItems.remove(ptiX);
            p->setReservation({client, p->getPrice() * (1 - (double) percentage / 100)});
            this->catalogItems.insert(ptiX);
            return true;
        }
    }
	return false;
}

void REAgency::addClientRecord(Client* client) {
	listingRecords.insert({client});
}

void REAgency::deleteClients() {
    HashTabClientRecord::iterator it = listingRecords.begin();
    while (it != listingRecords.end()) {
        if (it->getClientPointer()->getVisitedProperties().size() == 0 && it->getClientPointer()->getVisiting() != tuple<string,string,string,string>("","","","")){
            it = listingRecords.erase(it);
        }
        else
            ++it;
    }
}

void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
    for (const Client &c : candidates) {
        double counter = 0;
        for (Property *p : properties) {
            if (get<0>(p->getReservation())->getEMail() == c.getEMail())
                ++counter;
        }
        if (counter / c.getVisitedProperties().size() > min)
            clientProfiles.push(c);
    }
}

vector<Property*> REAgency::suggestProperties() {
	vector<Property*> tempProperties;
    priority_queue<Client> copy = clientProfiles;
    while (!copy.empty()) {
        Client c = copy.top();
        copy.pop();
        if (c.getVisitedProperties().size() == 0 && c.getVisiting() == tuple<string,string,string,string>("","","","")) continue;
        string last_postal;
        if (c.getVisiting() != tuple<string,string,string,string>("","","","")) {
            last_postal = get<1>(c.getVisiting());
        }
        else {
            last_postal = get<1>(*(c.getVisitedProperties().rbegin()));
        }
        Property *best_p = NULL;
        int diff = 9999999;
        for (Property *p : properties) {
            if (get<0>(p->getReservation()) == NULL && abs(stoi(p->getPostalCode()) - stoi(last_postal)) < diff){
                diff = abs(stoi(p->getPostalCode()) - stoi(last_postal));
                best_p = p;
            }
        }
        tempProperties.push_back(best_p);
    }
	return tempProperties;
}
