#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>

template <class Chamber>
class Hotel {
	std::vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const std::string city;
    std::list<Chamber> reservationsDone;
public:
	Hotel(int size, std::string municipality);
	~Hotel();
	std::vector<Chamber *> getChambers() const;
	void setChambers(std::vector<Chamber *> chambers);
	int getCapacity() const;
    std::list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(std::string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(std::string code, int floor);
    std::list<Chamber> roomsNeverReserved() const;
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};

template <class Chamber>
Hotel<Chamber>::Hotel(int size, std::string municipality) : maxCapacity(size), city(municipality) {
}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename std::vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
std::vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(std::vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

//------------------------------------------------------
//------------------------------------------------------
bool comp(Room *chamber1, Room *chamber2) {
    return *chamber1 < *chamber2;
}

//TODO
template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    if (chambers.size() >= maxCapacity) return false;
    for (Chamber *ch : chambers) {
        if ((*ch) == (*chamber))
            return false;
    }
    chambers.push_back(chamber);
    return true;
}


//TODO
template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    std::sort(chambers.begin(), chambers.end(), comp);
}

//TODO
template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(std::string code, int floor) {
    Chamber ch_aux(code, floor);
    typename std::vector<Chamber *>::iterator it = chambers.begin();
    while (it != chambers.end()) {
        if (*(*it) == ch_aux) {
            Chamber *result = *it;
            chambers.erase(it);
            return result;
        }
        it++;
    }
    throw NoSuchChamberException();
}

//TODO
class NoSuchFloorException {
    int floor;
public:
    NoSuchFloorException(int floor) {this->floor = floor;}
    int getFloor() { return floor;}
};

//TODO
template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    unsigned int totalChambers = 0;
    float totalArea = 0;
    for (Chamber *ch : chambers) {
        if (ch->getFloor() == floor) {
            totalChambers++;
            totalArea += ch->getArea();
        }
    }
    if (totalChambers == 0) throw NoSuchFloorException(floor);
    return totalArea / totalChambers;
}

//TODO
template<class Chamber>
bool Hotel<Chamber>::doReservation(std::string code, int floor){
    Chamber chamber(code, floor);
    for (Chamber *ch : chambers) {
        if ((*ch) == chamber) {
            if (ch->getReservation())
                break;
            ch->setReservation(true);
            reservationsDone.push_back(*ch);
            return true;
        }
    }
    return false;
}

//TODO
template<class Chamber>
std::list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    std::list<Chamber> res;
    bool found;
    for (Chamber *ch1 : chambers) {
        found = false;
        for (Chamber ch2 : reservationsDone) {
            if (*ch1 == ch2) {
                found = true;
                break;
            }
        }
        if (!found) {
            res.push_back(*ch1);
        }
    }
    return res;
}

#endif /* SRC_HOTEL_H_ */
