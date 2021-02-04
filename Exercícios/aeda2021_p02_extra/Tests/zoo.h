#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>

class Zoo {
	vector<Animal *> animals;
	vector<Veterinary *> veterinarians;
public:
    ~Zoo();
    /**
     * Returns the number of animals in the zoo
     * @return Number of animals in the zoo
     */
	unsigned numAnimals() const;
	unsigned numVeterinarians() const;
    void addAnimal(Animal *a1);
    string getInfo() const;
    bool isYoung(string nameA);
    /**
     * Allocates the veterinaries and gives each animal one.
     * @param isV Input stream where the file was loaded
     */
    void allocateVeterinarians(istream &isV);
    bool removeVeterinary(string nameV);
    bool operator < (Zoo& zoo2) const;
};


#endif /* ZOO_H_ */
