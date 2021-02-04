#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "zoo.h"
#include <string>
#include <fstream>

using testing::Eq;

/*
TEST(test, a_createAnimals){
    Animal *a1=new Dog("kurika",10,"estrela");  //name, age, breed
    Animal *a2=new Bat("bobo",2,70,2);  //nome, idade, velocidade_maxima, altura_maxima
    Animal *a3=new Dog("bobby",3,"rafeiro");
    Animal *a4=new Dog("fly",7,"dalmata");
    Animal *a5=new Bat("timao",7,80,4);
    EXPECT_EQ("kurika", a1->getName());
    EXPECT_EQ("bobo", a2->getName());
    EXPECT_EQ("bobby", a3->getName());
    EXPECT_EQ("fly", a4->getName());
    EXPECT_EQ("timao", a5->getName());
    EXPECT_EQ(true, a3->isYoung());
    EXPECT_EQ(false, a4->isYoung());
    EXPECT_EQ(true, a2->isYoung());
    EXPECT_EQ(false, a5->isYoung());
    EXPECT_EQ(2, Animal::getYoungest());
}


TEST(test, b_addAnimals){
    Zoo z1;

    Animal *a1=new Dog("kurika",10,"estrela");  //name, age, breed
    Animal *a2=new Bat("bobo",2,70,2);  //name, age, maximum velocity, maximum altitude
    Animal *a3=new Dog("bobby",3,"rafeiro");
    Animal *a4=new Dog("fly",7,"dalmata");
    Animal *a5=new Bat("timao",7,80,4);

    z1.addAnimal(a1);
    z1.addAnimal(a2);
    z1.addAnimal(a3);
    z1.addAnimal(a4);
    z1.addAnimal(a5);

    EXPECT_EQ(5, z1.numAnimals());
}

TEST(test, c_printAnimals){
    Zoo z1;

    Animal *a1=new Dog("kurika",10,"estrela");
    EXPECT_EQ("kurika, 10, estrela", a1->getInfo());

    Animal *a2=new Bat("bobo",2,70,2);
    EXPECT_EQ("bobo, 2, 70, 2", a2->getInfo());

    z1.addAnimal(a1);
    z1.addAnimal(a2);

    cout << z1.getInfo();
}

TEST(test, d_verifyYoungAnimal){
    Zoo z1;

    Animal *a1=new Dog("kurika",10,"estrela");
    Animal *a2=new Bat("bobo",2,70,2);

    z1.addAnimal(a1);
    z1.addAnimal(a2);

    EXPECT_EQ(false, z1.isYoung("kurika"));
    EXPECT_EQ(true, z1.isYoung("bobo"));
}

TEST(test, e_allocateVeterinarians){
    Zoo z1;

    Animal *a1=new Dog("kurika",10,"estrela");
    Animal *a2=new Bat("bobo",2,70,2);
    Animal *a3=new Dog("bobby",3,"rafeiro");
    Animal *a4=new Dog("fly",7,"dalmata");
    Animal *a5=new Bat("timao",7,80,4);

    z1.addAnimal(a1);
    z1.addAnimal(a2);
    z1.addAnimal(a3);
    z1.addAnimal(a4);
    z1.addAnimal(a5);

    //TODO write the correct path file
    ifstream fVet("vets.txt");
    if (!fVet) cerr << "File does not exist!\n";
    else z1.allocateVeterinarians(fVet);
    fVet.close();

    EXPECT_EQ(5, z1.numAnimals());
    EXPECT_EQ(3, z1.numVeterinarians());
    EXPECT_EQ("kurika, 10, Rui Silva, 1234, estrela", a1->getInfo());
}

TEST(test, f_removeVeterinary){
    Zoo z1;

    Animal *a1=new Dog("kurika",10,"estrela");
    Animal *a2=new Bat("bobo",2,70,2);
    Animal *a3=new Dog("bobby",3,"rafeiro");
    Animal *a4=new Dog("fly",7,"dalmata");
    Animal *a5=new Bat("timao",7,80,4);

    z1.addAnimal(a1);
    z1.addAnimal(a2);
    z1.addAnimal(a3);
    z1.addAnimal(a4);
    z1.addAnimal(a5);

    //TODO  write the correct path file
    ifstream fVet("vets.txt");
    if (!fVet) cerr << "File does not exist!!\n";
    else z1.allocateVeterinarians(fVet);
    fVet.close();

    EXPECT_EQ(5, z1.numAnimals());
    EXPECT_EQ(3, z1.numVeterinarians());
    EXPECT_EQ("kurika, 10, Rui Silva, 1234, estrela", a1->getInfo());

    z1.removeVeterinary("Rui Silva");

    EXPECT_EQ("kurika, 10, Artur Costa, 3542, estrela", a1->getInfo());
}


TEST(test, h_compareZoo){
    Zoo z1;

    Animal *a1=new Dog("kurika",10,"estrela");
    Animal *a2=new Bat("bobo",2,70,2);
    Animal *a3=new Dog("bobby",3,"rafeiro");
    Animal *a4=new Dog("fly",7,"dalmata");
    Animal *a5=new Bat("timao",7,80,4);

    z1.addAnimal(a1);
    z1.addAnimal(a2);
    z1.addAnimal(a3);
    z1.addAnimal(a4);
    z1.addAnimal(a5);

    Zoo z2;

    Animal *b1=new Dog("kurika",10,"estrela");
    Animal *b2=new Bat("bobo",2,70,2);
    Animal *b3=new Dog("bobby",3,"rafeiro");
    Animal *b4=new Dog("fly",7,"dalmata");

    z2.addAnimal(b1);
    z2.addAnimal(b2);
    z2.addAnimal(b3);
    z2.addAnimal(b4);

    EXPECT_EQ(true, z2 < z1);
}
*/