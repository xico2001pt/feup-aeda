#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "carPark.h"
#include <string>
using testing::Eq;

TEST(test, a_Search){
    CarPark p1(10,20);
    p1.addClient("Joao Santos");
    p1.addClient("Pedro Morais");
    p1.addClient("Rui Silva");
    p1.addClient("Susana Costa");
    p1.addClient("Maria Tavares");
    EXPECT_EQ(0, p1.clientPosition("Joao Santos"));
    EXPECT_EQ(4, p1.clientPosition("Maria Tavares"));
    EXPECT_EQ(1, p1.clientPosition("Pedro Morais"));
    EXPECT_EQ(-1, p1.clientPosition("Tiago Tavares"));
}

TEST(test, b_CarParkUse){
    CarPark p1(10,20);
    p1.addClient("Joao Santos");
    p1.addClient("Pedro Morais");
    p1.addClient("Rui Silva");
    p1.addClient("Susana Costa");
    p1.addClient("Maria Tavares");
    p1.enter("Maria Tavares");
    p1.enter("Susana Costa");
    p1.leave("Susana Costa");
    p1.leave("Maria Tavares");
    p1.enter("Maria Tavares");
    p1.leave("Maria Tavares");
    p1.enter("Rui Silva");
    p1.leave("Rui Silva");
    p1.enter("Susana Costa");
    p1.enter("Rui Silva");
    p1.leave("Rui Silva");
    p1.enter("Rui Silva");
    p1.enter("Pedro Morais");
    EXPECT_EQ(3, p1.getFrequency("Rui Silva"));
    EXPECT_EQ(1, p1.getFrequency("Pedro Morais"));
    EXPECT_EQ(0, p1.getFrequency("Joao Santos"));
    EXPECT_THROW(p1.getFrequency("Tiago Silva"), ClientDoesNotExist);
    try {
        p1.getFrequency("Tiago Silva");
    }
    catch (ClientDoesNotExist &e) {
        cout << "Caught Exception. Client does not exist: " << e.getName() << endl;
        EXPECT_EQ("Tiago Silva", e.getName());
    }
}

TEST(test, c_SortByFrequency){
    CarPark p1(10,20);
    p1.addClient("Joao Santos");
    p1.addClient("Pedro Morais");
    p1.addClient("Rui Silva");
    p1.addClient("Susana Costa");
    p1.addClient("Maria Tavares");
    p1.enter("Maria Tavares");
    p1.enter("Susana Costa");
    p1.leave("Susana Costa");
    p1.leave("Maria Tavares");
    p1.enter("Maria Tavares");
    p1.leave("Maria Tavares");
    p1.enter("Rui Silva");
    p1.leave("Rui Silva");
    p1.enter("Susana Costa");
    p1.enter("Rui Silva");
    p1.leave("Rui Silva");
    p1.enter("Rui Silva");
    p1.enter("Pedro Morais");
    // Joao Santos: frequency 0
    // Pedro Morais: frequency 1
    // Maria Tavares: frequency 2
    // Susana Costa: frequency 2
    // Rui Silva: frequency 3
    p1.sortClientsByFrequency();
    EXPECT_EQ(5,p1.getClients().size());
    if (p1.getClients().size()>=3) {
        InfoCard ic = p1.getClients()[2];
        EXPECT_EQ("Susana Costa", ic.name);
        EXPECT_EQ(2, ic.frequency);
    }
    if (p1.getClients().size()>=1) {
        InfoCard ic = p1.getClients()[0];
        EXPECT_EQ("Rui Silva", ic.name);
        EXPECT_EQ(3, ic.frequency);
    }
}

TEST(test, d_Between){
    CarPark p1(10,20);
    p1.addClient("Joao Santos");
    p1.addClient("Pedro Morais");
    p1.addClient("Rui Silva");
    p1.addClient("Susana Costa");
    p1.addClient("Maria Tavares");
    p1.enter("Maria Tavares");
    p1.enter("Susana Costa");
    p1.leave("Susana Costa");
    p1.leave("Maria Tavares");
    p1.enter("Maria Tavares");
    p1.leave("Maria Tavares");
    p1.enter("Rui Silva");
    p1.leave("Rui Silva");
    p1.enter("Susana Costa");
    p1.enter("Rui Silva");
    p1.leave("Rui Silva");
    p1.enter("Rui Silva");
    p1.enter("Pedro Morais");
    // Joao Santos: frequency 0
    // Pedro Morais: frequency 1
    // Maria Tavares: frequency 2
    // Susana Costa: frequency 2
    // Rui Silva: frequency 3
    vector<string> clients = p1.clientsBetween(2,3);
    EXPECT_EQ(3,clients.size());
    if (clients.size()>=1)
        EXPECT_EQ("Rui Silva", clients[0]);
    if (clients.size()>=2)
        EXPECT_EQ("Maria Tavares", clients[1]);
    if (clients.size()>=3)
        EXPECT_EQ("Susana Costa", clients[2]);
}

TEST(test, e_SortByName){
    CarPark p1(10,20);
    p1.addClient("Joao Santos");
    p1.addClient("Pedro Morais");
    p1.addClient("Rui Silva");
    p1.addClient("Susana Costa");
    p1.addClient("Maria Tavares");
    p1.enter("Maria Tavares");
    p1.enter("Susana Costa");
    p1.leave("Susana Costa");
    p1.leave("Maria Tavares");
    p1.enter("Maria Tavares");
    p1.leave("Maria Tavares");
    p1.enter("Rui Silva");
    p1.leave("Rui Silva");
    p1.enter("Susana Costa");
    p1.enter("Rui Silva");
    p1.leave("Rui Silva");
    p1.enter("Rui Silva");
    p1.enter("Pedro Morais");
    p1.sortClientsByName();
    EXPECT_EQ(5,p1.getClients().size());
    if (p1.getClients().size()>=3) {
        InfoCard ic = p1.getClients()[2];
        EXPECT_EQ("Pedro Morais", ic.name);
    }
    if (p1.getClients().size()>=1) {
        InfoCard ic = p1.getClients()[0];
        EXPECT_EQ("Joao Santos", ic.name);
    }
}

TEST(test, f_InfoClients){
    CarPark p1(10,20);
    p1.addClient("Joao Santos");
    p1.addClient("Pedro Morais");
    p1.addClient("Rui Silva");
    p1.addClient("Susana Costa");
    p1.addClient("Maria Tavares");
    p1.enter("Maria Tavares");
    p1.enter("Susana Costa");
    p1.leave("Susana Costa");
    p1.enter("Rui Silva");
    p1.enter("Susana Costa");
    cout << "This test never fails! VERIFY information written on the monitor" << endl;
    cout << p1;
    InfoCard ic=p1.getClientAtPos(2);
    EXPECT_EQ("Rui Silva", ic.name);
    EXPECT_THROW(p1.getClientAtPos(6), PositionDoesNotExist);
    try {
        p1.getClientAtPos(6);
    }
    catch (PositionDoesNotExist &e) {
        cout << "This test never fails! VERIFY information written on the monitor" << endl;
        cout << "Caught Exception. Position does not exist:" << e.getPosition() << endl;
        EXPECT_EQ(6, e.getPosition());
    }
}
