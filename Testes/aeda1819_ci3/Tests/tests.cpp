#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdlib>
#include <iostream>
#include "Property.h"
#include "Client.h"
#include "REAgency.h"

using testing::Eq;
using namespace std;

TEST(test_1, test_a){
    vector<Property*> properties;
    properties.push_back(new Property("Rua Dr Roberto Frias", "Joao", "100","t2",200000));
    properties.push_back(new Property("Rua Dr Roberto Frias", "Joao", "100","t2",180000));
    properties.push_back(new Property("Rua Dr Roberto Frias", "Joao", "100","t2",150000));
    properties.push_back(new Property("Rua Dr Roberto Frias", "Joao", "100","t2",220000));
    properties.push_back(new Property("Rua do Amial", "Miguel", "200","t2",190000));
    properties.push_back(new Property("Rua do Amial", "Pedro", "220","t3",240000));
    properties.push_back(new Property("Rua do Amial", "Pedro", "220","t3",250000));
    properties.push_back(new Property("Rua do Amial", "Luis", "220","t3",130000));
    properties.push_back(new Property("Rua do Amial", "Miguel", "280","t1",120000));
    properties.push_back(new Property("Alameda das Antas", "Luis", "300","t0",100000));
    properties.push_back(new Property("Alameda das Antas", "Luis", "320","t2",200000));
    properties.push_back(new Property("Alameda das Antas", "Pedro", "340","t2",230000));
    properties.push_back(new Property("Alameda das Antas", "Miguel", "360","t4",300000));
    properties.push_back(new Property("Alameda das Antas", "Miguel", "360","t3",260000));

    REAgency agency(properties);

    agency.generateCatalog();

    PropertyTypeItem pti1 = agency.getTypeItem("Rua Dr Roberto Frias","100","t2");
    EXPECT_EQ(4, pti1.getItems().size());
    PropertyTypeItem pti2 = agency.getTypeItem("Rua do Amial","220","t3");
    EXPECT_EQ(3, pti2.getItems().size());
    PropertyTypeItem pti3 = agency.getTypeItem("Alameda das Antas", "300","t0");
    EXPECT_EQ(1, pti3.getItems().size());
}

TEST(test_1, test_b){
    Property* pPtr1 = new Property("Rua Dr Roberto Frias", "Joao", "100","t2", 200000);
    Property* pPtr2 = new Property("Rua Dr Roberto Frias", "Joao", "100","t2",220000);
    Property* pPtr3 = new Property("Alameda das Antas", "Luis", "300","t0",100000);

    Client* c1 = new Client("Joao", "joao@gmail.com");
    pPtr2->setReservation(make_tuple(c1,100000));
    c1->addVisiting(pPtr2->getAddress(), pPtr2->getPostalCode(),pPtr2->getTypology(), to_string(pPtr2->getPrice()));

    Client* c2 = new Client("Maria", "maria@gmail.com");
    pPtr3->setReservation(make_tuple(c2,90000));
    c2->addVisiting(pPtr3->getAddress(), pPtr3->getPostalCode(),pPtr3->getTypology(), to_string(pPtr3->getPrice()));

    REAgency agency;

    agency.addTypeItem(pPtr1);
    agency.addTypeItem(pPtr2);
    agency.addTypeItem(pPtr3);

    vector<Property*> av1 = agency.getAvailableProperties(pPtr1);
    EXPECT_EQ(1, av1.size());
    vector<Property*> av2 = agency.getAvailableProperties(pPtr2);
    EXPECT_EQ(1, av2.size());
    vector<Property*> av3 = agency.getAvailableProperties(pPtr3);
    EXPECT_EQ(0, av3.size());
}

TEST(test_1, test_c){
    vector<Property*> properties;
    Property* pPtr1 = new Property("Rua Dr Roberto Frias", "Joao", "100","t2", 200000);
    Property* pPtr2 = new Property("Rua Dr Roberto Frias", "Joao", "100","t2",220000);
    Property* pPtr3 = new Property("Alameda das Antas", "Luis", "300","t0",100000);
    Property* pPtr4 = new Property("Rua do Amial","Joao","220","t3",260000);

    Client* c1 = new Client("Joao", "joao@gmail.com");
    Client* c2 = new Client("Maria", "maria@gmail.com");

    REAgency agency;

    agency.addTypeItem(pPtr1);
    agency.addTypeItem(pPtr2);
    agency.addTypeItem(pPtr3);

    bool loan1 = agency.reservePropertyFromCatalog(pPtr4, c1,10);
    EXPECT_EQ(false, loan1);

    bool loan2 = agency.reservePropertyFromCatalog(pPtr3, c1,20);
    EXPECT_EQ(true, loan2);

    if(get<0>(pPtr3->getReservation())!=NULL)
        EXPECT_EQ("Joao", get<0>(pPtr3->getReservation())->getName());

    EXPECT_EQ(80000, get<1>(pPtr3->getReservation()));

    bool loan3 = agency.reservePropertyFromCatalog(pPtr3, c2,10);
    EXPECT_EQ(false, loan3);

    if(get<0>(pPtr3->getReservation())!=NULL)
        EXPECT_EQ("Joao", get<0>(pPtr3->getReservation())->getName());

    bool loan4 = agency.reservePropertyFromCatalog(pPtr1, c2,20);
    EXPECT_EQ(true, loan4);

    if(get<0>(pPtr1->getReservation())!=NULL)
        EXPECT_EQ("Maria", get<0>(pPtr1->getReservation())->getName());

    EXPECT_EQ(160000, get<1>(pPtr1->getReservation()));
}

TEST(test_1, test_d){
    Client c1("Tiago", "t.silva@gmail.com");
    Client c2("Tiago", "t.silva@gmail.com");
    Client c3("Pedro", "pedro@gmail.com");
    Client c4("ana", "ana@gmail.com");
    Client c5("Maria", "maria.castro@gmail.com");
    Client c6("Tiago", "tiago@gmail.com");

    REAgency r1;
    r1.addClientRecord(&c1);
    vector<ClientRecord> cr1 = r1.getClientRecords();
    EXPECT_EQ(1, cr1.size());

    if (cr1.size()>0)
        EXPECT_EQ("t.silva@gmail.com", cr1[0].getEMail());

    r1.addClientRecord(&c2);
    cr1 = r1.getClientRecords();
    EXPECT_EQ(1, cr1.size());

    r1.addClientRecord(&c3);
    r1.addClientRecord(&c4);
    r1.addClientRecord(&c5);
    cr1 = r1.getClientRecords();
    EXPECT_EQ(4, cr1.size());

    r1.addClientRecord(&c6);
    cr1 = r1.getClientRecords();
    EXPECT_EQ(5, cr1.size());
}


TEST(test_1, test_e){
    Client* c1 = new Client("Joao", "joao@gmail.com");
    Client* c2 = new Client("Tiago", "t.silva@gmail.com");

    c1->addVisiting("Rua Dr Roberto Frias", "100","t2", "200000");

    vector<ClientRecord> crs1;
    crs1.push_back(ClientRecord(c1));
    crs1.push_back(ClientRecord(c2));

    REAgency r1;
    r1.setClientRecords(crs1);

    r1.deleteClients();
    crs1 = r1.getClientRecords();
    EXPECT_EQ(1, crs1.size());
    if (crs1.size()>0)
        EXPECT_EQ("Tiago", crs1[0].getName());
}

TEST(test_1, test_f){
    Client* c1 = new Client("Joao", "joao@gmail.com");
    Client* c2 = new Client("Maria", "maria@gmail.com");
    Client* c3 = new Client("Pedro", "pedro@gmail.com");

    vector<Property*> properties;
    Property* pPtr1 = new Property("Rua Dr Roberto Frias", "Joao", "100","t2", 200000);
    Property* pPtr2 = new Property("Rua Dr Roberto Frias", "Joao", "100","t2",220000);
    Property* pPtr3 = new Property("Alameda das Antas", "Luis", "300","t0",100000);
    Property* pPtr4 = new Property("Rua Dr Roberto Frias", "Joao", "100","t2",150000);
    Property* pPtr5 = new Property("Rua Dr Roberto Frias", "Joao", "100","t2",220000);
    Property* pPtr6 = new Property("Rua do Amial", "Miguel", "200","t2",190000);
    Property* pPtr7 = new Property("Rua do Amial", "Pedro", "220","t3",240000);

    properties.push_back(pPtr1);
    properties.push_back(pPtr2);
    properties.push_back(pPtr3);
    properties.push_back(pPtr4);
    properties.push_back(pPtr5);
    properties.push_back(pPtr6);
    properties.push_back(pPtr7);

    c1->addVisiting("Rua Dr Roberto Frias", "100","t2", "200000");
    c1->addVisiting("Alameda das Antas", "300","t0","100000");
    c1->addVisiting("Alameda das Antas", "300","t0","100000");

    pPtr1->setReservation(make_tuple(c1,100000));
    pPtr2->setReservation(make_tuple(c1,150000));
    pPtr3->setReservation(make_tuple(c1,80000));

    c2->addVisiting("Rua Dr Roberto Frias", "100","t2", "200000");
    c2->addVisiting("Rua do Amial", "220","t3","250000");
    pPtr4->setReservation(make_tuple(c2,100000));

    c3->addVisiting("Alameda das Antas", "300","t0","100000");
    c3->addVisiting("Alameda das Antas", "300","t2","180000");
    pPtr5->setReservation(make_tuple(c3,100000));
    pPtr6->setReservation(make_tuple(c3,150000));
    pPtr7->setReservation(make_tuple(c3,80000));

    vector<Client> candidates_0;
    candidates_0.push_back(*c1);

    vector<Client> candidates_1;
    candidates_1.push_back(*c2);

    vector<Client> candidates_2;
    candidates_2.push_back(*c1);
    candidates_2.push_back(*c2);
    candidates_2.push_back(*c3);

    REAgency r1(properties);
    r1.addBestClientProfiles(candidates_0, 1);
    EXPECT_EQ(1, r1.getClientProfiles().size());

    if (r1.getClientProfiles().size()>0)
        EXPECT_EQ("Joao",r1.getClientProfiles().top().getName());

    REAgency r2(properties);
    r2.addBestClientProfiles(candidates_1, 1);
    EXPECT_EQ(0, r2.getClientProfiles().size());

    REAgency r3(properties);
    r3.addBestClientProfiles(candidates_2, 1);
    EXPECT_EQ(2, r3.getClientProfiles().size());

    if (r3.getClientProfiles().size()>0)
        EXPECT_EQ("Pedro",r3.getClientProfiles().top().getName());
}

TEST(test_1, test_g){
    Client c1("Joao", "joao@gmail.com");
    Client c2("Maria", "maria@gmail.com");
    Client* c1Ptr = new Client("Joao", "joao@gmail.com");

    vector<Property*> properties;
    Property* pPtr1 = new Property("Rua Dr Roberto Frias", "Joao", "100","t2", 200000);
    Property* pPtr2 = new Property("Rua Dr Roberto Frias", "Joao", "110","t2",220000);
    Property* pPtr3 = new Property("Alameda das Antas", "Miguel", "120","t2",220000);

    properties.push_back(pPtr1);
    properties.push_back(pPtr2);
    properties.push_back(pPtr3);

    c1.addVisiting("Rua Dr Roberto Frias", "100","t2", "200000");

    pPtr2->setReservation(make_tuple(c1Ptr,150000));

    priority_queue<Client> candidates;
    candidates.push(c1);

    REAgency r1(properties);
    r1.setClientProfiles(candidates);

    vector<Property*> assertProp1;
    assertProp1.push_back(pPtr3);
    vector<Property*> assertProp2 = r1.suggestProperties();
    EXPECT_EQ(1,assertProp2.size());

    if(assertProp2.size()>0)
        EXPECT_EQ(assertProp1[0]->getAddress(), assertProp2[0]->getAddress());
}


